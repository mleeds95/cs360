// File: Boggle.cpp
// Author: Matthew Leeds
// Last Edit: 2015-04-08

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
    _dict = new vector<string>();
    _startChars = new bool[26];
    readDictFile(dictFile);
    dictFile.close();
}

Boggle::~Boggle() {
    delete[] _board;
    delete[] _boardSeen;
    delete[] _startChars;
    delete _dict;
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
// The std vector has constant time access.
void Boggle::readDictFile(ifstream& dictFile) {
    string line;
    while(getline(dictFile, line)) {
        _dict->push_back(line);
        _startChars[line[0] - 65] = true;
    }
}

void Boggle::printBoard() {
    for (uint i = 0; i < _numRows; ++i) {
        for (uint j = 0; j < _numCols; ++j) {
            cout << getBoardVal(i, j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Boggle::printBoardSeen() {
    for (uint i = 0; i < _numRows; ++i) {
        for (uint j = 0; j < _numCols; ++j) {
            cout << getBoardSeen(i, j) << " ";
        }
        cout << endl;
    }
}

void Boggle::printDict() {
    for (vector<string>::size_type i = 0; i < _dict->size(); ++i) {
        cout << (*_dict)[i] << endl;
    }
}

bool Boggle::_isStartChar(char& c) {
    return _startChars[c - 65];
}

// The built-in sort is n lg n.
void Boggle::sortDict() {
    sort(_dict->begin(), _dict->end());
}

// Do a binary search (lg n) for a word in the dictionary.
bool Boggle::_isValidWord(string check) {
    cout << "_isValidWord(" + check + ")" << endl;
    if (check.length() < 3)
        return false;
    return binary_search(_dict->begin(), _dict->end(), check);
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
            if (_isStartChar(getBoardVal(i, j)))
                _dfsVisit(i, j, "");
        }
    }
}

// Do a Depth-First Search from the specified location.
// If we reach a leaf node, check if it's a word.
void Boggle::_dfsVisit(uint i, uint j, string currentStr) {
    if (getBoardSeen(i, j))
        return;
    cout << "_dfsVisit(" << i << "," << j << "," << currentStr << ")" << endl;
    string str(1, getBoardVal(i, j));
    // TODO add Qu special case
    currentStr += str;
    setBoardSeen(i, j, true);
    if (_isValidWord(currentStr))
        cout << currentStr << endl;
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
