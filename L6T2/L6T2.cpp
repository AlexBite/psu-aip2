#include <iostream>
#include <fstream>
#include <list>
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

    ifstream inputFile("numbers.txt");
    if (!inputFile.is_open())
    {
        cerr << "Не удалось открыть файл." << endl;
        return 1;
    }

    int n;
    inputFile >> n;

    list<int> numbers;

    for (int i = 0; i < n; ++i)
    {
        int number;
        inputFile >> number;
        numbers.push_back(number);
    }

    inputFile.close();

    cout << "До удаления: ";
    displayList(numbers);

    cout << "Введите число, которое нужно удалить из списка: ";
    int a;
    cin >> a;

    numbers.remove(a);

    cout << "После удаления: ";
    displayList(numbers);

    return 0;
}
