// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
    T* data;
    int cap, frontIdx, rearIdx, count;
public:
    Queue(int c = 10) : cap(c), frontIdx(0), rearIdx(-1), count(0) {
        data = new T[cap];
    }
    ~Queue() { delete[] data; }

    void enqueue(const T& v) {
        if (count == cap) throw std::overflow_error("Очередь полна");
        rearIdx = (rearIdx + 1) % cap;
        data[rearIdx] = v;
        count++;
    }
    T dequeue() {
        if (isEmpty()) throw std::underflow_error("Очередь пуста");
        T v = data[frontIdx];
        frontIdx = (frontIdx + 1) % cap;
        count--;
        return v;
    }
    T front() const {
        if (isEmpty()) throw std::underflow_error("Очередь пуста");
        return data[frontIdx];
    }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }

    // Разворот — O(n)
    void reverse() {
        if (count <= 1) return;
        T* temp = new T[count];
        for (int i = 0; i < count; i++)
            temp[i] = data[(frontIdx + i) % cap];
        for (int i = 0; i < count; i++)
            data[(frontIdx + i) % cap] = temp[count - 1 - i];
        delete[] temp;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    Queue<int> q(10);
    q.enqueue(1); q.enqueue(2); q.enqueue(3); q.enqueue(4);

    std::cout << "Исходная: ";
    Queue<int> tmp = q;
    while (!tmp.isEmpty()) std::cout << tmp.dequeue() << " ";

    q.reverse();
    std::cout << "\nПосле reverse: ";
    while (!q.isEmpty()) std::cout << q.dequeue() << " ";
    std::cout << std::endl;
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
