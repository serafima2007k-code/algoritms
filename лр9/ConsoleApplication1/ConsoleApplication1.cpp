// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//  УЗЕЛ 
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};
void destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}
//  ЧАСТЬ 1: БИНАРНОЕ ДЕРЕВО 
class BinaryTree {
public:
    Node* root = nullptr;
    ~BinaryTree() { destroyTree(root); }

    // Прямой обход 
    void preOrder(Node* n) {
        if (!n) return;
        cout << n->data << " ";
        preOrder(n->left);
        preOrder(n->right);
    }

    // Симметричный обход 
    void inOrder(Node* n) {
        if (!n) return;
        inOrder(n->left);
        cout << n->data << " ";
        inOrder(n->right);
    }

    // Обратный обход
    void postOrder(Node* n) {
        if (!n) return;
        postOrder(n->left);
        postOrder(n->right);
        cout << n->data << " ";
    }
    // Уровневый обход (BFS)
    void levelOrder(Node* n) {
        if (!n) return;
        queue<Node*> q; q.push(n);
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            cout << cur->data << " ";
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
    }
    //проверка на полноту         
    bool isComplete(Node* n) {
        if (!n) return true;
        queue<Node*> q; q.push(n);
        bool nullFound = false;
        while (!q.empty()) {
            Node* cur = q.front(); q.pop();
            if (!cur) nullFound = true;
            else {
                if (nullFound) return false;
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        return true;
    }
};
// ЧАСТЬ 2: BST
class BST {
public:
    Node* root = nullptr;
    ~BST() { destroyTree(root); }

    // Вставка
    Node* insert(Node* n, int key) {
        if (!n) return new Node(key);
        if (key < n->data) n->left = insert(n->left, key);
        else if (key > n->data) n->right = insert(n->right, key);
        return n;
    }
    // Поиск
    Node* search(Node* n, int key) {
        if (!n || n->data == key) return n;
        return key < n->data ? search(n->left, key) : search(n->right, key);
    }
    // Минимум (для удаления)
    Node* findMin(Node* n) { return n->left ? findMin(n->left) : n; }

    // Удаление (все три случая)
    Node* remove(Node* n, int key) {
        if (!n) return nullptr;
        if (key < n->data) n->left = remove(n->left, key);
        else if (key > n->data) n->right = remove(n->right, key);
        else {
            if (!n->left && !n->right) { delete n; return nullptr; }      // лист
            if (!n->left) { Node* t = n->right; delete n; return t; }    // один ребёнок
            if (!n->right) { Node* t = n->left;  delete n; return t; }
            Node* m = findMin(n->right);                                  // два ребёнка
            n->data = m->data;
            n->right = remove(n->right, m->data);
        }
        return n;
    }
    // Симметричный обход
    void inOrder(Node* n) {
        if (!n) return;
        inOrder(n->left);
        cout << n->data << " ";
        inOrder(n->right);
    }
    // Высота
    int height(Node* n) {
        return n ? 1 + max(height(n->left), height(n->right)) : 0;
    }
    //  сбалансированное BST из отсортированного массива
    Node* buildBalanced(vector<int>& a, int l, int r) {
        if (l > r) return nullptr;
        int mid = (l + r) / 2;
        Node* n = new Node(a[mid]);
        n->left = buildBalanced(a, l, mid - 1);
        n->right = buildBalanced(a, mid + 1, r);
        return n;
    }
};
int main() {
    setlocale(LC_ALL, "ru");

    cout << " ЧАСТЬ 1: Бинарное дерево \n";
    BinaryTree bt;
    bt.root = new Node(10);
    bt.root->left = new Node(5);
    bt.root->right = new Node(15);
    bt.root->left->left = new Node(3);
    bt.root->left->right = new Node(7);
    bt.root->right->right = new Node(20);
    bt.root->left->right->left = new Node(6);
    bt.root->right->right->left = new Node(18);

    cout << "Прямой:      "; bt.preOrder(bt.root);   cout << "\n";
    cout << "Симметричный:"; bt.inOrder(bt.root);    cout << "\n";
    cout << "Обратный:    "; bt.postOrder(bt.root);  cout << "\n";
    cout << "Уровневый:   "; bt.levelOrder(bt.root); cout << "\n";
    cout << "Дерево полное? " << (bt.isComplete(bt.root) ? "Да" : "Нет") << "\n\n";

    cout << "ЧАСТЬ 2: BST \n";
    BST bst;
    for (int k : {50, 30, 70, 20, 40, 60, 80}) bst.root = bst.insert(bst.root, k);

    cout << "In-order:       "; bst.inOrder(bst.root); cout << "\n";
    cout << "Поиск 40:       " << (bst.search(bst.root, 40) ? "найден" : "нет") << "\n";
    cout << "Поиск 100:      " << (bst.search(bst.root, 100) ? "найден" : "нет") << "\n";
    cout << "Высота:         " << bst.height(bst.root) << "\n";

    bst.root = bst.remove(bst.root, 30);
    cout << "После удал. 30: "; bst.inOrder(bst.root); cout << "\n";

    vector<int> sorted = { 10, 20, 30, 40, 50, 60, 70 };
    BST balanced;
    balanced.root = balanced.buildBalanced(sorted, 0, sorted.size() - 1);
    cout << "Сбалансир. BST: "; balanced.inOrder(balanced.root); cout << "\n\n";

    cout << "ЧАСТЬ 3: Применение BST \n";
    BST tree;
    int randomArr[20];
    cout << "Случайные: ";
    for (int i = 0; i < 20; i++) {
        randomArr[i] = rand() % 100;
        cout << randomArr[i] << " ";
        tree.root = tree.insert(tree.root, randomArr[i]);
    }
    cout << "\nIn-order:  "; tree.inOrder(tree.root); cout << "\n";

    Node* mn = tree.root; while (mn->left)  mn = mn->left;
    Node* mx = tree.root; while (mx->right) mx = mx->right;
    cout << "Минимум: " << mn->data << ", Максимум: " << mx->data << "\n";
    cout << "Высота: " << tree.height(tree.root) << "\n";
    int del;
    cout << "Введите число для удаления: ";
    cin >> del;
    tree.root = tree.remove(tree.root, del);
    cout << "После удаления: "; tree.inOrder(tree.root); cout << "\n";
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
