// File: strassenMultiply.cpp
// Author: Matthew Leeds
// Last Edit: 2015-01-24

#include "matrix.h"

using namespace std;

// This uses Strassen's method to take the product of two square matrices.
Matrix* strassenMultiply(Matrix* pM1, Matrix* pM2, int n, int rowStart,  int colStart, 
                                                          int rowStart2, int colStart2) {
    // Assume both input matrices' dimensions are powers of two (and equal dimensions).
    Matrix* pProductMatrix = new Matrix(n);
    if (n == 1) {
        pProductMatrix->_matrix[0][0] = pM1->_matrix[rowStart][colStart] * pM2->_matrix[rowStart2][colStart2];
        pProductMatrix->_numMultiplications = 1;
    } else if (n == 2) {
        // Direct multiplication is much faster than Strassen's for small n values.
        pProductMatrix->_matrix[0][0] = pM1->_matrix[rowStart][colStart]     * pM2->_matrix[rowStart2][colStart2]
                                      + pM1->_matrix[rowStart][colStart+1]   * pM2->_matrix[rowStart2+1][colStart2];
        pProductMatrix->_matrix[0][1] = pM1->_matrix[rowStart][colStart]     * pM2->_matrix[rowStart2][colStart2+1]
                                      + pM1->_matrix[rowStart][colStart+1]   * pM2->_matrix[rowStart2+1][colStart2+1];
        pProductMatrix->_matrix[1][0] = pM1->_matrix[rowStart+1][colStart]   * pM2->_matrix[rowStart2][colStart2]
                                      + pM1->_matrix[rowStart+1][colStart+1] * pM2->_matrix[rowStart2+1][colStart2];
        pProductMatrix->_matrix[1][1] = pM1->_matrix[rowStart+1][colStart]   * pM2->_matrix[rowStart2][colStart2+1]
                                      + pM1->_matrix[rowStart+1][colStart+1] * pM2->_matrix[rowStart2+1][colStart2+1];
        pProductMatrix->_numMultiplications = 8;
        pProductMatrix->_numAdditions = 4;
    } else {
        // Use Strassen's method for large n values.
        int halfN = n / 2;
        bool add = false;
        bool sub = true;
        // First, calculate 10 intermediate matrices S1..S10
        Matrix* pS1  = pM2->addSquareSubmatrices(sub, halfN,     0, halfN, halfN, halfN);
        Matrix* pS2  = pM1->addSquareSubmatrices(add, halfN,     0,     0,     0, halfN);
        Matrix* pS3  = pM1->addSquareSubmatrices(add, halfN, halfN,     0, halfN, halfN);
        Matrix* pS4  = pM2->addSquareSubmatrices(sub, halfN, halfN,     0,     0,     0);
        Matrix* pS5  = pM1->addSquareSubmatrices(add, halfN,     0,     0, halfN, halfN);
        Matrix* pS6  = pM2->addSquareSubmatrices(add, halfN,     0,     0, halfN, halfN);
        Matrix* pS7  = pM1->addSquareSubmatrices(sub, halfN,     0, halfN, halfN, halfN);
        Matrix* pS8  = pM2->addSquareSubmatrices(add, halfN, halfN,     0, halfN, halfN);
        Matrix* pS9  = pM1->addSquareSubmatrices(sub, halfN,     0,     0, halfN,     0);
        Matrix* pS10 = pM2->addSquareSubmatrices(add, halfN,     0,     0,     0, halfN);
        pProductMatrix->_numAdditions += 10 * halfN * halfN;
        // Now calculate 7 product matrices P1..P7,
        // and account for each one's operations.
        Matrix* pP1 = strassenMultiply(pM1,  pS1, halfN,     0,     0,     0,     0);
        pProductMatrix->addOperationCounts(pP1);
        Matrix* pP2 = strassenMultiply(pS2,  pM2, halfN,     0,     0, halfN, halfN);
        pProductMatrix->addOperationCounts(pP2);
        Matrix* pP3 = strassenMultiply(pS3,  pM2, halfN,     0,     0,     0,     0);
        pProductMatrix->addOperationCounts(pP3);
        Matrix* pP4 = strassenMultiply(pM1,  pS4, halfN, halfN, halfN,     0,     0);
        pProductMatrix->addOperationCounts(pP4);
        Matrix* pP5 = strassenMultiply(pS5,  pS6, halfN,     0,     0,     0,     0);
        pProductMatrix->addOperationCounts(pP5);
        Matrix* pP6 = strassenMultiply(pS7,  pS8, halfN,     0,     0,     0,     0);
        pProductMatrix->addOperationCounts(pP6);
        Matrix* pP7 = strassenMultiply(pS9, pS10, halfN,     0,     0,     0,     0);
        pProductMatrix->addOperationCounts(pP7);
        // Calculate the solution product matrix.
        pProductMatrix->addExternalMatrices(pP5, add, pP4, false, halfN,     0,     0);
        pProductMatrix->addExternalMatrices(pP6, sub, pP2,  true, halfN,     0,     0);
        pProductMatrix->addExternalMatrices(pP1, add, pP2, false, halfN,     0, halfN);
        pProductMatrix->addExternalMatrices(pP3, add, pP4, false, halfN, halfN,     0);
        pProductMatrix->addExternalMatrices(pP5, sub, pP3, false, halfN, halfN, halfN);
        pProductMatrix->addExternalMatrices(pP1, sub, pP7,  true, halfN, halfN, halfN);
        // Account for the 12 additions of P matrices and the 2 addition assignments.
        pProductMatrix->_numAdditions += 14 * halfN * halfN; 
        delete pS1; delete pS2; delete pS3; delete pS4; delete pS5;
        delete pS6; delete pS7; delete pS8; delete pS9; delete pS10;
        delete pP1; delete pP2; delete pP3; delete pP4; delete pP5; 
        delete pP6; delete pP7;
    }
    return pProductMatrix;
}
