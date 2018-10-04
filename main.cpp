#include <iostream>
#include "tree/Tree.h"

using namespace std;

int main() {
    Tree<int> tree;
    tree.add(10);
    tree.add(12);
    tree.add(34);
    tree.add(33);
    tree.add(12);
    tree.add(121);
    tree.add(1);
    tree.add(3);
    tree.print();
    tree.cl();
    int size = tree.size();
    cout << size;
    /*Tree<int>::Iterator i(&tree);
    i.first();
    cout << i.node->data;
    i.last();
    cout << i.node->data;*/
    return 0;
}