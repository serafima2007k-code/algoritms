// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

//  УЗЕЛ 
struct Node {
    int key, h;
    Node* l, * r;
    Node(int k) : key(k), h(1), l(nullptr), r(nullptr) {}
};

int H(Node* n) { return n ? n->h : 0; }
int BF(Node* n) { return n ? H(n->l) - H(n->r) : 0; }
void upd(Node* n) { n->h = 1 + max(H(n->l), H(n->r)); }

//  ПОВОРОТЫ 
Node* RR(Node* y) { Node* x = y->l; y->l = x->r; x->r = y; upd(y); upd(x); return x; }
Node* LR(Node* x) { Node* y = x->r; x->r = y->l; y->l = x; upd(x); upd(y); return y; }

//  БАЛАНС 
Node* bal(Node* n) {
    upd(n);
    int b = BF(n);
    if (b > 1 && BF(n->l) >= 0) return RR(n);
    if (b > 1) { n->l = LR(n->l); return RR(n); }
    if (b < -1 && BF(n->r) <= 0) return LR(n);
    if (b < -1) { n->r = RR(n->r); return LR(n); }
    return n;
}

// AVL ВСТАВКА
Node* insertAVL(Node* n, int k) {
    if (!n) return new Node(k);
    if (k < n->key) n->l = insertAVL(n->l, k);
    else if (k > n->key) n->r = insertAVL(n->r, k);
    else return n;
    return bal(n);
}
//  BST ВСТАВКА 
Node* insertBST(Node* root, int key) {
    if (!root) return new Node(key);
    Node* cur = root;
    while (true) {
        if (key < cur->key) {
            if (!cur->l) { cur->l = new Node(key); break; }
            cur = cur->l;
        }
        else if (key > cur->key) {
            if (!cur->r) { cur->r = new Node(key); break; }
            cur = cur->r;
        }
        else break;
    }
    return root;
}

//  ПОИСК (итеративный) 
Node* findBST(Node* root, int key) {
    while (root && root->key != key)
        root = (key < root->key) ? root->l : root->r;
    return root;
}
// AVL поиск 
Node* findAVL(Node* n, int key) {
    if (!n || n->key == key) return n;
    return key < n->key ? findAVL(n->l, key) : findAVL(n->r, key);
}
//  УДАЛЕНИЕ AVL
Node* minNode(Node* n) { while (n->l) n = n->l; return n; }
Node* delAVL(Node* n, int k) {
    if (!n) return nullptr;
    if (k < n->key) n->l = delAVL(n->l, k);
    else if (k > n->key) n->r = delAVL(n->r, k);
    else {
        if (!n->l || !n->r) { Node* t = n->l ? n->l : n->r; delete n; return t; }
        Node* m = minNode(n->r);
        n->key = m->key;
        n->r = delAVL(n->r, m->key);
    }
    return bal(n);
}
int cntRange(Node* n, int lo, int hi) {
    if (!n) return 0;
    int c = (n->key >= lo && n->key <= hi);
    if (n->key > lo) c += cntRange(n->l, lo, hi);
    if (n->key < hi) c += cntRange(n->r, lo, hi);
    return c;
}
// ИТЕРАТИВНОЕ УДАЛЕНИЕ ДЕРЕВА 
void destroyIter(Node* root) {
    if (!root) return;
    vector<Node*> stk = { root };
    while (!stk.empty()) {
        Node* cur = stk.back(); stk.pop_back();
        if (cur->l) stk.push_back(cur->l);
        if (cur->r) stk.push_back(cur->r);
        delete cur;
    }
}
// TRIE 
struct TrieNode {
    TrieNode* c[26];
    bool end;
    TrieNode() : end(false) { fill(c, c + 26, nullptr); }
};

class Trie {
    TrieNode* root;
    void collect(TrieNode* n, string s, vector<string>& v) {
        if (n->end) v.push_back(s);
        for (int i = 0; i < 26; i++)
            if (n->c[i]) collect(n->c[i], s + char('a' + i), v);
    }
public:
    Trie() { root = new TrieNode(); }
    ~Trie() { destroy(root); }
    void destroy(TrieNode* n) {
        for (int i = 0; i < 26; i++) if (n->c[i]) destroy(n->c[i]);
        delete n;
    }
    void insert(const string& w) {
        TrieNode* cur = root;
        for (char ch : w) {
            int i = ch - 'a';
            if (!cur->c[i]) cur->c[i] = new TrieNode();
            cur = cur->c[i];
        }
        cur->end = true;
    }
    bool search(const string& w) {
        TrieNode* cur = root;
        for (char ch : w) {
            int i = ch - 'a';
            if (!cur->c[i]) return false;
            cur = cur->c[i];
        }
        return cur->end;
    }
    bool startsWith(const string& p) {
        TrieNode* cur = root;
        for (char ch : p) {
            int i = ch - 'a';
            if (!cur->c[i]) return false;
            cur = cur->c[i];
        }
        return true;
    }
    void exportToFile(const string& fname) {
        vector<string> v;
        collect(root, "", v);
        ofstream f(fname);
        for (auto& w : v) f << w << "\n";
    }
};
int main() {
    setlocale(LC_ALL, "ru");

    cout << " AVL \n";
    Node* avl = nullptr;
    for (int k : {10, 20, 30, 40, 50, 25}) avl = insertAVL(avl, k);
    cout << "  Поиск 25: " << (findAVL(avl, 25) ? "да" : "нет") << "\n";
    avl = delAVL(avl, 30);
    cout << "  Поиск 30: " << (findAVL(avl, 30) ? "да" : "нет") << "\n";
    cout << "  Узлов в [20,40]: " << cntRange(avl, 20, 40) << "\n";
    destroyIter(avl);

    cout << "\n Trie \n";
    Trie t;
    for (auto& w : { "cat", "car", "cart", "dog", "catfish" }) t.insert(w);
    cout << "  search(cat):    " << (t.search("cat") ? "да" : "нет") << "\n";
    cout << "  search(cattle): " << (t.search("cattle") ? "да" : "нет") << "\n";
    cout << "  startsWith(ca): " << (t.startsWith("ca") ? "да" : "нет") << "\n";
    t.exportToFile("words.txt");
    cout << "  Экспорт в words.txt\n";

    cout << "\n Сравнение \n";
    cout << "N\tТип\tAVL ins\tBST ins\tAVL srch\tBST srch\n";

    for (int N : {1000, 5000, 10000}) {
        for (int type = 0; type < 2; type++) {
            vector<int> d(N);
            for (int i = 0; i < N; i++) d[i] = type == 0 ? rand() % (N * 10) : i;

            // AVL
            Node* a = nullptr;
            auto s = high_resolution_clock::now();
            for (int x : d) a = insertAVL(a, x);
            auto e = high_resolution_clock::now();
            long long ai = duration_cast<microseconds>(e - s).count();

            s = high_resolution_clock::now();
            for (int x : d) findAVL(a, x);
            e = high_resolution_clock::now();
            long long as = duration_cast<microseconds>(e - s).count();
            destroyIter(a);

            // BST (итеративный)
            Node* b = nullptr;
            s = high_resolution_clock::now();
            for (int x : d) b = insertBST(b, x);
            e = high_resolution_clock::now();
            long long bi = duration_cast<microseconds>(e - s).count();

            s = high_resolution_clock::now();
            for (int x : d) findBST(b, x);
            e = high_resolution_clock::now();
            long long bs = duration_cast<microseconds>(e - s).count();
            destroyIter(b);

            cout << N << "\t" << (type == 0 ? "случайные" : "сортир.")
                << "\t" << ai << "\t" << bi << "\t" << as << "\t\t" << bs << "\n";
        }
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
