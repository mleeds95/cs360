// File: strassenMultiply.cpp
// Author: Matthew Leeds
// Last Edit: 2015-01-23

#include <iostream>
#include "matrix.h"

using namespace std;

// This uses Strassen's method to take the product of two square matrices.
Matrix* strassenMultiply(Matrix* pM1, Matrix* pM2, int n, int rowStart, int colStart, int rowStart2, int colStart2) {
    // Assume both input matrices' dimensions are powers of two (and equal).
    Matrix* pProductMatrix = new Matrix(n);
    if (n == 1) {
        pProductMatrix->_matrix[0][0] = pM1->_matrix[rowStart][colStart] * pM2->_matrix[rowStart2][colStart2];
    } else {
        int halfN = n / 2;
        // First, calculate 10 intermediate matrices S1..S10
        Matrix* pS1 = pM2->addSquareSubmatrices(true, halfN, 0, halfN, halfN, halfN);
        Matrix* pS2 = pM1->addSquareSubmatrices(false, halfN, 0, 0, 0, halfN);
        Matrix* pS3 = pM1->addSquareSubmatrices(false, halfN, halfN, 0, halfN, halfN);
        Matrix* pS4 = pM2->addSquareSubmatrices(true, halfN, halfN, 0, 0, 0);
        Matrix* pS5 = pM1->addSquareSubmatrices(false, halfN, 0, 0, halfN, halfN);
        Matrix* pS6 = pM2->addSquareSubmatrices(true, halfN, 0, 0, halfN, halfN);
        Matrix* pS7 = pM1->addSquareSubmatrices(true, halfN, 0, halfN, halfN, halfN);
        Matrix* pS8 = pM2->addSquareSubmatrices(false, halfN, halfN, 0, halfN, halfN);
        Matrix* pS9 = pM1->addSquareSubmatrices(true, halfN, 0, 0, halfN, 0);
        Matrix* pS10 = pM2->addSquareSubmatrices(false, halfN, 0, 0, 0, halfN);
        // Now calculate 7 product matrices P1..P7
        Matrix* pP1 = strassenMultiply(pM1, pS1, halfN, 0, 0, 0, 0);
        Matrix* pP2 = strassenMultiply(pS2, pM2, halfN, 0, 0, halfN, halfN);
        Matrix* pP3 = strassenMultiply(pS3, pM2, halfN, 0, 0, 0, 0);
        Matrix* pP4 = strassenMultiply(pM1, pS4, halfN, halfN, halfN, 0, 0);
        Matrix* pP5 = strassenMultiply(pS5, pS6, halfN, 0, 0, 0, 0);
        Matrix* pP6 = strassenMultiply(pS7, pS8, halfN, 0, 0, 0, 0);
        Matrix* pP7 = strassenMultiply(pS9, pS10, halfN, 0, 0, 0, 0);
        // Calculate the solution product matrix.
        pProductMatrix->addExternalMatrices(false, false, halfN, 0, 0, pP5, pP4);
        pProductMatrix->addExternalMatrices(true, true, halfN, 0, 0, pP6, pP2);
        pProductMatrix->addExternalMatrices(false, false, halfN, 0, halfN, pP1, pP2);
        pProductMatrix->addExternalMatrices(false, false, halfN, halfN, 0, pP3, pP4);
        pProductMatrix->addExternalMatrices(true, false, halfN, halfN, halfN, pP5, pP3);
        pProductMatrix->addExternalMatrices(true, true, halfN, halfN, halfN, pP1, pP7);
        delete pS1; delete pS2; delete pS3; delete pS4; delete pS5;
        delete pS6; delete pS7; delete pS8; delete pS9; delete pS10;
        delete pP1; delete pP2; delete pP3; delete pP4; delete pP5; 
        delete pP6; delete pP7;
    }
    return pProductMatrix;
}
