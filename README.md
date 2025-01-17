# AVL Tree Student Records Manager

A C++ program that uses an AVL Tree to manage student records. This project supports operations like insertion, deletion, search, and traversal of records based on UFID (Unique Student IDs).

## Features
- Self-balancing AVL Tree implementation.
- Insert and remove student records with UFID.
- Search by UFID or student name.
- Print the AVL tree in in-order, pre-order, or post-order traversal.
- Display the number of levels in the tree.
- Remove the nth student based on in-order traversal.

## Requirements
- C++17 or later.
- A compiler like GCC or Clang.

## Build Instructions
From the project root directory:
```bash
# Compile the program
g++ -std=c++17 -o AVLTreeProject main.cpp AVLTree.cpp Node.cpp

# Run the program
./AVLTreeProject
```
