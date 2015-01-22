// File: matrix.cpp
// Author: Matthew Leeds
// Last Edit: 2015-01-21

#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <cmath>

// This constructor allocates space for the matrix, but that's it.
Matrix::Matrix(int size) {
    this->_originalSize = size;
    // Calculate a dimension that's guaranteed to be a power of 2.
    int base2size = pow(2, ceil(log(size) / log(2)));
    this->_size = base2size;
    this->_matrix = new int*[this->_size];
    for (int i = 0; i < this->_size; i++) {
        this->_matrix[i] = new int[this->_size];
    }
}

// This constructor allocates space and fills the matrix with random values.
Matrix::Matrix(int size, unsigned int seed) {
    this->_originalSize = size;
    // Calculate a dimension that's guaranteed to be a power of 2.
    int base2size = pow(2, ceil(log(size) / log(2)));
    this->_size = base2size;
    this->_matrix = new int*[this->_size];
    for (int i = 0; i < this->_size; i++) {
        this->_matrix[i] = new int[this->_size];
    }
    // Fill array with random values 0-9
    srand(seed);
    for (int i = 0; i < this->_originalSize; i++) {
        for (int j = 0; j < this->_originalSize; j++) {
            this->_matrix[i][j] = rand() % 10;
        }
    }
    this->zeroFillExtras();
    this->findMaxMagnitude();
}

// This constructor allocates space and fills the matrix with values from a file.
// It is assumed that the file is formatted correctly, and that the 
// ifstream object is seeked to the right position before being passed to this.
Matrix::Matrix(ifstream& inFile, int size, int arrNum) {
    this->_originalSize = size;
    // Calculate a dimension that's guaranteed to be a power of 2.
    int base2size = pow(2, ceil(log(size) / log(2)));
    this->_size = base2size;
    this->_matrix = new int*[this->_size];
    for (int i = 0; i < this->_size; i++) {
        this->_matrix[i] = new int[this->_size];
    }
    // For each line, interpret everything but commas as integers
    for (int i = 0; i < size; i++) {
        string line = "";
        inFile >> line;
        stringstream ss(line);
        int j = 0;
        int num;
        while (ss >> num) {
            this->_matrix[i][j] = num;
            j++;
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
    }
    this->zeroFillExtras();
    this->findMaxMagnitude();
}

Matrix::~Matrix() {
    for (int i = 0; i < this->_size; i++) {
        delete []this->_matrix[i];
    }
    delete []this->_matrix;
}

// Some matrices are expanded to dimensions that are powers of two, so
// this fills that extra space with zeroes. The code is designed not
// to waste much time on ones that weren't expanded.
void Matrix::zeroFillExtras() {
    // Zero fill extra rows.
    for (int i = _originalSize; i < this->_size; i++) {
        for (int j = 0; j < this->_size; j++) {
            this->_matrix[i][j] = 0;
        }
    }
    // Zero fill extra columns.
    for (int j = _originalSize; j < this->_size; j++) {
        for (int i = 0; i < this->_originalSize; i++) {
            this->_matrix[i][j] = 0;
        }
    }
}

// Find the maximum magnitude value in the matrix. This can be useful for 
// determining how wide to make columns when printing it out.
void Matrix::findMaxMagnitude() {
    int maxVal = 0;
    //cout << this[0] << endl;
    for (int i = 0; i < this->_size; i++) {
        for (int j = 0; j < this->_size; j++) {
            if (abs(this->_matrix[i][j]) > maxVal) {
                maxVal = abs(this->_matrix[i][j]);
            }
        }
    }
    this->_maxMagnitude = maxVal;
    return;
}

// This overloads the redirection operator so matrices can be printed using cout.
// Values are printed in fixed-width columns, right-aligned.
ostream& operator<<(ostream& os, const Matrix& m) {
    int maxVal = m._maxMagnitude;
    string maxValString;
    ostringstream convert;
    convert << maxVal;
    maxValString = convert.str();
    int extraSpace = 2;
    int fieldWidth = extraSpace + maxValString.size();
    for (int i = 0; i < m._size; i++) {
        for (int j = 0; j < m._size; j++) {
            os << right << setw(fieldWidth) << m._matrix[i][j];
        }
        os << endl;
    }
    return os;
}

// This overloads the multiplication operator to take the product of two matrices.
// It will implement Strassen's algorithm to accomplish this reasonably fast.
Matrix* operator*(const Matrix& m1, const Matrix& m2) {
    // Assume both input matrices are square with the same dimensions.
    int n = m1._size;
    Matrix* pProductMatrix = new Matrix(n);
    //TODO implement Strassen's algorithm
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pProductMatrix->_matrix[i][j] = (m1._matrix[i][j] * m2._matrix[i][j]);
        }
    }
    pProductMatrix->findMaxMagnitude();
    return pProductMatrix;
}

Matrix* operator+(const Matrix& m1, const Matrix& m2) {
    //TODO
}

Matrix* operator-(const Matrix& m1, const Matrix& m2) {
    //TODO
}
