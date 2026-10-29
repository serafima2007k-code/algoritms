// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
#include <algorithm>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj; // Матрица смежности
public:
    Graph(int v) : V(v), adj(v, vector<int>(v, 0)) {}

    void addEdge(int u, int v, int w) {
        adj[u][v] = w;
        adj[v][u] = w; // Неориентированный граф
    }

    // --- Часть 1: Дейкстра O(V^2) + восстановление пути ---
    vector<int> dijkstra(int start, vector<int>& prev) {
        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);
        prev.assign(V, -1);
        dist[start] = 0;

        for (int i = 0; i < V - 1; i++) {
            int u = -1;
            for (int j = 0; j < V; j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;
            }
            if (u == -1 || dist[u] == INT_MAX) break;
            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (adj[u][v] != 0 && !visited[v] && dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                    prev[v] = u;
                }
            }
        }
        return dist;
    }

    vector<int> getPath(int start, int end, const vector<int>& prev) {
        vector<int> path;
        if (prev[end] == -1 && start != end) return path; // Пути нет
        for (int v = end; v != -1; v = prev[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        return path;
    }

    // --- Часть 2: Флойд-Уоршелл + Центр графа ---
    vector<vector<int>> floyd() {
        vector<vector<int>> dist = adj;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j && dist[i][j] == 0) dist[i][j] = INT_MAX;
            }
        }
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        return dist;
    }

    int findCenter() {
        vector<vector<int>> dist = floyd();
        int minEcc = INT_MAX, center = -1;
        for (int i = 0; i < V; i++) {
            int maxDist = 0;
            for (int j = 0; j < V; j++) {
                if (dist[i][j] != INT_MAX) maxDist = max(maxDist, dist[i][j]);
            }
            if (maxDist < minEcc) {
                minEcc = maxDist;
                center = i;
            }
        }
        return center;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    // --- ТЕСТ Части 1 и 2 ---
    Graph g(5);
    g.addEdge(0, 1, 4); g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1); g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8); g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);

    vector<int> prev;
    vector<int> dist = g.dijkstra(0, prev);
    cout << "Кратчайший путь от 0 до 4: " << dist[4] << "\nМаршрут: ";
    vector<int> path = g.getPath(0, 4, prev);
    for (int v : path) cout << v << " ";
    cout << "\n\nЦентр графа: вершина " << g.findCenter() << "\n\n";

    // --- ТЕСТ Части 3: Сравнение производительности ---
    cout << "Сравнение времени (мкс):\n";
    cout << "V\tДейкстра\tФлойд\n";

    for (int N : {10, 20, 50, 100}) {
        Graph bigG(N);
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (rand() % 3 == 0) bigG.addEdge(i, j, rand() % 20 + 1);
            }
        }

        auto t1 = chrono::high_resolution_clock::now();
        vector<int> p;
        bigG.dijkstra(0, p);
        auto t2 = chrono::high_resolution_clock::now();
        long long dTime = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

        t1 = chrono::high_resolution_clock::now();
        bigG.floyd();
        t2 = chrono::high_resolution_clock::now();
        long long fTime = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();

        cout << N << "\t" << dTime << "\t\t" << fTime << "\n";
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
