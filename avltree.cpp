/*
 * Author: S. Rapp (2020)
 *
 * This is based on the first google hit of "AVL in C++"
 * https://www.tutorialspoint.com/cplusplus-program-to-implement-avl-tree
 * by Karthikeya Boyini
 *
 * NOTE: It used to have a weird notion of right and left and partly some
 * 'C-ish old-style' that I fixed mostly. I also added a value field to make
 * it more interesting / useful. The root is now inside the AVLTree class
 * and not a global variable any more.
 */

#include <iostream>
#include <fstream>

#include "avltree.h"


using namespace std;

AVLTree::AVLTree()
    : root(nullptr)
{
}

int AVLTree::height(Node* t) const
{
    int h = 0;
    if (nullptr != t) {
        int l_height = height(t->left);
        int r_height = height(t->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

int AVLTree::difference(Node* p) const
{
    int l_height = height(p->left);
    int r_height = height(p->right);

    return (r_height - l_height);
}

Node* AVLTree::left_rotation(Node* parent)
{
    //cout<<"Left Rotation on " << parent->key << endl;
    Node *t;
    t = parent->right;          // this will be our new root
    parent->right = t->left;    // hand over subtree
    t->left = parent;           // rotate parent down
    return t;                   // return new root
}

Node* AVLTree::right_rotation(Node* parent)
{
    //cout<<"Right Rotation on " << parent->key << endl;
    Node *t;
    t = parent->left;           // this will be our new root
    parent->left = t->right;    // hand over subtree
    t->right = parent;          // rotate parend down
    return t;                   // return new root
}

Node* AVLTree::rightLeft_rotation(Node* parent)
{
    //cout<<"Right-Left Rotation on " << parent->key << endl;
    parent->right = right_rotation(parent->right);  // right rotation on lower
    return left_rotation(parent);                   // and left rotation on upper
}

Node* AVLTree::leftRight_rotation(Node* parent)
{
    //cout<<"Left-Right Rotation on " << parent->key << endl;
    parent->left = left_rotation(parent->left);     // left rotation on lower
    return right_rotation(parent);                  // and right rotation on upper
}

Node* AVLTree::balance(Node* t)
{
    int d = difference(t);
    if (d < -1) {
        // trouble is in left side
        if (difference(t->left) < 0)
            // trouble is left-left, need to rotate right to balance.
            t = right_rotation(t);
        else
            // trouble is left-right, need to rotate left-right to balance.
            t = leftRight_rotation(t);
    } else if (d > 1) {
        // trouble is in right side
        if (difference(t->right) > 0)
            // trouble is right-right, need to rotate left to balance.
            t = left_rotation(t);
        else
            // trouble is right-left, need to rotate right-left to balance.
            t = rightLeft_rotation(t);
    }
    return t;
}

Node* AVLTree::insert(Node* p, int key, const string &value)
{
    if (p == nullptr) {
        // we can insert a new node
        p = new Node(key,value,nullptr,nullptr);
        return p;
    } else if (key< p->key) {
        p->left = insert(p->left, key, value);
        p = balance(p);
    } else if (key >= p->key) {
        p->right = insert(p->right, key, value);
        p = balance(p);
    } return p;
}

void AVLTree::show(Node* p, int l) const
{
    // tree is printed sideways. top line is right-most entry.
    // indentation according to level.
    int i;
    if (p != nullptr) {
        show(p->right, l + 1);
        for (i = 0; i < l; i++)
            cout << "    ";
        cout << p->key << endl;
        show(p->left, l + 1);
    }
}

void AVLTree::inorder(Node* t) const
{
    if (t == nullptr)
        return;
    inorder(t->left);
    cout << t->key << " " << t->value << endl;
    inorder(t->right);
}

void AVLTree::preorder(Node* t) const
{
    if (t == nullptr)
        return;
    cout << t->key << " " << t->value << endl;
    preorder(t->left);
    preorder(t->right);
}

void AVLTree::postorder(Node* t) const
{
    if (t == nullptr)
        return;
    postorder(t ->left);
    postorder(t ->right);
    cout << t->key << " " << t->value << endl;
}

// writeDot dumps the graph into a file that is usable with AT&T's Graphviz package
// see https://de.wikipedia.org/wiki/Graphviz
// and http://graphviz.org/download/
//
// NOTE: assumes that all keys are different.
// It kind of works with trees that have multiple nodes with the same key, but
// the image is wrong (as it then uses the same graphical node)
void AVLTree::writeDot(const string &filename) const
{
    ofstream fs(filename);
    fs << "digraph avl {" << endl;
    fs << "node [nodesep=0.8]" << endl;
    writeDot(fs, root);
    fs << "}" << endl;
}

void AVLTree::writeDot(ostream &fs, Node *p) const
{
    static int ctr=0; // counter for the faked null nodes

    if (nullptr==p) return;

    // recursively write out left subtree
    writeDot(fs, p->left);

    // write the current node
    // we will write also "white color" nullptrs as separate fake nodes
    // to be able to better differentiate 'only left' from 'only right'
    // nodes that would otherwise be rendered the same in dot's automatic layout.
    // To remove any ambiguity, we also color the non null childs
    // red or green (as in navigation lights used for ships and airplanes)
    if (p->left)
    {
        fs << "   " << p->key << " -> " << p->left->key << "[color=red]" << endl;
    }
    else
    {
        fs << "   " << p->key << " -> n" << ++ctr << "[color=white]" << endl;
        fs << "   n" << ctr << "[color=white, fontcolor=white]" << endl;
    }
    if (p->right)
    {
        fs << "   " << p->key << " -> " << p->right->key << "[color=darkgreen]" << endl;
    }
    else
    {
        fs << "   " << p->key << " -> n" << ++ctr << "[color=white]"  << endl;
        fs << "   n" << ctr << "[color=white, fontcolor=white]" << endl;
    }

    // recursively write out right subtree
    writeDot(fs, p->right);
    //separate nodes
    fs << endl;
}

Node* AVLTree::remove(Node *p, int key){
    if (p == NULL) // not found
        return p;
    else if (key < p->key){ // search left
        p->left = remove(p->left, key);
        p = balance(p);
    }
    else if (key > p->key){ // search right
        p->right = remove(p->right, key);
        p = balance(p);
    }
    else { // found
        // Case 1: No child
        if (p->left == NULL && p->right == NULL) {
            delete p;
            p = NULL;
        } else if (p->left == NULL) { // Case 2: One child
            Node *temp = p;
            p = p->right;
            delete temp;
        } else if (p->right == NULL) { // Case 2: One child
            Node *temp = p;
            p = p->left;
            delete temp;
        } else { // case 3: 2 children
            Node *temp = FindMin(p->right); // find min on right side
            p->key = temp->key;
            p->right = remove(p->right, temp->key);
        }
    }
    return p;
}

Node* AVLTree::FindMin(Node *p){
    while (p->left !=NULL)
        p = p->left;

    return p;
}

void AVLTree::remove(int key){
    string tmp = "";
    if(find(key, tmp) == false){
        //cout << "Key has not been found!" << endl;
    }
    else{
        root = remove(root, key);
        //cout << "Key has been deleted!" << endl;
    }
}

Node* AVLTree::find(Node* p, int key, string &value){
    if(p==NULL)
        return NULL;
    if(key == p->key){
        return p;
    }
    else if(key < p->key){
        return find(p->left, key, value);
    }
    else{
        return find(p->right, key, value);
    }
}

bool AVLTree::find(int key, string &value){
    Node* tmp = find(root, key, value);
    if(tmp == NULL){
        return false;
    }
    else{
        value = tmp->value;
        return true;
    }
}

Node* AVLTree::member(Node *p, int key){
    if(p == NULL){
        return NULL;
    }
    if(key == p->key){
        return p;
    }
    else if(key < p->key){
        return member(p->left, key);
    }
    else{
        return member(p->right,key);
    }
}

bool AVLTree::member(int key){
    if(member(root, key) == NULL){
        return false;
    }
    return true;
}

Node* AVLTree::set(Node *p, int key, string value){
    if(p == NULL){
        return NULL;
    }
    if(key == p->key){
        return p;
    }
    else if(key < p->key){
        return set(p->left, key, value);
    }
    else{
        return set(p->right, key, value);
    }
}

bool AVLTree::set(int key, string value){
    Node* tmp = set(root, key, value);
    if(tmp == NULL){
        cout << "Key has not been changed because not found!" << endl;
        return false;
    }
    else{
        tmp->key = key;
        tmp->value = value;
        cout << "Key has been changed!" << endl;
        return true;
    }
}

Node* AVLTree::probe(Node *p, int key, string value){
    if(p == NULL){
        return NULL;
    }
    if(key == p->key){
        return p;
    }
    else if(key < p->key){
        return probe(p->left, key, value);
    }
    else{
        return probe(p->right, key, value);
    }
}

bool AVLTree::probe(int key, string value){
    Node* tmp = probe(root, key, value);
    if(tmp == NULL){
        root = insert(root, key, value);
        return false;
    }
    return true;
}







