// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;

public:
    ~DoublyLinkedList() { clear(); }
    // Вставка в конец — O(1)
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    // Вставка в начало — O(1)
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        count++;
    }

    // Удаление из начала — O(1)
    void pop_front() {
        if (!head) throw std::underflow_error("List is empty");
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        count--;
    }

    // Удаление из конца — O(1)
    void pop_back() {
        if (!tail) throw std::underflow_error("List is empty");
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        count--;
    }

    // Вывод — O(n)
    void print() const {
        std::cout << "[";
        for (Node* cur = head; cur; cur = cur->next) {
            std::cout << cur->data;
            if (cur->next) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    // Дополнительно: toVector — O(n)
    std::vector<T> toVector() const {
        std::vector<T> result;
        for (Node* cur = head; cur; cur = cur->next)
            result.push_back(cur->data);
        return result;
    }

    int size() const { return count; }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);

    std::cout << "Список: ";
    list.print();
    std::cout << "Размер: " << list.size() << "\n\n";

    std::vector<int> vec = list.toVector();
    std::cout << "Вектор: [";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
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
