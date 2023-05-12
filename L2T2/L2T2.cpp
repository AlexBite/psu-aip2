#include <iostream>
#include <vector>

std::vector<int> calculateMaxGold(const std::vector<int>& columns, int k) {
    int n = columns.size();
    std::vector<int> dp(n);
    std::vector<int> path(n);

    dp[0] = columns[0];  // Maximum gold on the first column
    path[0] = -1;  // Path to reach the first column

    for (int i = 1; i < n; i++) {
        dp[i] = columns[i];  // Maximum gold on the current column
        path[i] = i;  // Path to reach the current column

        // Check all previous reachable columns
        for (int j = 1; j <= k && i - j >= 0; j++) {
            // Calculate the maximum gold by considering the maximum gold on the previous reachable columns
            if (dp[i] < dp[i - j] + columns[i]) {
                dp[i] = dp[i - j] + columns[i];
                path[i] = i - j;
            }
        }
    }

    // Construct the path of column indices
    std::vector<int> goldPath;
    int index = n - 1;
    while (index != -1) {
        goldPath.push_back(index + 1);
        index = path[index];
    }

    // Reverse the path to get the correct order
    std::reverse(goldPath.begin(), goldPath.end());

    return goldPath;
}

int main() {
    int n;  // Number of columns
    int k;  // Maximum jump distance

    std::cout << "Enter the number of columns: ";
    std::cin >> n;

    std::cout << "Enter the maximum jump distance: ";
    std::cin >> k;

    std::vector<int> columns(n);
    std::cout << "Enter the number of gold coins on each column: ";
    for (int i = 0; i < n; i++) {
        std::cin >> columns[i];
    }

    std::vector<int> path = calculateMaxGold(columns, k);

    std::cout << "The Grasshopper should jump on the following columns to collect the most gold coins: ";
    for (int i = 0; i < path.size(); i++) {
        std::cout << path[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}