//
// Created by mrswimmer on 30.09.18.
//

#ifndef LAB_TREE_H
#define LAB_TREE_H

#define EMPTY_TREE_ERR 1
#define INVALID_INDEX_ERR 2
#define ITERATOR_END_ERR 3
#define ITERATOR_BEGIN_ERR 4

#include <iostream>

using namespace std;

template<class T>
class Tree {

    class Node {
    public:
        Node *left;
        Node *right;
        T data;

        Node(T data) {
            this->data = data;
            left = NULL;
            right = NULL;
        }
    };

public:

    void print() {
        printNode(root);
    }

    void add(T data) {
        addNode(root, data);
    }

    bool isEmpty() {
        return root == NULL;
    }

    Node *get(T data) {

    }

    int size() {
        count = 0;
        printNode(root);
        return count;
    }

    virtual ~Tree() {

    }

    class Iterator {
    public:
        Node *node;
        Tree *tree;

        Iterator(Tree *t) : tree(t) {

        }

        Iterator *first() {
            if (tree->isEmpty())
                throw EMPTY_TREE_ERR;
            down(tree->root);
            return this;
        }

        Iterator *last() {
            if (tree->isEmpty())
                throw EMPTY_TREE_ERR;
            up(tree->root);
            return this;
        }

        Iterator &operator--(int) {
            if (tree->isEmpty()) throw EMPTY_TREE_ERR;
            //do it
            return *this;
        };

        Iterator &operator++(int) {
            if (tree->isEmpty()) throw EMPTY_TREE_ERR;
            //do it
            return *this;
        };

        bool isInstalled() {
            return !this->node == NULL;
        }

        T read() {
            if (tree->isEmpty()) throw EMPTY_TREE_ERR;
            return node->data;
        }

        void write(T data) {
            if (tree->isEmpty()) throw EMPTY_TREE_ERR;
            node->data = data;
        }

        void down(Node *node) {
            this->node = node;
            if (node->left != NULL)
                down(node->left);
        }

        void up(Node *node) {
            this->node = node;
            if (node->right != NULL)
                up(node->right);
        }

    };

private:

    Node *root = NULL;

    int count = 0;

    void printNode(Node *node) {
        if (node->left != NULL)
            printNode(node->left);
        count++;
        cout << node->data << endl;
        if (node->right != NULL)
            printNode(node->right);
    }

    void addNode(Node *node, T data) {
        if (node == NULL) {
            root = new Node(data);
        } else {
            if (data < node->data) {
                if (node->left != NULL)
                    addNode(node->left, data);
                else {
                    node->left = new Node(data);
                }
            }
            if (data > node->data) {
                if (node->right != NULL)
                    addNode(node->right, data);
                else {
                    node->right = new Node(data);
                }
            }
        }
    }

    void clear() {
        //do it
    }
};


#endif //LAB_TREE_H
