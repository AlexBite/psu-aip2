#include <iostream>
#include <fstream>
#include <vector>

struct Node
{
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr)
    {
    }
};

class MinimumHeightTree
{
private:
    Node* root;

public:
    MinimumHeightTree() : root(nullptr)
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
        std::cout << std::endl;
    }

    void displayBackwardTraversal()
    {
        backwardTraversal(root);
        std::cout << std::endl;
    }

    void displayEndTraversal()
    {
        endTraversal(root);
        std::cout << std::endl;
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
            std::cout << node->key << " ";
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
            std::cout << node->key << " ";
        }
    }

    void endTraversal(Node* node)
    {
        if (node != nullptr)
        {
            endTraversal(node->left);
            std::cout << node->key << " ";
            endTraversal(node->right);
        }
    }

    Node* removeNode(Node* node, int value)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

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
    MinimumHeightTree mht;
    std::ifstream inputFile("numbers.txt");

    if (!inputFile.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        return 0;
    }

    int value;
    while (inputFile >> value)
    {
        mht.insert(value);
    }

    inputFile.close();

    std::cout << "Forward Traversal: ";
    mht.displayForwardTraversal();
    std::cout << "Backward Traversal: ";
    mht.displayBackwardTraversal();

    std::cout << "End Traversal: ";
    mht.displayEndTraversal();

    int removeValue;
    std::cout << "Enter the value to remove from the tree: ";
    std::cin >> removeValue;

    mht.remove(removeValue);
    std::cout << "Value " << removeValue << " has been removed from the tree." << std::endl;

    std::cout << "Forward Traversal after removal: ";
    mht.displayForwardTraversal();

    return 0;
}
