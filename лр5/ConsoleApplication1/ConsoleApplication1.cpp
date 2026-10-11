// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdexcept>

class TwoStacks {
    int* data;
    int size;
    int top1;   // вершина 1-го стека (растёт вправо)
    int top2;   // вершина 2-го стека (растёт влево)
public:
    TwoStacks(int n) : size(n), top1(-1), top2(n) { data = new int[size]; }
    ~TwoStacks() { delete[] data; }

    void push1(int v) {
        if (top1 + 1 == top2) throw std::overflow_error("Стек 1 полон");
        data[++top1] = v;
    }
    void push2(int v) {
        if (top1 + 1 == top2) throw std::overflow_error("Стек 2 полон");
        data[--top2] = v;
    }
    int pop1() {
        if (top1 == -1) throw std::underflow_error("Стек 1 пуст");
        return data[top1--];
    }
    int pop2() {
        if (top2 == size) throw std::underflow_error("Стек 2 пуст");
        return data[top2++];
    }
    bool isEmpty1() const { return top1 == -1; }
    bool isEmpty2() const { return top2 == size; }
};

int main() {
    setlocale(LC_ALL, "ru");
    TwoStacks ts(10);
    ts.push1(1); ts.push1(2); ts.push1(3);
    ts.push2(100); ts.push2(200); ts.push2(300);

    std::cout << "Стек 1: ";
    while (!ts.isEmpty1()) std::cout << ts.pop1() << " ";
    std::cout << "\nСтек 2: ";
    while (!ts.isEmpty2()) std::cout << ts.pop2() << " ";
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
