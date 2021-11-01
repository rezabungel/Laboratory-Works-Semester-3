// 2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
Постройте сбалансированное дерево (используйте класс map
библиотеки STL), которое содержит значения V по ключам K (таблица 2.1).
Постройте функции поиска элемента по значению и по ключу. Постройте
функцию вывода содержимого дерева с помощью итераторов. Постройте
функцию filter(), которая принимает предикат P и возвращает новое дерево с
объектами, для которых предикат принимает истинное значение (для всех
вариантов условие предиката: значение поля V выше некоторого порога
threshold, в случае хранения нескольких полей достаточно проверить одно из
них).

Примечание: В этом задании не требуется создавать класс дерева, нужно
использовать класс map из библиотеки STL и написать отдельно требуемые
функции (не методы класса).

Вариант 18.
Таблица 2.1. Ключи и хранимая в ассоциативном контейнере map информация.

Ключ K: Фамилия и имя

Хранимая информация: «Школьник». V: дата рождения
*/

//красно-черное (сблансированное) дерево map, есть интерфейс доступа к значению по ключу

#include <iostream>
#include <string>
#include <map>

using namespace std;

bool conditions(int value) //Проверка. Отбор тех, кому больше или сейчас 18. (2021-18=2003)
{
	if (value <= 2003)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T1, class T2>
typename map<T1, T2>::iterator find_by_key(map<T1, T2>& people, T1 key)
{
	typename map<T1, T2>::iterator it = people.find(key);
	if (it != people.end())
	{
		cout << "The element with key '" << key << "' is found" << endl;
		return it;
	}
	else
	{
		cout << "The element with key '" << key << "' was not found" << endl;
		return it;
	}
}

template<class T1, class T2>
typename map<T1, T2>::iterator find_by_value(map<T1, T2>& people, T2 value)
{
	typename map<T1, T2>::iterator it = people.begin();
	while (it != people.end() && it->second != value)
	{
		it++;
	}
	if (it == people.end())
	{
		cout << "The element with value '" << value << "' was not found" << endl;
		return it;
	}
	else
	{
		cout << "The element with value '" << value << "' is found" << endl;
		return it;
	}
}

template<class T1, class T2>
map<T1, T2> filter(map<T1, T2>& people, bool (*ptr)(T2)) //Фильтруем дерево. Условие люди, которым 18 или больше.
{
	map<T1, T2> result;
	typename map<T1, T2>::iterator it = people.begin();
	while (it != people.end())
	{
		if (ptr(it->second))
		{
			result[it->first] = it->second;
		}
		it++;
	}
	return result;
}

template<class T1, class T2>
void print(map<T1, T2>& people)
{
	cout << "\nMap:\n";
	typename map<T1, T2>::iterator it = people.begin();
	while (it != people.end())
	{
		cout << "Key: " << it->first << ", value: " << it->second << "\n";
		it++;
	}
}



int main()
{
	map<string, int> schoolboy;
	schoolboy["Petrov"] = 2002;
	schoolboy["Ivanov"] = 2005;
	schoolboy["Sidorov"] = 2007;
	schoolboy["Nikolaev"] = 2014;
	schoolboy["Abramov"] = 2012;
	schoolboy["Fedorov"] = 2001;
	schoolboy["Kuznetsov"] = 1999;
	print(schoolboy);

	//Для проверки поиска по ключу и поиска по значению.
	map<string, int> search_result;
	string key = "Abramov";
	int value = 2002;
	map<string, int>::iterator it_find;

	cout << "\nTest find_by_key." << endl;

	it_find = find_by_key(schoolboy, key);
	if (it_find != schoolboy.end())
	{
		search_result[it_find->first] = it_find->second;
	}
	key = "AAA"; //Ищем теперь по другому ключу.
	it_find = find_by_key(schoolboy, key);
	if (it_find != schoolboy.end())
	{
		search_result[it_find->first] = it_find->second;
	}

	cout << "\nTest find_by_value." << endl;

	it_find = find_by_value(schoolboy, value);
	if (it_find != schoolboy.end())
	{
		search_result[it_find->first] = it_find->second;
	}
	value = 1010;//Ищем теперь по другому значению.
	it_find = find_by_value(schoolboy, value);
	if (it_find != schoolboy.end())
	{
		search_result[it_find->first] = it_find->second;
	}

	print(search_result);

	cout << "\nTest filter" << endl;
	map<string, int> adults; //adults - взрослые.
	adults = filter(schoolboy, conditions);
	print(adults);
}





/*
||||||||||||||||||||||||||||||||||||||||||||||||||
Разные способы добавления элементов в контейнер.

	marks.insert(pair<string, int>("A", 10));

	marks.insert(make_pair("B", 15));

	marks.emplace("C", 20);

	marks["D"] = 12;

Последний способ позволяет не только добавить элемент, но и изменить его значение. Т.е. он сначала проверяет если элемент в контейнере, если да, то меняет его значение, если элемента нет, то добавляет его в контейнер.


||||||||||||||||||||||||||||||||||||||||||||||||||
Поиск в контейнерe. Поиск осуществляется по ключу.

map<string, int>::iterator it = marks.find("ключ");

Результат метода find - это итератор, который указывает на пару ключ-значение в map, в случае если он смог найти элемент с таким ключом.
Если элемент найден не будет, то итератор будет указывать в область памяти за контейнером (в никуда) или что то же самое marks.end()

	map<string, int>::iterator it = marks.find("A");
	if (it != marks.end())                            //можно написать if (marks.find("A") != marks.end())
	{
		cout << "Element found" << endl;
	}
	else
	{
		cout << "Element not found" << endl;
	}


||||||||||||||||||||||||||||||||||||||||||||||||||
Удаление элементов из контейнер. (Удаление по ключу)

marks.erase("ключ");


||||||||||||||||||||||||||||||||||||||||||||||||||
*/



/*
	(Ваш код)

	//итератор пробегает по map
	map<string, int>::iterator it_m = marks.begin();
		while (it_m != marks.end())
	{
		//перемещение по списку с помощью итератора, нет операции [i]
		cout << "Key: " << it_m->first << ", value: " << it_m->second << "\n";
		it_m++;
	}
*/