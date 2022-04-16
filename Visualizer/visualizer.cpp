#include "visualizer.hpp"

Visualizer::Visualizer(int aov) : numberOfElements(aov),
algorithm(Algorithm::Shell),
barWidth(static_cast<float>(window_width) / numberOfElements),
tick(1),
last_tick(clock()),
since_last_tick(clock()),
is_window_inited(false) {}

Visualizer::~Visualizer() {}

void Visualizer::InitWindow() {
	if (!is_window_inited) {
		this->window.create(sf::VideoMode(window_width, window_height), "Visualizer");
		window.setActive(false);
	}
}

void Visualizer::Visualize(Algorithm alg) {
	this->algorithm = alg;
	this->values.clear();
	this->bars.clear();

	//Инициализация вектора элементов
	for (int i = 0; i < numberOfElements; i++) {
		values.push_back(rnd() % (window_height - 2) + 1);
	}

	//Инициализация вектора столбцов
	for (int i = 0; i < numberOfElements; i++) {
		sf::RectangleShape bar(sf::Vector2f(barWidth, values[i]));
		bar.setOutlineThickness(numberOfElements > 500 ? 0.f : 0.5f);
		bar.setSize(sf::Vector2f(barWidth - bar.getOutlineThickness() * 2, values[i]));
		bar.setOutlineColor(sf::Color::Black);
		bar.setPosition(barWidth * i + bar.getOutlineThickness(), window_height - values[i]);
		bars.push_back(bar);
	}

	InitWindow();
	window.setActive(false);

	sf::Thread displayingThread(&Visualizer::Render, this);
	displayingThread.launch();
	sf::Thread sortingThread(&Visualizer::Sort, this);
	sortingThread.launch();
	window.setActive(false);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				window.close();
				break;
			}
		}
	}
}

void Visualizer::Render() {
	window.setActive(true);
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		window.clear();
		for (int i = 0; i < numberOfElements; i++) {
			bars[i].setPosition(barWidth * i, window_height - values[i]);
			window.draw(bars[i]);
		}
		window.display();
	}
}

void Visualizer::Sort() {
	if (numberOfElements <= 50)
		tick = 8;
	else if (numberOfElements <= 100)
		tick = 5;
	else if (numberOfElements <= 300)
		tick = 3;
	else if (numberOfElements <= 500)
		tick = 2;
	else
		tick = 1;
	since_last_tick = clock();
	last_tick = clock();

	switch (this->algorithm) {
	case Algorithm::Bubble:
		BubbleSort();
		break;

	case Algorithm::Insertion:
		InsertionSort();
		break;

	case Algorithm::Gnome:
		GnomeSort();
		break;

	case Algorithm::Shell:
		ShellSort();
		break;

	case Algorithm::Shaker:
		ShakerSort();
		break;

	case Algorithm::Merge:
		MergeSort(0, numberOfElements - 1);
		break;

	case Algorithm::Selection:
		SelectionSort();
		break;
	case Algorithm::Quick:
		QuickSort(0, numberOfElements - 1);
		break;
	}

	SortEnding();
}

void Visualizer::BubbleSort() {
	for (int i = 0; i < numberOfElements - 1; i++) {
		for (int j = 0; j < numberOfElements - i - 1; j++) {
			WaitTick();

			bars[j].setFillColor(sf::Color::Red);
			if (values[j] > values[j + 1]) {
				std::swap(bars[j], bars[j + 1]);

				std::swap(values[j], values[j + 1]);
			}
			bars[j].setFillColor(sf::Color::White);
		}
		WaitTick();
		bars[numberOfElements - i - 1].setFillColor(sf::Color::White);
	}
}
void Visualizer::ShellSort() {
	int i, j, step;
	int tmp;
	sf::RectangleShape tmp_bar;
	for (step = numberOfElements / 2; step > 0; step /= 2)
		for (i = step; i < numberOfElements; i++)
		{
			tmp = values[i];
			tmp_bar = bars[i];
			for (j = i; j >= step; j -= step)
			{
				bars[j].setFillColor(sf::Color::Red);
				WaitTick();
				if (tmp < values[j - step]) {
					values[j] = values[j - step];
					bars[j] = bars[j - step];
					bars[j].setFillColor(sf::Color::White);
				}
				else
					break;
			}
			values[j] = tmp;
			bars[j] = tmp_bar;
		}
}
void Visualizer::InsertionSort() {
	int i, key, j;
	for (i = 1; i < numberOfElements; i++)
	{
		bars[i - 1].setFillColor(sf::Color::Green);
		for (int j = i; j > 0 && values[j - 1] > values[j]; j--) {
			bars[j].setFillColor(sf::Color::Red);
			WaitTick();
			std::swap(values[j - 1], values[j]);
			std::swap(bars[j - 1], bars[j]);
			bars[j - 1].setFillColor(sf::Color::White);
		}
		bars[i - 1].setFillColor(sf::Color::White);
	}
}
void Visualizer::GnomeSort() {
	int i = 1;
	while (i < numberOfElements) {
		bars[i].setFillColor(sf::Color::Red);
		if (i == 0 || values[i - 1] <= values[i]) {
			bars[i].setFillColor(sf::Color::White);
			i++;
		}
		else {
			WaitTick();
			std::swap(values[i], values[i - 1]);
			std::swap(bars[i], bars[i - 1]);
			bars[i].setFillColor(sf::Color::White);
			i--;
		}
	}
}
void Visualizer::ShakerSort() {
	int i, j, k, m = values.size();
	bool sorted = false;
	for (i = 0; i < m;) {
		if (sorted)
			break;
		sorted = true;
		//WaitTick();
		for (j = i + 1; j < m; j++) {
			bars[j].setFillColor(sf::Color::Red);
			WaitTick();
			if (values[j] < values[j - 1]) {
				sorted = false;
				std::swap(values[j], values[j - 1]);
				std::swap(bars[j], bars[j - 1]);
				bars[j - 1].setFillColor(sf::Color::White);
			}
			else
				bars[j].setFillColor(sf::Color::White);
		}
		m--;
		if (sorted)
			break;
		for (k = m - 1; k > i; k--) {
			bars[k].setFillColor(sf::Color::Red);
			WaitTick();
			if (values[k] < values[k - 1]) {
				sorted = false;
				std::swap(values[k], values[k - 1]);
				std::swap(bars[k], bars[k - 1]);
				bars[k - 1].setFillColor(sf::Color::White);
			}
			else
				bars[k].setFillColor(sf::Color::White);
		}
		i++;
	}
}
void Visualizer::MergeSort(int l, int r) {
	int m;
	if (l < r) {
		int m = l + (r - l) / 2;
		MergeSort(l, m);
		MergeSort(m + 1, r);
		merge(l, m, r);
	}
}
void Visualizer::SelectionSort() {
	int max = 0, max_index, not_sorted_count = values.size();
	for (int i = 0; i < values.size(); i++) {
		for (int j = 0; j < not_sorted_count; j++) {
			bars[j].setFillColor(sf::Color::Red);
			WaitTick();
			if (max < values[j]) {
				max = values[j];
				max_index = j;
			}
			bars[j].setFillColor(sf::Color::White);
		}
		std::swap(values[not_sorted_count - 1], values[max_index]);
		std::swap(bars[not_sorted_count - 1], bars[max_index]);
		max = 0;
		not_sorted_count--;
	}
}
void Visualizer::QuickSort(int low, int high) {
	tick = 2;
	int mid;
	int f = low, l = high;
	mid = values[(f + l) / 2]; //Вычисление опорного элемента
	WaitTick();
	do
	{
		while (values[f] < mid) f++;
		while (values[l] > mid) l--;
		bars[f].setFillColor(sf::Color::Red);
		WaitTick();
		if (f <= l) //Перестановка элементов
		{
			std::swap(values[f], values[l]);
			std::swap(bars[f], bars[l]);
			f++;
			l--;
			bars[l + 1].setFillColor(sf::Color::White);
		}
		else
			bars[f].setFillColor(sf::Color::White);
	} while (f < l);
	WaitTick();
	if (low < l)
		QuickSort(low, l);
	if (f < high)
		QuickSort(f, high);
}

void Visualizer::merge(int l, int m, int r) {
	int i, j, k, nl, nr;
	
	nl = m - l + 1; nr = r - m;		//Размер левого и правого подмассивов
	int* larr = new int[nl];
	int* rarr = new int[nr];

	sf::RectangleShape* lbar = new sf::RectangleShape[nl];
	sf::RectangleShape* rbar = new sf::RectangleShape[nr];

	//Заполнить левый и правый подмассивы
	for (i = 0; i < nl; i++) {
		bars[l + i].setFillColor(sf::Color::Red);
		WaitTick();
		larr[i] = values[l + i];
		lbar[i] = bars[l + i];
		bars[l + i].setFillColor(sf::Color::Red);
	}
	for (j = 0; j < nr; j++) {
		bars[m + 1 + j].setFillColor(sf::Color::Red);
		WaitTick();
		rarr[j] = values[m + 1 + j];
		rbar[j] = bars[m + 1 + j];
		bars[m + 1 + j].setFillColor(sf::Color::Red);
	}
	i = 0; j = 0; k = l;
	//Вставить подмассивы в массив
	while (i < nl && j < nr) {
		bars[k].setFillColor(sf::Color::Red);
		WaitTick();
		if (larr[i] <= rarr[j]) {
			values[k] = larr[i];
			bars[k] = lbar[i];
			i++;
		}
		else {
			values[k] = rarr[j];
			bars[k] = rbar[j];
			j++;
		}
		bars[k].setFillColor(sf::Color::White);
		k++;
	}
	while (i < nl) {
		bars[k].setFillColor(sf::Color::Red);
		WaitTick();
		values[k] = larr[i];
		bars[k] = lbar[i];
		bars[k].setFillColor(sf::Color::White);
		i++; k++;
	}
	while (j < nr) {
		bars[k].setFillColor(sf::Color::Red);
		WaitTick();
		values[k] = rarr[j];
		bars[k] = rbar[j];
		bars[k].setFillColor(sf::Color::White);
		j++; k++;
	}
}

void Visualizer::SortEnding() {
	for (int i = 0; i < numberOfElements; i++) {

		WaitTick();


		bars[i].setFillColor(sf::Color::Green);
	}
	for (int i = 0; i < numberOfElements; i++) {
		bars[i].setFillColor(sf::Color::White);
	}
}

void Visualizer::WaitTick() {
	while (since_last_tick < tick) {
		std::this_thread::sleep_for(std::chrono::nanoseconds(tick * 100));
		since_last_tick = clock() - last_tick;
	}
	last_tick = clock();
	since_last_tick = 0;
}

int Visualizer::rnd() {
	static const int init_generator = (srand((unsigned)time(nullptr)), 0);
	return rand();
}