// File: MfrLinkedList.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-19

#include "MfrLinkedList.h"

MfrLinkedList::MfrLinkedList() {
    head = NULL;
    numItems = 0;
}

MfrLinkedList::~MfrLinkedList() {}

void MfrLinkedList::addValue(ManufacturerInfo* inMInfo, bool inAlias, unsigned int inUPC) {
    Node* n = new Node();
    n->mInfo = inMInfo;
    n->alias = inAlias;
    n->UPC = inUPC;
    n->next = head;
    head = n;
    numItems++;
}
