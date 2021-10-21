// 1.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Святченко Артём Андреевич

/*Заполните список из пункта 1 объектами класса С(таблица 1.2),
сохраняя убывание по приоритету : полю или группе полей, указанных в
варианте.Функция pop() должна удалять объект из контейнера и возвращать
как результат объект с наибольшим приоритетом(определяется по полям,
указанным в третьем столбце таблицы 1.2: больший приоритет имеет объект
с большим значением первого поля; если значение первого поля совпадает,
то сравниваются значения второго поля и так далее).Если больший
приоритет имеют объекты с меньшим значением поля(упорядоченность по
возрастанию), это указано в скобках.

Пример из варианта 1: объекты недвижимости сортируются по убыванию
цены.Если цена совпадает, то сравниваем по адресу, но для адреса уже
используется упорядочение по возрастанию(“меньший” адрес - больший
приоритет, строки сравниваются в лексикографическом порядке, “как в
словаре”).

Таблица 1.2 Вариант 18.

Класс С
«Школьник».
Минимальный набор полей: фамилия, имя, пол, класс, дата рождения, адрес.

Приоритет
Класс; дата рождения (по возрастанию); фамилия и имя (по возрастанию).
*/

#include <list>
#include <iostream>
#include <string>

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
	//Приоритет: Класс (по убыванию); дата рождения (по возрастанию); фамилия и имя(по возрастанию).
	bool operator > (const school& other)
	{
		if (this->classroom < other.classroom)
		{
			return true;
		}
		else if (this->classroom == other.classroom)
		{
			if (this->data > other.data)
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

template<class  T>
void push(list<T>& L, T element)//Вставка элемента с сохранением приоритета.
{

	auto it = L.begin();
	while (it != L.end())
	{
		if (*it > element)
		{
			L.insert(it, element);
			break;
		}
		*it++;
	}
	if (it == L.end())//Если такое место не нашлось, то добавляем в конец списка.
	{
		L.push_back(element);
	}
}

template<class  T>
T pop(list<T>& L)//Удаляет элемент с наибольшим приоритетом. Такой элемент хранится в начале списка. Возвращаться будет удаленный элемент.
{
	auto it = L.begin();
	school save(*it);
	L.erase(it);
	return save;
}

template<class  T>
void printlist(list<T>& L)
{
	auto it = L.begin();
	while (it != L.end())
	{
		cout << *it << endl;
		*it++;
	}
}



int main()
{
	setlocale(LC_ALL, "Russian");
	list<school> people;
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

	//Добавление учеников в двусвязный список с сохранением приоритета.
	//Приоритет: Класс (по убыванию); дата рождения (по возрастанию); фамилия и имя(по возрастанию).
	people.push_back(A1);
	push(people, A2);
	push(people, A3);
	push(people, A4);
	push(people, A5);
	push(people, A6);
	push(people, A7);
	push(people, A8);
	push(people, A9);
	push(people, A10);
	printlist(people);

	cout << endl << endl << endl;
	school test;
	test = pop(people);
	cout << test;
	cout << endl << endl << endl;
	cout << "Список после удаления:" << endl;
	printlist(people);

	return 0;
}