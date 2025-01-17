#ifndef AVLTREE_PROJECT_AVLTREE_H
#define AVLTREE_PROJECT_AVLTREE_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <stack>
#include "Node.h"

using namespace std;

class AVLTree{

private:
    Node* root;
    int nodeCount;

public:

//AVL Tree constructor
    AVLTree();

//AVL Tree destructor
    ~AVLTree();

//Node Getter
    Node* getRoot();
//Root Setter
    void setRoot(Node* newRoot);

// Left rotation
    static Node* rotateLeft(Node *node);

// Right rotation
    static Node* rotateRight(Node *node);

// Right-Left rotation
    Node* rotateRightLeft(Node *node);

// Left-Right rotation
    Node* rotateLeftRight(Node *node);

// Recursively finds the height of the tree
    int getHeight(Node* pNode);

// Finds the balance factor of a node (height of left subtree - height of right subtree)
    int balanceFactor(Node* node);

// Helper function that balances the tree if necessary by making rotations
    Node* balanceAndRotate(Node* node, int ID);


// Insert function that takes in root node & the new name & ID being inserted
    Node* insert(Node* node, const string& name, int ID);

// Removes a node when provided with an initial node & the UFID of the node to delete
    Node* remove(Node* node, int UFID);

// Searches for a match for a UFID, if so, it prints the corresponding name
    bool searchID(Node* node, int UFID);

// Finds student with a specified name and prints the associated UFID.
    bool searchName(Node* pNode, const string& name);

    void printInOrder(Node* pNode);

    void printPreOrder(Node* pNode);

    void printPostOrder(Node* pNode);

    void printLevelCount(Node* pNode);

    Node* removeInorder(Node* pNode, int n);

/// Helper Functions for AVLTree Class to make life easier

    // Adds the nodes of the tree into a referenced vector in the inOrder order
    void inOrder(Node* pNode, vector<Node*>& nodes);

    // Adds the nodes of the tree into a referenced vector in the preOrder order
    void preOrder(Node* pNode, vector<Node*>& nodes);

    // Adds the nodes of the tree into a referenced vector in the postOrder order
    void postOrder(Node* pNode, vector<Node*>& nodes);

    // Checks whether a UFID exists in the tree
    bool doesUFIDExist(Node* node, int UFID);
};

#endif //AVLTREE_PROJECT_AVLTREE_H
