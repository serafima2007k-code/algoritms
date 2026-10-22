// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Coach {
private:
    string name;
    string sport;
public:
    Coach(const string& n, const string& s) : name(n), sport(s) {
        cout << "  Создан тренер: " << name << " (" << sport << ")" << endl;
    }
    ~Coach() {
        cout << "  Удалён тренер: " << name << endl;
    }
    void print() const {
        cout << "    Тренер: " << name << ", вид: " << sport << endl;
    }
    string getName() const { return name; }
};

class Member {
private:
    string name;
    int age;
    static int memberCount;
public:
    Member(const string& n, int a) : name(n), age(a) {
        memberCount++;
        cout << "    Создан участник: " << name << " (" << age << " лет)"
            << "  [всего участников: " << memberCount << "]" << endl;
    }
    ~Member() {
        memberCount--;
        cout << "    Удалён участник: " << name << "  [осталось: " << memberCount << "]" << endl;
    }
    // Геттер для имени (нужен для вывода в секции)
    string getName() const { return name; }
    void print() const {
        cout << "      Участник: " << name << ", возраст: " << age << endl;
    }
    static int getCount() { return memberCount; }
};
int Member::memberCount = 0;

class Section {
private:
    string name;
    Coach* coach;                // агрегация: тренер существует отдельно
    vector<Member*> members;     // агрегация: участники существуют отдельно
public:
    Section(const string& n, Coach* c) : name(n), coach(c) {
        cout << "  Создана секция: " << name << " (тренер: " << coach->getName() << ")" << endl;
    }
    ~Section() {
        cout << "  Удалена секция: " << name << endl;
        // тренер и участники НЕ удаляются
    }
    void addMember(Member* m) {
        if (m) {
            members.push_back(m);
            cout << "    В секцию " << name << " добавлен участник " << m->getName() << endl;
        }
    }
    void print() const {
        cout << "  Секция \"" << name << "\", тренер: " << coach->getName() << endl;
        if (members.empty()) {
            cout << "    (нет участников)" << endl;
        }
        else {
            for (const auto* m : members) m->print();
        }
    }
    string getName() const { return name; }
};

class SportsClub {
private:
    static SportsClub* instance;
    string clubName;
    vector<Section*> sections;   // агрегация: секции существуют отдельно
    vector<Coach*> coaches;      // агрегация: тренеры существуют отдельно
    // Приватный конструктор
    SportsClub(const string& name) : clubName(name) {
        cout << "Создан спортивный клуб \"" << clubName << "\" (Singleton)" << endl;
    }
public:
    // Запрещаем копирование
    SportsClub(const SportsClub&) = delete;
    SportsClub& operator=(const SportsClub&) = delete;

    // Статический метод доступа к единственному экземпляру
    static SportsClub* getInstance(const string& name = "Спорт-Сити") {
        if (instance == nullptr) {
            instance = new SportsClub(name);
        }
        return instance;
    }

    ~SportsClub() {
        cout << "Уничтожен спортивный клуб \"" << clubName << "\"" << endl;
    }
    void addCoach(Coach* c) {
        if (c) {
            coaches.push_back(c);
            cout << "  В клуб добавлен тренер: " << c->getName() << endl;
        }
    }
    void addSection(Section* s) {
        if (s) {
            sections.push_back(s);
            cout << "  В клуб добавлена секция: " << s->getName() << endl;
        }
    }
    void print() const {
        cout << "Тренеры:" << endl;
        if (coaches.empty()) cout << "  (нет)" << endl;
        else for (const auto* c : coaches) c->print();

        cout << "Секции:" << endl;
        if (sections.empty()) cout << "  (нет)" << endl;
        else for (const auto* s : sections) s->print();
    }

    static void destroyInstance() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }
};
// Определение статического указателя
SportsClub* SportsClub::instance = nullptr;

int main() {
    setlocale(LC_ALL, "ru");
 
    // Создаём тренеров
    Coach c1("Иван Петров", "футбол");
    Coach c2("Мария Смирнова", "баскетбол");
    Coach c3("Алексей Иванов", "плавание");

    // Создаём участников 
    Member m1("Анна", 20);
    Member m2("Борис", 22);
    Member m3("Виктор", 19);
    Member m4("Галина", 21);

    // Получаем единственный экземпляр клуба
    SportsClub* club = SportsClub::getInstance("Чемпион");
    SportsClub* club2 = SportsClub::getInstance();
  
    // Добавляем тренеров в клуб
    club->addCoach(&c1);
    club->addCoach(&c2);
    club->addCoach(&c3);

    // Создаём секции 
    Section sec1("Футбол", &c1);
    Section sec2("Баскетбол", &c2);
    Section sec3("Плавание", &c3);

    // Добавляем секции в клуб
    club->addSection(&sec1);
    club->addSection(&sec2);
    club->addSection(&sec3);

    // Добавляем участников в секции
    sec1.addMember(&m1);
    sec1.addMember(&m2);
    sec2.addMember(&m3);
    sec3.addMember(&m4);

    // Выводим состояние клуба
    club->print();

    cout << "\nВсего участников: " << Member::getCount() << endl;

    SportsClub::destroyInstance();

    cout << "\nПосле уничтожения клуба тренеры, секции и участники живы:\n";
    c1.print();
    c2.print();
    sec1.print();
    cout << "Участники: ";
    m1.print(); m2.print(); m3.print(); m4.print();
    cout << "Всего участников: " << Member::getCount() << endl;
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
