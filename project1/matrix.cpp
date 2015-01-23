// File: matrix.cpp
// Author: Matthew Leeds
// Last Edit: 2015-01-22
// This class defines a matrix that can be used for multiplication/addition/subtraction.

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
    this->_size = size;
    this->_matrix = new int*[this->_size];
    for (int i = 0; i < this->_size; i++) {
        this->_matrix[i] = new int[this->_size];
    }
}

// This constructor allocates space and fills the matrix with random values.
Matrix::Matrix(int size, unsigned int seed) {
    this->_size = size;
    this->_matrix = new int*[this->_size];
    for (int i = 0; i < this->_size; i++) {
        this->_matrix[i] = new int[this->_size];
    }
    // Fill array with random values 0-9
    srand(seed);
    for (int i = 0; i < this->_size; i++) {
        for (int j = 0; j < this->_size; j++) {
            this->_matrix[i][j] = rand() % 10;
        }
    }
}

// This constructor allocates space and fills the matrix with values from a file.
// It is assumed that the file is formatted correctly, and that the 
// ifstream object is seeked to the right position before being passed to this.
Matrix::Matrix(ifstream& inFile, int size) {
    this->_size = size;
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
}

Matrix::~Matrix() {
    for (int i = 0; i < this->_size; i++) {
        delete []this->_matrix[i];
    }
    delete []this->_matrix;
}

// Find the maximum magnitude value in the matrix. This can be useful for 
// determining how wide to make columns when printing it out.
int Matrix::findMaxMagnitude() const{
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

// This overloads the redirection operator so matrices can be printed using cout.
// Values are printed in fixed-width columns, right-aligned.
ostream& operator<<(ostream& os, const Matrix& m) {
    int maxVal = m.findMaxMagnitude();
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

// This overloads the addition operator to add two square matrices 
// by adding their respective elements.
Matrix* operator+(const Matrix& m1, const Matrix& m2) {
    int n = m1._size;
    Matrix* pSumMatrix = new Matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pSumMatrix->_matrix[i][j] = (m1._matrix[i][j] + m2._matrix[i][j]);
        }
    }
    return pSumMatrix; 
}

// This overloads the subtraction operator for (square) matrices.
Matrix* operator-(const Matrix& m1, const Matrix& m2) {
    int n = m1._size;
    Matrix* pSumMatrix = new Matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pSumMatrix->_matrix[i][j] = (m1._matrix[i][j] - m2._matrix[i][j]);
        }
    }
    return pSumMatrix; 
}

// This takes four indices, assumes they refer to two square submatrices
// with the same dimensions and adds them, returning the result.
// N is the size of each submatrix. subtract enables subtraction instead.
Matrix* Matrix::addSquareSubmatrices(bool subtract, int n, int rowStart, int colStart, int rowStart2, int colStart2) const {
    Matrix* pMatrix = new Matrix(n);
    int i, j, k, l;
    k = rowStart2;
    for (i = rowStart; i < rowStart + n; i++) {
        l = colStart2;
        for (j = colStart; j < colStart + n; j++) {
            if (subtract)
                pMatrix->_matrix[i-rowStart][j-colStart] = this->_matrix[i][j] - this->_matrix[k][l];
            else
                pMatrix->_matrix[i-rowStart][j-colStart] = this->_matrix[i][j] + this->_matrix[k][l];
            l++;
        }
        k++;
    }
    return pMatrix;
}
