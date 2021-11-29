// 3.3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Дана матрица смежности неориентированного взвешенного графа
(таблица 3.1, 0 означает отсутствие ребра).

Напишите функцию для поиска минимального пути (в смысле
суммарного веса пройденных рёбер) между i-м и всеми остальными
пунктами, куда можно построить маршрут. Результат должен быть
представлен с помощью одного из контейнеров STL.

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
#include <string>
#include <vector>

using namespace std;

class Bellman_Ford
{
private:
	//Matrix - хранит информацию о взвешенном графе.
	vector<vector<int>> Matrix;
	//Result - хранит кратчайшие пути от одной вершины до всех остальных. 
	vector<vector<int>> Result;
	//Negative cycle - хранит информацию о наличии отрицательного цикла в графе. (true - есть отрицательный цикл; false - нет отрицательного цикла).
	bool Negative_cycle = false;
	//Application_of_the_algorithm - хранит информацию о применении алгоритма Беллмана-Форда. (true - алгоритм применялся; false - алгоритм не применялся).  
	bool Application_of_the_algorithm = false;

	/*
	Application_of_the_algorithm = false - когда алгоритм не применялся, или значения в матрице были измененны, например set_row или set_column.
	Значение false говорит о том, что матрица кратчайших путей не соответствует матрице взвешенного графа.
	*/

protected:
	int find_min(vector<int> result_of_addition)
	{
		int min = result_of_addition[0];
		for (int i = 1; i < result_of_addition.size(); i++)
		{
			if (min > result_of_addition[i])
			{
				min = result_of_addition[i];
			}
		}
		return min;
	}

public:
	//Конструктор 1 - Задание матрицы в программе (ввод одного числа, создатся матрица NxN и начнется заполнение случайными числами).
	Bellman_Ford(int size_matrix)
	{
		for (int i = 0; i < size_matrix; i++)
		{
			vector<int> temp;//Временный вектор, который необходим для заполнения матрицы смежности.
			for (int j = 0; j < size_matrix; j++)
			{
				temp.push_back(rand() % 100 - 5);
			}
			Matrix.push_back(temp);
		}
	}

	//Конструктор 2 - Матрица будет скопирована из основной программы. (Передаваемая матрица должна быть квадратной).
	Bellman_Ford(vector<vector<int>> mat)
	{
		Matrix = mat;
	}

	//Деструктор.
	~Bellman_Ford() {};

	//Геттеры.
	vector<vector<int>> get_Matrix()//Получить Matrix (хранит информацию о взвешенном графе).
	{
		return Matrix;
	}
	vector<vector<int>> get_Result()//Получить Result (хранит кратчайшие пути от одной вершины до всех остальных).
	{
		if (Application_of_the_algorithm == true)
		{
			if (Negative_cycle == true)
			{
				cout << "Граф содержит отрицательный цикл." << endl;
				cout << "Матрица, хранящая информацию о кратчайших путях - будет хранить нули." << endl;
			}
		}
		else
		{
			cout << endl << endl << endl << "***************************************************************************************************" << endl;
			cout << "Алгоритм Беллмана-Форда не применялся или матрица, хранящая информацию о графе, была изменена." << endl;
			cout << "Сейчас будет применён алгоритм и выдан результат." << endl;
			cout << "***************************************************************************************************" << endl << endl << endl;
			Algoritm_Bellman_Ford();
		}
		return Result;
	}
	vector<int> get_Matrix_row(int number_row)//Получить строку матрицы, хранящий взвешенный граф.
	{
		vector<int> row;
		if (number_row > 0 && number_row <= Matrix.size())
		{
			row = Matrix[number_row - 1];
		}
		else
		{
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Строки c номером " << number_row << " нету в матрице. Будет возвращенна 1-ая строка.";
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			row = Matrix[0];
		}
		return row;
	}
	vector<int> get_Matrix_column(int number_column)//Получить столбец матрицы, хранящий взвешенный граф.
	{
		vector<int> column;
		if (number_column > 0 && number_column <= Matrix.size())
		{
			for (int i = 0; i < Matrix.size(); i++)
			{
				column.push_back(Matrix[i][number_column - 1]);
			}
		}
		else
		{
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Столбца c номером " << number_column << " нету в матрице. Будет возвращен 1-ый столбец.";
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			for (int i = 0; i < Matrix.size(); i++)
			{
				column.push_back(Matrix[i][0]);
			}
		}
		return column;
	}
	bool get_Negative_cycle()//Получить информацию о наличии отрицательного цикла.
	{
		if (Application_of_the_algorithm != true)
		{
			cout << endl << endl << endl << "***************************************************************************************************" << endl;
			cout << "Алгоритм Беллмана-Форда не применялся или матрица, хранящая информацию о графе, была изменена." << endl;
			cout << "Сейчас будет применён алгоритм и выдан результат." << endl;
			cout << "***************************************************************************************************" << endl << endl << endl;
			Algoritm_Bellman_Ford();
			return Negative_cycle;
		}
		return Negative_cycle;
	}
	bool get_Application_of_the_algorithm()//Получить информацию о применении алгоритма Беллмана-Форда
	{
		return Application_of_the_algorithm;
	}
	//Сеттеры. (Если изменить значения в матрице, хранящий взвешенный граф, то алгоритм Беллмана-Форда нужно будет применить ещё раз для новых данных).
	void set_Matrix_row(int number_row, vector<int> row)//Параметр 1 - номер строки. Параметр 2 - строка, которая заменит старую строку.
	{
		if (row.size() > Matrix.size())
		{
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "В передаваемой строке есть проблема. Она больше, чем строки в матрице. Из передаваемой строки, будут взяты только первые N элементов (N-размерность матрицы).";
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			for (int i = row.size(); i > Matrix.size(); i--)
			{
				row.pop_back();
			}
		}
		else
		{
			if (row.size() < Matrix.size())
			{
				cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
				cout << "В передаваемой строке есть проблема. Она меньше, чем строки в матрице. Передаваемая строка будет дополнена нулями.";
				cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
				for (int i = row.size(); i < Matrix.size(); i++)
				{
					row.push_back(0);
				}
			}
		}
		if (number_row > 0 && number_row <= Matrix.size())
		{
			Matrix[number_row - 1] = row;
		}
		else
		{
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "В матрице нет строки c номером " << number_row << ". Будет заменена 1-ая строка.";
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			Matrix[0] = row;
		}
		Application_of_the_algorithm = false;
	}
	void set_Matrix_column(int number_column, vector<int> column)//Параметр 1 - номер столбца. Параметр 2 - столбец, который заменит старый столбец.
	{
		if (column.size() > Matrix.size())
		{
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "В передаваемом столбце есть проблема. Он больше, чем столбцы в матрице. Из передаваемого столбца, будут взяты только первые N элементов (N-размерность матрицы).";
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			for (int i = column.size(); i > Matrix.size(); i--)
			{
				column.pop_back();
			}
		}
		else
		{
			if (column.size() < Matrix.size())
			{
				cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
				cout << "В передаваемом столбце есть проблема. Он меньше, чем столбцы в матрице. Передаваемый столбец будет дополнен нулями.";
				cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
				for (int i = column.size(); i < Matrix.size(); i++)
				{
					column.push_back(0);
				}
			}
		}
		if (number_column > 0 && number_column <= Matrix.size())
		{
			for (int i = 0; i < Matrix.size(); i++)
			{
				Matrix[i][number_column - 1] = column[i];
			}
		}
		else
		{
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "В матрице нет столбца c номером " << number_column << ". Будет заменён 1-ый столбец.";
			cout << endl << "///////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
			for (int i = 0; i < Matrix.size(); i++)
			{
				Matrix[i][0] = column[i];
			}
		}
		Application_of_the_algorithm = false;
	}

	//Метод, реализующий алгоритм.
	vector<vector<int>> Algoritm_Bellman_Ford()
	{
		//Обнуляем матрицу кратчайших путей. Это обнуление будет выполняться, когда мы повторно применяем алгоритм (больше 1 раза). 
		if (Result.size() > 0)
		{
			for (int i = 0; i < Result.size(); i++)
			{
				Result[i].clear();
			}
			Result.clear();
		}

		vector<vector<int>> help_matrix;
		vector<vector<int>> intermediate_matrix;
		vector<int> temp;//Временный вектор, который необходим для заполнения матрицы.
		//Инициализируем Result.
		for (int i = 0; i < Matrix.size(); i++)
		{
			for (int j = 0; j < Matrix.size(); j++)
			{
				if (Matrix[i][j] == 0)
				{
					temp.push_back(9999999); //9999999 - наша бесконечность, которая говорит об отсутствии пути.
				}
				else
				{
					temp.push_back(Matrix[i][j]);
				}
			}
			Result.push_back(temp);
			help_matrix.push_back(temp);
			intermediate_matrix.push_back(temp);
			temp.clear();
		}
		for (int i = 0; i < Matrix.size(); i++)//Если у вершины нет петли, то в ней устанавливается 0.
		{
			if (Result[i][i] == 9999999)
			{
				Result[i][i] = 0;
				help_matrix[i][i] = 0;
				intermediate_matrix[i][i] = 0;
			}
		}

		for (int i = 0; i < Matrix.size() - 1; i++) //Алгоритм находит кратчайший путь до всех вершин за N-1 итерацию, где N - кол-во вершин в графе.
		{
			for (int j = 0; j < Matrix.size(); j++)
			{
				for (int count_column = 0; count_column < Matrix.size(); count_column++)
				{
					for (int k = 0; k < Matrix.size(); k++)
					{
						temp.push_back(intermediate_matrix[j][k] + help_matrix[k][count_column]);
					}
					temp.push_back(intermediate_matrix[j][count_column]);//Взятие элемента, который был раньше.
					int min = find_min(temp);
					Result[j][count_column] = min;
					temp.clear();
				}
			}
			intermediate_matrix = Result;
		}

		//N-ная итерация, которая определит наличие отрицательного цикла.
		for (int j = 0; j < Matrix.size(); j++)
		{
			for (int count_column = 0; count_column < Matrix.size(); count_column++)
			{
				for (int k = 0; k < Matrix.size(); k++)
				{
					temp.push_back(intermediate_matrix[j][k] + help_matrix[k][count_column]);
				}
				temp.push_back(intermediate_matrix[j][count_column]);//Взятие элемента, который был раньше.
				int min = find_min(temp);
				Result[j][count_column] = min;
				temp.clear();
			}
		}

		if (intermediate_matrix == Result)
		{
			//cout << endl << endl << endl << "***************************************************************************************************" << endl;
			//cout << "Отрицательного цикла в графе - нет.";
			//cout << endl << "***************************************************************************************************" << endl << endl << endl;
			for (int i = 0; i < Matrix.size(); i++) //Заменяем нашу бесконечность на ноль. (пути нет).
			{
				for (int j = 0; j < Matrix.size(); j++)
				{
					if (Result[i][j] == 9999999)
					{
						Result[i][j] = 0;
					}
				}
			}
			Negative_cycle = false;
		}
		else
		{
			//cout << endl << endl << endl << "***************************************************************************************************" << endl;
			//cout << "Граф содержит отрицательный цикл." << endl;
			//cout << "Матрица, хранящая информацию о кратчайших путях - будет хранить нули.";
			for (int i = 0; i < Matrix.size(); i++)
			{
				for (int j = 0; j < Matrix.size(); j++)
				{
					Result[i][j] = 0;
				}
			}
			//cout << endl << "***************************************************************************************************" << endl << endl << endl;
			Negative_cycle = true;
		}
		Application_of_the_algorithm = true;
		return Result;
	}

	//Вывод матрицы смежности.
	void print_Matrix()
	{
		cout << "--------------------------------------------Data Matrix--------------------------------------------" << endl;
		for (int i = 0; i < Matrix.size(); i++)
		{
			for (int j = 0; j < Matrix[i].size(); j++)
			{
				cout << Matrix[i][j] << "\t";
			}
			cout << endl;
		}
		cout << "---------------------------------------------------------------------------------------------------" << endl;
	}

	//Вывод матрици минимальных маршрутов.
	void print_Result()
	{
		if (Application_of_the_algorithm == true)
		{
			if (Negative_cycle == true)
			{
				cout << endl << "***************************************************************************************************" << endl;
				cout << "Граф содержит отрицательный цикл." << endl;
				cout << "Матрица, хранящая информацию о кратчайших путях - будет хранить нули." << endl;
				cout << "-------------------------------------------Result Matrix-------------------------------------------" << endl;
				for (int i = 0; i < Result.size(); i++)
				{
					for (int j = 0; j < Result[i].size(); j++)
					{
						cout << Result[i][j] << "\t";
					}
					cout << endl;
				}
				cout << "---------------------------------------------------------------------------------------------------" << endl;
				cout << endl << "***************************************************************************************************" << endl;

			}
			else
			{
				cout << "Отрицательного цикла в графе - нет." << endl;
				cout << "-------------------------------------------Result Matrix-------------------------------------------" << endl;
				for (int i = 0; i < Result.size(); i++)
				{
					for (int j = 0; j < Result[i].size(); j++)
					{
						cout << Result[i][j] << "\t";
					}
					cout << endl;
				}
				cout << "---------------------------------------------------------------------------------------------------" << endl;
			}
		}
		else
		{
			cout << endl << "***************************************************************************************************" << endl;
			cout << "Алгоритм Беллмана-Форда не применялся или матрица, хранящая информацию о графе, была изменена.";
			cout << endl << "***************************************************************************************************" << endl;
		}
	}

	//Переопределение операции << для вывода в консоль и вывода в файл.
	friend ostream& operator<< (ostream& ustream, Bellman_Ford& obj);
};

ostream& operator<<(ostream& ustream, Bellman_Ford& obj)
{
	string str;
	str = "Матрица, которая хранит информацию о взвешенном графе.";
	ustream << str << endl;
	ustream << "--------------------------------------------Data Matrix--------------------------------------------" << endl;
	for (int i = 0; i < obj.Matrix.size(); i++)
	{
		for (int j = 0; j < obj.Matrix[i].size(); j++)
		{
			ustream << obj.Matrix[i][j] << "\t";
		}
		ustream << endl;
	}
	ustream << "---------------------------------------------------------------------------------------------------" << endl << endl << endl;

	if (obj.Application_of_the_algorithm == true)
	{
		if (obj.Negative_cycle == true)
		{
			str = "Взвешенный граф имеет отрицательный цикл.";
			ustream << str << endl;
		}
		else
		{
			str = "Взвешенный граф не имеет отрицательного цикла.";
			ustream << str << endl << endl << endl;
			str = "Матрица кратчайших путей от одной вершины до всех остальных.";
			ustream << str << endl;
			ustream << "-------------------------------------------Result Matrix-------------------------------------------" << endl;
			for (int i = 0; i < obj.Result.size(); i++)
			{
				for (int j = 0; j < obj.Result[i].size(); j++)
				{
					ustream << obj.Result[i][j] << "\t";
				}
				ustream << endl;
			}
			ustream << "---------------------------------------------------------------------------------------------------" << endl;
		}
	}
	else
	{
		str = "Алгоритм Беллмана-Форда не был применён.";
		ustream << str << endl;
	}

	return ustream;
}

void print_matrix_from_main(vector<vector<int>>& mat)
{
	cout << "----------------------------------------------Matrix-----------------------------------------------" << endl;
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
	setlocale(LC_ALL, "Russian");

	vector<vector<int>> mat =
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
	print_matrix_from_main(mat);

	cout << endl << endl << endl << endl << "***************************************************************************************************" << endl << endl << endl << endl;

	Bellman_Ford Graph(mat);

	Graph.print_Matrix();//Вывод взвешенного графа в консоль. Взвешенный граф представлен в виде таблицы NxN, где N - кол-во вершин.

	//Graph.Algoritm_Bellman_Ford();//Применение алгоритма Беллмана-Форда. (Результат будет сохранен во внутреннюю переменную класса, также результат можно присвоить матрице 'vector<vector<int>> {имя_матрицы}').

	vector<vector<int>> matrix_min_routes = Graph.Algoritm_Bellman_Ford();//Применение алгоритма Беллмана-Форда. (Результат будет сохранен во внутреннюю переменную класса и присвоен матрице 'vector<vector<int>> {имя_матрицы}').

	Graph.print_Result();//Вывод матрицы минимальных маршрутов в консоль для взвешенного графа.

	////Тест геттеров.
	//vector<vector<int>> test_mat;
	//test_mat = Graph.get_Matrix();
	//test_mat = Graph.get_Result();
	//vector<int> test;
	//test = Graph.get_Matrix_row(1);
	//test = Graph.get_Matrix_column(1);
	//bool test_info;
	//test_info = Graph.get_Application_of_the_algorithm();
	//test_info = Graph.get_Negative_cycle();

	////Тест сеттеров. (После сеттеров, нужно будет применить алгоритм Беллмана-Форда ещё раз, так как матрица изменилась).
	//Graph.set_Matrix_row(3, test);
	//Graph.set_Matrix_column(3, test);

	//cout << endl << endl << endl << "Тест потокового вывода." << endl;
	//cout << Graph;
	//cout << "Конец теста потокового вывода." << endl << endl << endl;

	return 0;
}