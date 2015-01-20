// File: matrix.h
// Author: Matthew Leeds
// Last Edit: 2015-01-20

using namespace std;

class Matrix {
    public:
        Matrix();
        Matrix(int rows, int columns);
        ~Matrix();

    private:
       int** _matrix;
       int _rows;
       int _columns; 
}
