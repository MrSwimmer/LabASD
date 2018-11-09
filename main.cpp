
#include "tree/Tree.h"

using namespace std;


void showMenu() {
    cout << endl;

    cout << "1. Watch tree" << endl;
    cout << "2. Clear tree" << endl;
    cout << "3. Empty check" << endl;
    cout << "4. Show value by key" << endl;
    cout << "5. Change value by key" << endl;
    cout << "6. Add value by key" << endl;
    cout << "7. Delete value by key" << endl;
    cout << "8. Walk" << endl;
    cout << "9. Insert in root" << endl;
    cout << "10. Tree size" << endl;
    cout << "11. Iterator to first key position" << endl;
    cout << "12. Iterator to last key position" << endl;
    cout << "13. Change value at iterator's position" << endl;
    cout << "14. Show value at iterator's position" << endl;
    cout << "15. Next key" << endl;
    cout << "16. Prev key" << endl;
    cout << "0. Exit" << endl;
}

int main() {
    Tree<int, int> tree;
    Tree<int, int>::Iterator iter(tree);

    showMenu();

    bool exit = false;
    int com;
    while (!exit) {
        cout << "input command:";
        cin >> com;
        cout << endl;
        try {
            switch (com) {
                case 0:
                    exit = true;
                    break;
                default:
                    cout << "No such command exist" << endl;
                    break;

                case 1: {
                    tree.print();
                    break;
                }

                case 2: {
                    tree.clear();
                    break;
                }

                case 3: {
                    cout << tree.isEmpty() << endl;
                    break;
                }

                case 4: {
                    cout << "Insert key: ";
                    int k;
                    cin >> k;
                    cout << endl;
                    cout << tree.get(k) << endl;
                    break;
                }

                case 5: {
                    cout << "Insert key: ";
                    int k;
                    cin >> k;
                    cout << endl;
                    cout << "Insert new value: ";
                    cin >> tree.get(k);
                    cout << endl;
                    break;
                }

                case 6: {
                    cout << "Insert key: ";
                    int k;
                    cin >> k;
                    cout << endl;
                    cout << "Insert new value: ";
                    int val;
                    cin >> val;
                    cout << tree.add(val, k) << endl;
                    break;
                }

                case 7: {
                    cout << "Insert key: ";
                    int k;
                    cin >> k;
                    cout << endl;
                    cout << tree.remove(k) << endl;
                    break;
                }

                case 8: {
                    tree.Lt_t_Rt();
                    break;
                }

                case 9: {
                    //ToDo Реализовать вставку в корень
                    break;
                }

                case 10: {
                    cout << "Tree length: " << tree.getSize() << endl;
                    break;
                }

                case 11: {
                    iter.first();
                    break;
                }

                case 12: {
                    iter.last();
                    break;
                }

                case 13: {
                    cout << "Insert new value: ";
                    cin >> *iter;
                    cout << endl;
                    break;
                }

                case 14: {
                    cout << *iter << endl;
                    break;
                }

                case 15: {
                    cout << iter++ << endl;
                    break;
                }

                case 16: {
                    cout << iter-- << endl;
                    break;
                }

                case 17: {
                    break;
                }

            }
        } catch (int code) {
            switch (code) {
                case EMPTY_TREE:
                    cout << "Empty tree" << endl;
                    break;
                case KEY_DOES_NOT_EXIST:
                    cout << "this key does not exist in tree" << endl;
                    break;
                case ITERATOR_END:
                    cout << "Iterator is out of tree" << endl;
                    break;
                default:
                    break;
            }
        }
    }

    return 0;
}