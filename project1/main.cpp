// File: main.cpp
// Author: Matthew Leeds
// For: CS 360, Project 1
// Last Edit: 2015-01-20

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include "matrix.h"

using namespace std;

int main(int argc, char* argv[]) {
    int n; // matrix size
    const char* filename = "datafile";
    Matrix* pMatrix1;
    Matrix* pMatrix2;
    if (argc == 3) {
        // Assume they're specifying the array size using '-n #'.
        string arg1 = argv[1];
        string arg2 = argv[2];
        bool syntaxError = false;
        if (arg1 == "-n") {
            try {
                n = atoi(arg2.c_str());
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
            pMatrix1 = new Matrix(n, time(NULL));
            pMatrix2 = new Matrix(n, time(NULL));
        }
    } else {
        // Assume we're supposed to be reading data from a file.
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "Error: File '" << filename << "' not found or inaccessible.\n";
            return 2;
        } else {
            // Assume the data file is formatted correctly.
            string line1;
            inFile >> line1;
            n = atoi(line1.substr(2).c_str());
            pMatrix1 = new Matrix(inFile, n, 0);
            pMatrix2 = new Matrix(inFile, n, 1);
            inFile.close();
        }
    }
    // At this point, matrix1 and matrix2 should be initialized.
    // Use the overloaded * operator to take the product of the matrices.
    Matrix* pMatrix3 = (*pMatrix1) + (*pMatrix2);
    // Output some useful info.
    cout << "N=" <<  n << endl << endl;
    cout << "Input matrix A" << endl;
    cout << *pMatrix1 << endl;
    cout << "Input matrix B" << endl;
    cout << *pMatrix2 << endl;
    cout << "Output matrix C" << endl;
    cout << *pMatrix3 << endl;
    /*
    cout << "Number of multiplications: " << pMatrix3->_numMultiplications << endl << endl;;
    cout << "Number of additions: " << pMatrix3->_numAdditions << endl;
    */
    delete pMatrix1;
    delete pMatrix2;
    delete pMatrix3;
    return 0;
}
