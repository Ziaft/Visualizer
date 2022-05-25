#include "visualizer.hpp"
#include <map>
int main()
{
	int aov, choice;
	std::map<int, std::string> algs = {
		{0, "Shellsort"},
		{1, "Insertionsort"},
		{2, "Bubblesort"},
		{3, "Gnomesort"},
		{4, "Shakersort"},
		{5, "Mergesort"},
		{6, "Selection sort"},
		{7, "Quicksort"}
	};

	while (true) {
	setting_amount:
		std::cout << "Enter amount of elements: ";
		std::cin >> aov;

		if (aov == 0) {
			std::cout << "It must be joke, right?.." << std::endl;
			goto setting_amount;
		}
		else if (aov < 0)
			aov = -aov;
		if (aov > 10000)
			aov = 10000;
		Visualizer test_visualizer(aov);

	selection:
		std::cout << "Choose sorting algorithm: " << std::endl;
		for (int i = 0; i < algs.size(); i++)
			std::cout << i << ") " << algs[i] << std::endl;
		std::cin >> choice;
		Algorithm selected_alg;
		switch (choice) {
		case 0:
			selected_alg = Algorithm::Shell;
			break;
		case 1:
			selected_alg = Algorithm::Insertion;
			break;
		case 2:
			selected_alg = Algorithm::Bubble;
			break;
		case 3:
			selected_alg = Algorithm::Gnome;
			break;
		case 4:
			selected_alg = Algorithm::Shaker;
			break;
		case 5:
			selected_alg = Algorithm::Merge;
			break;
		case 6:
			selected_alg = Algorithm::Selection;
			break;
		case 7:
			selected_alg = Algorithm::Quick;
			break;
		default:
			std::cout << "Invalid input" << std::endl;
			goto selection;
			break;
		}
		test_visualizer.Visualize(selected_alg);
	}
	return 0;
}