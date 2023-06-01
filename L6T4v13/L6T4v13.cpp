#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

void displayArray(const vector<char>& arr) {
    cout << "Массив: ";
    for (const auto& element : arr) {
        cout << element << " ";
    }
    cout << endl;
}

int main() {
    system("chcp 65001");

    int n;
    cout << "Введите количество символов: ";
    cin >> n;

    vector<char> characters(n);

    cout << "Введите символы: ";
    for (int i = 0; i < n; ++i) {
        cin >> characters[i];
    }

    cout << "До удаления" << endl;
    displayArray(characters);

    int count = 0;
    for (auto it = characters.begin(); it != characters.end();) {
        ++count;
        if (count % 3 == 0) {
            it = characters.erase(it);
        } else {
            ++it;
        }
    }

    cout << "После удаления" << endl;
    displayArray(characters);

    return 0;
}
