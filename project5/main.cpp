// File: main.cpp
// Author: Matthew Leeds
// Purpose: CS 360, Project 5 (Boggle)
// Last Edit: 2015-03-29

#include "Boggle.h"

using namespace std;

const char* BOARD_FILENAME = "board.txt";
const char* DICT_FILENAME = "dict.txt";

int main() {
    Boggle myBoggle = Boggle(BOARD_FILENAME, DICT_FILENAME);
    myBoggle.printBoard();
    myBoggle.sortDict();
    myBoggle.findWords();
    return 0;
}
