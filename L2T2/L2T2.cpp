#include <iostream>
#include <vector>

using namespace std;

vector<int> calculateMaxGold(const vector<int>& columns, int maxJumpDistance)
{
    int n = columns.size();
    vector<int> dp(n); // Макимальное количество золота на каждом столбце
    vector<int> path(n); // Значние = ссылка на предыдущую оптимальную кувшинку

    // Кузнечик всегда начинает с первого столбца
    dp[0] = columns[0];
    path[0] = -1;

    for (int i = 1; i < n; i++)
    {
        dp[i] = columns[i];
        path[i] = i;

        // Проверяем все предыдущие столбцы в пределах досигаемости
        for (int j = 1; j <= maxJumpDistance && i - j >= 0; j++)
        {
            // Высчитываем максимальное кол-во золота 
            if (dp[i] < dp[i - j] + columns[i])
            {
                dp[i] = dp[i - j] + columns[i];
                path[i] = i - j;
            }
        }
    }

    // Построить путь по индексам столбцов
    vector<int> goldPath;
    int index = n - 1;
    while (index != -1)
    {
        goldPath.push_back(index + 1);
        index = path[index];
    }

    // Развернуть путь, чтобы получить верный порядок
    reverse(goldPath.begin(), goldPath.end());

    return goldPath;
}

int main()
{
    system("chcp 65001");

    int n;
    cout << "Введите количество стобцов: ";
    cin >> n;

    int k;
    cout << "Введите максимальную длину прыжка: ";
    cin >> k;

    vector<int> columns(n);
    cout << "Введите количество золотых монет на каждом столбце: ";
    for (int i = 0; i < n; i++)
        cin >> columns[i];

    vector<int> path = calculateMaxGold(columns, k);

    cout << "Кузнечик должен прыгать по следующим колонкам, чтобы собрать максимальное количество золотых монет: ";
    for (int i : path)
        cout << i << " ";

    cout << endl;

    return 0;
}
