// 4.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Напишите функцию, решающую задачу о максимальном
паросочетании (варианты графов в виде списка рёбер указаны в
таблице 4.1).

Таблица 4.1. Список рёбер для пункта 4.2 (номер строки соответствует
индексу вершины в левой доле, содержимое строки – индексы вершины
в правой доле, с которыми соответствующая вершина левой доли
связана ребром)

Вариант 18.
Список рёбер

{
	{ 3, 4, 5 },
	{ 7 },
	{ 5 },
	{ 5, 6, 7 }
};

*/

//Решение задачи реализовано с помощью алгоритма Куна.

#include <iostream>
#include <vector>

using namespace std;

int find_max_in_matrix(vector<vector<int>>& find)
{
	int max = find[0][0];
	for (int i = 0; i < find.size(); i++)
	{
		for (int j = 0; j < find[i].size(); j++)
		{
			if (find[i][j] > max)
			{
				max = find[i][j];
			}
		}
	}
	return max;
}

bool try_kuhn(int v, vector<vector<int>>& g, vector<int>& used, vector<int>& mt)//v-откуда хотим сделать шаг. g-список рёбер (передаем по ссылке, чтобы сэкономить), used-те вершины, которые в решении используются, mt-список пар (из правой доли графа в левую долю графа) (решение). (used и mt в процессе вызова функции будут меняться - поэтому их НУЖНО передать по ссылке).
{
	if (used[v])//Если вершина V обработана или(и) участвует в паросочетании, то заканчиваем.
	{
		return false;
	}
	used[v] = true;//Иначе, говорим, что мы осмотрели эту вершину.

	for (int i = 0; i < g[v].size(); ++i)//Просматриваем список рёбер и смотрим, куда из вершины V можно сделать шаг. Если найдём какой-то результат, то вернём из цикла "true" (смогли добавить новую пару). Если не найдем, то вернём "false" (при текущих парах, которые уже есть, новых пар не образуется).
	{
		int to = g[v][i];//Куда можно построить ребро?.
		if (mt[to] == -1 || try_kuhn(mt[to], g, used, mt))//Если его можно использовать (в решении пункт to (вершина в правой доле) не содержится).
		{//Добавляем to в решение.
			mt[to] = v;
			return true;
		}
	}
	return false;
}

vector<int> kuhn(vector<vector<int>>& matrix)//matrix - матрица, хранящая список рёбер.
{
	vector<int> mt;//Массив показывает само решение. (Из правой доли в левую долю графа).
	vector<int> used;//Показывает какие вершины участвуют в нашем решении.
	vector<int> answer;//Сохраняет решение слева на право.
	int max = find_max_in_matrix(matrix);

	mt.assign(max + 1, -1);//max+1 потому что вершины начинаются с 0 (max+1 - количество вершин в правой доле графа).
	answer.assign(matrix.size(), -1);

	for (int v = 0; v < matrix.size(); ++v)
	{
		used.assign(matrix.size(), false);//Обнуление массива used.		
		if (try_kuhn(v, matrix, used, mt))
		{
			for (int i = 0; i < max + 1; ++i)
			{
				if (mt[i] != -1)
				{
					answer[mt[i]] = i;
				}
			}
		}
	}

	return answer;
}

void print_answer_kuhn(vector<int>& matching)//matching - паросочетание.
{
	//Из левой доли графа в правую долю.
	cout << "-----------------------------------------Maximum matching------------------------------------------" << endl;
	for (int i = 0; i < matching.size(); i++)
	{
		cout << i << " -> " << matching[i] << endl;
	}
	cout << "---------------------------------------------------------------------------------------------------" << endl;
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



int main()
{
	cout << "\n---Kuhn algorithm---\n";
	vector<vector<int>> test =
	{
		{ 0, 1, 4},//Список ребер.
		{ 0 },
		{ 1, 2, 4 },
		{ 1, 3 }
	};
	print_matrix(test);

	vector<int> maximum_matching;
	maximum_matching = kuhn(test);
	print_answer_kuhn(maximum_matching);

	cout << endl << endl << endl << "***************************************************************************************************" << endl << endl << endl << endl;

	vector<vector<int>> task =
	{
		{ 3, 4, 5 },
		{ 7 },
		{ 5 },
		{ 5, 6, 7 }
	};

	print_matrix(task);

	vector<int> maximum_matching_task;
	maximum_matching_task = kuhn(task);
	print_answer_kuhn(maximum_matching_task);

	return 0;
}