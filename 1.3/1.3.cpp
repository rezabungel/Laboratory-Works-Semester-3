// 1.3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Святченко Артём Андреевич

/*
Постройте шаблон класса двусвязного списка путём наследования от
класса IteratedLinkedList. Реализуйте функции добавления элемента push() и
удаления элемента pop() в классе-наследнике D (для четных вариантов D –
Стек, для нечетных – Очередь) согласно схеме: для класса Стек элементы
добавляются в конец, извлекаются с конца; для класса Очередь элементы
добавляются в конец, извлекаются с начала. Постройте наследник класса D.
Переопределите функцию добавления нового элемента таким образом, чтобы
контейнер оставался упорядоченным. Реализуйте функцию filter() из пункта
1.

Вариант 18 - значит Стек.
*/

#include <iostream>
#include <fstream>

using namespace std;

template <class T>
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
		prev - prev_ptr;
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

template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}
	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";
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
			ptr = ptr.getNext();
		}
		return *this;
	}
	ListIterator& operator++(int v)
	{
		if (ptr != NULL)
		{
			ptr = ptr.getNext();
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

};

//Класс итерируемый список - наследник связного списка, родитель для класс Стек.
template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }
	virtual ~IteratedLinkedList() { cout << "\nIteratedLinkedList destructor"; }

	ListIterator<T> iterator;

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
class Stack : public LinkedListParent<T>//Мой класс - стек.
{//Стек элементы добавляются в конец, извлекаются с конца.
public:
	Stack() : LinkedListParent<T>() { cout << "\nStack constructor"; }
	virtual ~Stack() { cout << "\nStack destructor"; }


	virtual Element<T>* push(T value) override
	{
		if (num > 0)
		{
			Element<T>* newElem = new Element<T>();
			tail->setNext(newElem);
			newElem->setPrevious(tail);
			//tail=tail->getNext();  //LinkesListParent::tail... - на новых компиляторах...
			LinkesListParent::tail = tail->getNext();
		}
		else
		{





		}
		num = num + 1;
		return tail;
	}

	//pop()
	//filter()

};


int main()
{
	cout << "Hello World!\n";
}

