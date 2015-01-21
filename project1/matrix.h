// File: matrix.h
// Author: Matthew Leeds
// Last Edit: 2015-01-20

#include <string>

using namespace std;

class Matrix {
    public:
        Matrix(int size);
        Matrix(int size, unsigned int seed);
        Matrix(string filename, int size, int arrNum);
        ~Matrix();
        int findMaxMagnitude();
        friend ostream& operator<<(ostream& os, const Matrix& m);
        friend Matrix* operator*(const Matrix& m1, const Matrix& m2);

    private:
       int** _matrix;
       int _size;
       int _maxMagnitude;
       int _numMultiplications;
       int _numAdditions;
};
