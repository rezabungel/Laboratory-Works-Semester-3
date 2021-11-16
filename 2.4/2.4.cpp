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
	Heap<T>(int MemorySize = 100)//конструктор
	{
		arr = new Node<T>[MemorySize];
		len = 0;
		size = MemorySize;
	}
	~Heap<T>()//деструктор
	{
		delete[] arr;
	}

	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }

	//Если len=10, то максимальный индекс 10-1=9.
	Node<T>& operator[](int index)
	{
		while (!(index >= 0 && index < len))
		{
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Некорректный индекс: " << index << endl;
			cout << "Введите index ещё раз (диапазон индексов [0:" << len - 1 << "]). index="; cin >> index;
			cout << "////////////////////////////////////////////////////////////////////////////////" << endl;
		}
		return arr[index];
	}

	//поменять местами элементы arr[index1], arr[index2]
	void Swap(int index1, int index2)
	{
		while (!(index1 >= 0 && index1 < len))
		{
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Некорректный индекс: " << index1 << endl;
			cout << "Введите index1 ещё раз (диапазон индексов [0:" << len - 1 << "]). index1="; cin >> index1;
			cout << "////////////////////////////////////////////////////////////////////////////////" << endl;
		}
		while (!(index2 >= 0 && index2 < len))
		{
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Некорректный индекс: " << index2 << endl;
			cout << "Введите index1 ещё раз (диапазон индексов [0:" << len - 1 << "]). index2="; cin >> index2;
			cout << "////////////////////////////////////////////////////////////////////////////////" << endl;
		}
		Node<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}

	//скопировать данные между двумя узлами
	void Copy(Node<T>* dest, Node<T>* source) //(copy - работает с указателями, поэтому, чтобы передать обычный объект нужно использовать ссылки)
	{
		dest->setValue(source->getValue());
	}

	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	Node<T>* GetLeftChild(int index)
	{
		if (index >= 0 && index * 2 + 1 < len)
		{
			return &arr[index * 2 + 1];
		}
		else
		{
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Авария. GetLeftChild. Некорректный индекс (выход из допустимого диапазона индексов). ";
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			exit(1); //Аварийное завершение.
		}
	}
	Node<T>* GetRightChild(int index)
	{
		if (index >= 0 && index * 2 + 2 < len)
		{
			return &arr[index * 2 + 2];
		}
		else
		{
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Авария. GetRightChild. Некорректный индекс (выход из допустимого диапазона индексов). ";
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			exit(1);//Аварийное завершение.
		}
	}
	Node<T>* GetParent(int index)
	{
		if (index == 0)
		{
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "У корня нет родителя. Будет выдан корень.";
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			return 0;
		}
		if (index >= 0 && index < len)
		{
			if (index % 2 == 0)
			{
				return &arr[index / 2 - 1];
			}
			return &arr[index / 2];
		}
		else
		{
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Авария. GetParent. Некорректный индекс (выход из допустимого диапазона индексов). ";
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			exit(1);//Аварийное завершение.
		}
	}
	int GetLeftChildIndex(int index)
	{
		if (index >= 0 && index * 2 + 1 < len)
		{
			return index * 2 + 1;
		}
		else
		{
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Авария. GetLeftChildIndex. Некорректный индекс (выход из допустимого диапазона индексов). ";
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			exit(1); //Аварийное завершение.
		}
	}
	int GetRightChildIndex(int index)
	{
		if (index >= 0 && index * 2 + 2 <= len) ////
		{
			return index * 2 + 2;
		}
		else
		{
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Авария. GetRightChildIndex. Некорректный индекс (выход из допустимого диапазона индексов). ";
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			exit(1);//Аварийное завершение.
		}
	}
	int GetParentIndex(int index)
	{
		if (index >= 0 && index < len)
		{
			if (index == 0)
			{
				return 0;
			}
			if (index % 2 == 0)
			{
				return index / 2 - 1;
			}
			else
			{
				return index / 2;
			}
		}
		else
		{
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			cout << "Авария. GetParentIndex. Некорректный индекс (выход из допустимого диапазона индексов). ";
			cout << endl << "////////////////////////////////////////////////////////////////////////////////" << endl;
			exit(1);//Аварийное завершение.
		}
	}

	void Heapify(int index = 0) //То же, что и SiftDown
	{
		int leftChild;
		int rightChild;
		int largestChild;

		leftChild = 2 * index + 1;
		rightChild = 2 * index + 2;

		//нужно сравнить элементы и при необходимости произвести просеивание вниз
		if (rightChild < len)
		{//если есть правый элемент, то есть и левый элемент
			if (arr[leftChild] > arr[rightChild])
			{
				largestChild = leftChild;//случай, когла левый элемент больше правого
			}
			else
			{
				largestChild = rightChild;//случай, когла правый элемент больше левого
			}
			if (arr[index] < arr[largestChild])
			{
				Swap(index, largestChild);
				Heapify(largestChild); //рекурсия
			}
		}
		else//есть только левый элемент (правого элемента нет)
		{
			if (leftChild < len && arr[index] < arr[leftChild])
			{
				Swap(index, leftChild);
				Heapify(leftChild);//рекурсия
			}
		}
	}

	//просеить элемент вверх
	void SiftUp(int index = -1)
	{
		if (index == -1) index = len - 1;
		if (index <= 0) return; //меньше 0 - мы нигде, надо выхидить. 0 корень- его не с кем менять, тоже выходим
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

	Node<T>* ExtractMax()
	{//исключить максимум и запустить просеивание кучи
		if (len == 0) return NULL; //Если длина равна 0, то ничего не нужно делать
		Node<T>* res = new Node<T>;
		Copy(res, &arr[0]); //copy - работает с указателями, поэтому, чтобы передать обычный объект нужно использовать ссылки

		Swap(0, len - 1); //Copy(&arr[0], &arr[len - 1]);
		len--;
		Heapify();//по-умолчанию начинает с нулевого элемента

		return res;
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
	void PreOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void InOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void PostOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
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

	Heap<school> Tree;
	Tree.Add(A1);
	Tree.Add(A2);
	Tree.Add(A3);
	Tree.Add(A4);
	Tree.Add(A5);
	Tree.Add(A6);
	Tree.Add(A7);
	Tree.Add(A8);
	Tree.Add(A9);
	Tree.Add(A10);
	cout << "\n-----\nStraight:\n";
	void(*f_ptr)(Node<school>*); f_ptr = print;
	Tree.Straight(f_ptr);

	cout << endl << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
	cout << "---Ввывод в остортированном виде heapsort. (Элементы будут удалены из heap, т.к. используется 'ExtractMax()')---" << endl;
	int i = 0;
	while (i < Tree.getCount()) //теперь это heapsort
	{
		Node<school>* N = Tree.ExtractMax();
		N->print();
		delete N;
		cout << endl;
	}
	cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
	return 0;
}