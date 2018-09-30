//
// Created by mrswimmer on 30.09.18.
//

#ifndef LAB_TREE_H
#define LAB_TREE_H

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

    Tree() {
    }

    void print() {
        printNode(root);
    }


    void add(T data) {
        addNode(root, data);
    }

private:

    Node *root = NULL;

    void printNode(Node *node) {
        if (node->left != NULL)
            printNode(node->left);
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
};


#endif //LAB_TREE_H
