// 2.4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Используйте шаблон класса Heap (куча, пирамида) для хранения
объектов в соответствии с пунктом 2 задания №1 (используется
упорядоченность по приоритету, в корне дерева – максимум). Реализуйте
функцию удаления корня дерева ExtractMax(). Выведите элементы Heap в
порядке убывания приоритета с её помощью.

Вариант 18.

Класс С
«Школьник».
Минимальный набор полей: фамилия, имя, пол, класс, дата рождения, адрес.

Приоритет
Класс; дата рождения; фамилия и имя.
*/

#include <iostream>

using namespace std;

class school
{
private:
	string surname;//Фамилия.
	string name;//Имя.
	bool floor;//Пол (0-женский, 1-мужской).
	int classroom;//Класс.
	string data;//Жата рождения (год, месяц, день).
	string address;//Адрес(Город).
public:
	school()
	{
		surname = "Фамилия?";
		name = "Имя?";
		floor = false;
		classroom = 0;
		data = "дата рождения?";
		address = "адрес?";
	}
	school(string Xsurname, string Xname, bool Xfloor, int Xclassroom, string Xdata, string Xaddress) //Конструктор.
	{
		surname = Xsurname;
		name = Xname;
		floor = Xfloor;
		classroom = Xclassroom;
		data = Xdata;
		address = Xaddress;
	}
	//Сеттеры.
	void setsurname(string a) //Запись фамилии.
	{
		surname = a;
	}
	void setname(string a) //Запись имени.
	{
		name = a;
	}
	void setfloor(bool a) //Запись пола.
	{
		floor = a;
	}
	void setclassroom(int a) //Запись класса.
	{
		classroom = a;
	}
	void setdata(string a) //Запись даты.
	{
		data = a;
	}
	void setaddress(string a) //Запись адреса.
	{
		address = a;
	}
	//Геттеры.
	string getsurname() //Выдать фамилию.
	{
		return surname;
	}
	string getname() //Выдать имя.
	{
		return name;
	}
	bool getfloor() //Выдать пол.
	{
		return floor;
	}
	int getclassroom() //Выдать класс.
	{
		return classroom;
	}
	string getdata() //Выдать дату.
	{
		return data;
	}
	string getaddress() //Выдать адрес.
	{
		return address;
	}
	//Приоритет: Класс; дата рождения; фамилия и имя.
	bool operator > (const school& other)
	{
		if (this->classroom > other.classroom)
		{
			return true;
		}
		else if (this->classroom == other.classroom)
		{
			if (this->data < other.data) //2003 год > 2004 года, т.к. первому будет 18, а второму - 17 (18 > 17).
			{
				return true;
			}
			else if (this->data == other.data)
			{
				if (this->surname > other.surname)
				{
					return true;
				}
				else if (this->name > other.name)
				{
					return true;
				}
			}
		}
		return false;
	}
	bool operator < (const school& other)
	{
		if (this->classroom < other.classroom)
		{
			return true;
		}
		else if (this->classroom == other.classroom)
		{
			if (this->data > other.data) //2003 год > 2004 года, т.к. первому будет 18, а второму - 17 (18 > 17).
			{
				return true;
			}
			else if (this->data == other.data)
			{
				if (this->surname < other.surname)
				{
					return true;
				}
				else if (this->name < other.name)
				{
					return true;
				}
			}
		}
		return false;
	}
	bool operator == (const school& other)
	{
		if (this->classroom == other.classroom && this->data == other.data && this->surname == other.surname && this->name == other.name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend ostream& operator<< (ostream& ustream, school& obj);	//Вывод информации.
};

ostream& operator<< (ostream& ustream, school& obj)
{
	{
		char Xfloor;
		if (obj.getfloor() == false)
		{
			Xfloor = 'Ж';
		}
		else
		{
			Xfloor = 'М';
		}
		ustream << "Школьник:\t" << obj.getsurname() << " " << obj.getname() << ". Пол:\t" << Xfloor << ". Класс:\t" << obj.getclassroom() << ". Дата рождения (год.месяц.цисло):\t" << obj.getdata() << " Адрес:\t" << obj.getaddress();
		return ustream;
	}
}

//узел дерева
template <class T>
class Node
{
private:
	T value;
public:
	Node<T>() {}
	Node<T>(T n)
	{
		value = n;
	}
	//установить данные в узле
	T getValue() { return value; }
	void setValue(T v) { value = v; }

	//cравнение узлов
	bool operator<(Node N)
	{
		if (value < N.getValue())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator>(Node N)
	{
		if (value > N.getValue())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator>=(Node N)
	{
		if (value >= N.getValue())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator<=(Node N)
	{
		if (value <= N.getValue())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator==(Node N)
	{
		if (value == N.getValue())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator!=(Node N)
	{
		if (value != N.getValue())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	T operator*()
	{
		return value;
	}
	//вывод содержимого одного узла
	void print()
	{
		cout << value;
	}

	template<class T> friend ostream& operator<< (ostream& ustream, Node<T>& obj);	//Вывод информации.
};

template<class T>
ostream& operator<< (ostream& ustream, Node<T>& obj)
{
	{
		ustream << obj.value;
		return ustream;
	}
}

template <class T>
void print(Node<T>* N)
{
	T temporary = N->getValue();
	cout << temporary << "\n";
}

//куча (heap)
template <class T>
class Heap
{
private:
	//массив
	Node<T>* arr;
	//сколько элементов добавлено
	int len;
	//сколько памяти выделено
	int size;
public:
	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }
	Node<T>& operator[](int index)
	{
		if (index < 0 || index >= len)
			;//?

		return arr[index];
	}
	//конструктор
	Heap<T>(int MemorySize = 100)
	{
		arr = new Node<T>[MemorySize];
		len = 0;
		size = MemorySize;
	}
	//поменять местами элементы arr[index1], arr[index2]
	void Swap(int index1, int index2)
	{
		if (index1 <= 0 || index1 >= len)
			;
		if (index2 <= 0 || index2 >= len)
			;
		//здесь нужна защита от дурака
		Node<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}
	//скопировать данные между двумя узлами
	void Copy(Node<T>* dest, Node<T>* source)
	{
		dest->setValue(source->getValue());
	}
	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	Node<T>* GetLeftChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return &arr[index * 2 + 1];
	}
	Node<T>* GetRightChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return &arr[index * 2 + 2];
	}
	Node<T>* GetParent(int index)
	{
		if (index <= 0 || index >= len)
			;
		//здесь нужна защита от дурака
		if (index % 2 == 0)
			return &arr[index / 2 - 1];
		return &arr[index / 2];
	}
	int GetLeftChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return index * 2 + 1;
	}
	int GetRightChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return index * 2 + 2;
	}
	int GetParentIndex(int index)
	{
		if (index <= 0 || index >= len)
			;
		//здесь нужна защита от дурака
		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}
	//просеить элемент вверх
	void SiftUp(int index = -1)
	{
		if (index == -1) index = len - 1;
		int parent = GetParentIndex(index);
		int index2 = GetLeftChildIndex(parent);
		if (index2 == index) index2 = GetRightChildIndex(parent);
		int max_index = index;
		if (index < len && index2 < len && parent >= 0)
		{
			if (arr[index] > arr[index2])
				max_index = index;
			if (arr[index] < arr[index2])
				max_index = index2;
		}
		if (parent < len && parent >= 0 && arr[max_index]>arr[parent])
		{
			//нужно просеивание вверх
			Swap(parent, max_index);
			SiftUp(parent);
		}
	}
	//добавление элемента - вставляем его в конец массива и просеиваем вверх
	template <class T>
	void Add(T v)
	{
		Node<T>* N = new Node<T>;
		N->setValue(v);
		Add(N);
	}
	template <class T>
	void Add(Node<T>* N)
	{
		if (len < size)
		{
			Copy(&arr[len], N);
			len++;
			SiftUp();
		}
	}
	//перечислить элементы кучи и применить к ним функцию
	void Straight(void(*f)(Node<T>*))
	{
		int i;
		for (i = 0; i < len; i++)
		{
			f(&arr[i]);
		}
	}
	//перебор элементов, аналогичный проходам бинарного дерева
	void InOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	//Все совпадения с реальными людьми случайны.
	school A1("Гусев", "Никита", true, 11, "2004.10.10", "Москва");
	school A2("Любимова", "Милана", false, 10, "2005.09.11", "Краснодар");
	school A3("Фролов", "Роман", true, 5, "2010.01.05", "Волгоград");
	school A4("Журавлев", "Роман", true, 1, "2014.09.11", "Москва");
	school A5("Иванова", "Алиса", false, 4, "2011.12.11", "Дубна");
	school A6("Иванова", "Галя", false, 4, "2011.12.11", "Дубна");
	school A7("Степанов", "Степан", true, 7, "2008.11.15", "Москва");
	school A8("Власов", "Матвей", true, 7, "2008.11.17", "Мытищи");
	school A9("Ковалев", "Даниил", true, 10, "2005.07.07", "Москва");
	school A10("Макаров", "Тигран", true, 11, "2003.11.11", "Москва");
	if (A1 < A10)
	{
		cout << A1 << endl;
	}
	else
	{
		cout << A10 << endl;
	}


	Node<school> G = A1;
	cout << G << endl;
	cout << endl << endl << endl;
	G.print();
	cout << endl << endl << endl;
	print(&G);

	school A99 = *G;
	cout << A99;

	/*Heap<int> Tree;
	Tree.Add(1);
	Tree.Add(-1);
	Tree.Add(-2);
	Tree.Add(2);
	Tree.Add(5);
	Tree.Add(6);
	Tree.Add(-3);
	Tree.Add(-4);
	Tree.Add(4);
	Tree.Add(3);
	cout << "\n-----\nStraight:";
	void(*f_ptr)(Node<int>*); f_ptr = print;
	Tree.Straight(f_ptr);
	char c; cin >> c;*/


	return 0;
}