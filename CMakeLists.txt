cmake_minimum_required(VERSION 3.24)
project(AVLTree_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(AVLTree_Project src/main.cpp
        src/AVLTree.h
        src/Node.h
        src/Node.cpp
        src/AVLTree.cpp)
