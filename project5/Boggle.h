// File: Boggle.h
// Author: Matthew Leeds
// Last Edit: 2015-04-09

#pragma once
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef unsigned int uint;

struct Node {
    Node* parent;
    vector<Node*>* children;
    char val;
    bool lastLetter;
    Node(char c, bool b) {
        parent = NULL;
        val = c;
        children = new vector<Node*>();
        lastLetter = b;
    }
    ~Node() {
        for (vector<Node*>::iterator it = children->begin(); it != children->end(); ++it)
            delete *it;
        delete children;
    }
};

class Boggle {
    public:
        Boggle(const char* boardFilename, const char* dictFilename);
        ~Boggle();
        void readBoardFile(ifstream& boardFile);
        void readDictFile(ifstream& dictFile);
        void printBoard();
        void printBoardSeen();
        void findWords();
        char& getBoardVal(uint i, uint j);
        void setBoardVal(uint i, uint j, char c);
        bool getBoardSeen(uint i, uint j);
        void setBoardSeen(uint i, uint j, bool b);

    private:
        unsigned int _numRows;
        unsigned int _numCols;
        char* _board;    
        bool* _boardSeen;
        Node** _dictTrie;
        void _dfsVisit(uint i, uint j, string currentStr);
        void _markAllSeen(bool b);
        bool _isValidPrefix(string);
        bool _isValidWord(string);
        bool _checkTrie(Node* n, string s, bool checkFull);
        void _insertTrieNode(Node* thisNode, string s);
        void _printDictTrie();
        void _printDictTrieNode(Node* n);
        Node* _getTrieChild(Node* n, char& c);
};
