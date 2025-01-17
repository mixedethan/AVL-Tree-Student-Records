#include "Node.h"

// Node constructor implementation
Node::Node(string name, int UFID) {
    this->name = name;
    this->UFID = UFID;
    this->left = nullptr;
    this->right = nullptr;
}
