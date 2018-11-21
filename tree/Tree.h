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
        Data data;
        Key key;
        Node *left;
        Node *right;

        Node(Data x, Key y);
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

    private:
        Node *tree_successor(Node *x);

        Node *left_parent(Node *r, Node *x);

        Node *tree_predecessor(Node *x);

        Node *right_parent(Node *r, Node *x);
    };


    friend class Iterator;

public://методы интерфейса

    Tree();//конструктор по умолчанию
    Tree(Tree<Data, Key> &tree);//конструктор копирования
    ~Tree();//деструктор

    long long getOperations(); //число просмотренных операций узлов дерева
    int getSize(); //опрос размера дерева
    void clear(); //очистка дерева
    bool isEmpty(); //проверка на пустоту
    Data &get(Key key); //доступ к данным по ключу
    bool add(Data data, Key key); //включение данных с заданным ключом
    bool remove(Key key); //удаление данных с заданным ключом
    void Lt_t_Rt(); //обход узлов дерева по схеме Lt->data->Rt
    bool root_insert(Data data, Key key); //Вставка в корень
    void print(); //вывод структуры дерева на экран

private:
    Node *root; //указатель на корень

    int length; //длина дерева

    long long operations; //число просмотров

    Node *getRoot();

    void setRoot(Node *root);


    Node *addSupport(Node *root, Data data, Key key, bool &inserted);//включение данных с заданным ключом
    //вспомогательные методы
    void show(Node *t, int level);//вспомогательный метод распечатки

    void levelCounter(Node *t, int level, int &sum);

    void copy(Node *t);


    Node *removeSupport(Node *root, Key key, bool &deleted);

    Node *del(Node *rightNode, Node *root);

    Node *L(Node *rootNode);

    Node *R(Node *rootNode);

    Data &searchSupport(Node *rootNode, Key key);

    void Lt_t_Rt(Node *node); //обход узлов дерева по схеме Lt->data->Rt

    void DelAll(Node *t);


    Node *root_insert_rec(Node *rootNode, Data data, Key key, bool &inserted);


};

//--------------Методы класса Tree-----------
template<class Data, class Key>
Tree<Data, Key>::Tree() { //По умолчанию
    root = nullptr;
    length = 0;
}

template<class Data, class Key>
Tree<Data, Key>::Tree(Tree<Data, Key> &tree) { //Конструктор копирования
    root == NULL;
    length = 0;
    copy(tree.root);
}

template<class Data, class Key>
void Tree<Data, Key>::copy(Tree<Data, Key>::Node *t) { //Копирование дерева
    if (t == NULL) return;
    add(t->data, t->key);//добавляем узел в дерево
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
    if (length == 0) return;
    if (getRoot()) {
        DelAll(getRoot());
    }
    setRoot(NULL);
    length = 0;
    operations = 0;
}

template<class Data, class Key>
void Tree<Data, Key>::DelAll(Node *t) {
    if (t->left) DelAll(t->left);                //Ничего не сделает если ссылки пусты
    if (t->right) DelAll(t->right);
    delete t;
}


template<class Data, class Key>
// Проверка дерева на пустоту
bool Tree<Data, Key>::isEmpty() { return (root == nullptr); }


template<class Data, class Key>
// Поиск
Data &Tree<Data, Key>::get(Key key) {
    if (getRoot() == nullptr) throw EMPTY_TREE;
    operations++;
    return searchSupport(getRoot(), key);
}


template<class Data, class Key>
// Поиск элемента
Data &Tree<Data, Key>::searchSupport(Node *rootNode, Key key) {
    if (rootNode == nullptr) {
        throw KEY_DOES_NOT_EXIST;
    }

    if (key == rootNode->key) {
        return rootNode->data;
    }

    if (key < rootNode->key) {
        operations++;
        return searchSupport(rootNode->left, key);
    } else {
        operations++;
        return searchSupport(rootNode->right, key);
    }
}


template<class Data, class Key>
//Вставка по ключу
bool Tree<Data, Key>::add(Data data, Key key) {
    operations = 0;
    bool isInserted = false;
    if (root == NULL) {
        root = new Node(data, key);
        return true;
    }
    addSupport(root, data, key, isInserted);
    return isInserted;
}

template<class Data, class Key>
//Вставка по ключу
typename Tree<Data, Key>::Node *Tree<Data, Key>::addSupport(Node *rootNode, Data data, Key key, bool &inserted) {
    if (rootNode == nullptr) {
        inserted = true;
        length++;
        operations++;
        rootNode = (new Node(data, key));
        return rootNode;
    }
    operations++;
    if (key == rootNode->key) {
        inserted = false;
        return rootNode;
    }
    if (key < rootNode->key) {
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
    operations++;
    if (key < rootNode->key) {
        rootNode->left = removeSupport(rootNode->left, key, deleted);
        return rootNode;
    }

    if (key > rootNode->key) {
        rootNode->right = removeSupport(rootNode->right, key, deleted);
        return rootNode;
    }


    deleted = true;
    length--;

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
    operations++;
    if (rightNode->left != nullptr) {
        rightNode->left = del(rightNode->left, root);
        return rightNode;
    }
    root->key = rightNode->key;
    root->data = rightNode->data;
    Node *buffer = rightNode->right;
    rightNode = nullptr;
    return buffer;
}


template<class Data, class Key>
// Обход дерева Lt_t_Rt
void Tree<Data, Key>::Lt_t_Rt() {
    Lt_t_Rt(getRoot());
}


template<class Data, class Key>
// Обход дерева Lt_t_Rt
void Tree<Data, Key>::Lt_t_Rt(Node *node) {
    if (node == nullptr) return;

    Lt_t_Rt(node->left);
    cout << node->key << ":" << node->data << endl;
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
    cout << t->key << endl;
    show(t->left, level + 1);
}

template<class Data, class Key>
long long Tree<Data, Key>::getOperations() {

    long long cp = operations;
    operations = 0;
    return cp;
}

//вспомогательные методы
template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::Iterator::tree_successor(Tree<Data, Key>::Node *x) {
    if (x == NULL) return NULL;
    if (x->right != NULL) {
        Node *tmp = x->right;
        if (tmp->left != NULL) {
            tmp = tmp->left;
            tree_successor(tmp);
        }
        return tmp;
    } else return left_parent(tree->getRoot(), x);
}

template<class Data, class Key>
typename Tree<Data, Key>::Node *
Tree<Data, Key>::Iterator::left_parent(Tree<Data, Key>::Node *r, Tree<Data, Key>::Node *x) {
    if (r == NULL) return NULL;
    if (x->key < r->key) {
        Node *n = left_parent(r->left, x);
        if (n != NULL) return n;
        else return r;
    } else return left_parent(r->right, x);

}

template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::Iterator::tree_predecessor(Tree<Data, Key>::Node *x) {
    if (x == NULL) return NULL;
    if (x->left != NULL) {
        Node *tmp = x->left;
        if (tmp->right != NULL) {
            tmp = tmp->right;
            tree_successor(tmp);
        }
        return tmp;
    } else return right_parent(tree->getRoot(), x);
}

template<class Data, class Key>
typename Tree<Data, Key>::Node *
Tree<Data, Key>::Iterator::right_parent(Tree<Data, Key>::Node *r, Tree<Data, Key>::Node *x) {
    if (r == NULL) return NULL;
    if (x->key > r->key) {
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

template<class Data, class Key>
bool Tree<Data, Key>::root_insert(Data data, Key key) {
    bool inserted = false;
    if (root == NULL) {
        operations++;
        root = new Node(data, key);
        return true;
    }
    root = root_insert_rec(root, data, key, inserted);
    return inserted;
}


template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::root_insert_rec(Node *rootNode, Data data, Key key, bool &inserted) {
    operations++;
    if (rootNode == NULL) {
        length++;
        inserted = true;
        rootNode = new Node(data, key);
        return rootNode;
    }

    if (key == rootNode->key) {
        inserted = false;
        return rootNode;
    }

    if (key < rootNode->key) {
        rootNode->left = root_insert_rec(rootNode->left, data, key, inserted);
        if (inserted) {
            return R(rootNode);
        } else {
            return rootNode;
        }

    } else {
        rootNode->right = root_insert_rec(rootNode->right, data, key, inserted);
        if (inserted) {
            rootNode = L(rootNode);
            return rootNode;
        } else {
            return rootNode;
        }

    }
}

//Правый поворот
template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::R(Node *rootNode) {
    operations++;
    if (rootNode == NULL) {
        return NULL;
    } else {
        Node *x = rootNode->left;
        rootNode->left = x->right;
        x->right = rootNode;
        rootNode = x;
        return x;
    }
}


//Левый поворот
template<class Data, class Key>
typename Tree<Data, Key>::Node *Tree<Data, Key>::L(Node *rootNode) {
    operations++;
    if (rootNode == NULL) {
        return NULL;
    } else {
        Node *x = rootNode->right;
        rootNode->right = x->left;
        x->left = rootNode;
        rootNode = x;
        return x;
    }
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
        return cur->data;
    } else throw ITERATOR_END;
}

template<class Data, class Key>
bool Tree<Data, Key>::Iterator::operator++(int) {
    if (status()) {
        cur = tree_successor(cur);
        return true;
    } else return false;
}

template<class Data, class Key>
bool Tree<Data, Key>::Iterator::operator--(int) {
    if (status()) {
        cur = tree_predecessor(cur);
        return true;
    } else return false;
}

template<class Data, class Key>
Tree<Data, Key>::Node::Node(Data x, Key y) {
    data = x;
    key = y;
    left = NULL;
    right = NULL;
}