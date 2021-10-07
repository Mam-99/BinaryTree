#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Node
{
public:
    Node(int k, string v = "", Node* l = nullptr, Node* r = nullptr);
    int key;
    int height = 0;
    string value;
    Node* left;
    Node* right;
};

#endif // NODE_H
