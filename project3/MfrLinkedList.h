// File: MfrLinkedList.h
// Author: Matthew Leeds
// Last Edit: 2015-02-24

#pragma once
#include "ManufacturerData.h"

struct ManufacturerInfo;

struct LLNode {
    ManufacturerInfo* mInfo;
    bool alias;
    unsigned int UPC;
    LLNode* next;
};

class MfrLinkedList {
    public:
        MfrLinkedList();
        ~MfrLinkedList();
        void addValue(ManufacturerInfo* mI, bool al, unsigned int UPC);
        LLNode* head;
        unsigned int numItems;
};
