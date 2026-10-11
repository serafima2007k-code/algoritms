// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

// БЫСТРАЯ СОРТИРОВКА (рекурсивная) 
int partition(int a[], int low, int high) {
    int pivot = a[high], i = low - 1;   // опорный — последний элемент
    for (int j = low; j < high; j++)
        if (a[j] <= pivot)              
            swap(a[++i], a[j]);         
    swap(a[i + 1], a[high]);           
    return i + 1;                       
}

// Рекурсивная быстрая сортировка
void quickRec(int a[], int low, int high) {
    if (low < high) {                   
        int p = partition(a, low, high);
        quickRec(a, low, p - 1);       
        quickRec(a, p + 1, high);       
    }
}

// БЫСТРАЯ СОРТИРОВКА (итеративная с ручным стеком)
void quickIter(int a[], int low, int high) {
    int stack[200000], top = -1;        // ручной стек
    stack[++top] = low;                
    stack[++top] = high;

    while (top >= 0) {                  
        high = stack[top--];            // извлекаем диапазон
        low = stack[top--];

        if (low < high) {
            int p = partition(a, low, high);   
            if (p - 1 > low) { stack[++top] = low;  stack[++top] = p - 1; }
            if (p + 1 < high) { stack[++top] = p + 1; stack[++top] = high; }
        }
    }
}

// СОРТИРОВКА СЛИЯНИЕМ 
void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;    // размеры половин
    int* L = new int[n1], * R = new int[n2];   // временные массивы

    for (int i = 0; i < n1; i++) L[i] = a[l + i];      
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];  

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)      
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) a[k++] = L[i++];     
    while (j < n2) a[k++] = R[j++];     

    delete[] L; delete[] R;          
}

// Рекурсивная сортировка слиянием
void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;       
        mergeSort(a, l, m);            
        mergeSort(a, m + 1, r);         
        merge(a, l, m, r);             
    }
}

//  ПИРАМИДАЛЬНАЯ СОРТИРОВКА 
// Восстанавливает свойство max-кучи для узла i
void heapify(int a[], int n, int i) {
    int lg = i, l = 2 * i + 1, r = 2 * i + 2;   
    if (l < n && a[l] > a[lg]) lg = l;  
    if (r < n && a[r] > a[lg]) lg = r;  
    if (lg != i) {                     
        swap(a[i], a[lg]);          
        heapify(a, n, lg);          
    }
}

void heapSort(int a[], int n) {
    // Строим max-кучу
    for (int i = n / 2 - 1; i >= 0; i--) heapify(a, n, i);
    // Извлекаем максимумы по одному
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);               // максимум — в конец
        heapify(a, i, 0);               // восстанавливаем кучу
    }
}

//  ИЗМЕРЕНИЕ ВРЕМЕНИ 
// Принимает любую функцию сортировки
template <typename F>
long long time(F f, int src[], int n) {
    int* c = new int[n];                // копия исходного массива
    for (int i = 0; i < n; i++) c[i] = src[i];

    auto s = high_resolution_clock::now();  // старт
    f(c, n);                                // запускаем сортировку
    auto e = high_resolution_clock::now();  // финиш

    delete[] c;
    return duration_cast<microseconds>(e - s).count();   // разница
}
int main() {
    setlocale(LC_ALL, "ru");

    const int N = 50000;                // размер массива
    int* arr = new int[N];
    for (int i = 0; i < N; i++) arr[i] = rand() % N;   // случайные числа

    cout << "Сравнение производительности (N = " << N << "):\n\n";

    // Быстрая рекурсивная
    cout << "Quick (рекурсивная):  "
        << time([](int a[], int n) { quickRec(a, 0, n - 1); }, arr, N) << " мкс\n";

    // Быстрая итеративная (с ручным стеком)
    cout << "Quick (итеративная):  "
        << time([](int a[], int n) { quickIter(a, 0, n - 1); }, arr, N) << " мкс\n";

    // Слиянием
    cout << "Merge sort:           "
        << time([](int a[], int n) { mergeSort(a, 0, n - 1); }, arr, N) << " мкс\n";

    // Пирамидальная
    cout << "Heap sort:            "
        << time(heapSort, arr, N) << " мкс\n";

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
