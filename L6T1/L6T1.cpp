#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

void displayVector(const vector<int>& arr) {
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    system("chcp 65001");

    ifstream inputFile("numbers.txt");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл." << endl;
        return 1;
    }

    int n;
    inputFile >> n;

    vector<int> numbers(n);

    for (int i = 0; i < n; ++i) {
        inputFile >> numbers[i];
    }

    inputFile.close();

    int evenCount = 0;
    int oddCount = 0;

    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it % 2 == 0) {
            evenCount++;
        } else {
            oddCount++;
        }
    }

    cout << "Перед сортировкой: ";
    displayVector(numbers);

    sort(numbers.rbegin(), numbers.rend());

    cout << "После сортировки: ";
    displayVector(numbers);

    cout << "Количество четных элементов: " << evenCount << endl;
    cout << "Количество нечетных элементов: " << oddCount << endl;

    return 0;
}
