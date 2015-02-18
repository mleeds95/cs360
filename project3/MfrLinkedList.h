// File: MfrLinkedList.h
// Author: Matthew Leeds
// Last Edit: 2015-02-17

#pragma once
#include "ManufacturerData.h"

struct ManufacturerInfo;

struct Node {
    ManufacturerInfo* mInfo;
    bool alias;
    Node* next;
};

class MfrLinkedList {
    public:
        MfrLinkedList();
        ~MfrLinkedList();
        void addValue(ManufacturerInfo* mI, bool al);
        Node* head;
};
