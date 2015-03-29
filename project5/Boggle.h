// File: Boggle.h
// Author: Matthew Leeds
// Last Edit: 2015-03-29

#pragma once
#include <fstream>
#include <vector>

using namespace std;

typedef unsigned int uint;

class Boggle {
    public:
        Boggle(const char* boardFilename, const char* dictFilename);
        ~Boggle();
        void readBoardFile(ifstream& boardFile);
        void readDictFile(ifstream& dictFile);
        void printBoard();
        void printDict();
        void sortDict();
        void findWords();
        char& getBoardVal(uint i, uint j);

    private:
        unsigned int _numRows;
        unsigned int _numCols;
        char* _board;    
        vector<string>* _dict;
};
