// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdexcept>
#include <queue>
#include <chrono>
using namespace std;
using namespace chrono;

// Шаблонный класс FixedQueue<T, N> 
template <typename T, int N>
class FixedQueue {
private:
    T data[N];
    int frontIndex = 0;
    int rearIndex = -1;
    int count = 0;

public:
    // O(1)
    bool enqueue(const T& value) {
        if (isFull()) return false;
        rearIndex = (rearIndex + 1) % N;
        data[rearIndex] = value;
        count++;
        return true;
    }

    // O(1)
    T dequeue() {
        if (isEmpty()) throw out_of_range("Очередь пуста!");
        T value = data[frontIndex];
        frontIndex = (frontIndex + 1) % N;
        count--;
        return value;
    }

    // O(1)
    T front() const {
        if (isEmpty()) throw out_of_range("Очередь пуста!");
        return data[frontIndex];
    }

    bool isEmpty() const { return count == 0; }   // O(1)
    bool isFull() const { return count == N; }     // O(1)
    int size() const { return count; }             // O(1)

    // O(n) — только для вывода
    void print() const {
        cout << "[";
        int index = frontIndex;
        for (int i = 0; i < count; i++) {
            cout << data[index];
            if (i < count - 1) cout << ", ";
            index = (index + 1) % N;
        }
        cout << "]" << endl;
    }
};

// Измерение времени
template <typename Func>
long long measureTime(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    setlocale(LC_ALL, "ru");

    // Демонстрация
    cout << "=== FixedQueue<int, 5> ===\n";
    FixedQueue<int, 5> q;
    for (int i = 1; i <= 5; i++) q.enqueue(i * 10);
    q.print();
    cout << "front = " << q.front() << ", size = " << q.size() << endl;
    q.dequeue();
    q.print();
    cout << "isEmpty: " << (q.isEmpty() ? "Да" : "Нет") << endl;
    cout << "isFull:  " << (q.isFull() ? "Да" : "Нет") << endl;

    // Сравнение с STL
    cout << "\n=== Сравнение с std::queue ===\n";
    const int SIZE = 10000;

    long long t1 = measureTime([]() {
        FixedQueue<int, SIZE> fq;
        for (int i = 0; i < SIZE; i++) fq.enqueue(i);
        while (!fq.isEmpty()) fq.dequeue();
        });

    long long t2 = measureTime([]() {
        queue<int> sq;
        for (int i = 0; i < SIZE; i++) sq.push(i);
        while (!sq.empty()) sq.pop();
        });

    cout << "FixedQueue: " << t1 << " мкс\n";
    cout << "std::queue: " << t2 << " мкс\n";

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
