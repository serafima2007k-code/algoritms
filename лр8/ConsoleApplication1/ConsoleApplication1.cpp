// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

// ЧАСТЬ 1: ДВОИЧНЫЙ ПОИСК В СДВИНУТОМ МАССИВЕ 
int searchRotated(const int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;

        if (arr[left] <= arr[mid]) {                    // левая половина отсортирована
            if (target >= arr[left] && target < arr[mid]) right = mid - 1;
            else                                          left = mid + 1;
        }
        else {                                        // правая половина отсортирована
            if (target > arr[mid] && target <= arr[right]) left = mid + 1;
            else                                           right = mid - 1;
        }
    }
    return -1;
}

// ЧАСТЬ 2: ХЕШ-ТАБЛИЦА (ЦЕПОЧКИ, string -> string) 
class HashTable {
    struct Node {
        string key, value;
        Node* next;
        Node(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
    };
    vector<Node*> table;
    int size, count;

    // Хеш-функция для строки (полиномиальный хеш)
    int hash(const string& key) const {
        unsigned long h = 0;
        for (char c : key) h = h * 31 + c;   // 31 — простое число
        return h % size;
    }

public:
    HashTable(int s = 101) : size(s), count(0) { table.resize(size, nullptr); }

    ~HashTable() {                          // освобождение памяти
        for (auto* head : table)
            while (head) { Node* t = head; head = head->next; delete t; }
    }

    void insert(const string& key, const string& value) {
        int idx = hash(key);
        for (Node* cur = table[idx]; cur; cur = cur->next)
            if (cur->key == key) { cur->value = value; return; }   // обновляем
        Node* newNode = new Node(key, value);                       // иначе — новый узел
        newNode->next = table[idx];
        table[idx] = newNode;
        count++;
    }

    bool find(const string& key, string& result) const {
        for (Node* cur = table[hash(key)]; cur; cur = cur->next)
            if (cur->key == key) { result = cur->value; return true; }
        return false;
    }

    bool remove(const string& key) {
        int idx = hash(key);
        Node* cur = table[idx];
        Node* prev = nullptr;
        while (cur) {
            if (cur->key == key) {
                if (prev) prev->next = cur->next; else table[idx] = cur->next;
                delete cur; count--; return true;
            }
            prev = cur; cur = cur->next;
        }
        return false;
    }

    int getSize() const { return count; }
};

//  ЧАСТЬ 3: ЗАМЕР ВРЕМЕНИ 
template <typename F>
long long measure(F f) {
    auto s = high_resolution_clock::now();
    f();
    auto e = high_resolution_clock::now();
    return duration_cast<microseconds>(e - s).count();
}

int main() {
    setlocale(LC_ALL, "ru");
    cout << "=== ЧАСТЬ 1: Поиск в сдвинутом массиве ===\n";
    int arr[] = { 7, 9, 11, 13, 1, 3, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int t : {1, 5, 7, 13, 8}) {
        int pos = searchRotated(arr, n, t);
        cout << "  " << t << (pos != -1 ? " найден на позиции " + to_string(pos) : " не найден") << "\n";
    }
    cout << "\n=== ЧАСТЬ 2: Хеш-таблица (цепочки) ===\n";
    HashTable ht(7);
    ht.insert("apple", "яблоко");
    ht.insert("banana", "банан");
    ht.insert("cherry", "вишня");
    ht.insert("date", "финик");
    ht.insert("fig", "инжир");

    string val;
    if (ht.find("banana", val)) cout << "  banana -> " << val << "\n";
    if (ht.find("fig", val))    cout << "  fig -> " << val << "\n";
    if (!ht.find("kiwi", val))  cout << "  kiwi не найден\n";
    ht.remove("banana");
    cout << "  Всего элементов: " << ht.getSize() << "\n";
    cout << "\n=== ЧАСТЬ 3: Сравнение (N = 1000, 10000, 100000) ===\n";
    cout << "N\t\tБинарный\tХеш\n";

    for (int N : {1000, 10000, 100000}) {
        vector<int> sortedArr(N);
        for (int i = 0; i < N; i++) sortedArr[i] = i;

        HashTable bigHT(N * 2);
        for (int i = 0; i < N; i++) bigHT.insert("key" + to_string(i), "val");

        // 1000 запросов
        vector<int> qInt;
        vector<string> qStr;
        for (int i = 0; i < 1000; i++) {
            int r = rand() % N;
            qInt.push_back(r);
            qStr.push_back("key" + to_string(r));
        }

        long long tBin = measure([&]() {           // бинарный поиск
            for (int q : qInt) {
                int l = 0, r = N - 1;
                while (l <= r) {
                    int m = l + (r - l) / 2;
                    if (sortedArr[m] == q) break;
                    if (sortedArr[m] < q) l = m + 1; else r = m - 1;
                }
            }
            });

        string tmp;
        long long tHash = measure([&]() {          // хеш-поиск
            for (auto& q : qStr) bigHT.find(q, tmp);
            });

        cout << N << "\t\t" << tBin << "\t\t" << tHash << "\n";
    }
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
