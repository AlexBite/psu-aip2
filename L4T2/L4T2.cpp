#include <iostream>
#include <fstream>
#include <vector>

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

class BalancedTree
{
private:
    Node* root;

public:
    BalancedTree() : root(nullptr)
    {
    }

    void insert(int value)
    {
        root = insertNode(root, value);
    }

    Node* insertNode(Node* node, int value)
    {
        if (node == nullptr)
        {
            node = new Node(value);
        }
        else if (value < node->key)
        {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->key)
        {
            node->right = insertNode(node->right, value);
        }
        return node;
    }

    void displayForwardTraversal()
    {
        forwardTraversal(root);
        cout << endl;
    }

    void displayBackwardTraversal()
    {
        backwardTraversal(root);
        cout << endl;
    }

    void displayEndTraversal()
    {
        endTraversal(root);
        cout << endl;
    }

    void remove(int value)
    {
        root = removeNode(root, value);
    }

private:
    void forwardTraversal(Node* node)
    {
        if (node != nullptr)
        {
            cout << node->key << " ";
            forwardTraversal(node->left);
            forwardTraversal(node->right);
        }
    }

    void backwardTraversal(Node* node)
    {
        if (node != nullptr)
        {
            backwardTraversal(node->left);
            backwardTraversal(node->right);
            cout << node->key << " ";
        }
    }

    void endTraversal(Node* node)
    {
        if (node != nullptr)
        {
            endTraversal(node->left);
            cout << node->key << " ";
            endTraversal(node->right);
        }
    }

    Node* removeNode(Node* node, int value)
    {
        if (node == nullptr)
            return nullptr;

        if (value < node->key)
        {
            node->left = removeNode(node->left, value);
        }
        else if (value > node->key)
        {
            node->right = removeNode(node->right, value);
        }
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr)
            {
                Node* temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr)
            {
                Node* temp = node;
                node = node->left;
                delete temp;
            }
            else
            {
                Node* minRight = findMin(node->right);
                node->key = minRight->key;
                node->right = removeNode(node->right, minRight->key);
            }
        }

        return node;
    }

    Node* findMin(Node* node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }
};

int main()
{
    system("chcp 65001");
    BalancedTree mht;
    ifstream inputFile("numbers.txt");

    if (!inputFile.is_open())
    {
        cout << "Не удалось открыть файл." << endl;
        return 0;
    }

    cout << "Исходная последовательность: ";
    int value;
    while (inputFile >> value)
    {
        cout << value << " ";
        mht.insert(value);
    }
    cout << endl;

    inputFile.close();

    cout << "Прямой обход: ";
    mht.displayForwardTraversal();
    cout << "Обратный обход: ";
    mht.displayBackwardTraversal();

    cout << "Концевой обход: ";
    mht.displayEndTraversal();

    int removeValue;
    cout << "Введите значение для удаления из дерева: ";
    cin >> removeValue;

    mht.remove(removeValue);
    cout << "Узел со значением " << removeValue << " удалеён." << endl;

    cout << "Прямой обход после удаления: ";
    mht.displayForwardTraversal();

    return 0;
}
