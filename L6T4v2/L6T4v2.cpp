#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

void displayPositions(const vector<int>& positions) {
    if (positions.empty()) {
        cout << "Буква не найдена." << endl;
        return;
    }

    cout << "Позиции буквы: ";
    for (auto it = positions.begin(); it != positions.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    system("chcp 65001");  // Set console code page to UTF-8

    int n;
    cout << "Введите количество символов: ";
    cin >> n;

    vector<char> characters(n);

    cout << "Введите символы: ";
    for (int i = 0; i < n; ++i) {
        cin >> characters[i];
    }

    char letter;
    cout << "Введите букву для поиска: ";
    cin >> letter;

    vector<int> positions;

    for (int i = 0; i < n; ++i) {
        if (characters[i] == letter) {
            positions.push_back(i);
        }
    }

    displayPositions(positions);

    return 0;
}
