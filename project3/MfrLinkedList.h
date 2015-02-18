// File: MfrLinkedList.h
// Author: Matthew Leeds
// Last Edit: 2015-02-17

#include "ManufacturerData.h"

class MfrLinkedList {

    struct Node {
        ManufacturerInfo* mInfo;
        bool alias;
        Node* next;
    };

    public:
        MfrLinkedList() { head = NULL; }
        ~MfrLinkedList() {
            Node* n = head;
            while (n != NULL) {
                head = head->next;
                if (!n->alias) delete n->mInfo;
                delete n;
                n = head;
            }
        }
        void addValue(ManufacturerInfo* mI, bool al) {
            Node* n = new Node();
            n->mInfo = mI;
            n->alias = al;
            n->next = head;
            head = n;
        }
        Node* head;    
};
