// 1.4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Святченко Артём Андреевич

/*
Постройте итераторы для перемещения по списку. Переопределите
функцию вывода содержимого списка с помощью итераторов. Итераторы
двунаправленные.
*/

#include <iostream>
#include <fstream>

using namespace std;

bool conditions(int value) //Проверка на кратность 3. Если да, то кратное. Если нет, то не кратное.
{
	return (value % 3 == 0);
}

template<class T>
class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next;
	Element* prev;
	//информация, хранимая в поле
	T field;
public:
	Element(T value = 0, Element<T>* next_ptr = NULL, Element<T>* prev_ptr = NULL)
	{
		field = value;
		next = next_ptr;
		prev = prev_ptr;
	}
	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	//доступ к полю с хранимой информацией field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	template<class T> friend ostream& operator<< (ostream& ustream, Element<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
	ustream << obj.field;
	return ustream;
}

template <class T>
class LinkedListParent
{
protected:
	//достаточно хранить начало и конец
	Element<T>* head;
	Element<T>* tail;
	//для удобства храним количество элементов
	int num;
public:
	virtual int Number() { return num; }

	virtual Element<T>* getBegin() { return head; }

	virtual Element<T>* getEnd() { return tail; }

	LinkedListParent()
	{
		//конструктор без параметров
		cout << "\nParent constructor";
		head = NULL;
		tail = NULL;
		num = 0;
	}

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T>* push(T value) = 0;

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual Element<T>* pop() = 0;

	virtual ~LinkedListParent()
	{
		//деструктор - освобождение памяти
		cout << "\nParent destructor";
		Element<T>* temp = NULL;
		while (LinkedListParent<T>::head != NULL)
		{
			if (LinkedListParent<T>::head == LinkedListParent<T>::tail)
			{
				delete LinkedListParent<T>::head;
				LinkedListParent<T>::head = LinkedListParent<T>::tail = NULL;
			}
			else
			{
				temp = LinkedListParent<T>::head;
				LinkedListParent<T>::head = LinkedListParent<T>::head->getNext();
				delete temp;
				temp = NULL;
			}
			LinkedListParent<T>::num = LinkedListParent<T>::num - 1;
		}
	}
	//получение элемента по индексу - какова асимптотическая оценка этого действия ?
	virtual Element<T>* operator[](int i)
	{
		//индексация
		if (i<0 || i>num) return NULL;
		int k = 0;

		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	template<class T> friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);

	template<class T> friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
};

template<typename ValueType>
class ListIterator;//Предварительное объявление класса необходимо для работы переопределения operator << в LinkedListParent.

template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj) //Переделаем, используя итератор.
{
	ListIterator<T> iterator_current;
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (iterator_current = obj.getBegin(); iterator_current != NULL; iterator_current++)
		{
			ustream << (*iterator_current).getValue() << " ";
		}
		return ustream;
	}
	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (iterator_current = obj.getBegin(); iterator_current != NULL; iterator_current++, i++)
	{
		ustream << "arr[" << i << "] = " << (*iterator_current).getValue() << "\n";
	}
	return ustream;
}

template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
	//чтение из файла и консоли совпадают
	int len;
	ustream >> len;
	//здесь надо очистить память под obj, установить obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
	//Текущий элемент.
	Element<ValueType>* ptr;
public:
	//Конструкторы.
	ListIterator() { ptr = NULL; }
	//ListIterator(ValueType* p) { ptr = p; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }

	//Перемещение с помощью итераторов.
	ListIterator& operator++()
	{
		if (ptr != NULL)
		{
			ptr = ptr->getNext();
		}
		return *this;
	}
	ListIterator& operator++(int v)
	{
		if (ptr != NULL)
		{
			ptr = ptr->getNext();
		}
		return *this;
	}
	ListIterator& operator--()
	{
		if (ptr != NULL)
		{
			ptr = ptr->getPrevious();
		}
		return *this;
	}
	ListIterator& operator--(int v)
	{
		if (ptr != NULL)
		{
			ptr = ptr->getPrevious();
		}
		return *this;
	}

	//Присваивание.
	ListIterator& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }
	ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }

	//Проверка итераторов на равенство.
	bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }
	bool operator==(ListIterator const& other) const { return ptr == other.ptr; } //need for BOOST_FOREACH

	//Получить значение.
	Element<ValueType>& operator*()
	{
		return *ptr;
	}

	template<class T> friend ostream& operator << (ostream& ustream, ListIterator<ValueType>& obj);
};

template<class ValueType>
ostream& operator << (ostream& ustream, ListIterator<ValueType>& obj)
{
	ustream << (*obj).getValue() << endl;
	return ustream;
}

//Класс итерируемый список - наследник связного списка, родитель для класс Стек.	
template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }
	virtual ~IteratedLinkedList() { cout << "\nIteratedLinkedList destructor"; }

	ListIterator<T> begin()
	{
		ListIterator<T> it = LinkedListParent<T>::head; return it;
	}
	ListIterator<T> end()
	{
		ListIterator<T> it = LinkedListParent<T>::tail; return it;
	}
};

template <class T>
class Stack : public IteratedLinkedList<T>//Мой класс - стек.
{//Стек элементы добавляются в конец, извлекаются с конца.
public:
	Stack() : IteratedLinkedList<T>() { cout << "\nStack constructor"; }
	virtual ~Stack() { cout << "\nStack destructor"; }

	virtual Element<T>* push(T value)
	{
		if (LinkedListParent<T>::num > 0)
		{
			Element<T>* newElem = new Element<T>(value);
			LinkedListParent<T>::tail->setNext(newElem);
			newElem->setPrevious(LinkedListParent<T>::tail);
			LinkedListParent<T>::tail = LinkedListParent<T>::tail->getNext();
		}
		else
		{
			LinkedListParent<T>::tail = new Element<T>(value);
			LinkedListParent<T>::head = LinkedListParent<T>::tail;
		}
		LinkedListParent<T>::num = LinkedListParent<T>::num + 1;
		return LinkedListParent<T>::tail;
	}

	virtual Element<T>* pop()  //Удаляет последий элемент.
	{
		if (LinkedListParent<T>::num > 1)
		{
			Element<T>* temp = LinkedListParent<T>::tail;
			LinkedListParent<T>::tail = LinkedListParent<T>::tail->getPrevious();
			LinkedListParent<T>::tail->setNext(NULL);
			temp->setNext(NULL);
			temp->setPrevious(NULL);
			LinkedListParent<T>::num = LinkedListParent<T>::num - 1;
			return temp;
		}
		else
		{//Последний элемент (попадем при LinkedListParent<T>::num=1).
			cout << "\nList is empty";
			Element<T>* temp = LinkedListParent<T>::tail;
			LinkedListParent<T>::head = NULL;
			LinkedListParent<T>::tail = NULL;
			LinkedListParent<T>::num = LinkedListParent<T>::num - 1;
			temp->setNext(NULL);
			temp->setPrevious(NULL);
			return temp;
		}
	}

	virtual void filter(Stack<T>& base, bool (*ptr_func)(T))//Фильтруем список. Условие числа кратные 3.
	{
		ListIterator<T> iterator = this->LinkedListParent<T>::head;
		while (iterator != NULL)
		{
			if (ptr_func((*iterator).getValue()))
			{
				base.push((*iterator).getValue());
			}
			iterator++;
		}
	}
};

template <class T>
class D : public Stack<T>//Мой класс - стек.
{
public:
	D() : Stack<T>() { cout << "\nD constructor"; }
	virtual ~D() { cout << "\nD destructor"; }

	virtual Element<T>* push(T value) //Добавление элементов с сохранением отсортированности.
	{
		if (LinkedListParent<T>::num > 0)
		{

			ListIterator<T> iterator = LinkedListParent<T>::head;
			Element<T>* newElem = new Element<T>(value);
			while (iterator != NULL && (*iterator).getValue() <= newElem->getValue())
			{
				iterator++;
			}
			if (iterator == NULL)
			{
				LinkedListParent<T>::tail->setNext(newElem);
				newElem->setPrevious(LinkedListParent<T>::tail);
				LinkedListParent<T>::tail = LinkedListParent<T>::tail->getNext();
			}
			else if (iterator == LinkedListParent<T>::head)
			{
				LinkedListParent<T>::head->setPrevious(newElem);
				newElem->setNext(LinkedListParent<T>::head);
				LinkedListParent<T>::head = LinkedListParent<T>::head->getPrevious();
			}
			else
			{
				Element<T>* temp = (*iterator).getPrevious();
				newElem->setNext(temp->getNext());
				(*iterator).setPrevious(newElem);
				newElem->setPrevious(temp);
				temp->setNext(newElem);
			}
		}
		else
		{
			LinkedListParent<T>::tail = new Element<T>(value);
			LinkedListParent<T>::head = LinkedListParent<T>::tail;
		}
		LinkedListParent<T>::num = LinkedListParent<T>::num + 1;
		return LinkedListParent<T>::tail;
	}
};

int main()
{
	Stack<int> S;
	S.push(1);
	S.push(2);
	S.push(3);

	cout << endl << S;

	ListIterator<int> p;
	cout << endl << "Start with the head." << endl;
	p = S.getBegin();
	while (p != NULL)
	{
		cout << p;
		p++;
	}
	cout << endl << "Start with the tail." << endl;
	p = S.getEnd();
	while (p != NULL)
	{
		cout << p;
		p--;
	}

	D<int> A; //Элементы добавятся с сохранением отсортированности.
	A.push(1);
	A.push(7);
	A.push(-4);
	A.push(1);
	A.push(191);
	A.push(53);
	A.push(9);
	cout << endl << A;
}