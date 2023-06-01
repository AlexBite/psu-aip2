#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <cstdlib>

using namespace std;

void displayList(const list<int>& lst)
{
    for (auto it = lst.begin(); it != lst.end(); ++it)
        cout << *it << " ";

    cout << endl;
}

int main()
{
    system("chcp 65001");

    ifstream inputFile1("list1.txt");
    if (!inputFile1.is_open())
    {
        cerr << "Не удалось открыть файл первого списка." << endl;
        return 1;
    }

    int n;
    inputFile1 >> n;

    list<int> list1;

    for (int i = 0; i < n; ++i)
    {
        int number;
        inputFile1 >> number;
        list1.push_back(number);
    }

    inputFile1.close();

    ifstream inputFile2("list2.txt");
    if (!inputFile2.is_open())
    {
        cerr << "Не удалось открыть файл второго списка." << endl;
        return 1;
    }

    int m;
    inputFile2 >> m;

    list<int> list2;

    for (int i = 0; i < m; ++i)
    {
        int number;
        inputFile2 >> number;
        list2.push_back(number);
    }

    inputFile2.close();

    cout << "Первый список: ";
    displayList(list1);

    cout << "Второй список: ";
    displayList(list2);

    list1.sort();
    list2.sort();

    list1.merge(list2);

    cout << "Результат слияния: ";
    displayList(list1);

    return 0;
}
