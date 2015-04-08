// File: Boggle.h
// Author: Matthew Leeds
// Last Edit: 2015-04-08

#pragma once
#include <fstream>
#include <vector>

using namespace std;

typedef unsigned int uint;

enum Color {WHITE, GRAY, BLACK};

class Boggle {
    public:
        Boggle(const char* boardFilename, const char* dictFilename);
        ~Boggle();
        void readBoardFile(ifstream& boardFile);
        void readDictFile(ifstream& dictFile);
        void printBoard();
        void printBoardColors();
        void printDict();
        void printStartChars();
        void sortDict();
        void findWords();
        char& getBoardVal(uint i, uint j);
        void setBoardVal(uint i, uint j, char c);
        Color getBoardColor(uint i, uint j);
        void setBoardColor(uint i, uint j, Color c);

    private:
        unsigned int _numRows;
        unsigned int _numCols;
        char* _board;    
        Color* _boardColors;
        bool* _startChars;
        vector<string>* _dict;
        void _dfsVisit(uint i, uint j, string currentStr);
        void _paintWhite();
        bool _isValidWord(string check);
        bool _isStartChar(char& c);
};
