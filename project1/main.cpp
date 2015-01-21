// File: main.cpp
// Author: Matthew Leeds
// For: CS 360, Project 1
// Last Edit: 2015-01-19

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <stdexcept>
#include "matrix.h"

using namespace std;

int main(int argc, char* argv[]) {
    int n; // matrix size
    const char* filename = "datafile";
    Matrix* pMatrix1;
    Matrix* pMatrix2;
    if (argc == 3) {
        string arg1 = argv[1];
        string arg2 = argv[2];
        bool syntaxError = false;
        if (arg1 == "-n") {
            try {
                n = stoi(arg2);
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
            pMatrix1 = new Matrix(n);
            pMatrix2 = new Matrix(n);
        }
    } else {
        // Assume we're supposed to be reading data from a file.
        ifstream infile(filename);
        if (!infile.is_open()) {
            cout << "Error: File '" << filename << "' not found or inaccessible.\n";
            return 2;
        } else {
            // Assume the data file is formatted correctly.
            string line1;
            infile >> line1;
            n = stoi(line1.substr(2));
            infile.close();
            pMatrix1 = new Matrix(filename, n, 0);
            pMatrix2 = new Matrix(filename, n, 1);
        }
    }
    // At this point, matrix1 and matrix2 should be initialized.
    cout << *pMatrix1 << endl;
    //TODO multiply
    //TODO display result
    delete pMatrix1;
    delete pMatrix2;
    return 0;
}
