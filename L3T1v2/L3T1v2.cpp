#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    double data;
    Node* prev;
    Node* next;

    Node(double value) : data(value), prev(nullptr), next(nullptr)
    {
    }
};

class LinkedList
{
private:
    Node* head;
    Node* tail;
    stack<double> dataStack;

public:
    LinkedList() : head(nullptr), tail(nullptr)
    {
    }

    void insertAtBeginning(double value)
    {
        Node* newNode = new Node(value);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        dataStack.push(value);
    }

    void insertAtEnd(double value)
    {
        Node* newNode = new Node(value);

        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        dataStack.push(value);
    }

    void insertAtMiddle(double value)
    {
        if (head == nullptr)
        {
            insertAtBeginning(value);
            return;
        }

        Node* current = head;
        int count = 0;

        while (current != nullptr)
        {
            count++;
            current = current->next;
        }

        int middleIndex = count / 2;

        current = head;
        for (int i = 1; i < middleIndex; i++)
        {
            current = current->next;
        }

        Node* newNode = new Node(value);
        newNode->prev = current;
        newNode->next = current->next;
        current->next->prev = newNode;
        current->next = newNode;

        dataStack.push(value);
    }

    void removeNumber(double value)
    {
        Node* current = head;

        while (current != nullptr)
        {
            if (current->data == value)
            {
                if (current == head)
                {
                    head = current->next;
                    if (head != nullptr)
                    {
                        head->prev = nullptr;
                    }
                }
                else if (current == tail)
                {
                    tail = current->prev;
                    if (tail != nullptr)
                    {
                        tail->next = nullptr;
                    }
                }
                else
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }

                delete current;
                break;
            }

            current = current->next;
        }

        // Удаление значения из стека
        stack<double> tempStack;
        while (!dataStack.empty())
        {
            double top = dataStack.top();
            dataStack.pop();
            if (top != value)
            {
                tempStack.push(top);
            }
        }
        while (!tempStack.empty())
        {
            dataStack.push(tempStack.top());
            tempStack.pop();
        }
    }

    void swapNumbers(double value1, double value2)
    {
        Node* node1 = nullptr;
        Node* node2 = nullptr;
        Node* current = head;

        while (current != nullptr)
        {
            if (current->data == value1)
            {
                node1 = current;
            }
            else if (current->data == value2)
            {
                node2 = current;
            }

            current = current->next;
        }

        if (node1 == nullptr || node2 == nullptr)
        {
            cout << "Одно или несколько значений не найдены в списке." << endl;
            return;
        }

        double tempData = node1->data;
        node1->data = node2->data;
        node2->data = tempData;
    }

    void displayNumbers()
    {
        Node* current = head;
        if (current == nullptr)
        {
            cout << "Список пуст.";
            return;
        }

        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }

    void displaySum()
    {
        double sum = 0;

        while (!dataStack.empty())
        {
            sum += dataStack.top();
            dataStack.pop();
        }

        cout << "Сумма всех элементов: " << sum << endl;
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
    LinkedList list;
    bool isExit = false;
    while (!isExit)
    {
        int choice = -1;
        cout << endl;
        cout << "Выберите пункт меню" << endl;
        cout << "1. Вывести содержимое списка" << endl;
        cout << "2. Вставить в начало" << endl;
        cout << "3. Вставить в середину" << endl;
        cout << "4. Вставить в конец" << endl;
        cout << "5. Удаление числа из списка" << endl;
        cout << "6. Перестановка двух чисел местами" << endl;
        cout << "7. Сумма всех элементов списка" << endl;
        cout << "0. Выход" << endl;
        cout << "Выбрать: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            {
                cout << "Содержимое: ";
                list.displayNumbers();
                break;
            }
        case 2:
            {
                double value;
                cout << "Введите число: ";
                cin >> value;
                list.insertAtBeginning(value);
                break;
            }
        case 3:
            {
                double value;
                cout << "Введите число: ";
                cin >> value;
                list.insertAtMiddle(value);
                break;
            }
        case 4:
            {
                double value;
                cout << "Введите число: ";
                cin >> value;
                list.insertAtEnd(value);
                break;
            }
        case 5:
            {
                double value;
                cout << "Введите число: ";
                cin >> value;
                list.removeNumber(value);
                break;
            }
        case 6:
            double value1;
            cout << "Введите значние первого числа: ";
            cin >> value1;

            double value2;
            cout << "Введите значение второго числа: ";
            cin >> value2;

            list.swapNumbers(value1, value2);
            break;
        case 7:
            list.displaySum();
            break;
        case 0:
            isExit = true;
            cout << "Работа завершена.";
            break;
        default:
            cout << "Введите номер пункта меню." << endl;
            break;
        }
    }

    return 0;
}
