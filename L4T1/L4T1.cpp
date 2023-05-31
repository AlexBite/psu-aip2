#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr)
    {
    }
};

class BinarySearchTree
{
private:
    Node* root;

public:
    BinarySearchTree() : root(nullptr)
    {
    }

    void add(int value)
    {
        root = addNode(root, value);
    }

    Node* addNode(Node* node, int value)
    {
        if (node == nullptr)
        {
            node = new Node(value);
        }
        else if (value < node->key)
        {
            node->left = addNode(node->left, value);
        }
        else if (value > node->key)
        {
            node->right = addNode(node->right, value);
        }
        return node;
    }

    // Вывод боком
    void printSideways()
    {
        sideways(root, 0);
    }

    // Вывод со скобками
    void printParentheses()
    {
        displayParenthesesHelper(root);
        cout << endl;
    }

    Node* search(int value)
    {
        return searchNode(root, value);
    }

    Node* searchNode(Node* node, int value)
    {
        if (node == nullptr || node->key == value)
            return node;

        if (value < node->key)
            return searchNode(node->left, value);

        return searchNode(node->right, value);
    }

private:
    // Вывод боком (обратный обход)
    void sideways(Node* node, int level)
    {
        if (node == nullptr)
            return;

        sideways(node->right, level + 1);

        for (int i = 0; i < level; i++)
        {
            cout << "    ";
        }
        cout << node->key << endl;

        sideways(node->left, level + 1);
    }

    void displayParenthesesHelper(Node* node)
    {
        if (node == nullptr)
            return;

        cout << "(";
        cout << node->key;
        if (node->left != nullptr || node->right != nullptr)
        {
            displayParenthesesHelper(node->left);
            cout << " ";
            displayParenthesesHelper(node->right);
        }
        cout << ")";
    }
};

int main()
{
    system("chcp 65001");
    BinarySearchTree bst;
    ifstream inputFile("numbers.txt");

    if (!inputFile.is_open())
    {
        cout << "Не удалось открыть файл." << endl;
        return 0;
    }

    int value;
    while (inputFile >> value)
        bst.add(value);

    inputFile.close();

    cout << "Ввывод боком: " << endl;
    bst.printSideways();

    cout << "Вывод со скобками: ";
    bst.printParentheses();

    int searchValue;
    cout << "Введит значение для поиска: ";
    cin >> searchValue;

    Node* result = bst.search(searchValue);
    if (result != nullptr)
    {
        cout << "Адрес узла со значнием " << searchValue << ": " << result << endl;
    }
    else
    {
        cout << "Значение " << searchValue << " не найдено." << endl;
    }

    return 0;
}
