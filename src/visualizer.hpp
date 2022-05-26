#pragma once
#include<SFML/Graphics.hpp>
#include<thread>
#include<chrono>
#include<mutex>
#include<vector>
#include<iostream>

enum Algorithm {
	Bubble,
	Shell,
	Gnome,
	Insertion,
	Shaker,
	Merge,
	Selection,
	Quick
};

const int window_width = 1200;
const int window_height = 800;

class Visualizer {
public:
	Visualizer(int aon);
	~Visualizer();

	void Visualize(Algorithm alg);

private:
	void InitWindow();
	void Render();
	void Sort();

	void SortEnding();
	void WaitTick();
	int rnd();
	void merge(int low, int high, int mid);

	void BubbleSort();
	void ShellSort();
	void GnomeSort();
	void InsertionSort();
	void ShakerSort();
	void MergeSort(int left, int right);
	void SelectionSort();
	void QuickSort(int low, int high);

	unsigned short since_last_tick;
	unsigned short last_tick;
	unsigned short tick;

	bool is_window_inited;
	Algorithm algorithm;
	int numberOfElements;					//Количество элементов
	float barWidth;
	std::vector<int> values;				//Вектор, хранящий значения
	sf::RenderWindow window;
	std::vector<sf::RectangleShape> bars;	//Вектор, хранящий столбцы
};