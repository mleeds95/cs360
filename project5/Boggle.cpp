// File: Boggle.cpp
// Author: Matthew Leeds
// Last Edit: 2015-03-28

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
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
    for (int i = 0; i < _numRows * _numCols; ++i) {
        _board[i] = 0;
    } 
    readBoardFile(boardFile);
    boardFile.close();
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
}

void Boggle::readBoardFile(ifstream& boardFile) {
    for (int i = 0; i < _numRows; ++i) {
        for (int j = 0; j < _numCols; ++j) {
            string val;
            boardFile >> val;
            _board[_numRows*i + j] = val.c_str()[0];
        }
    }
}

void Boggle::readDictFile(ifstream& dictFile) {
    //TODO read dict into memory
}

void Boggle::printBoard() {
    for (int i = 0; i < _numRows; ++i) {
        for (int j = 0; j < _numCols; ++j) {
            cout << _board[_numRows*i + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
