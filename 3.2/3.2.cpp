// 3.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Дана матрица смежности неориентированного взвешенного графа
(таблица 3.1, 0 означает отсутствие ребра).

Запустите функцию, реализующую алгоритм поиска в глубину, для
перечисления всех вершин в минимальном остовном дереве. Результат
должен быть представлен с помощью одного из контейнеров STL.

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


#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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

void print_vector(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
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
	if (start < 0 || start >= mat.size())
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

//BFS - Breadth-First Search (поиск в ширину или обход в ширину) - На i-той итерации, мы обрабатываем те вершины, которые находятся на расстоянии i рёбер от исходной. 
//(В данной реализации возвращает минимальное количество ребер от стартовой вершины, до всех остальных (не смотрим на вес, только на количество)).
vector<int> BFS(vector<vector<int>>& mat, int start)
{
	if (start < 0 || start >= mat.size())
	{
		cout << "Неверно указана вершина старта. Вершина старта устанавливается в ноль." << endl;
		start = 0;
	}
	vector<int> used(mat.size(), 0);//Вектор, хранящий информацию о взятых вершинах

	vector<int> dist(mat.size(), -1);//Хранит количество шагов, сколько мы сделали от стартовой вершины до всех остальных
	dist[start] = 0;//Расстояние из стартовой вершины до старта = 0

	queue<int> graph_node;//Список активных вершин
	graph_node.push(start);

	while (!graph_node.empty())
	{
		int vertex = graph_node.front();
		graph_node.pop();

		for (int i = 0; i < mat.size(); i++)
		{
			if (mat[vertex][i] != 0 && used[i] == 0) //Первое условие - между узлами есть связь; второе - узел, в который мы придем еще не рассматривался
			{
				graph_node.push(i);

				if (dist[i] == -1)
				{
					dist[i] = dist[vertex] + 1;
				}
			}
		}
		used[vertex] = 1;//Закончили обработку вершины
	}

	return dist;
}

//DFS - Depth-First Search (поиск в глубину или обход в глубину) - один из основных методов обхода графа, часто используемый для проверки связности, поиска цикла и компонент сильной связности и для топологической сортировки.
//(В данной реализации возвращает порядковые номера вершин, через сколько итераций мы попадем в них, начиная со стартовой вершины)
vector<int> DFS(vector<vector<int>>& mat, int start) //Обход в глубину, для случая, когда мы передаем матрицу смежности.
{
	if (start < 0 || start >= mat.size())
	{
		cout << "Неверно указана вершина старта. Вершина старта устанавливается в ноль." << endl;
		start = 0;
	}
	vector<int> used(mat.size(), 0);//Вектор, хранящий информацию о взятых вершинах

	vector<int> dist(mat.size(), -1);//Хранит количество шагов, сколько мы сделали от стартовой вершины до всех остальных
	dist[start] = 0;//Расстояние из стартовой вершины до старта = 0

	stack<int> graph_node;//Список активных вершин
	graph_node.push(start);

	int step = 0;

	while (!graph_node.empty())
	{
		int vertex = graph_node.top();
		graph_node.pop();

		for (int i = mat.size() - 1; i >= 0; i--) //Т.к. мы работаем в стэке - запускаем цикл в обратную сторону, чтобы вершины обходились в порядке возрастания (0..1..2..).
		{
			if (mat[vertex][i] != 0 && used[i] == 0) //Первое условие - между узлами есть связь; второе - узел, в который мы придем еще не рассматривался
			{
				graph_node.push(i);
			}
		}

		if (dist[vertex] < 0)
		{
			dist[vertex] = step;
		}
		used[vertex] = 1;//Закончили обработку вершины
		step++;
	}

	return dist;
}

vector<int> DFS(vector<Edge>& min_ostov, int start) //Обход в глубину, для случая, когда мы передаем минимальный остов. (В данной реализации возвращает порядковые номера вершин, через сколько итераций мы попадем в них, начиная со стартовой вершины)
{
	if (start < 0 || start > min_ostov.size())
	{
		cout << "Неверно указана вершина старта. Вершина старта устанавливается в ноль." << endl;
		start = 0;
	}

	vector<int> used(min_ostov.size() + 1, 0);//Вектор, хранящий информацию о взятых вершинах

	vector<int> dist(min_ostov.size() + 1, -1);//Хранит количество шагов, сколько мы сделали от стартовой вершины до всех остальных
	dist[start] = 0;//Расстояние из стартовой вершины до старта = 0

	stack<int> graph_node;//Список активных вершин
	graph_node.push(start);

	int step = 0;

	while (!graph_node.empty())
	{
		int vertex = graph_node.top();
		graph_node.pop();

		for (int i = min_ostov.size() - 1; i >= 0; i--)
		{
			if (min_ostov[i].get_from() == vertex && used[min_ostov[i].get_to()] == 0)
			{
				graph_node.push(min_ostov[i].get_to());
			}
		}

		if (dist[vertex] < 0)
		{
			dist[vertex] = step;
		}
		used[vertex] = 1;//Закончили обработку вершины
		step++;
	}

	return dist;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int start = 0;

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
	vector<Edge> ostov = min_ostov(mat, start);
	print_min_ostov(ostov);

	cout << endl;
	vector<int> graph_traversal;

	graph_traversal = BFS(mat, start);
	cout << "BFS - обход в ширину (вернёт минимальное кол-во рёбер от стартовой вершины (" << start << ") до всех остальных): ";
	print_vector(graph_traversal);

	graph_traversal = DFS(mat, start);
	cout << "DFS - обход в глубину -передаём матрицу смежности-(возвращает порядковые номера вершин, через сколько итераций мы попадем в них, начиная со стартовой вершины (" << start << ")): ";
	print_vector(graph_traversal);

	graph_traversal = DFS(ostov, start);
	cout << "DFS - обход в глубину -передаём минимальный остов-(возвращает порядковые номера вершин, через сколько итераций мы попадем в них, начиная со стартовой вершины (" << start << ")): ";
	print_vector(graph_traversal);

	cout << endl << endl << endl;

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
	vector<Edge> ostov_1 = min_ostov(mat_1, start);
	print_min_ostov(ostov_1);

	cout << endl;
	vector<int> graph_traversal_1;

	graph_traversal_1 = BFS(mat_1, start);
	cout << "BFS - обход в ширину (вернёт минимальное кол-во рёбер от стартовой вершины (" << start << ") до всех остальных): ";
	print_vector(graph_traversal_1);

	graph_traversal_1 = DFS(mat_1, start);
	cout << "DFS - обход в глубину -передаём матрицу смежности-(возвращает порядковые номера вершин, через сколько итераций мы попадем в них, начиная со стартовой вершины (" << start << ")): ";
	print_vector(graph_traversal_1);

	graph_traversal_1 = DFS(ostov_1, start);
	cout << "DFS - обход в глубину -передаём минимальный остов-(возвращает порядковые номера вершин, через сколько итераций мы попадем в них, начиная со стартовой вершины (" << start << ")): ";
	print_vector(graph_traversal_1);

	return 0;
}