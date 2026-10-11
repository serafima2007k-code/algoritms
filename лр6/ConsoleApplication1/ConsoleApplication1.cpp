// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>
#include <algorithm>
#include <climits>
using namespace std;
using namespace chrono;

// ЧАСТЬ 1: РЕКУРСИЯ 
// Задача 1: Факториал
long long factorial(int n) {
    if (n <= 1) return 1;          // базовый случай
    return n * factorial(n - 1);   // шаг рекурсии
}

// Задача 2: Числа Фибоначчи
long long fib(int n) {
    if (n <= 1) return n;          // базовый случай
    return fib(n - 1) + fib(n - 2);
}

// Задача 3: Определитель 3×3
double determinant3x3(double m[3][3]) {
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
        - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
        + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

// Задача 4: Обход лабиринта с поиском кратчайшего пути
const int N = 5;
char maze[N][N] = {
    {'S', ' ', '#', ' ', '#'},
    {'#', ' ', '#', ' ', '#'},
    {' ', ' ', ' ', ' ', '#'},
    {'#', '#', ' ', ' ', '#'},
    {' ', ' ', ' ', 'F', '#'}
};
bool visited[N][N] = { false };
int minPath = INT_MAX;

void findShortest(int x, int y, int len) {
    if (x < 0 || x >= N || y < 0 || y >= N) return;
    if (maze[x][y] == '#' || visited[x][y]) return;

    if (maze[x][y] == 'F') {
        if (len < minPath) minPath = len;
        return;
    }

    visited[x][y] = true;
    findShortest(x + 1, y, len + 1);   // вниз
    findShortest(x - 1, y, len + 1);   // вверх
    findShortest(x, y + 1, len + 1);   // вправо
    findShortest(x, y - 1, len + 1);   // влево
    visited[x][y] = false;             // возврат
}

//  ЧАСТЬ 2: СОРТИРОВКИ 
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;   // оптимизация
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        if (minIdx != i) swap(arr[i], arr[minIdx]);
    }
}

// Измерение времени сортировки
template <typename Func>
long long measureTime(Func sortFunc, int src[], int n) {
    int* copy = new int[n];
    for (int i = 0; i < n; i++) copy[i] = src[i];

    auto start = high_resolution_clock::now();
    sortFunc(copy, n);
    auto end = high_resolution_clock::now();

    delete[] copy;
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    setlocale(LC_ALL, "ru");

    // Задача 1: Факториал
    cout << "Задача 1. Факториал:\n";
    for (int i = 0; i <= 10; i++)
        cout << "  " << i << "! = " << factorial(i) << "\n";

    // Задача 2: Числа Фибоначчи
    cout << "\nЗадача 2. Числа Фибоначчи:\n";
    for (int i = 0; i <= 15; i++)
        cout << "  fib(" << i << ") = " << fib(i) << "\n";

    // Задача 3: Определитель 3×3
    cout << "\nЗадача 3. Определитель 3x3:\n";
    double m[3][3] = {
        {2, 1, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    cout << "  Матрица:\n";
    for (int i = 0; i < 3; i++) {
        cout << "    ";
        for (int j = 0; j < 3; j++) cout << m[i][j] << " ";
        cout << "\n";
    }
    cout << "  Определитель = " << determinant3x3(m) << "\n";

    // Задача 4: Лабиринт
    cout << "\nЗадача 4. Обход лабиринта:\n";
    findShortest(0, 0, 0);
    if (minPath != INT_MAX)
        cout << "  Кратчайший путь: " << minPath << " шагов\n";
    else
        cout << "  Путь не найден\n";

    //  ЧАСТЬ 2: СОРТИРОВКИ
    cout << "\n СРАВНЕНИЕ СОРТИРОВОК \n\n";

    const int SIZE = 5000;
    int* arr = new int[SIZE];
    for (int i = 0; i < SIZE; i++) arr[i] = rand() % SIZE;

    cout << "Размер массива: " << SIZE << "\n\n";
    cout << "Пузырьковая: " << measureTime(bubbleSort, arr, SIZE) << " мкс\n";
    cout << "Вставками:   " << measureTime(insertionSort, arr, SIZE) << " мкс\n";
    cout << "Выбором:     " << measureTime(selectionSort, arr, SIZE) << " мкс\n";
    cout << "std::sort:   " << measureTime([](int a[], int n) { sort(a, a + n); }, arr, SIZE) << " мкс\n";

    delete[] arr;
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
