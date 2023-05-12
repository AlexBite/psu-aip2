#include <iostream>
#include <fstream>

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

    void insertFromFile(const std::string& filename)
    {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            std::cout << "Failed to open file." << std::endl;
            return;
        }

        int value;
        while (inputFile >> value)
        {
            insert(value);
        }

        inputFile.close();
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

        std::cout << "Element " << value << " added to the list." << std::endl;
    }

    void display()
    {
        if (head == nullptr)
        {
            std::cout << "The list is empty." << std::endl;
            return;
        }

        Node* current = head;
        std::cout << "Elements in the list: ";
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void displayElement(int value)
    {
        Node* current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                std::cout << "Element " << value << " found at address: " << current << std::endl;
                return;
            }
            current = current->next;
        }
        std::cout << "Element " << value << " not found in the list." << std::endl;
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
    LinkedList linkedList;
    int choice;

    while (true)
    {
        std::cout << "Select a menu item:" << std::endl;
        std::cout << "1. Forming a list (reading from a file)" << std::endl;
        std::cout << "2. Adding a list item from the keyboard" << std::endl;
        std::cout << "3. Displaying all elements of the list" << std::endl;
        std::cout << "4. Display the element with the given value" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string filename;
            int numNumbers;

            std::cout << "Enter the name of the file: ";
            std::cin >> filename;
            std::cout << "Enter the number of numbers: ";
            std::cin >> numNumbers;

            linkedList.insertFromFile(filename);
        }
        else if (choice == 2)
        {
            int value;

            std::cout << "Enter the value to be added: ";
            std::cin >> value;

            linkedList.insert(value);
        }
        else if (choice == 3)
        {
            linkedList.display();
        }
        else if (choice == 4)
        {
            int value;
            std::cout << "Enter the value to search for: ";
            std::cin >> value;

            linkedList.displayElement(value);
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
