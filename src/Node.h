#ifndef AVLTREE_PROJECT_NODE_H
#define AVLTREE_PROJECT_NODE_H

#include <string>
using namespace std;

struct Node // Basic Node class
{
    string name;
    int UFID;
    Node* left;
    Node* right;

    Node(string name, int UFID);
};

#endif //AVLTREE_PROJECT_NODE_H
