#ifndef AVLTREE_H
#define AVLTREE_H

#include "node.h"

class AVLTree {
public:
    AVLTree();
    bool empty() const {return nullptr == root;};
    void insert(int key, string value = "") {root = insert(root, key, value);};

    /*
     *  not implemented -> your task!
     */
    // remove the key/value from the tree
    void remove(int key);
    // remove all key/value pairs from the tree
    void clear();
    // check if key is present
    bool member(int key);
    // check if key is present and return the value for it
    // (assumes unique keys)
    bool find(int key, string &value);
    // check if key is present and replace value if it is
    // (assumes unique keys)
    bool set(int key, string value);
    // check if key is present and insert key/value only if it is not
    // (when used always instead of insert, only adds unique keys)
    bool probe(int key, string value);

    // helpful for debugging
    void show() const {show(root, 0);};   // print out tree on terminal
    void writeDot(const string &filename) const; // write out tree to file, suitable for graphviz's dot

    // traversal
    void inorder() const {inorder(root);};
    void preorder() const {preorder(root);};
    void postorder() const {postorder(root);};

private:
    // helper functions
    int height(Node* p) const;
    int difference(Node* p) const;

    // rotations
    Node* right_rotation(Node* p);
    Node* left_rotation(Node* p);
    Node* rightLeft_rotation(Node* p);
    Node* leftRight_rotation(Node* p);

    // AVL rules for selfbalancing
    Node* balance(Node* p);

    Node* insert(Node* p, int key, const string& value);

    // implementation of debugging methods
    void show(Node* p, int) const;
    void writeDot(ostream &fs, Node* p) const;

    // implementation of traversal
    void inorder(Node* p) const;
    void preorder(Node* p) const;
    void postorder(Node* p) const;

    //Aufgabe1 + 2
    Node* find(Node* p, int key, string &value);
    Node* remove(Node* p, int key);
    Node* FindMin(Node* p);
    Node* member(Node* p, int key);
    Node* set(Node* p, int key, string value);
    Node* probe(Node* p, int key, string value);
    // where everything starts for this AVL tree
    Node* root;
};

#endif // AVLTREE_H
