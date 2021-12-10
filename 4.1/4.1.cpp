// 4.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Используя граф из задачи 3.1, найдите максимальный поток между
вершиной 0 и вершиной с максимальным индексом. Вес рёбер считать
пропускной способностью.

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

//Алгоритм Форда-Фалкерсона - алгоритм для поиска максимального потока.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INFINITY 10000 //Условное число, обозначающее бесконечность.

//FillVectorWith - заполняет вектор размера size, элементам value (по умолчанию заполняет нулями).
void FillVectorWith(vector<int>& v, int size = 0, int value = 0)
{
	if (size != 0)
	{
		v.resize(0);
		for (int i = 0; i < size; i++)
			v.push_back(value);
	}
	for (int i = 0; i < v.size(); i++)
		v[i] = value;
}

//FillVectorWith - заполняет матрицу размера width X height, элементам value (по умолчанию заполняет нулями).
void FillMatrixWith(vector<vector<int> >& matrix, int width = 0, int height = 0, int value = 0)
{
	if (width != 0 && height != 0)
	{
		matrix.resize(0);
		int i, j;
		for (i = 0; i < height; i++)
		{
			vector<int> v1;
			for (j = 0; j < width; j++)
			{
				v1.push_back(value);
			}
			matrix.push_back(v1);
		}
	}
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
			matrix[i][j] = value;
	}
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



//Поиск максимального потока - задача определения кокое кол-во груза можем запустить на нашем графе. 
int FindPath(vector<vector<int> >& f, vector<vector<int> >& c, int source, int target, int vertices) //f - сколько запущенно грузов, c- пропускные способности, source - исток, target - сток, vertices- кол-во вершин в нашем графе.
{
	int i;
	int CurVertex;

	vector<int> Flow; FillVectorWith(Flow, vertices, 0); //Flow - значение потока через данную вершину на данном шаге поиска
	vector<int> Link; FillVectorWith(Link, vertices, -1); //Link[i] - хранит номер предыдущей вершины на пути i -> исток (позволяет восстановить маршрут (в i-то месте этого вектора хранится номер вершины из которой мы пришли в i-тую вершину)).
	Flow[source] = INFINITY;//Изначально считается, что поток в исходной вершине бесконечен, поток во всех остальных вершинах нулевой. 

	//Поиск пути - реализован через поиск в ширину.
	queue<int> q;
	q.push(source);//Начинает из вершины source (исток).	

	while (!q.empty())
	{
		CurVertex = q.front();
		q.pop();

		for (int i = 0; i < vertices; i++)
		{
			if (c[CurVertex][i] - f[CurVertex][i] > 0 && Flow[i] == 0)
			{
				q.push(i);
				Link[i] = CurVertex;
				if (c[CurVertex][i] - f[CurVertex][i] < Flow[CurVertex])
				{
					Flow[i] = c[CurVertex][i] - f[CurVertex][i];
				}
				else
				{
					Flow[i] = Flow[CurVertex];
				}
			}
		}
	}

	if (Link[target] == -1) //Если не удалось добраться до финального пункта, то возвращаем 0, иначе возвращаем тот поток, который оказался в конечном пункте. 
	{
		return 0;
	}

	CurVertex = target;
	while (CurVertex != source)
	{
		f[Link[CurVertex]][CurVertex] = f[Link[CurVertex]][CurVertex] + Flow[target];
		CurVertex = Link[CurVertex];
	}

	////Служебная информация.
	//cout << "\nFlow: " << Flow[target] << "Link: ";
	//for (int i = 0; i < vertices; i++)
	//{
	//	cout << Link[i] << " ";
	//}

	return Flow[target];
}

//Основная функция поиска максимального потока.
int MaxFlow(vector<vector<int> >& f, vector<vector<int> >& c, int source, int target, int vertices) //f - сколько запущенно грузов, c- пропускные способности, source - исток, target - сток, vertices- кол-во вершин в нашем графе.
{
	FillMatrixWith(f, 0, 0, 0); //Заполнение нашей матрицы потока нулями (вначале поток равен 0).
	int MaxFlow = 0;
	int AddFlow;

	do
	{
		AddFlow = FindPath(f, c, source, target, vertices); //FindPath - находит новый путь и возвращает сколько можно запустить грузов.
		MaxFlow = MaxFlow + AddFlow; //Запоминаем кол-во грузов
	} while (AddFlow > 0); //Если не удалось найти новый путь - значит закончили наш алгоритм (нулевой поток - нет новых путей).

	return MaxFlow;
}

int main()
{
	int source = 0; //откуда?
	int target = 5; //куда?
	int vertices = 6; // число вершин в графе

	vector<vector<int> > c =
	{
	{	0, 16, 0, 0, 13, 0 },
	{	0, 0, 12, 0, 6, 0 },
	{	0, 0, 0, 0, 9, 20 },
	{	0, 0, 7, 0, 0, 4 },
	{	0, 0, 0, 14, 0, 0 },
	{	0, 0, 0, 0, 0, 0 },
	};
	print_matrix(c);
	vector<vector<int> > f;
	// f[i][j] - поток, текущий от вершины i к j
	// c[i][j] - максимальная величина потока, способная течь по ребру (i,j)
	FillMatrixWith(f, vertices, vertices, 0);//Заполнение матрицы f - нулями.

	// набор вспомогательных переменных, используемых функцией FindPath - обхода в ширину

	// поиск пути, по которому возможно пустить поток алгоритмом обхода графа в ширину
	// функция ищет путь из истока в сток, по которому еще можно пустить поток,
	// считая вместимость ребера (i,j) равной c[i][j] - f[i][j]
	cout << "\nResult: " << MaxFlow(f, c, source, target, vertices);

	cout << endl << endl << endl << endl;

	vector<vector<int> > matrix =
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
	print_matrix(matrix);
	vector<vector<int> > f_matrix;
	FillMatrixWith(f_matrix, matrix.size(), matrix.size(), 0);
	cout << "\nResult: " << MaxFlow(f_matrix, matrix, source, target, matrix.size());

	return 0;
}