// File: RedBlackTree.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-24

#include <iostream>
#include "RedBlackTree.h"
#include "ManufacturerData.h"

RedBlackTree::RedBlackTree() {
    _root = NULL;
}

RedBlackTree::~RedBlackTree() {
    _freeNodesRecursively(_root);
}

void RedBlackTree::_freeNodesRecursively(Node* n) {
    if (n != NULL) {
        _freeNodesRecursively(n->left);
        _freeNodesRecursively(n->right);
        delete n;
    }
}

void RedBlackTree::printTree(Node* n) {
    cout << " " << n->mfrCode << (n->red ? "r" : "b") << " ( ";
    if (n->left == NULL) cout << " NULL ";
    else printTree(n->left);
    cout << " , ";
    if (n->right == NULL) cout << " NULL ";
    else printTree(n->right);
    cout << " ) ";
}


// inserts a new node into the tree given some data, 
// and ensures the tree still follows the RBT rules.
void RedBlackTree::insertNode(unsigned int inMfrCode, ManufacturerInfo* inMInfo, bool inAlias) {
    Node* newNode = new Node();
    newNode->mfrCode = inMfrCode;
    newNode->mInfo = inMInfo;
    newNode->alias = inAlias;
    if (_root == NULL) {
        _root = newNode;
        _root->red = false;
    } else {
        bool foundIt = false;
        Node* current = _root;
        while (!foundIt) {
            if (inMfrCode < current->mfrCode) {
                if (current->left == NULL) {
                    newNode->parent = current;
                    current->left = newNode;
                    foundIt = true;
                } else {
                    current = current->left;
                }
            } else if (current->right == NULL) {
                newNode->parent = current;
                current->right = newNode;
                foundIt = true;
            } else {
                current = current->right;
            }
        }
        if (current->red) 
            _enforceRedBlackProperties(newNode);
    }
    printTree(_root);
    cout << endl;
}

// recursively enforces Red-Black Tree properties that may have 
// been violated by an insertion.
void RedBlackTree::_enforceRedBlackProperties(Node* n) {
    if (n == NULL)
       return;
    if (n == _root) {
        n->red = false;
        return;
    }
    if (!n->parent->red)
        return;
    Node* uncle = _getUncle(n);
    if (uncle != NULL && uncle->red) {
        n->parent->red = false;
        uncle->red = false;
        if (n->parent->parent != NULL)
            n->parent->parent->red = true;
        _enforceRedBlackProperties(n->parent->parent);
    } else {
        // if n isn't linear with it's parent, fix that first
        if (_isRightChild(n) && !_isRightChild(n->parent)) {
            n = n->parent;
            _leftRotate(n);
        } else if (!_isRightChild(n) && _isRightChild(n->parent)) {
            n = n->parent;
            _rightRotate(n);
        }
        n->parent->red = false;
        n->parent->parent->red = true;
        if (!_isRightChild(n->parent))
            _rightRotate(n->parent->parent);
        else
            _leftRotate(n->parent->parent);
    }
    _root->red = false;
    _enforceRedBlackProperties(n);
}

// add records from an array to the tree
void RedBlackTree::growTree(UPCInfo** allUPCs, unsigned long numUPCs) {
    for (unsigned long i = 0; i < numUPCs; i++) {
        insertNode(allUPCs[i]->UPC, allUPCs[i]->mInfo, allUPCs[i]->alias);
    }
}

// returns the sibling of a node's parent
Node* RedBlackTree::_getUncle(Node* n) {
    if (n->parent == NULL) {
        return NULL;
    } 
    if (_isRightChild(n->parent)) {
        return n->parent->parent->left;
    } else {
        return n->parent->parent->right;
    }
}

// returns true if a node is the right child of its parent
bool RedBlackTree::_isRightChild(Node* n) {
    if (n != NULL && n == n->parent->right)
        return true;
    return false;
}

// rotates a node so that it is the left child of its (former) right child
void RedBlackTree::_leftRotate(Node* n) {
    if (n == NULL)
        return;
    Node* rightSubtree = n->right;
    n->right = rightSubtree->left;
    if (rightSubtree->left != NULL)
        rightSubtree->left->parent = n;
    rightSubtree->parent = n->parent;
    if (n->parent == NULL)
        _root = rightSubtree;
    else if (_isRightChild(n))
        n->parent->right = rightSubtree;
    else
        n->parent->left = rightSubtree;
    rightSubtree->left = n;
    n->parent = rightSubtree;
}

// rotates a node so that it is the right child of its (former) left child
void RedBlackTree::_rightRotate(Node* n) {
    if (n == NULL)
        return;
    Node* leftSubtree = n->left;
    n->left = leftSubtree->right;
    if (leftSubtree->right != NULL)
        leftSubtree->right->parent = n;
    leftSubtree->parent = n->parent;
    if (n->parent == NULL)
        _root = leftSubtree;
    else if (_isRightChild(n))
        n->parent->right = leftSubtree;
    else
        n->parent->left = leftSubtree;
    leftSubtree->right = n;
    n->parent = leftSubtree;
}
