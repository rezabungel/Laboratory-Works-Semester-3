// 2.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Постройте очередь с приоритетами на основе адаптера priority_queue. Типы
ключей и значений соответствуют пункту 2 задания №1. Выведите элементы
очереди в порядке убывания приоритета.

Вариант 18.
Таблица 2.1. Ключи и хранимая в ассоциативном контейнере map информация.

Ключ K: Фамилия и имя

Хранимая информация: «Школьник». V: дата рождения
*/



#include <iostream>
#include <string>
#include <queue>

using namespace std;

class schoolboy
{
private:
	string surname; //Фамилия ученика.
	int data; //Дата рождения (год)
public:
	schoolboy()
	{
		surname = "Фамилия?";
		data = 0;
	}
	schoolboy(string Xsurname, int Xdata) //Конструктор.
	{
		surname = Xsurname;
		data = Xdata;
	}
	//Сеттеры.
	void setsurname(string a) //Запись фамилии.
	{
		surname = a;
	}
	void setdata(int a) //Запись дату рождения (год).
	{
		data = a;
	}
	//Геттеры.
	string getsurname() //Выдать фамилию.
	{
		return surname;
	}
	int getdata() //Выдать дату рождения (год).
	{
		return data;
	}

	friend bool operator < (const schoolboy& a, const schoolboy& b)
	{
		if (a.surname < b.surname)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend bool operator > (const schoolboy& a, const schoolboy& b)
	{
		if (a.surname > b.surname)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend ostream& operator<< (ostream& ustream, schoolboy& obj); //Вывод информации.
};

ostream& operator<< (ostream& ustream, schoolboy& obj)
{
	{
		ustream << "Школьник:\t" << obj.getsurname() << " Дата рождения (год):\t" << obj.getdata();
		return ustream;
	}
}

template<typename T>
void print_queue(T& q) //После вывода наш контейнер останеться пустым.
{
	schoolboy a;
	while (!q.empty())
	{
		a = q.top();
		cout << a << endl;
		q.pop();
	}
	cout << '\n';
}



int main()
{
	setlocale(LC_ALL, "Russian");
	schoolboy A("Petrov", 2002);
	schoolboy B("Ivanov", 2005);
	schoolboy C("Sidorov", 2007);
	schoolboy D("Nikolaev", 2014);
	schoolboy E("Abramov", 2012);
	schoolboy F("Fedorov", 2001);
	schoolboy G("Kuznetsov", 1999);

	cout << "***************************************************************" << endl;
	schoolboy test;
	cout << "Test getsurname: " << test.getsurname() << endl;
	cout << "Test getdata: " << test.getdata() << endl;
	test.setsurname("ABC");
	test.setdata(3000);
	cout << "Test setsurname, setdata and output to the console: " << test << endl;
	cout << "***************************************************************" << endl << endl;

	priority_queue<schoolboy> q;
	q.push(A);
	q.push(B);
	q.push(C);
	q.push(D);
	q.push(E);
	q.push(F);
	q.push(G);

	print_queue(q);
}
