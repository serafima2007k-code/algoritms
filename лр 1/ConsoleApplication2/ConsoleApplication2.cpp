// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Item {
private:
    string name;
    double price;
    int quantity;
    static int itemCount;   // статический счётчик созданных товаров
public:
    // Конструктор
    Item(const string& n, double p, int q)
        : name(n), price(p), quantity(q) {
        itemCount++;
        cout << "  Создан товар: " << name << " (цена: " << price
            << ", кол-во: " << quantity << ")  [всего товаров: " << itemCount << "]" << endl;
    }
    // Деструктор
    ~Item() {
        itemCount--;
        cout << "  Удалён товар: " << name << "  [осталось: " << itemCount << "]" << endl;
    }
    // Геттеры
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    // Вывод информации о товаре
    void print() const {
        cout << "    " << name << ", цена: " << price << " руб., кол-во: " << quantity << endl;
    }
    // Статический метод для получения количества товаров
    static int getCount() { return itemCount; }
};

// Определение статического поля 
int Item::itemCount = 0;

class Cart {
private:
    string owner;               // владелец корзины
    vector<Item*> items;        // указатели на товары (агрегация)
public:
    Cart(const string& o) : owner(o) {
        cout << "Создана корзина для " << owner << endl;
    }
    ~Cart() {
        cout << "Уничтожена корзина для " << owner << endl;
    }
    // Добавление товара
    void addItem(Item* item) {
        if (item != nullptr) {
            items.push_back(item);
            cout << "  В корзину добавлен товар: " << item->getName() << endl;
        }
    }
    // Вывод содержимого корзины
    void print() const {
        cout << "Корзина " << owner << " содержит:" << endl;
        if (items.empty()) {
            cout << "  (пусто)" << endl;
        }
        else {
            for (const auto* item : items) {
                item->print();
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    Item apple("Яблоко", 50.0, 3);
    Item bread("Хлеб", 30.0, 2);
    Item milk("Молоко", 80.0, 1);

    cout << "\nВсего товаров: " << Item::getCount() << endl;

    Cart cart("Анна");
    cart.addItem(&apple);
    cart.addItem(&bread);
    cart.addItem(&milk);
    cart.print();

    cout << "\nСоздаём временную корзину в блоке:\n";
    {
        Cart tempCart("Временная");
        tempCart.addItem(&apple);  // можно добавить тот же товар
        tempCart.print();
    }
    cout << "\nПосле уничтожения корзин товары всё ещё существуют:\n";
    apple.print();
    bread.print();
    milk.print();
    cout << "Всего товаров: " << Item::getCount() << endl;
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
