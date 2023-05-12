#include <iostream>
#include <fstream>

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insertNode(root, value);
    }

    Node* insertNode(Node* node, int value) {
        if (node == nullptr) {
            node = new Node(value);
        } else if (value < node->key) {
            node->left = insertNode(node->left, value);
        } else if (value > node->key) {
            node->right = insertNode(node->right, value);
        }
        return node;
    }

    void displaySideways() {
        sideways(root, 0);
    }

    void displayParentheses() {
        displayParenthesesHelper(root);
        std::cout << std::endl;
    }

    Node* search(int value) {
        return searchNode(root, value);
    }

    Node* searchNode(Node* node, int value) {
        if (node == nullptr || node->key == value) {
            return node;
        } else if (value < node->key) {
            return searchNode(node->left, value);
        } else {
            return searchNode(node->right, value);
        }
    }

private:
    void sideways(Node* node, int level) {
        if (node != nullptr) {
            sideways(node->right, level + 1);

            for (int i = 0; i < level; i++) {
                std::cout << "    ";
            }
            std::cout << node->key << std::endl;

            sideways(node->left, level + 1);
        }
    }

    void displayParenthesesHelper(Node* node) {
        if (node != nullptr) {
            std::cout << "(";
            std::cout << node->key;
            if (node->left != nullptr || node->right != nullptr) {
                displayParenthesesHelper(node->left);
                std::cout << " ";
                displayParenthesesHelper(node->right);
            }
            std::cout << ")";
        }
    }
};

int main() {
    BinarySearchTree bst;
    std::ifstream inputFile("numbers.txt");

    if (!inputFile.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return 0;
    }

    int value;
    while (inputFile >> value) {
        bst.insert(value);
    }

    inputFile.close();

    std::cout << "Binary Search Tree (Sideways):" << std::endl;
    bst.displaySideways();

    std::cout << "Binary Search Tree (Parentheses): ";
    bst.displayParentheses();

    int searchValue;
    std::cout << "Enter the value to search for: ";
    std::cin >> searchValue;

    Node* result = bst.search(searchValue);
    if (result != nullptr) {
        std::cout << "Node address of key " << searchValue << ": " << result << std::endl;
    } else {
        std::cout << "Key " << searchValue << " not found in the tree." << std::endl;
    }

    return 0;
}
