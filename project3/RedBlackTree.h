// File: RedBlackTree.h
// Author: Matthew Leeds
// Last Edit: 2015-02-20

#pragma once
#include <cstdlib>

struct UPCInfo;
struct ManufacturerInfo;

struct Node {
    Node* parent;
    Node* left;
    Node* right;
    unsigned int mfrCode;
    ManufacturerInfo* mInfo;
    bool alias;
    bool red; // false = black
    Node() {
        parent = NULL;
        left = NULL;
        right = NULL;
        red = true;
        alias = false;
    }
};

class RedBlackTree {
    public:
        RedBlackTree();
        ~RedBlackTree();
        void insertNode(unsigned int mfrCode, ManufacturerInfo* mInfo, bool alias);
        void growTree(UPCInfo** allUPCs, unsigned long numUPCs);
        void printTree(Node*);
    
    private:
        Node* _root;
        void _freeNodesRecursively(Node* n);
        void _enforceRedBlackProperties(Node*);
        Node* _getUncle(Node*);
        bool _isRightChild(Node*);
        void _leftRotate(Node*);
        void _rightRotate(Node*);
};
