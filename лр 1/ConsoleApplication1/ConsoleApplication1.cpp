#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Класс вагон
class Carriage {
private:
    int number;
    string type;   
    int seats;
public:
    Carriage(int num, const string& t, int s)
        : number(num), type(t), seats(s) {
        cout << "  Создан вагон №" << number << " (" << type
            << ", " << seats << " мест)" << endl;
    }
    // Деструктор
    ~Carriage() {
        cout << "  Уничтожен вагон №" << number << endl;
    }
    void print() const {
        cout << "    Вагон №" << number << ", тип: " << type
            << ", мест: " << seats << endl;
    }
};

// Класс поезд
class Train {
private:
    string name;
    vector<Carriage> carriages;   // композиция: вагоны внутри поезда
public:
    Train(const string& n) : name(n) {
        cout << "Создан поезд \"" << name << "\"" << endl;
    }
    ~Train() {
        cout << "Уничтожен поезд \"" << name << "\"" << endl;
    }
    // Добавление вагона 
    void addCarriage(int num, const string& type, int seats) {
        carriages.emplace_back(num, type, seats);  // создаёт вагон в векторе
    }
    void print() const {
        cout << "Поезд \"" << name << "\", вагоны:" << endl;
        if (carriages.empty()) {
            cout << "  (нет вагонов)" << endl;
        }
        for (const auto& c : carriages) {
            c.print();
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    // Создаём поезд
    Train train("Стрела");
    train.addCarriage(1, "купе", 36);
    train.addCarriage(2, "плацкарт", 54);
    train.addCarriage(3, "купе", 36);
    train.print();

    return 0;
}