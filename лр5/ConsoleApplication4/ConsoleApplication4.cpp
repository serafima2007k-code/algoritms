// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdexcept>
#include <functional>

template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
    T* heap;
    int count, cap;
    Compare comp;
public:
    PriorityQueue(int c = 10, Compare cmp = Compare())
        : cap(c), count(0), comp(cmp) {
        heap = new T[cap];
    }
    ~PriorityQueue() { delete[] heap; }

    void push(const T& v) {
        if (count == cap) throw std::overflow_error("PQ полна");
        heap[count] = v;
        int i = count++;
        while (i > 0) {
            int p = (i - 1) / 2;
            if (comp(heap[p], heap[i])) { std::swap(heap[i], heap[p]); i = p; }
            else break;
        }
    }
    T pop() {
        if (isEmpty()) throw std::underflow_error("PQ пуста");
        T top = heap[0];
        heap[0] = heap[--count];
        int i = 0;
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, m = i;
            if (l < count && comp(heap[m], heap[l])) m = l;
            if (r < count && comp(heap[m], heap[r])) m = r;
            if (m == i) break;
            std::swap(heap[i], heap[m]); i = m;
        }
        return top;
    }
    T top() const {
        if (isEmpty()) throw std::underflow_error("PQ пуста");
        return heap[0];
    }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

// Пользовательский тип
struct Person {
    std::string name;
    int age;
    bool operator<(const Person& o) const { return age < o.age; }
};

int main() {
    setlocale(LC_ALL, "ru");

    // 1. Сортировка по возрасту (max-heap через operator<)
    PriorityQueue<Person> pq;
    pq.push({ "Иван", 25 });
    pq.push({ "Мария", 30 });
    pq.push({ "Алексей", 20 });

    std::cout << "По возрасту (max):\n";
    while (!pq.isEmpty()) {
        Person p = pq.pop();
        std::cout << p.name << " (" << p.age << ")\n";
    }

    // 2. Сортировка по имени через компаратор
    struct ByName {
        bool operator()(const Person& a, const Person& b) const {
            return a.name < b.name;
        }
    };
    PriorityQueue<Person, ByName> pq2(10, ByName());
    pq2.push({ "Иван", 25 });
    pq2.push({ "Мария", 30 });
    pq2.push({ "Алексей", 20 });

    std::cout << "\nПо имени (max):\n";
    while (!pq2.isEmpty()) {
        Person p = pq2.pop();
        std::cout << p.name << " (" << p.age << ")\n";
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
