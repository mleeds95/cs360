// File: matrix.h
// Author: Matthew Leeds
// Last Edit: 2015-01-20

#include <string>

using namespace std;

class Matrix {
    public:
        Matrix(int size);
        Matrix(string filename, int size, int arrNum);
        ~Matrix();
        friend ostream& operator<<(ostream& os, const Matrix& m);
        int findMaxMagnitude();

    private:
       int** _matrix;
       int _size;
       int _maxMagnitude;
       int _numMultiplications;
       int _numAdditions;
};
