#include <iostream>
#include "tree/Tree.h"

using namespace std;

int main() {
    Tree<int, int> tree;

    cout<<tree.add( 7, 5)<<endl;
    cout<<tree.add(7, 4)<<endl;
    cout<<tree.add( 7, 6)<<endl;
    cout<<tree.add( 7, 2)<<endl;
    cout<<tree.add( 7, 9)<<endl;
    tree.print();
    return 0;
}