// 3.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Дана матрица смежности неориентированного взвешенного графа
(таблица 3.1, 0 означает отсутствие ребра).

Необходимо построить минимальное остовное дерево.

Таблица 3.1
Вариант 18.

Матрица смежности
{
	{ 0, 0, 0, 7, 6, 0, 1, 4, 4, 5, 6, 6, 7 },
	{ 0, 0, 6, 4, 4, 1, 2, 3, 2, 0, 1, 4, 2 },
	{ 0, 6, 0, 8, 8, 4, 3, 6, 5, 3, 6, 6, 5 },
	{ 7, 4, 8, 0, 5, 4, 5, 8, 0, 9, 3, 6, 8 },
	{ 6, 4, 8, 5, 0, 1, 4, 2, 7, 7, 7, 2, 0 },
	{ 0, 1, 4, 4, 1, 0, 7, 4, 4, 2, 4, 2, 6 },
	{ 1, 2, 3, 5, 4, 7, 0, 7, 1, 2, 2, 9, 8 },
	{ 4, 3, 6, 8, 2, 4, 7, 0, 8, 4, 2, 3, 2 },
	{ 4, 2, 5, 0, 7, 4, 1, 8, 0, 2, 5, 8, 1 },
	{ 5, 0, 3, 9, 7, 2, 2, 4, 2, 0, 5, 9, 7 },
	{ 6, 1, 6, 3, 7, 4, 2, 2, 5, 5, 0, 9, 6 },
	{ 6, 4, 6, 6, 2, 2, 9, 3, 8, 9, 9, 0, 5 },
	{ 7, 2, 5, 8, 0, 6, 8, 2, 1, 7, 6, 5, 0 }
};
*/

//Для нахождения минимального остовного дерева графа существуют два основных алгоритма: алгоритм Прима (с точки зрения вершин) и алгоритм Краскала (с точки зрения рёбер). Они оба имеют сложность O(MlogN)

//Хотя оба алгоритма работают за O(MlogN), существуют константные различия в скорости их работы. На разреженных графах (количество рёбер примерно равно количеству
//вершин) быстрее работает алгоритм Краскала, а на насыщенных (количество рёбер примерно равно квадрату количеству вершин) - алгоритм Прима (при использовании
//матрицы смежности).

//На практике чаще используется алгоритм Краскала.

//В программе реализован алгоритм Прима.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge
{
private:
	int from, to, weight;
public:
	Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
	Edge(const Edge& E)
	{
		from = E.from;
		to = E.to;
		weight = E.weight;
	}

	//Геттеры
	int get_from()
	{
		return from;
	}
	int get_to()
	{
		return to;
	}
	int get_weight()
	{
		return weight;
	}
	//Сеттеры
	void set_from(int a)
	{
		from = a;
	}
	void set_to(int a)
	{
		to = a;
	}
	void set_weight(int a)
	{
		weight = a;
	}

	bool operator<(const Edge& E)
	{
		if (weight < E.weight)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator>(const Edge& E)
	{
		if (weight > E.weight)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend ostream& operator<<(ostream& s, Edge& e);
};

ostream& operator<<(ostream& s, Edge& e)
{
	s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
	return s;
}

void print_matrix(vector<vector<int>>& mat)
{
	cout << "--------------------------------------------Data Matrix--------------------------------------------" << endl;
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------------------------------" << endl;
}

void print_min_ostov(vector<Edge>& min_ostov_tree)
{
	int weight_ostov = 0;
	cout << "Вывод минимального остовного дерева:" << endl;
	cout << "from -> to = weight" << endl;

	for (int i = 0; i < min_ostov_tree.size(); i++)
	{
		weight_ostov = weight_ostov + min_ostov_tree[i].get_weight();
		cout << min_ostov_tree[i] << endl;
	}

	cout << "Вес этого дерева = " << weight_ostov << endl;
}

vector<Edge> min_ostov(vector<vector<int>>& mat, int start) //start - это вершина, поэтому от 0 до максимальной вершины
{
	if (start < 0 && start >mat.size())
	{
		cout << "Неверно указана вершина старта. Вершина старта устанавливается в ноль." << endl;
		start = 0;
	}

	vector<Edge> ostov_tree;//Минимальное остовное дерево
	vector<Edge> list_vert;//Список смежности
	vector<int> vertexes(mat.size(), 0);//Вектор, хранящий информацию о взятых вершинах

	vertexes[start] = 1;

	for (int i = 0; i < mat.size(); i++)//Записывает все вершины матрицы смежности в виде списка смежности. (Даже если 0 1 есть в списке, 1 0 все равно добавляем)
	{
		for (int j = 0; j < mat.size(); j++)
		{
			if (mat[i][j] != 0)
			{
				Edge for_push(i, j, mat[i][j]);
				list_vert.push_back(for_push);
			}
		}
	}

	//Сортировка списка смежности
	sort(list_vert.begin(), list_vert.end(),
		[](Edge& a, Edge& b) //Лямбда - для сортировки по убыванию
		{
			return a.get_weight() > b.get_weight();
		});

	while (!list_vert.empty())//Цикл работает до тех пор, пока в списке смежности еще есть элементы
	{
		for (int i = list_vert.size() - 1; i >= 0; i--)
		{
			if (vertexes[list_vert[i].get_from()] == 1)
			{
				if (vertexes[list_vert[i].get_to()] == 1)
				{
					list_vert.erase(list_vert.begin() + i);
				}
				else
				{
					vertexes[list_vert[i].get_to()] = 1;

					ostov_tree.push_back(list_vert[i]);

					list_vert.erase(list_vert.begin() + i);

					break;
				}
			}
		}
	}

	return ostov_tree;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	vector<vector<int>> mat =
	{
		{0, 1, 2, 3, 4, 5, 0},
		{1, 0, 0, 0, 0, 2, 0},
		{2, 0, 0, 0, 0, 0, 0},
		{3, 0, 0, 0, 3, 0, 0},
		{4, 0, 0, 3, 0, 0, 0},
		{5, 2, 0, 0, 0, 0, 5},
		{0, 0, 0, 0, 0, 5, 0}
	};
	print_matrix(mat);

	cout << endl;
	vector<Edge> ostov = min_ostov(mat, 6);
	print_min_ostov(ostov);

	cout << endl;

	vector<vector<int>> mat_1 =
	{
		{ 0, 0, 0, 7, 6, 0, 1, 4, 4, 5, 6, 6, 7 },
		{ 0, 0, 6, 4, 4, 1, 2, 3, 2, 0, 1, 4, 2 },
		{ 0, 6, 0, 8, 8, 4, 3, 6, 5, 3, 6, 6, 5 },
		{ 7, 4, 8, 0, 5, 4, 5, 8, 0, 9, 3, 6, 8 },
		{ 6, 4, 8, 5, 0, 1, 4, 2, 7, 7, 7, 2, 0 },
		{ 0, 1, 4, 4, 1, 0, 7, 4, 4, 2, 4, 2, 6 },
		{ 1, 2, 3, 5, 4, 7, 0, 7, 1, 2, 2, 9, 8 },
		{ 4, 3, 6, 8, 2, 4, 7, 0, 8, 4, 2, 3, 2 },
		{ 4, 2, 5, 0, 7, 4, 1, 8, 0, 2, 5, 8, 1 },
		{ 5, 0, 3, 9, 7, 2, 2, 4, 2, 0, 5, 9, 7 },
		{ 6, 1, 6, 3, 7, 4, 2, 2, 5, 5, 0, 9, 6 },
		{ 6, 4, 6, 6, 2, 2, 9, 3, 8, 9, 9, 0, 5 },
		{ 7, 2, 5, 8, 0, 6, 8, 2, 1, 7, 6, 5, 0 }
	};
	print_matrix(mat_1);

	cout << endl;
	vector<Edge> ostov_1 = min_ostov(mat_1, 0);
	print_min_ostov(ostov_1);

	return 0;
}



/*Есть ещё и другие способы задания матриц.*/

////Способ задания матрицы
//vector<vector<int>> imatrix;
//const size_t row = 5;
//const size_t col = 3;
//// Заполнение
//for (size_t i = 0; i < row; ++i)
//{
//	vector<int> temp;
//	for (size_t j = 0; j < col; ++j)
//	{
//		temp.push_back(rand() % 100);
//	}
//	imatrix.push_back(temp);
//}
//// Печать
//print_matrix(imatrix);

////Способ задания матрицы
//const size_t v_count = 5;
//vector<vector<int> > matrix(v_count, vector<int>(v_count, 0)); // квадратная матрица, инициализируем элементы первого вектора векторами с 0 элементами
//
////Изменяем значения в этой квадратной матрице.
//for (size_t i = 0; i < v_count; ++i)
//{
//	for (size_t j = 0; j < v_count; ++j)
//		matrix[i][j] = rand() % 2;
//}
//// Печать
//print_matrix(matrix);