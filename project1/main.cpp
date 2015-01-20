// File: main.cpp
// Author: Matthew Leeds
// For: CS 360, Project 1
// Last Edit: 2015-01-19

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 3) {
        string arg1 = argv[1];
        string arg2 = argv[2];
        bool syntaxError = false;
        if (arg1 == "-n") {
            try {
                int n = stoi(arg2);
            } catch (const invalid_argument& err) {
                syntaxError = true;
            }
        } else {
            syntaxError = true;
        }
        if (syntaxError) {
            cout << "Usage: './project1 -n 6' for two random-filled 6x6 matrices.\n";
            return 1;
        } else {
            //TODO populate matrix data from random
            srand(time(NULL));
            cout << rand() % 10 << endl;;
        }
    } else {
        ifstream infile("datafile");
        if (!infile.is_open()) {
            cout << "Error: File 'datafile' not found or inaccessible.\n";
            return 2;
        } else {
            //TODO populate matrix data from file
            infile.close();
        }
    }
    return 0;
}
