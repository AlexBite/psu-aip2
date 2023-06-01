#include <iostream>
#include <fstream>
#include <queue>
#include <cstdlib>

using namespace std;

void displayQueue(const queue<double>& q) {
    cout << "Очередь: ";
    queue<double> temp = q;
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;
}

double findMax(const queue<double>& q) {
    queue<double> temp = q;
    double maxElement = temp.front();
    temp.pop();
    while (!temp.empty()) {
        if (temp.front() > maxElement) {
            maxElement = temp.front();
        }
        temp.pop();
    }
    return maxElement;
}

int main() {
    system("chcp 65001");  // Set console code page to UTF-8

    ifstream inputFile("data.txt");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл." << endl;
        return 1;
    }

    queue<double> dataQueue;

    double number;
    while (inputFile >> number) {
        dataQueue.push(number);
    }

    inputFile.close();

    displayQueue(dataQueue);

    double maxElement = findMax(dataQueue);
    cout << "Максимальный элемент: " << maxElement << endl;

    return 0;
}
