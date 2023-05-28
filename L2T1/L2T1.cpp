#include <iostream>
#include <vector>

using namespace std;

void findNumberCombinations(const vector<int>& numbers, int target, vector<int>& currentCombination, int currentIndex) {
    // Если target равно 0, то комбинация найдена
    if (target == 0) {
        for (int num : currentCombination) {
            cout << num << " ";
        }
        cout << endl;
        return;
    }

    // Если прошли все числа, то значит комбинации не получилось
    if (currentIndex >= numbers.size() || target < 0) {
        return;
    }
    
    // Включить текущее число в комбинацию
    currentCombination.push_back(numbers[currentIndex]);
    findNumberCombinations(numbers, target - numbers[currentIndex], currentCombination, currentIndex + 1);

    // Исключить текущее число из комбинации
    currentCombination.pop_back();
    findNumberCombinations(numbers, target, currentCombination, currentIndex + 1);
}

int main() {
    system("chcp 65001");
    int target;
    cout << "Введите искомое число: ";
    cin >> target;

    int numCount;
    cout << "Задайте количество натуральных чисел: ";
    cin >> numCount;

    vector<int> numbers(numCount);
    cout << "Введите натуральные числа: ";
    for (int i = 0; i < numCount; i++) {
        cin >> numbers[i];
    }

    cout << "Возможные комбинации:" << endl;

    vector<int> currentCombination;
    findNumberCombinations(numbers, target, currentCombination, 0);

    return 0;
}