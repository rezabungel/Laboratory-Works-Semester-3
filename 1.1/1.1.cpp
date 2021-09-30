// 1.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Святченко Артём Андреевич

/*
Постройте связный список (используйте класс list библиотеки STL), 
который содержит объекты указанного в таблице 1.1 типа T. Постройте 
функции добавления push() и удаления pop() элементов таким образом, чтобы 
список оставался отсортированным при выполнении этих операций 
(допустимо удаление из начала контейнера, с конца и из произвольного 
места). Постройте функцию filter(), которая принимает предикат P (см. 
таблицу 1.1) и возвращает новый список с объектами, для которых предикат 
принимает истинное значение. Постройте функцию вывода содержимого 
списка с помощью итераторов. 
Примечание: В этом задании не требуется создавать класс списка, нужно 
использовать класс list из библиотеки STL и написать отдельно требуемые 
функции (не методы класса).

Таблица 1.1 Вариант 18.

Тип T 
int

Условие предиката P.
Только числа, кратные 3.
*/

#include <list>
#include <iostream>

using namespace std;

bool conditions(int value) //Проверка на кратность 3. Если да, то кратное. Если нет, то не кратное.
{
    return (value % 3 == 0);
}

template<class T>
void push(list<T>& lst, T element)//Вставка элемента с сохранением отсортированности.
{
    typename list<T>::iterator p = lst.begin();
    while (p != lst.end() && *p <= element)//В итераторе нельзя одновременно идти и добавлять(удалять) значения.
    {
        p++;
    }
    //Проверяем какое из условий нарушилось.
    if (p == lst.end())
    {
        lst.push_back(element);
    }
    else
    {
        lst.insert(p, element);
    }
}

template<class T>
void pop(list<T>& lst, T nomer)
{
    int counter = 1;
    typename list<T>::iterator p = lst.begin();
    while (p != lst.end())
    {
        if (counter == nomer)
        {
            break;
        }
        p++;
        counter++;
    }
    lst.erase(p);
}

template<class T>
list<T> filter(list<T> base, bool (*ptr)(T))//Фильтруем список. Условие числа кратные 3.
{
    list<T> result;
    typename list<T>::iterator p = base.begin();
    while (p != base.end())
    {
        if (ptr(*p))
        {
            result.push_back(*p);
        }
        p++;
    }
    return (result);
}

template<class T>
void print(list<T> lst)//Вывод списка.
{
    typename list<T>::iterator p = lst.begin();
    while (p != lst.end())
    {
        //Перемещение по контейнеру с помощью указателя.
        cout << *p << " ";
        p++;
    }
    cout << endl;
}



int main()
{
    list<int> one;
    for (int i = 0; i < 10; i = i + 1)
    {
        one.push_back(i);
    }
    cout << "Start list: ";
    print(one);

    cout << endl;

    int a = 0;
    cout << "Test function push." << endl;
    cout << "What number do you want to insert. a=";
    cin >> a;
    cout << "ok." << endl;
    push(one, a);
    print(one); //Вывод списка.

    cout << endl;

    int b = 0;
    cout << "List size : " << one.size() << endl;
    cout << "Kakoy po schetu element vy khotite udalit'.(chisla ot 1 do " << one.size() << ") b=";
    cin >> b;
    while (b<1 || b>one.size())
    {
        cout << "Byl vveden ne pravil'nyy nomer elementa." << endl;
        cout << "Poprobuyte yeshcho raz." << endl;
        cout << "Mozhno vvodit' tol'ko сhisla ot 1 do " << one.size() << ". b = ";
        cin >> b;
    }
    cout << "Ok." << endl;
    pop(one, b);
    print(one); //Вывод списка.

    cout << endl;

    list<int> filtered;
    filtered = filter(one, conditions);
    cout << "Filtration conditions: chisla kratnyye 3." << endl;
    cout << "Filtered list: ";
    print(filtered); //Вывод списка.

    return 0;
}