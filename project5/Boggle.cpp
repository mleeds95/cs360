// File: Boggle.cpp
// Author: Matthew Leeds
// Last Edit: 2015-04-09

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Boggle.h"

using namespace std;

Boggle::Boggle(const char* boardFilename, const char* dictFilename) {
    // Read in data from the board file.
    ifstream boardFile(boardFilename);
    if (!boardFile.is_open()) {
        cerr << "Error: " << boardFilename << " not found!" << endl;
        return;
    }
    boardFile >> _numRows;
    boardFile >> _numCols;
    _board = new char[_numRows * _numCols];
    readBoardFile(boardFile);
    boardFile.close();
    // Keep track of whether nodes have been visited
    _boardSeen = new bool[_numRows * _numCols];
    _markAllSeen(false);
    // Read in data from the dictionary file.
    ifstream dictFile(dictFilename);
    if (!dictFile.is_open()) {
        cerr << "Error: " << dictFilename << " not found!" << endl;
        return;
    }
    readDictFile(dictFile);
    dictFile.close();
}

Boggle::~Boggle() {
    delete[] _board;
    delete[] _boardSeen;
    delete _dictTrie;
}

void Boggle::testWords() {
    cout << endl << "TESTING" << endl;
    cout << "THE ";
    cout << _isValidWord("THE") << endl;
    cout << "TO ";
    cout << _isValidWord("TO") << endl;
    cout << "MATTHEW ";
    cout << _isValidWord("MATTHEW") << endl;
}

char& Boggle::getBoardVal(uint i, uint j) {
    return _board[_numRows*i + j];
}

void Boggle::setBoardVal(uint i, uint j, char c) {
    _board[_numRows*i + j] = c;
}

bool Boggle::getBoardSeen(uint i, uint j) {
    return _boardSeen[_numRows*i + j];
}

void Boggle::setBoardSeen(uint i, uint j, bool b) {
    _boardSeen[_numRows*i + j] = b;
}

// Read characters from the given file, assuming they're formatted correctly.
void Boggle::readBoardFile(ifstream& boardFile) {
    for (uint i = 0; i < _numRows; ++i) {
        for (uint j = 0; j < _numCols; ++j) {
            string val;
            boardFile >> val;
            setBoardVal(i, j, val.c_str()[0]);
        }
    }
}

// Read the dict file and record if we find words starting with each letter.
// Assume we can trust the input and only ALL CAPS are used.
// Use a prefix tree so later we can stop searches that can't lead to any words.
void Boggle::readDictFile(ifstream& dictFile) {
    _dictTrie = new Node*[26]();
    string line;
    while (getline(dictFile, line)) {
        if (_dictTrie[line[0] - 65] == NULL)
            _dictTrie[line[0] - 65] = new Node(line[0], (line.length() == 1));
        if (line.length() > 1)
            _insertTrieNode(_dictTrie[line[0] - 65], line.substr(1));
    } 
}

void Boggle::_insertTrieNode(Node* n, string s) {
    if (s.length() == 0) return;
    // If n already has a child with the next letter, add the rest of the string from there.
    Node* nextNode = _getTrieChild(n, s[0]);
    if (nextNode != NULL) {
        if (s.length() == 1) nextNode->lastLetter = true;
        else _insertTrieNode(nextNode, s.substr(1));
    } else {
        Node* newNode = new Node(s[0], (s.length() == 1));
        newNode->parent = n;
        n->children->push_back(newNode);
        _insertTrieNode(newNode, s.substr(1));
    }
}

void Boggle::_printDictTrie() {
    for (uint i = 0; i < 26; ++i) {
        cout << endl << "ROOT NODE " << i << endl;
        _printDictTrieNode(_dictTrie[i]);
        cout << endl;
    }
}
        
void Boggle::_printDictTrieNode(Node* n) {
    if (n != NULL) {
        cout << " " << n->val << " (";
        for (vector<Node*>::iterator it = n->children->begin(); it != n->children->end(); ++it) {
            _printDictTrieNode(*it);
        }
        cout << ")";
    }
}

void Boggle::printBoard() {
    cout << endl;
    for (uint i = 0; i < _numRows; ++i) {
        for (uint j = 0; j < _numCols; ++j) {
            cout << getBoardVal(i, j) << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Boggle::printBoardSeen() {
    for (uint i = 0; i < _numRows; ++i) {
        for (uint j = 0; j < _numCols; ++j) {
            cout << getBoardSeen(i, j) << " ";
        }
        cout << endl;
    }
}

// Use _dictTrie to check if a given string is a prefix for any word.
bool Boggle::_isValidPrefix(string s) {
    if (s.length() == 0) return false;
    if (s.length() == 1 && _dictTrie[s[0] - 65] != NULL) return true;
    return _checkTrie(_dictTrie[s[0] - 65], s.substr(1), false);
}

// Checks whether the given string exists in the trie, starting at the given node.
// If checkFull is true, only return true if we're at the last letter of a word when the search terminates.
bool Boggle::_checkTrie(Node* n, string s, bool checkFull) {
    if (n == NULL) return false;
    Node* nextNode = _getTrieChild(n, s[0]);
    if (nextNode != NULL) {
        if (s.length() == 1)
            return (checkFull ? nextNode->lastLetter : true);
        return _checkTrie(nextNode, s.substr(1), checkFull);
    } else {
        return false;
    }
}

// Search the given node's children for a character, returning NULL if it's not found or its Node if it is.
Node* Boggle::_getTrieChild(Node* n, char& c) {
    for (vector<Node*>::iterator it = n->children->begin(); it != n->children->end(); ++it) {
        if ((*it)->val == c) return *it;
    }
    return NULL;
}

// Use _dictTrie to check if a given string is a full word in the trie.
bool Boggle::_isValidWord(string s) {
    if (s.length() < 3) return false;
    return _checkTrie(_dictTrie[s[0] - 65], s.substr(1), true);
}

void Boggle::_markAllSeen(bool b) {
    for (uint i = 0; i < _numRows * _numCols; ++i)
        _boardSeen[i] = b;
}

// Valid words are paths of 3 or more adjacent, non-repeating letters
// that form something found in the dictionary. Use a Depth-First Search 
// to find as many as we can.
void Boggle::findWords() {
    for (uint i = 0; i < _numRows; ++i) {
        for (uint j = 0; j < _numCols; ++j) {
            _markAllSeen(false);
            _dfsVisit(i, j, "");
        }
    }
}

// Do a Depth-First Search from the specified location.
// If we reach a leaf node, check if it's a word.
void Boggle::_dfsVisit(uint i, uint j, string currentStr) {
    if (getBoardSeen(i, j)) return;
    //cout << "_dfsVisit(" << i << "," << j << "," << currentStr << ")" << endl;
    string str(1, getBoardVal(i, j));
    // TODO add Qu special case
    currentStr += str;
    if (!_isValidPrefix(currentStr)) return;
    if (_isValidWord(currentStr)) cout << currentStr << endl;
    setBoardSeen(i, j, true);
    bool top = (i > 0);
    bool left = (j > 0);
    bool right = (j < _numCols - 1);
    bool bottom = (i < _numRows - 1);
    if (top) {
        _dfsVisit(i-1, j, currentStr);
        if (left) _dfsVisit(i-1, j-1, currentStr);
        if (right) _dfsVisit(i-1, j+1, currentStr);
    }
    if (bottom) {
        _dfsVisit(i+1, j, currentStr);
        if (left) _dfsVisit(i+1, j-1, currentStr);
        if (right) _dfsVisit(i+1, j+1, currentStr);
    }
    if (left)
        _dfsVisit(i, j-1, currentStr);
    if (right)
        _dfsVisit(i, j+1, currentStr);
    setBoardSeen(i, j, false);
}
