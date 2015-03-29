// File: Boggle.h
// Author: Matthew Leeds
// Last Edit: 2015-03-28

#pragma once
#include <fstream>
#include <cstdlib>

using namespace std;

class Boggle {
    public:
        Boggle(const char* boardFilename, const char* dictFilename);
        ~Boggle();
        void readBoardFile(ifstream& boardFile);
        void readDictFile(ifstream& dictFile);
        void printBoard();
        char& operator()(int i, int j) { return _board[_numRows * i + _numCols]; }

    private:
        unsigned int _numRows;
        unsigned int _numCols;
        char* _board;    
};
