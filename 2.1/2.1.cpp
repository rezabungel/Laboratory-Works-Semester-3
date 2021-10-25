﻿// 2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
#include <map>

using namespace std;

int main()
{
	map<string, int> marks;
	marks["Petrov"] = 5;
	marks["Ivanov"] = 4;
	marks["Sidorov"] = 5;
	marks["Nikolaev"] = 3;
	marks["Abramov"] = 4;
	marks["Fedorov"] = 5;
	marks["Kuznetsov"] = 4;
	cout << "\nMap:\n";
	//итератор пробегает по map
	map<string, int>::iterator it_m = marks.begin();
	while (it_m != marks.end())
	{
		//перемещение по списку с помощью итератора, нет операции [i]
		cout << "Key: " << it_m->first << ", value: " << it_m->second << "\n";
		it_m++;
	}
}