// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <map>

using namespace std;
using namespace chrono;

// 1.1 Рекурсивный метод
int knapRec(int i, int W, const vector<int>& w, const vector<int>& v) {
    if (i < 0 || W == 0) return 0;
    if (w[i] > W) return knapRec(i - 1, W, w, v);
    return max(knapRec(i - 1, W, w, v), knapRec(i - 1, W - w[i], w, v) + v[i]);
}

// 1.2 Мемоизация
int knapMemo(int i, int W, const vector<int>& w, const vector<int>& v, vector<vector<int>>& memo) {
    if (i < 0 || W == 0) return 0;
    if (memo[i][W] != -1) return memo[i][W];
    if (w[i] > W) return memo[i][W] = knapMemo(i - 1, W, w, v, memo);
    return memo[i][W] = max(knapMemo(i - 1, W, w, v, memo), knapMemo(i - 1, W - w[i], w, v, memo) + v[i]);
}

// 1.3 Табличный метод
int knapTable(int W, const vector<int>& w, const vector<int>& v) {
    int n = w.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            if (w[i - 1] > j) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
        }
    }
    return dp[n][W];
}

// Восстановление предметов
vector<int> getItems(int W, const vector<int>& w, const vector<int>& v) {
    int n = w.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= W; j++)
            dp[i][j] = (w[i - 1] > j) ? dp[i - 1][j] : max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);

    vector<int> res;
    int j = W;
    for (int i = n; i > 0; i--) {
        if (dp[i][j] != dp[i - 1][j]) { res.push_back(i - 1); j -= w[i - 1]; }
    }
    reverse(res.begin(), res.end());
    return res;
}

// ==== ЧАСТЬ 2: LCS С ВЕСАМИ + ВЫВОД ТАБЛИЦЫ ===
void lcsWeighted(const string& X, const string& Y, map<char, int>& wt) {
    int m = X.size(), n = Y.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Заполнение таблицы
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) dp[i][j] = dp[i - 1][j - 1] + wt[X[i - 1]];
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Вывод таблицы ДП (для наглядности)
    cout << "\nТаблица ДП (LCS с весами):\n    ";
    for (char c : Y) cout << c << "  ";
    cout << "\n  ";
    for (int i = 0; i <= n; i++) cout << "---";
    cout << "\n";
    for (int i = 0; i <= m; i++) {
        if (i == 0) cout << "  ";
        else cout << X[i - 1] << " ";
        for (int j = 0; j <= n; j++) cout << dp[i][j] << "  ";
        cout << "\n";
    }

    // Восстановление подпоследовательности
    string res = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) { res = X[i - 1] + res; i--; j--; }
        else if (dp[i - 1][j] > dp[i][j - 1]) i--;
        else j--;
    }
    cout << "Максимальный вес LCS: " << dp[m][n] << "\nLCS: " << res << "\n";
}

int main() {
    setlocale(LC_ALL, "ru");

    // ===== ЧАСТЬ 1 =====
    cout << "=== ЧАСТЬ 1: РЮКЗАК ===\n";
    vector<int> w = { 2, 3, 4, 5 }, v = { 3, 4, 5, 8 };
    int W = 10, n = w.size();

    auto t1 = high_resolution_clock::now();
    int r1 = knapRec(n - 1, W, w, v);
    auto t2 = high_resolution_clock::now();
    auto timeRec = duration_cast<microseconds>(t2 - t1).count();

    vector<vector<int>> memo(n, vector<int>(W + 1, -1));
    t1 = high_resolution_clock::now();
    int r2 = knapMemo(n - 1, W, w, v, memo);
    t2 = high_resolution_clock::now();
    auto timeMemo = duration_cast<microseconds>(t2 - t1).count();

    t1 = high_resolution_clock::now();
    int r3 = knapTable(W, w, v);
    t2 = high_resolution_clock::now();
    auto timeTable = duration_cast<microseconds>(t2 - t1).count();

    cout << "Макс. стоимость: " << r1 << " / " << r2 << " / " << r3 << "\n";
    cout << "Время: рек=" << timeRec << " мкс, мемо=" << timeMemo << " мкс, табл=" << timeTable << " мкс\n";

    vector<int> items = getItems(W, w, v);
    cout << "Выбранные предметы: ";
    int totalW = 0;
    for (int idx : items) { cout << idx << " "; totalW += w[idx]; }
    cout << "\nВес: " << totalW << " (из " << W << ")\n";

    // ===== ЧАСТЬ 2 =====
    cout << "\n=== ЧАСТЬ 2: LCS С ВЕСАМИ ===\n";
    string X = "ABCBDAB", Y = "BDCABA";
    map<char, int> wt = { {'A', 2}, {'B', 3}, {'C', 5}, {'D', 1} };
    cout << "X: " << X << "\nY: " << Y << "\nВеса: A=2, B=3, C=5, D=1\n";
    lcsWeighted(X, Y, wt);

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
