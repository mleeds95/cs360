// File: Boggle.cpp
// Author: Matthew Leeds
// Last Edit: 2015-03-29

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Boggle.h"

using namespace std;

Boggle::Boggle(const char* boardFilename, const char* dictFilename) {
    ifstream boardFile(boardFilename);
    if (!boardFile.is_open()) {
        cerr << "Error: " << boardFilename << " not found!" << endl;
        return;
    }
    boardFile >> _numRows;
    boardFile >> _numCols;
    _board = new char[_numRows * _numCols];
    for (uint i = 0; i < _numRows * _numCols; ++i) {
        _board[i] = 0;
    } 
    readBoardFile(boardFile);
    boardFile.close();
    ifstream dictFile(dictFilename);
    if (!dictFile.is_open()) {
        cerr << "Error: " << dictFilename << " not found!" << endl;
        return;
    }
    _dict = new vector<string>();
    readDictFile(dictFile);
    dictFile.close();
}

Boggle::~Boggle() {
    delete[] _board;
    delete _dict;
}

char& Boggle::getBoardVal(uint i, uint j) {
    return _board[_numRows*i + j];
}

void Boggle::readBoardFile(ifstream& boardFile) {
    for (uint i = 0; i < _numRows; ++i) {
        for (uint j = 0; j < _numCols; ++j) {
            string val;
            boardFile >> val;
            _board[_numRows*i + j] = val.c_str()[0];
        }
    }
}

// The std vector has constant time access.
void Boggle::readDictFile(ifstream& dictFile) {
    string line;
    while(getline(dictFile, line)) {
        _dict->push_back(line);
    }
}

void Boggle::printBoard() {
    for (uint i = 0; i < _numRows; ++i) {
        for (uint j = 0; j < _numCols; ++j) {
            cout << _board[_numRows*i + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Boggle::printDict() {
    for (vector<string>::size_type i = 0; i < _dict->size(); ++i) {
        cout << (*_dict)[i] << endl;
    }
}

// The built-in sort is n lg n.
void Boggle::sortDict() {
    sort(_dict->begin(), _dict->end());
}

void Boggle::findWords() {
    //TODO
}
