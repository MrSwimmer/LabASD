
#include "tree/Tree.h"

#include <math.h>

using namespace std;

typedef unsigned long long INT_64;

INT_64 lrand() {
    return rand() << 16 | rand();
}

void test_rand(int n) {
    Tree<INT_64, int> tree;

    INT_64 *m = new INT_64[n];

    for (int i = 0; i < n; i++) {
        m[i] = lrand();
        tree.add(1, m[i]);
    }


    double I = 0;
    double D = 0;
    double S = 0;

    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) {
            tree.remove(lrand());
            D += tree.getOperations();
            tree.add(1, m[rand() % n]);
            I += tree.getOperations();
            try {
                tree.get(lrand());
                S += tree.getOperations();
            } catch (int code) { S += tree.getOperations(); }
        } else {
            int ind = rand() % n;
            tree.remove(m[ind]);
            D += tree.getOperations();
            INT_64 key = lrand();
            tree.add(1, key);
            I += tree.getOperations();
            m[ind] = key;
            try {
                tree.get(m[rand() % n]);
                S += tree.getOperations();
            } catch (int code) { S += tree.getOperations(); }

        }

    }
    cout << "items count:" << tree.getSize() << endl;
    cout << "1.39*log2(n)=" << 1.39 * (log(n) / log(2)) << endl;
    cout << "Count insert: " << I / (n / 2) << endl;
    cout << "Count delete: " << D / (n / 2) << endl;
    cout << "Count search: " << S / (n / 2) << endl;
    delete[] m;

}

void test_sort(int n) {
    Tree<INT_64, int> tree;

    INT_64 *m = new INT_64[n];

    for (int i = 0; i < n; i++) {
        m[i] = i * 1000;
        tree.add(1, m[i]);
    }

    cout << "items count:" << tree.getSize() << endl;
    double I = 0;
    double D = 0;
    double S = 0;

    for (int i = 0; i < n / 2; i++) {
        if (i % 10 == 0) {
            int k = lrand() % (1000 * n);
            k = k + !(k % 2);
            tree.remove(k);
            D += tree.getOperations();
            tree.add(1, m[rand() % n]);
            I += tree.getOperations();
            k = lrand() % (1000 * n);
            k = k + !(k % 2);
            try {
                tree.get(k);
                S += tree.getOperations();
            } catch (int code) { S += tree.getOperations(); }
        } else {
            int ind = rand() % n;
            tree.remove(m[ind]);
            D += tree.getOperations();
            int k = lrand() % (1000 * n);
            k = k + k % 2;
            tree.add(1, k);
            I += tree.getOperations();
            m[ind] = k;
            try {
                tree.get(m[rand() % n]);
                S += tree.getOperations();
            } catch (int code) { S += tree.getOperations(); }

        }
    }
    cout << "items count:" << tree.getSize() << endl;
    cout << "n/2=" << n / 2 << endl;
    cout << "Count insert: " << I / (n / 2) << endl;
    cout << "Count delete: " << D / (n / 2) << endl;
    cout << "Count search: " << S / (n / 2) << endl;
    delete[] m;
}





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
    cout << "17. test" << endl;
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
                    cout << "Insert key: ";
                    int k;
                    cin >> k;
                    cout << endl;
                    cout << "Insert new value: ";
                    int val;
                    cin >> val;
                    cout << tree.root_insert(val, k) << endl;
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
                    int number;
                    cout << "Input tree length: ";
                    cin >> number;
                    cout << endl;
                    cout << "Random tree: " << endl;
                    test_rand(number);
                    cout << "--------------------------------------------" << endl;
                    cout << "Sorted tree: " << endl;
                    test_sort(number);
                    break;
                }

                case 100: {
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