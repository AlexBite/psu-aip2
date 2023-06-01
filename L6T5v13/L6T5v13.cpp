#include <iostream>
#include <fstream>
#include <stack>
#include <cstdlib>

using namespace std;

void displayStack(const stack<int>& s) {
    cout << "Стек: ";
    stack<int> temp = s;
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
}

int countNegativeElements(const stack<int>& s) {
    stack<int> temp = s;
    int count = 0;
    while (!temp.empty()) {
        if (temp.top() < 0) {
            count++;
        }
        temp.pop();
    }
    return count;
}

int main() {
    system("chcp 65001");

    ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл." << endl;
        return 1;
    }

    stack<int> dataStack;

    int number;
    while (inputFile >> number) {
        dataStack.push(number);
    }

    inputFile.close();

    displayStack(dataStack);

    int negativeCount = countNegativeElements(dataStack);
    cout << "Количество отрицательных элементов: " << negativeCount << endl;

    return 0;
}
