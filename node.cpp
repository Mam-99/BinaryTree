#include "node.h"

Node::Node(int k, string v, Node* l, Node* r)
    : key(k)
    , value(v)
    , left(l)
    , right(r)
{
}
