#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
    int data;
    Node* next;
};

class LinkedList
{
private:
    Node* head;

public:
    LinkedList() : head(nullptr)
    {
    }

    void insert(int value)
    {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }

        cout << "Элемент со значением " << value << " добавлен в список." << endl;
    }

    void insertFromFile(const string& filename, int numsCount)
    {
        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            cout << "Не удалось открыть файл." << endl;
            return;
        }

        int value;
        for (int i = 0; i < numsCount; i++)
        {
            inputFile >> value;
            insert(value);
        }

        inputFile.close();
    }

    void displayElement(int value)
    {
        Node* current = head;
        int index = 0;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                cout << "Элемент со значнием " << value << " найден по индексу: " << index + 1 << endl;
                return;
            }
            current = current->next;
            index++;
        }
        cout << "Элемент со значнием " << value << " не найден." << endl;
    }

    void display()
    {
        if (head == nullptr)
        {
            cout << "Список пуст." << endl;
            return;
        }

        Node* current = head;
        cout << "Содержимое списка: ";
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~LinkedList()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main()
{
    system("chcp 65001");
    LinkedList linkedList;
    int choice;

    while (true)
    {
        cout << "Выберите пункт меню" << endl;
        cout << "1. Загрузить числа из файла" << endl;
        cout << "2. Добавить число вручную" << endl;
        cout << "3. Отобразить все элементы списка" << endl;
        cout << "4. Отобразить элемент с заданным значнием" << endl;
        cout << "5. Выход" << endl;
        cout << "Выбрать: ";
        cin >> choice;

        if (choice == 1)
        {
            string filename;
            cout << "Введите название файла: ";
            cin >> filename;

            int numsCount;
            cout << "Введите количество чисел: ";
            cin >> numsCount;

            linkedList.insertFromFile(filename, numsCount);
        }
        else if (choice == 2)
        {
            int value;

            cout << "Введите значние: ";
            cin >> value;

            linkedList.insert(value);
        }
        else if (choice == 3)
        {
            linkedList.display();
        }
        else if (choice == 4)
        {
            int value;
            cout << "Введите искомое значние: ";
            cin >> value;

            linkedList.displayElement(value);
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cout << "Введите число соответствующее одному из пунктов меню." << endl;
        }
    }

    return 0;
}
