// 2.3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Постройте шаблон сбалансированного дерева. Используйте его для
хранения объектов класса C по ключам K в соответствии с таблицей (2.3).
Переопределите функцию вывода содержимого дерева с помощью
итераторов (в порядке возрастания / убывания ключей). Добавьте функции
поиска элемента по ключу, значению.

Вариант 18.
Таблица 2.3. Ключ и тип объекта, хранимого в контейнере АВЛ-дерево

Ключ: Фамилия и имя

Класс C: «Школьник».Минимальный набор полей: фамилия, имя, пол, класс, дата рождения, адрес.
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
	//Ключ: Фамилия и имя. 
	bool operator < (const school& other)
	{
		if (this->surname < other.surname)
		{
			return true;
		}
		else if (this->surname == other.surname)
		{
			if (this->name < other.name)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	bool operator > (const school& other)
	{
		if (this->surname > other.surname)
		{
			return true;
		}
		else if (this->surname == other.surname)
		{
			if (this->name > other.name)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	bool operator == (const school& other)
	{
		if (this->surname == other.surname && this->name == other.name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator <= (const school& other)
	{
		if (this->surname == other.surname && this->name == other.name)
		{
			return true;
		}
		else
		{
			if (this->surname < other.surname)
			{
				return true;
			}
			else if (this->surname == other.surname)
			{
				if (this->name < other.name)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	bool operator >= (const school& other)
	{
		if (this->surname == other.surname && this->name == other.name)
		{
			return true;
		}
		else
		{
			if (this->surname > other.surname)
			{
				return true;
			}
			else if (this->surname == other.surname)
			{
				if (this->name > other.name)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
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

template<class T>
class Node //узел
{
protected:
	//закрытые переменные Node N; N.data = 10 вызовет ошибку
	T data;

	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;

	//переменная, необходимая для поддержания баланса дерева
	int height;
public:
	//Конструктор. Устанавливаем стартовые значения для указателей
	Node<T>()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		height = 1;
	}
	Node<T>(T n)
	{
		data = n;
		left = right = parent = NULL;
		height = 1;
	}
	//доступные извне переменные и функции
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }

	virtual int getHeight() { return height; }
	virtual void setHeight(int h) { height = h; }

	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }

	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }

	virtual void print()
	{
		cout << "\n" << data;
	}

	template<class T> friend ostream& operator<< (ostream& stream, Node<T>& N);
};

template<class T>
ostream& operator<< (ostream& stream, Node<T>& N)
{
	stream << "\nNode data: " << N.data << ", height: " << N.height;
	return stream;
}

template<class T>
void print(Node<T>* N)
{
	T value = N->getData();
	cout << "\n" << value;
}

template<class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T>* root;
public:
	Tree<T>() { root = NULL; }//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда

	Tree<T>(Node<T>* N) { root = N; }

	~Tree()
	{
		//деструктор - освобождение памяти
		cout << "\nParent destructor";
		clear(root);
	}

	void clear(Node<T>* N)
	{
		if (N != NULL)
		{
			if (N->getLeft() != NULL)
			{
				clear(N->getLeft());
			}
			if (N->getRight() != NULL)
			{
				clear(N->getRight());
			}
			delete N;
			N = NULL;
			root = NULL;
		}
	}

	//доступ к корневому элементу
	virtual Node<T>* getRoot() { return root; }

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* Add_R(Node<T>* N)
	{
		return Add_R(N, root);
	}

	virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current)
	{
		if (N == NULL) return NULL;
		if (root == NULL)
		{
			root = N;
			return N;
		}

		if (Current->getData() > N->getData())
		{
			//идем влево
			if (Current->getLeft() != NULL)
				Current->setLeft(Add_R(N, Current->getLeft()));
			else
				Current->setLeft(N);
			Current->getLeft()->setParent(Current);
		}
		if (Current->getData() < N->getData())
		{
			//идем вправо
			if (Current->getRight() != NULL)
				Current->setRight(Add_R(N, Current->getRight()));
			else
				Current->setRight(N);
			Current->getRight()->setParent(Current);
		}
		if (Current->getData() == N->getData())
			//нашли совпадение
			;
		//для несбалансированного дерева поиска
		return Current;
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T>* Add(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		return Add_R(N);
	}

	//удаление узла
	virtual void Remove(Node<T>* N)
	{
		if (N->getLeft() == NULL && N->getRight() == NULL) //удаление листа в дереве
		{
			if (N != root)
			{
				Node<T>* current = N->getParent();
				if (current->getLeft() == N)
				{
					current->setLeft(NULL);
				}
				else
				{
					current->setRight(NULL);
				}
				delete N;
				N = NULL;
				return;
			}
			else
			{
				delete N;
				N = NULL;
				root = NULL;
				return;
			}
		}

		if (N->getLeft() != NULL && N->getRight() == NULL)//удаление узла с одним поддервом слева
		{
			if (N != root)
			{
				Node<T>* current = N->getParent();
				if (current->getLeft() == N)
				{
					current->setLeft(N->getLeft());
				}
				else
				{
					current->setRight(N->getLeft());
				}
				current = N->getLeft();
				current->setParent(N->getParent());
				delete N;
				N = NULL;
				return;
			}
			else
			{
				root = root->getLeft();
				root->setParent(NULL);
				delete N;
				N = NULL;
				return;
			}
		}

		if (N->getLeft() == NULL && N->getRight() != NULL)//удаление узла с одним поддервом справа
		{
			if (N != root)
			{
				Node<T>* current = N->getParent();
				if (current->getLeft() == N)
				{
					current->setLeft(N->getRight());
				}
				else
				{
					current->setRight(N->getRight());
				}
				current = N->getRight();
				current->setParent(N->getParent());
				delete N;
				N = NULL;
				return;
			}
			else
			{
				root = root->getRight();
				root->setParent(NULL);
				delete N;
				N = NULL;
				return;
			}
		}

		if (N->getLeft() != NULL && N->getRight() != NULL)//удаление узла с двумя поддервьями
		{
			Node<T>* current = N->getRight();
			while (current->getLeft() != NULL)
			{
				current = current->getLeft();
			}
			if (current->getLeft() == NULL && current->getRight() == NULL) //"current->getLeft() == NULL" - эту проверку можно убрать, т.к. мы в самом левом узле правого поддрева (у него нет элементов левее него).
			{
				//Самый левый элемент в правом поддереве - лист
				if (N != root)
				{
					if (N->getRight() == current)
					{
						Node<T>* cur = N->getParent();
						current->setParent(N->getParent());
						current->setLeft(N->getLeft());
						current->setRight(NULL);
						if (cur->getLeft() == N)
						{
							cur->setLeft(current);
						}
						else
						{
							cur->setRight(current);
						}
						cur = N->getLeft();
						cur->setParent(current);
						delete N;
						N = NULL;
						return;
					}
					else
					{
						Node<T>* cur = current->getParent();
						cur->setLeft(NULL);
						current->setParent(N->getParent());
						current->setLeft(N->getLeft());
						current->setRight(N->getRight());
						cur = N->getParent();
						if (cur->getLeft() == N)
						{
							cur->setLeft(current);
						}
						else
						{
							cur->setRight(current);
						}
						cur = N->getRight();
						cur->setParent(current);

						cur = N->getLeft();
						cur->setParent(current);
						delete N;
						N = NULL;
						return;
					}
				}
				else
				{
					if (N->getRight() == current)
					{
						current->setParent(N->getParent());
						current->setLeft(N->getLeft());
						current->setRight(NULL);
						root = current;
						Node<T>* cur = current->getLeft();
						cur->setParent(current);
						delete N;
						N = NULL;
						return;
					}
					else
					{
						Node<T>* cur = current->getParent();
						cur->setLeft(NULL);
						current->setParent(N->getParent());
						current->setLeft(N->getLeft());
						current->setRight(N->getRight());
						cur = N->getRight();
						cur->setParent(current);
						cur = N->getLeft();
						cur->setParent(current);
						root = current;
						delete N;
						N = NULL;
						return;
					}
				}
			}
			else
			{
				//Самый левый элемент в правом поддереве имеет правое поддерево
				if (N != root)
				{
					if (N->getRight() == current)
					{
						Node<T>* cur = current->getRight();
						current->setParent(N->getParent());
						current->setLeft(N->getLeft());
						current->setRight(cur);
						cur->setParent(current);
						cur = current->getParent();
						if (cur->getLeft() == current)
						{
							cur->setLeft(current);
						}
						else
						{
							cur->setRight(current);
						}
						cur = N->getLeft();
						cur->setParent(current);
						delete N;
						N = NULL;
						return;
					}
					else
					{
						Node<T>* cur = current->getParent();
						cur->setLeft(current->getRight());
						cur = current->getRight();
						cur->setParent(current->getParent());
						current->setParent(N->getParent());
						current->setLeft(N->getLeft());
						current->setRight(N->getRight());
						cur = N->getParent();
						if (cur->getLeft() == current)
						{
							cur->setLeft(current);
						}
						else
						{
							cur->setRight(current);
						}
						cur = N->getRight();
						cur->setParent(current);
						cur = N->getLeft();
						cur->setParent(current);
						delete N;
						N = NULL;
						return;
					}
				}
				else
				{
					if (N->getRight() == current)
					{
						current->setParent(N->getParent());
						current->setLeft(N->getLeft());
						Node<T>* cur = N->getLeft();
						cur->setParent(current);
						root = current;
						delete N;
						N = NULL;
						return;
					}
					else
					{
						Node<T>* cur = current->getParent();
						cur->setLeft(current->getRight());
						cur = current->getRight();
						cur->setParent(current->getParent());
						current->setParent(N->getParent());
						current->setLeft(N->getLeft());
						current->setRight(N->getRight());
						cur = N->getLeft();
						cur->setParent(current);
						cur = N->getRight();
						cur->setParent(current);
						root = current;
						delete N;
						N = NULL;
						return;
					}
				}
			}
		}
	}

	virtual Node<T>* Min(Node<T>* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;

		if (Current == NULL)
			Current = root;
		while (Current->getLeft() != NULL)
			Current = Current->getLeft();

		return Current;
	}

	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		//максимум - это самый "правый" узел. Идём по дереву всегда вправо
		if (root == NULL) return NULL;

		if (Current == NULL)
			Current = root;
		while (Current->getRight() != NULL)
			Current = Current->getRight();

		return Current;
	}

	//поиск узла в дереве. Первый параметр - что искать, второй - в каком поддереве искать
	virtual Node<T>* Find(T data, Node<T>* Current)
	{
		//база рекурсии
		if (Current == NULL) return NULL;

		if (Current->getData() == data) return Current;

		//рекурсивный вызов
		if (Current->getData() > data) return Find(data, Current->getLeft());

		if (Current->getData() < data) return Find(data, Current->getRight());
	}

	//Три способа обхода дерева:
	// 
	//  *******
	//  *  А  *
	//  * / \ *
	//  *B   С*
	//  *******
	// 
	//Обход дерева сверху вниз(в прямом порядке) : A, B, C — префиксная форма.
	//Обход дерева в симметричном порядке(слева направо) : B, A, C — инфиксная форма.
	//Обход дерева в обратном порядке(снизу вверх) : B, C, A — постфиксная форма.

	//Обход дерева в префиксной форме будет иметь вид
	virtual void PreOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}

	//Обход дерева в инфиксной форме будет иметь вид (InOrder-обход даст отсортированную последовательность)
	virtual void InOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);
	}

	//Обход дерева в постфиксной форме будет иметь вид
	virtual void PostOrder(Node<T>* N, void (*f)(Node<T>*))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}
};

//Класс итератор по дереву
template<typename ValueType> //ValueType . итератор может смотреть на элементы с произвольным типом
class TreeIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
	Node<ValueType>* ptr;
public:
	TreeIterator() { ptr = NULL; }
	TreeIterator(Node<ValueType>* p) { ptr = p; }
	TreeIterator(const TreeIterator& it) //Конструктор копий.
	{
		ptr = it.ptr;
	}

	//Присваивание.
	TreeIterator& operator=(const TreeIterator& it)
	{
		ptr = it.ptr;
		return *this;
	}
	TreeIterator& operator=(Node<ValueType>* p)
	{
		ptr = p;
		return *this;
	}

	bool operator!=(TreeIterator const& other) { return ptr != other.ptr; }
	bool operator==(TreeIterator const& other) { return ptr == other.ptr; }

	//Получить значение.
	Node<ValueType>& operator*()
	{
		return *ptr;
	}

	//Перемещение с помощью итераторов.
	TreeIterator& operator++()
	{
		Node<ValueType>* root_tree = ptr;
		while (root_tree->getParent() != NULL)
		{
			root_tree = root_tree->getParent();
		}

		if (ptr->getRight() != NULL)
		{
			ptr = ptr->getRight();
			while (ptr->getLeft() != NULL)
			{
				ptr = ptr->getLeft();
			}
			return *this;
		}
		if (ptr == root_tree && ptr->getRight() == NULL)//корень без правого поддерева - это максимум.
		{
			return *this;
		}
		Node<ValueType>* Current = ptr;
		ValueType value = Current->getData();
		while (Current->getParent() != NULL && value >= Current->getData())
		{
			Current = Current->getParent();
		}
		if (Current->getData() > value)
		{
			ptr = Current;
		}
		return *this;
	}
	TreeIterator& operator++(int v)
	{
		Node<ValueType>* root_tree = ptr;
		while (root_tree->getParent() != NULL)
		{
			root_tree = root_tree->getParent();
		}

		if (ptr->getRight() != NULL)
		{
			ptr = ptr->getRight();
			while (ptr->getLeft() != NULL)
			{
				ptr = ptr->getLeft();
			}
			return *this;
		}
		if (ptr == root_tree && ptr->getRight() == NULL)//корень без правого поддерева - это максимум.
		{
			return *this;
		}
		Node<ValueType>* Current = ptr;
		ValueType value = Current->getData();
		while (Current->getParent() != NULL && value >= Current->getData())
		{
			Current = Current->getParent();
		}
		if (Current->getData() > value)
		{
			ptr = Current;
		}
		return *this;
	}

	TreeIterator& operator--()
	{
		Node<ValueType>* root_tree = ptr;
		while (root_tree->getParent() != NULL)
		{
			root_tree = root_tree->getParent();
		}

		if (ptr->getLeft() != NULL)
		{
			ptr = ptr->getLeft();
			while (ptr->getRight() != NULL)
			{
				ptr = ptr->getRight();
			}
			return *this;
		}
		if (ptr == root_tree && ptr->getLeft() == NULL)//корень без левого поддерева - это минимум.
		{
			return *this;
		}
		Node<ValueType>* Current = ptr;
		ValueType value = Current->getData();
		while (Current->getParent() != NULL && value <= Current->getData())
		{
			Current = Current->getParent();
		}
		if (Current->getData() < value)
		{
			ptr = Current;
		}
		return *this;
	}
	TreeIterator& operator--(int v)
	{
		Node<ValueType>* root_tree = ptr;
		while (root_tree->getParent() != NULL)
		{
			root_tree = root_tree->getParent();
		}

		if (ptr->getLeft() != NULL)
		{
			ptr = ptr->getLeft();
			while (ptr->getRight() != NULL)
			{
				ptr = ptr->getRight();
			}
			return *this;
		}
		if (ptr == root_tree && ptr->getLeft() == NULL)//корень без левого поддерева - это минимум.
		{
			return *this;
		}
		Node<ValueType>* Current = ptr;
		ValueType value = Current->getData();
		while (Current->getParent() != NULL && value <= Current->getData())
		{
			Current = Current->getParent();
		}
		if (Current->getData() < value)
		{
			ptr = Current;
		}
		return *this;
	}
};

//класс итерируемое дерево поиска
template<class T>
class IteratedTree : public Tree<T>
{
public:
	IteratedTree<T>() : Tree<T>() {}

	TreeIterator<T> begin()
	{
		TreeIterator<T> it = Tree<T>::Min();
		return it;
	}
	TreeIterator<T> end()
	{
		TreeIterator<T> it = Tree<T>::Max();
		return it;
	}
};

//AVL_Tree - потомок класса Tree, АВЛ-дерево (сбалансированное дерево поиска)
template<class T>
class AVL_Tree : public IteratedTree<T>
{
protected:
	//определение разности высот двух поддеревьев
	int bfactor(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		return (hr - hl);
	}

	//при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
	//после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
	//значение могло поменяться
	void fixHeight(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		p->setHeight((hl > hr ? hl : hr) + 1);
	}

	//краеугольные камни АВЛ-деревьев - процедуры поворотов
	Node<T>* RotateRight(Node<T>* p) //правый поворот вокруг p
	{
		Node<T>* q = p->getLeft();
		if (p->getParent() != NULL)
		{
			if (p->getParent()->getLeft() == p)
				p->getParent()->setLeft(q);
			else
				p->getParent()->setRight(q);
		}
		q->setParent(p->getParent());
		p->setParent(q);
		if (q->getRight() != NULL) q->getRight()->setParent(p);

		if (p == Tree<T>::root) Tree<T>::root = q;

		p->setLeft(q->getRight());
		q->setRight(p);

		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node<T>* RotateLeft(Node<T>* q) //левый поворот вокруг q
	{
		Node<T>* p = q->getRight();
		if (q->getParent() != NULL)
		{
			if (q->getParent()->getLeft() == q)
				q->getParent()->setLeft(p);
			else
				q->getParent()->setRight(p);
		}
		p->setParent(q->getParent());
		q->setParent(p);
		if (p->getLeft() != NULL) p->getLeft()->setParent(q);

		if (q == Tree<T>::root) Tree<T>::root = p;

		q->setRight(p->getLeft());
		p->setLeft(q);

		fixHeight(q);
		fixHeight(p);
		return p;
	}

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	Node<T>* Balance(Node<T>* p) //балансировка узла p
	{
		fixHeight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->getRight()) < 0)
			{
				p->setRight(RotateRight(p->getRight()));
				p->getRight()->setParent(p);
			}
			return RotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->getLeft()) > 0)
			{
				p->setLeft(RotateLeft(p->getLeft()));
				p->getLeft()->setParent(p);
			}
			return RotateRight(p);
		}

		return p; //балансировка не нужна
	}

public:
	//конструктор AVL_Tree вызывает конструктор базового класса Tree
	AVL_Tree<T>() : IteratedTree<T>() {}//AVL_Tree constructor
	~AVL_Tree<T>() {}//AVL_Tree destructor

	virtual Node<T>* Add_R(Node<T>* N)
	{
		return Add_R(N, Tree<T>::root);
	}

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node<T>* Add_R(Node<T>* N, Node<T>* Current)
	{
		//вызываем функцию Add_R из базового класса
		Node<T>* AddedNode = Tree<T>::Add_R(N, Current);
		//применяем к добавленному узлу балансировку
		return Balance(AddedNode);
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual Node<T>* Add(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		return Add_R(N);
	}

	//удаление узла
	virtual void Remove(Node<T>* N)
	{
		Tree<T>::Remove(N);
		Balance(Tree<T>::root);
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
	school A10("Макаров", "Тигран", true, 11, "2004.11.11", "Москва");

	AVL_Tree<school> T;

	T.Add(A1);
	T.Add(A2);
	T.Add(A3);
	T.Add(A4);
	T.Add(A5);
	T.Add(A6);
	T.Add(A7);
	T.Add(A8);
	T.Add(A9);
	T.Add(A10);

	Node<school>* M = T.Min();

	school A11 = M->getData();

	cout << "\nMin = " << A11 << "\nFind " << A3 << ": " << T.Find(A3, T.getRoot());

	void (*f_ptr)(Node<school>*); f_ptr = print;
	cout << "\n-----\nInorder:";
	T.InOrder(T.getRoot(), f_ptr);

	cout << endl << "/////////////////////////////////////////////////////////" << endl;
	cout << "Test iterator++" << endl;
	TreeIterator<school> iter = T.begin();
	while (iter != T.end())
	{
		cout << *iter << " ";
		iter++;
	}
	iter++;
	cout << *iter << " ";
	cout << endl << "/////////////////////////////////////////////////////////" << endl;
	cout << "Test iterator--" << endl;
	while (iter != T.begin())
	{
		cout << *iter << " ";
		iter--;
	}
	iter--;
	cout << *iter << " ";

	cout << endl << "/////////////////////////////////////////////////////////" << endl;
	cout << "\n-----\nPreorder:";
	T.PreOrder(T.getRoot(), f_ptr);

	cout << "\n-----\nInorder:";
	T.InOrder(T.getRoot(), f_ptr);

	cout << "\n-----\nPostorder:";
	T.PostOrder(T.getRoot(), f_ptr);

	cout << endl;
	char c; cin >> c;
	return 0;
}