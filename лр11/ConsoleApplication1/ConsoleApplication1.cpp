// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int v) : V(v), adj(v) {}

    // Часть 1: Добавление и удаление рёбер
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void removeEdge(int u, int v) {
        adj[u].erase(remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
        adj[v].erase(remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
    }
    void print() {
        for (int i = 0; i < V; i++) {
            cout << i << ": ";
            for (int u : adj[i]) cout << u << " ";
            cout << "\n";
        }
    }

    // Вспомогательная функция для DFS (рекурсивный)
    void dfsHelper(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        for (int u : adj[v])
            if (!visited[u]) dfsHelper(u, visited);
    }

    // Часть 2: DFS и BFS
    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS: ";
        dfsHelper(start, visited);
        cout << "\n";
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        cout << "BFS: ";
        while (!q.empty()) {
            int v = q.front(); q.pop();
            cout << v << " ";
            for (int u : adj[v]) {
                if (!visited[u]) {
                    visited[u] = true;
                    q.push(u);
                }
            }
        }
        cout << "\n";
    }

    // Часть 2 (Вариант 9): Есть ли путь
    bool hasPath(int u, int target) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[u] = true;
        q.push(u);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (v == target) return true;
            for (int next : adj[v])
                if (!visited[next]) { visited[next] = true; q.push(next); }
        }
        return false;
    }

    // Часть 3: Вывод компонент связности
    void printComponents() {
        vector<bool> visited(V, false);
        int comp = 1;
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                cout << "Компонента " << comp++ << ": ";
                dfsHelper(i, visited);
                cout << "\n";
            }
        }
    }

    // Часть 3: Кратчайший путь (BFS)
    void printShortestPath(int start, int end) {
        vector<int> parent(V, -1), dist(V, -1);
        queue<int> q;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (v == end) break;
            for (int u : adj[v]) {
                if (dist[u] == -1) {
                    dist[u] = dist[v] + 1;
                    parent[u] = v;
                    q.push(u);
                }
            }
        }

        if (dist[end] == -1) {
            cout << "Пути от " << start << " до " << end << " нет.\n";
            return;
        }

        vector<int> path;
        for (int v = end; v != -1; v = parent[v]) path.push_back(v);
        reverse(path.begin(), path.end());

        cout << "Кратчайший путь от " << start << " до " << end << ": ";
        for (int v : path) cout << v << " ";
        cout << "(длина: " << dist[end] << ")\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    Graph g(7); // Граф на 7 вершин (от 0 до 6)

    // Создаём граф по картинке из задания
    g.addEdge(0, 1); g.addEdge(1, 2); g.addEdge(2, 3);
    g.addEdge(0, 5); g.addEdge(1, 4);
    g.addEdge(5, 4); g.addEdge(4, 6);

    cout << "=== 1. Исходный граф ===\n";
    g.print();

    cout << "\n=== 2. Обходы (от вершины 0) ===\n";
    g.DFS(0);
    g.BFS(0);

    cout << "\n=== 3. Задача варианта 9 (Есть ли путь) ===\n";
    cout << "Путь 0 -> 6: " << (g.hasPath(0, 6) ? "Да" : "Нет") << "\n";
    cout << "Путь 2 -> 5: " << (g.hasPath(2, 5) ? "Да" : "Нет") << "\n";

    cout << "\n=== 4. Компоненты связности ===\n";
    g.printComponents();

    cout << "\n=== 5. Кратчайшие пути ===\n";
    g.printShortestPath(0, 6);
    g.printShortestPath(2, 4);

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
