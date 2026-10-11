// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdexcept>

template <typename T>
class Deque {
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& v) : data(v), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int count;
    T sum;    // храним сумму — O(1) доступ
public:
    Deque() : head(nullptr), tail(nullptr), count(0), sum(0) {}
    ~Deque() {
        while (head) { Node* t = head; head = head->next; delete t; }
    }

    void push_front(const T& v) {
        Node* n = new Node(v);
        if (!head) head = tail = n;
        else { n->next = head; head->prev = n; head = n; }
        count++; sum += v;
    }
    void push_back(const T& v) {
        Node* n = new Node(v);
        if (!tail) head = tail = n;
        else { tail->next = n; n->prev = tail; tail = n; }
        count++; sum += v;
    }
    T pop_front() {
        if (isEmpty()) throw std::underflow_error("Дек пуст");
        Node* t = head;
        T v = t->data;
        head = head->next;
        if (head) head->prev = nullptr; else tail = nullptr;
        delete t; count--; sum -= v;
        return v;
    }
    T pop_back() {
        if (isEmpty()) throw std::underflow_error("Дек пуст");
        Node* t = tail;
        T v = t->data;
        tail = tail->prev;
        if (tail) tail->next = nullptr; else head = nullptr;
        delete t; count--; sum -= v;
        return v;
    }
    T getSum() const { return sum; }   // O(1)
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

int main() {
    setlocale(LC_ALL, "ru");
    Deque<int> dq;
    dq.push_back(10); dq.push_back(20);
    dq.push_front(5); dq.push_back(30);

    std::cout << "Сумма: " << dq.getSum() << "\n";   // 65
    dq.pop_front();
    std::cout << "После pop_front: " << dq.getSum() << "\n"; // 60
    dq.pop_back();
    std::cout << "После pop_back: " << dq.getSum() << "\n";  // 30
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
