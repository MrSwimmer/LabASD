#include <iostream>
#include <list>
#include <stack>

#define EMPTY_TREE 0
#define KEY_DOES_NOT_EXIST 1
#define ITERATOR_END 2

#define PAIR std::pair< Node *, bool >            //0 - влево, 1 - вправо

using namespace std;


template<class Data, class Key>
class Tree {
    class Node {

    public:
        Data t;
        Key k;
        Node *left;
        Node *right;

        //Node();
        Node(Data x, Key y);
        //~Node();
    };

    friend class Tree;

public:
    class Iterator {
    private:
        Tree *tree;
        Node *cur;
    public:
        Iterator(Tree<Data, Key> &tree);//конструктор
        bool first();//установка на первый узел в дереве с минимальным ключом
        bool last();//установка на последний узел в дереве с максимальным ключом
        bool status();//проверка состояния итератора
        Data &operator*();//доступ по чтению и записи к данным текущего узла в дереве
        bool operator++(int);//переход к следующему по значению ключа узлу в дереве
        bool operator--(int);//переход к предыдущему по значению ключа узлу в дереве
    };

    friend class Iterator;

public://методы интерфейса
    int getSize();//опрос размера дерева
    void clear();//очистка дерева
    bool isEmpty();//проверка на пустоту
    Data &search(Key key);//доступ к данным по ключу




    bool add(Data data, Key key);//включение данных с заданным ключом
    Node *addSupport(Node *root, Data data, Key key, bool &inserted);//включение данных с заданным ключом

    bool remove(Key key);//удаление данных с заданным ключом
    void Lt_t_Rt(Node *node);//обход узлов дерева по схеме Lt->t->Rt

    void print();//вывод структуры дерева на экран
    int getOperations();//число просмотренных операций узлов дерева

    bool root_insert(Data data, Key key);

    Tree();//конструктор по умолчанию
    Tree(Tree<Data, Key> &ttree);//конструктор копирования
    ~Tree();//деструктор

private:
    Node *root;
public:
    void setRoot(Node *root);

    int length;//длина дерева
    int operations;//число просмотров

private:
//указатель на корень


    //вспомогательные методы
    void show(Node *t, int level);//вспомогательный метод распечатки
    void levelCounter(Node *t, int level, int &sum);

    Node *tree_successor(Node *x);

    Node *left_parent(Node *r, Node *x);

    Node *tree_predecessor(Node *x);

    Node *right_parent(Node *r, Node *x);

    void copy(Node *t);

    Node *getRoot();

    Node *removeSupport(Node *root, Key key, bool &deleted);

    Node *del(Node *rightNode, Node *root);

    Node *L(Node *rootNode);

    Node *R(Node *rootNode);

    Data &searchSupport(Node *rootNode, Key key);
};

//--------------Методы класса Tree-----------
template<class Data, class Key>
Tree<Data, Key>::Tree() { //По умолчанию
    root = NULL;
    length = 0;
}

template<class Data, class Key>
Tree<Data, Key>::Tree(Tree<Data, Key> &ttree) { //Конструктор копирования
    root == NULL;
    length = 0;
    copy(ttree.root);
}

template<class Data, class Key>
void Tree<Data, Key>::copy(Tree<Data, Key>::Node *t) { //Копирование дерева
    if (t == NULL) return;
    add(t->t, t->k);//добавляем узел в дерево
    copy(t->left);//делаем то же самое для его сыновей
    copy(t->right);
}

template<class Data, class Key>
Tree<Data, Key>::~Tree() {
    clear();
}

template<class Data, class Key>
int Tree<Data, Key>::getSize() { return length; }

template<class Data, class Key>

//Очистка дерева
void Tree<Data, Key>::clear() {
    //ToDo clear()
}

template<class Data, class Key>
// Проверка дерева на пустоту
bool Tree<Data, Key>::isEmpty() { return (root == NULL); }



template<class Data, class Key>
// Поиск
Data &Tree<Data, Key>::search(Key key) {
    if (getRoot() == nullptr) throw EMPTY_TREE;
    return searchSupport(getRoot(), key);
}


template<class Data, class Key>
// Поиск элемента
Data &Tree<Data, Key>::searchSupport(Node *rootNode, Key key) {
    if (rootNode == nullptr) {
        throw KEY_DOES_NOT_EXIST;
    }

    if (key == rootNode->k) {
        return rootNode->t;
    }

    if (key < rootNode->k) {
        return searchSupport(rootNode->left, key);
    } else {
        return searchSupport(rootNode->right, key);
    }
}






template<class Data, class Key>
//Вставка по ключу
bool Tree<Data, Key>::add(Data data, Key key) {
    operations = 0;
    bool isInserted = false;
    addSupport(getRoot(), data, key, isInserted);
    return isInserted;
}

template<class Data, class Key>
//Вставка по ключу
typename Tree<Data, Key>::Node *Tree<Data, Key>::addSupport(Node *rootNode, Data data, Key key, bool &inserted) {
    operations = 0;
    if (rootNode == nullptr) {
        inserted = true;
        if (getRoot() == nullptr) {
            setRoot(new Node(data, key));
            return getRoot();
        }
        rootNode = new Node(data, key);
        return rootNode;
    }

    if (key == rootNode->k) {
        inserted = false;
        return rootNode;
    }
    if (key < rootNode->k) {
        rootNode->left = addSupport(rootNode->left, data, key, inserted);
    } else {
        rootNode->right = addSupport(rootNode->right, data, key, inserted);
    }
    return rootNode;
}

template<class Data, class Key>
//Удаление по ключу
bool Tree<Data, Key>::remove(Key key) {
    bool deleted = false;
    removeSupport(getRoot(), key, deleted);
    return deleted;
}

template<class Data, class Key>
//Удаление по ключу
typename Tree<Data, Key>::Node *Tree<Data, Key>::removeSupport(Node *rootNode, Key key, bool &deleted) {
    if (rootNode == nullptr) {
        deleted = false;
        return rootNode;
    }
    if (key < rootNode->k) {
        rootNode->left = removeSupport(rootNode->left, key, deleted);
        return rootNode;
    }

    if (key > rootNode->k) {
        rootNode->right = removeSupport(rootNode->right, key, deleted);
        return rootNode;
    }


    deleted = true;

    if (rootNode->left == nullptr and rootNode->right == nullptr) {
        rootNode = nullptr;
        return nullptr;
    }

    if (rootNode->left == nullptr) {
        Node *buffer = rootNode->right;
        rootNode = nullptr;
        return buffer;
    }

    if (rootNode->right == nullptr) {
        Node *buffer = rootNode->left;
        rootNode = nullptr;
        return buffer;
    }

    rootNode->right = del(rootNode->right, rootNode);
}

template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::del(Node *rightNode, Node *root) {

    if (rightNode->left != nullptr) {
        rightNode->left = del(rightNode->left, root);
        return rightNode;
    }
    root->k = rightNode->k;
    root->t = rightNode->t;
    Node *buffer = rightNode->right;
    rightNode = nullptr;
    return buffer;
}


template<class Data, class Key>
// Обход дерева Lt_t_Rt
void Tree<Data, Key>::Lt_t_Rt(Node *node) {
    if (node == nullptr) return;

    Lt_t_Rt(node->left);
    cout << node->t << endl;
    Lt_t_Rt(node->right);
}


template<class Data, class Key>
// Используется для вывода структуры дерева
void Tree<Data, Key>::levelCounter(Tree<Data, Key>::Node *t, int level, int &sum) {
    if (t == NULL) return;
    levelCounter(t->left, level + 1, sum);
    levelCounter(t->right, level + 1, sum);
    if (t->left == NULL || t->right == NULL) sum += level;
}

template<class Data, class Key>
// Вывод на экран структуры дерева
void Tree<Data, Key>::print() {
    if (root == NULL) return;
    show(root, 0);
}

template<class Data, class Key>
// Вывод на экран структуры дерева
void Tree<Data, Key>::show(Node *t, int level) {
    if (t == NULL) return;
    show(t->right, level + 1);
    for (int i = 0; i <= 3 * level; i++) {
        cout << " ";
    }
    cout << t->k << endl;
    show(t->left, level + 1);
}

template<class Data, class Key>
int Tree<Data, Key>::getOperations() { return operations; }

//вспомогательные методы
template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::tree_successor(Tree<Data, Key>::Node *x) {
    if (x == NULL) return NULL;
    if (x->right != NULL) {
        Node *tmp = x->right;
        while (tmp->left != NULL) {
            tmp = tmp->left;
        }
        return tmp;
    } else return left_parent(root, x);
}

template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::left_parent(Tree<Data, Key>::Node *r, Tree<Data, Key>::Node *x) {
    if (r == NULL) return NULL;
    if (x->k < r->k) {
        Node *n = left_parent(r->left, x);
        if (n != NULL) return n;
        else return r;
    } else return left_parent(r->right, x);

}

template<class Data, class Key>
// Переписать рекурсивно
typename Tree<Data, Key>::Node *Tree<Data, Key>::tree_predecessor(Tree<Data, Key>::Node *x) {
    if (x == NULL) return NULL;
    if (x->left != NULL) {
        Node *tmp = x->left;
        while (tmp->right != NULL) {
            tmp = tmp->right;
        }
        return tmp;
    } else return right_parent(root, x);
}

template<class Data, class Key>
// Переписать рекурсивно
typename Tree<Data, Key>::Node *Tree<Data, Key>::right_parent(Tree<Data, Key>::Node *r, Tree<Data, Key>::Node *x) {
    if (r == NULL) return NULL;
    if (x->k > r->k) {
        Node *n = right_parent(r->right, x);
        if (n != NULL) return n;
        else return r;
    } else return right_parent(r->left, x);
}

template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::getRoot() {
    return root;
}

template<class Data, class Key>
void Tree<Data, Key>::setRoot(Tree::Node *root) {
    Tree::root = root;
}


//Вставка в корень
template<class Data, class Key>
bool Tree<Data, Key>::root_insert(Data data, Key key) {
    Node *t = getRoot();
    if (t == NULL) {
        length++;
        setRoot(new Node(data, key));
        return true;
    }
    Node *pred;
    stack<PAIR > stk;        //stack< std::pair< Node*, bool > > stk
    stack<PAIR > predstk;    //Стек с предыдущими
    while (t != NULL) {
        pred = t;
        if (key == t->k) {        //Если нельзя вставить
            while (!stk.empty()) {    //Чистим стек
                stk.pop();
                predstk.pop();
            }
            return false;            //Выходим
        }
        if (key < t->k) {            //Двигаемся налево
            stk.push(PAIR(t, 1));
            predstk.push(PAIR(t, 1));
            t = t->left;
        } else {                        //Двигаемся направо
            stk.push(PAIR(t, 0));
            predstk.push(PAIR(t, 0));
            t = t->right;
        }
    }
    if (key < pred->k) pred->left = new Node(data, key);
    else pred->right = new Node(data, key);
    //Раскрутка стеков
    predstk.pop();
    while (!predstk.empty()) {            //Доходим до вершины дерева

        PAIR pr = stk.top();
        Node *n = pr.first;
        PAIR pred = predstk.top();
        if (pr.second) {
            if (pred.second) {
                pred.first->left = R(n);
            } else {
                pred.first->right = R(n);
            }
        } else {
            if (pred.second) {
                pred.first->left = L(n);
            } else {
                pred.first->right = L(n);
            }
        }
        predstk.pop();
        stk.pop();
    }
    PAIR pr = stk.top();                    //Работаем с вершиной
    Node *n = pr.first;
    if (pr.second) {
        setRoot(R(n));
    } else {
        setRoot(L(n));
    }
    stk.pop();
    return true;
}

//Правый поворот
template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::R(Node *p) {
    Node *q = p->left;
    if (!q) return p;
    p->left = q->right;
    q->right = p;
    return q;
}

//Левый поворот
template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::L(Node *q) {
    Node *p = q->right;
    if (!p) return q;
    q->right = p->left;
    p->left = q;
    return p;
}


//--------------Методы класса Iterator----------
template<class Data, class Key>
Tree<Data, Key>::Iterator::Iterator(Tree<Data, Key> &tree) {
    this->tree = &tree;
    cur = NULL;
}

template<class Data, class Key>
bool Tree<Data, Key>::Iterator::status() {
    return (cur != NULL);
}

template<class Data, class Key>
bool Tree<Data, Key>::Iterator::first() {
    cur = tree->root;
    if (cur != NULL) {
        while (cur->left != NULL)
            cur = cur->left;
        return true;
    } else return false;
}

template<class Data, class Key>
bool Tree<Data, Key>::Iterator::last() {
    cur = tree->root;
    if (cur != NULL) {
        while (cur->right != NULL)
            cur = cur->right;
        return true;
    } else return false;
}

template<class Data, class Key>
Data &Tree<Data, Key>::Iterator::operator*() {
    if (status()) {
        return cur->t;
    } else throw ITERATOR_END;
}

template<class Data, class Key>
bool Tree<Data, Key>::Iterator::operator++(int) {
    if (status()) {
        cur = tree->tree_successor(cur);
        return true;
    } else return false;
}

template<class Data, class Key>
bool Tree<Data, Key>::Iterator::operator--(int) {
    if (status()) {
        cur = tree->tree_predecessor(cur);
        return true;
    } else return false;
}
//---------------Методы класса Node-------------
/*
template <class Data, class Key>
Tree<Data,Key>::Node::Node() {
    left=NULL;
    right=NULL;
}*/

template<class Data, class Key>
Tree<Data, Key>::Node::Node(Data x, Key y) {
    t = x;
    k = y;
    left = NULL;
    right = NULL;
}


/*
template <class Data, class Key>
Tree<Data,Key>::Node::~Node() {
    delete t;
    delete k;
    left=NULL;
    right=NULL;
}*/