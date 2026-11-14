// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) parent[rx] = ry;
        else if (rank[rx] > rank[ry]) parent[ry] = rx;
        else { parent[ry] = rx; rank[rx]++; }
        return true;
    }
};

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const { return w < other.w; }
};

int primMST(vector<vector<int>>& matrix, int V, int start) {
    vector<int> minEdge(V, INT_MAX), parent(V, -1);
    vector<bool> inMST(V, false);
    minEdge[start] = 0;
    int totalWeight = 0;

    cout << "--- Прим (рёбра в порядке добавления) ---\n";
    for (int i = 0; i < V; i++) {
        int u = -1;
        for (int j = 0; j < V; j++) {
            if (!inMST[j] && (u == -1 || minEdge[j] < minEdge[u])) u = j;
        }

        if (u == -1 || minEdge[u] == INT_MAX) {
            cout << "Граф несвязный!\n";
            return -1;
        }

        inMST[u] = true;
        totalWeight += minEdge[u];

        if (parent[u] != -1) {
            cout << "  " << parent[u] << " - " << u << " (вес: " << minEdge[u] << ")\n";
        }

        for (int v = 0; v < V; v++) {
            if (matrix[u][v] != 0 && !inMST[v] && matrix[u][v] < minEdge[v]) {
                minEdge[v] = matrix[u][v];
                parent[v] = u;
            }
        }
    }
    return totalWeight;
}

int kruskalMST(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end());
    DSU dsu(V);
    int totalWeight = 0, edgesUsed = 0;

    cout << "--- Краскал ---\n";
    for (const Edge& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            totalWeight += e.w;
            edgesUsed++;
            cout << "  " << e.u << " - " << e.v << " (вес: " << e.w << ")\n";
            if (edgesUsed == V - 1) break;
        }
    }

    if (edgesUsed != V - 1) {
        cout << "Граф несвязный!\n";
        return -1;
    }
    return totalWeight;
}

int main() {
    setlocale(LC_ALL, "ru");

    // ===== ЧАСТЬ 3: Задача о прокладке сетей (из задания) =====
    int V = 6;
    vector<vector<int>> matrix(V, vector<int>(V, 0));
    auto add = [&](int u, int v, int w) { matrix[u][v] = matrix[v][u] = w; };

    // Города A(0), B(1), C(2), D(3), E(4), F(5)
    add(0, 1, 4); // A-B
    add(0, 2, 3); // A-C
    add(1, 2, 2); // B-C
    add(1, 3, 2); // B-D
    add(2, 4, 3); // C-E
    add(3, 4, 5); // D-E
    add(4, 5, 5); // E-F

    vector<Edge> edges = {
        {0,1,4}, {0,2,3}, {1,2,2}, {1,3,2}, {2,4,3}, {3,4,5}, {4,5,5}
    };

    cout << "=== ЗАДАЧА О ПРОКЛАДКЕ СЕТЕЙ ===\n";
    int primWeight = primMST(matrix, V, 0);
    cout << "Общий вес MST (Прим): " << primWeight << "\n\n";

    int kruskalWeight = kruskalMST(edges, V);
    cout << "Общий вес MST (Краскал): " << kruskalWeight << "\n\n";

    // ===== ЧАСТЬ 2: Тест на V=1000 (простая сортировка) =====
    cout << "=== ТЕСТ НА V=1000 (Граф с большим количеством вершин) ===\n";
    int Vbig = 1000;
    vector<Edge> bigEdges;
    for (int i = 0; i < Vbig - 1; i++) {
        bigEdges.push_back({ i, i + 1, rand() % 100 + 1 });
    }
    for (int i = 0; i < Vbig; i++) {
        for (int j = i + 2; j < Vbig; j++) {
            if (rand() % 100 < 5) bigEdges.push_back({ i, j, rand() % 100 + 1 });
        }
    }

    auto start = chrono::high_resolution_clock::now();
    int w = kruskalMST(bigEdges, Vbig);
    auto end = chrono::high_resolution_clock::now();

    cout << "Вес MST (V=1000): " << w << "\n";
    cout << "Время (Краскал): "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " мс\n";

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
