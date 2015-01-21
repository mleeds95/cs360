// File: matrix.cpp
// Author: Matthew Leeds
// Last Edit: 2015-01-20

#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>

Matrix::Matrix(int size) {
    this->_size = size;
    this->_matrix = new int*[this->_size];
    for (int i = 0; i < this->_size; i++) {
        this->_matrix[i] = new int[this->_size];
    }
    // Fill array with random values 0-9
    srand(time(NULL));
    for (int i = 0; i < this->_size; i++) {
        for (int j = 0; j < this->_size; j++) {
            this->_matrix[i][j] = rand() % 10;
        }
    }
    this->_maxMagnitude = this->findMaxMagnitude();
}

Matrix::Matrix(string filename, int size, int arrNum) {
    this->_size = size;
    this->_matrix = new int*[this->_size];
    for (int i = 0; i < this->_size; i++) {
        this->_matrix[i] = new int[this->_size];
    }
    ifstream inFile(filename.c_str());
    // seek directly to the appropriate part of the file
    int lineLength = size * 2; // values, commas, end of line
    inFile.seekg(4 + (arrNum * (lineLength * size)));
    for (int i = 0; i < this->_size; i++) {
        string line = "";
        inFile >> line;
        stringstream ss(line);
        int j = 0;
        int num;
        while (ss >> num) {
            this->_matrix[i][j] = num;
            j++;
            if (ss.peek() == ',') ss.ignore();
        }
    }
    this->_maxMagnitude = this->findMaxMagnitude();
}

Matrix::~Matrix() {
    for (int i = 0; i < this->_size; i++) {
        delete []this->_matrix[i];
    }
    delete []this->_matrix;
}

int Matrix::findMaxMagnitude() {
    int maxVal = 0;
    for (int i = 0; i < this->_size; i++) {
        for (int j = 0; j < this->_size; j++) {
            if (abs(this->_matrix[i][j]) > maxVal) {
                maxVal = abs(this->_matrix[i][j]);
            }
        }
    }
    return maxVal;
}

ostream& operator<<(ostream& os, const Matrix& m) {
    int maxVal = m._maxMagnitude;
    string String = static_cast<ostringstream*>( &(ostringstream() << maxVal) )->str();
    //TODO setw stuff
    return os;
}
