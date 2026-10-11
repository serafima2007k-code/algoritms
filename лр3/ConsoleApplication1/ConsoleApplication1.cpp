// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class Vector {
private:
    T* data;
    int sz;
    int cap;

public:
    // Конструктор по умолчанию
    Vector() : data(nullptr), sz(0), cap(0) {}

    // Конструктор (размер, значение)
    explicit Vector(int n, const T& value = T()) : sz(n), cap(n) {
        if (n < 0) throw std::invalid_argument("Size < 0");
        data = new T[cap];
        for (int i = 0; i < sz; i++) data[i] = value;
    }

    // Конструктор копирования
    Vector(const Vector& other) : sz(other.sz), cap(other.cap) {
        data = new T[cap];
        for (int i = 0; i < sz; i++) data[i] = other.data[i];
    }

    // Конструктор перемещения
    Vector(Vector&& other) noexcept
        : data(other.data), sz(other.sz), cap(other.cap) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    // Деструктор
    ~Vector() { delete[] data; }

    // Оператор присваивания копированием
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            sz = other.sz;
            cap = other.cap;
            data = new T[cap];
            for (int i = 0; i < sz; i++) data[i] = other.data[i];
        }
        return *this;
    }

    // Оператор присваивания перемещением
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            sz = other.sz;
            cap = other.cap;
            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }

    // push_back
    void push_back(const T& value) {
        if (sz >= cap) {
            int newCap = (cap == 0) ? 1 : cap * 2;
            T* newData = new T[newCap];
            for (int i = 0; i < sz; i++) newData[i] = data[i];
            delete[] data;
            data = newData;
            cap = newCap;
        }
        data[sz++] = value;
    }

    int size() const { return sz; }
    int capacity() const { return cap; }

    T& operator[](int i) {
        if (i < 0 || i >= sz) throw std::out_of_range("Index out of range");
        return data[i];
    }

    void clear() { sz = 0; }

    // merge — слияние двух отсортированных векторов
    Vector<T> merge(const Vector<T>& other) const {
        Vector<T> result;
        int i = 0, j = 0;
        while (i < sz && j < other.sz)
            result.push_back(data[i] <= other.data[j] ? data[i++] : other.data[j++]);
        while (i < sz) result.push_back(data[i++]);
        while (j < other.sz) result.push_back(other.data[j++]);
        return result;
    }

    void print() const {
        std::cout << "[";
        for (int i = 0; i < sz; i++) {
            std::cout << data[i];
            if (i < sz - 1) std::cout << ", ";
        }
        std::cout << "]";
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    // Правило пяти
    Vector<int> v1(3, 5);
    Vector<int> v2 = v1;              // копирование
    Vector<int> v3 = std::move(v2);   // перемещение
    std::cout << "v1: "; v1.print(); std::cout << "\n";
    std::cout << "v3 (из v2): "; v3.print(); std::cout << "\n";
    std::cout << "v2 после перемещения: " << v2.size() << "\n\n";

    // merge
    Vector<int> a, b;
    for (int i = 1; i <= 5; i += 2) a.push_back(i);
    for (int i = 2; i <= 6; i += 2) b.push_back(i);
    std::cout << "a: "; a.print(); std::cout << "\n";
    std::cout << "b: "; b.print(); std::cout << "\n";
    Vector<int> c = a.merge(b);
    std::cout << "merge: "; c.print(); std::cout << "\n";

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
