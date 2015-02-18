// File: MfrLinkedList.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-18

#include "MfrLinkedList.h"

MfrLinkedList::MfrLinkedList() {
    head = NULL;
}

MfrLinkedList::~MfrLinkedList() {
    Node* n = head;
    while (n != NULL) {
        head = head->next;
        if (!n->alias) delete n->mInfo;
        delete n;
        n = head;
    }
}

void MfrLinkedList::addValue(ManufacturerInfo* mInfo, bool al) {
    Node* n = new Node();
    n->mInfo = mInfo;
    n->alias = al;
    n->next = head;
    head = n;
}
