#include <iostream>
#include <vector>

void findNumberCombinations(const std::vector<int>& numbers, int target, std::vector<int>& currentCombination, int currentIndex) {
    // Base case: If target becomes 0, we have found a valid combination
    if (target == 0) {
        // Print the current combination
        for (int num : currentCombination) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        return;
    }

    // Base case: If currentIndex reaches the end of the numbers vector or target becomes negative,
    // we cannot form a valid combination
    if (currentIndex >= numbers.size() || target < 0) {
        return;
    }

    // Recursive case:
    // 1. Include the current number in the combination
    currentCombination.push_back(numbers[currentIndex]);
    findNumberCombinations(numbers, target - numbers[currentIndex], currentCombination, currentIndex + 1);

    // 2. Exclude the current number from the combination
    currentCombination.pop_back();
    findNumberCombinations(numbers, target, currentCombination, currentIndex + 1);
}

void findAllCombinations(const std::vector<int>& numbers, int target) {
    std::vector<int> currentCombination;
    findNumberCombinations(numbers, target, currentCombination, 0);
}

int main() {
    int target;
    std::cout << "Enter the target number: ";
    std::cin >> target;

    int numCount;
    std::cout << "Enter the number of natural numbers: ";
    std::cin >> numCount;

    std::vector<int> numbers(numCount);
    std::cout << "Enter the natural numbers: ";
    for (int i = 0; i < numCount; i++) {
        std::cin >> numbers[i];
    }

    std::cout << "Possible combinations:" << std::endl;
    findAllCombinations(numbers, target);

    return 0;
}