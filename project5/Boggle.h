// File: Boggle.h
// Author: Matthew Leeds
// Last Edit: 2015-04-08

#pragma once
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef unsigned int uint;

class Boggle {
    public:
        Boggle(const char* boardFilename, const char* dictFilename);
        ~Boggle();
        void readBoardFile(ifstream& boardFile);
        void readDictFile(ifstream& dictFile);
        void printBoard();
        void printBoardSeen();
        void printDict();
        void sortDict();
        void findWords();
        char& getBoardVal(uint i, uint j);
        void setBoardVal(uint i, uint j, char c);
        bool getBoardSeen(uint i, uint j);
        void setBoardSeen(uint i, uint j, bool b);
        void testWords();

    private:
        unsigned int _numRows;
        unsigned int _numCols;
        char* _board;    
        bool* _boardSeen;
        bool* _startChars;
        vector<string>* _dict;
        void _dfsVisit(uint i, uint j, string currentStr);
        void _markAllSeen(bool b);
        bool _isValidWord(string check);
        bool _isStartChar(char& c);
};
