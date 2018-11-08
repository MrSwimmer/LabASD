
#include "tree/Tree.h"

using namespace std;

int main() {
    Tree<int, int> tree;

//    cout<<tree.add( 7, 5)<<endl;
//    cout<<tree.add(7, 4)<<endl;
//    cout<<tree.add( 7, 6)<<endl;
//    cout<<tree.add( 7, 2)<<endl;
//    cout<<tree.add( 7, 9)<<endl;
//    cout<<tree.add( 7, 10)<<endl;
//    cout<<tree.add( 7, 11)<<endl;
    cout << tree.root_insert(7, 0) << endl;
    cout << tree.root_insert(8, 7) << endl;
    cout << tree.root_insert(9, 8) << endl;
    cout << tree.root_insert(10, 2) << endl;
    cout << tree.root_insert(11, 3) << endl;
    cout << tree.root_insert(12, 4) << endl;
    cout << tree.root_insert(13, 100) << endl;
    cout << tree.root_insert(14, 50) << endl;
    cout << tree.root_insert(15, 1) << endl;
    cout << tree.search(3) << endl;
    tree.print();
    return 0;
}