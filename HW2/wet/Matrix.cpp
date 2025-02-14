#include "Matrix.h"
#include "Utilities.h"
#include <iostream>

//--------------------------------------Our Generic Functions-------------------------------------//
void testLegitInitSizes(int matrixLength, int matrixWidth);

void testCompSizesNorm(int matrix1Length, int matrix1Width, int matrix2Length, int matrix2Width);

void testCompSizesMult(int matrix1Length, int matrix1Width, int matrix2Length, int matrix2Width);

void testLegitIndex(int i, int j, int matrixLength, int matrixWidth);

bool testSizesEqual(int matrix1Length, int matrix1Width, int matrix2Length, int matrix2Width);

//----------------------------------------Our Constructors----------------------------------------//
Matrix::Matrix(int length, int width) {
    testLegitInitSizes(length, width);
    // if one of the sizes == 0 -----> the matrix isn't legit, just init it to be 0x0
    if (length == 0 || width == 0) {
        this->length = 0;
        this->width = 0;
    } else {
        this->length = length;
        this->width = width;
    }
    matrixData = new int[length * width]();
};

Matrix::Matrix(const Matrix &matrix) :
        length(matrix.length), width(matrix.width),
        matrixData(new int[matrix.width * matrix.length]) {
    for (int i = 0; i < matrix.width * matrix.length; ++i) {
        this->matrixData[i] = matrix.matrixData[i];
    }
}

Matrix::~Matrix() {
    delete[] this->matrixData;
}

//-----------------------------------------Our Operators------------------------------------------//
Matrix &Matrix::operator=(const Matrix &otherMatrix) {
    // straight forward test - for case when free data before init.
    if (this == &otherMatrix) {
        return *this;
    }
    // resize the matrix accordingly.
    if (this->length != otherMatrix.length) {
        this->length = otherMatrix.length;
    }
    if (this->width != otherMatrix.width) {
        this->width = otherMatrix.width;
    }
    // delete old data.
    delete[] this->matrixData;
    // init new data array and fill it.
    this->matrixData = new int[this->length * this->width];
    for (int i = 0; i < this->length * this->width; ++i) {
        this->matrixData[i] = otherMatrix.matrixData[i];
    }

    return *this;
}

int &Matrix::operator()(int i, int j) {
    // in case we want to be able to change the value in that specific coord - return REF
    testLegitIndex(i, j, this->length, this->width);
    return this->matrixData[i * this->width + j];
}

int Matrix::operator()(int i, int j) const {
    // in case we dont want to be able to change the value in that specific coord - return VAL
    testLegitIndex(i, j, this->length, this->width);
    return this->matrixData[i * this->width + j];
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    // for loop to print the matrix.
    for (int i = 0; i < matrix.length; ++i) {
        os << "|";
        for (int j = 0; j < matrix.width; ++j) {
            os << matrix(i, j) << "|";
        }
        os << std::endl;
    }
    return os;
}

Matrix operator+(const Matrix &matrix1, const Matrix &matrix2) {
    int i1 = matrix1.length, j1 = matrix1.width;
    int i2 = matrix2.length, j2 = matrix2.width;
    testCompSizesNorm(i1, j1, i2, j2);

    // operator+ makes no on provided matrices so we return a new matrix by VAL
    Matrix newMatrix = matrix1;
    for (int i = 0; i < i1; ++i) {
        for (int j = 0; j < j1; ++j) {
            newMatrix(i, j) = ((int) matrix1(i, j)) + ((int) matrix2(i, j));
        }
    }
    return newMatrix;
}

Matrix &Matrix::operator+=(const Matrix &addThisMatrix) {
    int i1 = this->length, j1 = this->width;
    int i2 = addThisMatrix.length, j2 = addThisMatrix.width;
    testCompSizesNorm(i1, j1, i2, j2);
    // use of the copy constructor used in operator+
    (*this) = ((*this) + addThisMatrix);
    return (*this);
}

Matrix operator-(const Matrix &matrix1, const Matrix &matrix2) {
    int i1 = matrix1.length, j1 = matrix1.width;
    int i2 = matrix2.length, j2 = matrix2.width;
    testCompSizesNorm(i1, j1, i2, j2);

    // operator- makes no on provided matrices so we return a new matrix by VAL
    Matrix newMatrix = matrix1;
    for (int i = 0; i < i1; ++i) {
        for (int j = 0; j < j1; ++j) {
            newMatrix(i, j) = ((int) matrix1(i, j)) - ((int) matrix2(i, j));
        }
    }
    return newMatrix;
}

Matrix &Matrix::operator-=(const Matrix &subThisMatrix) {
    int i1 = this->length, j1 = this->width;
    int i2 = subThisMatrix.length, j2 = subThisMatrix.width;
    testCompSizesNorm(i1, j1, i2, j2);

    // use of the copy constructor used in operator-
    (*this) = ((*this) - subThisMatrix);
    return (*this);
}

Matrix operator*(const Matrix &matrix1, const Matrix &matrix2) {
    int i1 = matrix1.length, j1 = matrix1.width;
    int i2 = matrix2.length, j2 = matrix2.width;
    testCompSizesMult(i1, j1, i2, j2);

    // operator* makes no on provided matrices so we return a new matrix by VAL
    int newLength = i1, newWidth = j2;
    Matrix calculationMatrix(newLength, newWidth);
    // Calculate new-data
    for (int i = 0; i < newLength; ++i) {
        for (int j = 0; j < newWidth; ++j) {
            int sum = 0;
            for (int k = 0; k < matrix1.width; ++k) {
                sum += matrix1.matrixData[i * matrix1.width + k] *
                       matrix2.matrixData[k * matrix2.width + j];
            }
            calculationMatrix.matrixData[i * newWidth + j] = sum;
        }
    }
    return calculationMatrix;
}

Matrix &Matrix::operator*=(const Matrix &multThisMatrix) {
    int i1 = this->length, j1 = this->width;
    int i2 = multThisMatrix.length, j2 = multThisMatrix.width;
    testCompSizesMult(i1, j1, i2, j2);

    // use of the copy constructor and operator*
    (*this) = (*this) * multThisMatrix;
    return *this;
}

Matrix operator-(const Matrix &matrix) {
    // here we dont want to change the matrix data - just return a new matrix by VAL.
    // use an empty finalMatrix - for now holds 0 in every entry
    Matrix finalMatrix(matrix.length, matrix.width);
    // deduct from (0) ----- get -value of original matrix
    finalMatrix -= matrix;
    return finalMatrix;
}

Matrix operator*(int scalar, const Matrix &matrix) {
    // here we dont want to change the matrix data - just return a new matrix by VAL.
    Matrix finalMatrix = matrix;
    for (int i = 0; i < matrix.length; ++i) {
        for (int j = 0; j < matrix.width; ++j) {
            finalMatrix(i, j) = scalar * finalMatrix(i, j);
        }
    }
    return finalMatrix;
}

Matrix operator*(const Matrix &matrix, int scalar) {
    // use the prev operator. same thing, different arg order.
    return (scalar * matrix);
}

Matrix &Matrix::operator*=(int scalar) {
    // uses the copy constructor.
    (*this) = ((*this) * scalar);
    return *this;
}

bool operator==(const Matrix &matrix1, const Matrix &matrix2) {
    int i1 = matrix1.length, j1 = matrix1.width;
    int i2 = matrix2.length, j2 = matrix2.width;
    if (!testSizesEqual(i1, j1, i2, j2)) {
        return false;
    };

    // if we have one coord where the matrices are not equal in value: RETURN FALSE
    for (int i = 0; i < matrix1.length; ++i) {
        for (int j = 0; j < matrix1.width; ++j) {
            if (matrix1(i, j) != matrix2(i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix &matrix1, const Matrix &matrix2) {
    // the exact logical opposite of operator!=
    return !(matrix1 == matrix2);
}

Matrix Matrix::transpose() {
    // Make copy of THIS Matrix
    Matrix temp(*this);
    // Apply size changes on THIS Matrix
    temp.length = this->width;
    temp.width = this->length;
    // Start switching places
    for (int i = 0; i < temp.length; ++i) {
        for (int j = 0; j < temp.width; ++j) {
            (temp)(i, j) = (*this)(j, i);
        }
    }
    return temp;
}

Matrix Matrix::rotateClockwise() {
    // rotateClockwise:
    // transpose & switch cols
    Matrix temp(*this);
    temp = temp.transpose();
    for (int j = 0; j < temp.width / 2; ++j) {
        for (int i = 0; i < temp.length; ++i) {
            int tempVal = (temp)(i, j);
            (temp)(i, j) = temp(i, temp.width - 1 - j);
            (temp)(i, temp.width - 1 - j) = tempVal;
        }
    }
    return temp;
}

Matrix Matrix::rotateCounterClockwise() {
    // rotateCounterClockwise:
    // transpose & switch rows
    Matrix temp(*this);
    temp = temp.transpose();
    for (int i = 0; i < temp.length / 2; ++i) {
        for (int j = 0; j < temp.width; ++j) {
            int tempVal = (temp)(i, j);
            (temp)(i, j) = temp(temp.length - 1 - i, j);
            (temp)(temp.length - 1 - i, j) = tempVal;
        }
    }
    return temp;
}


//--------------------------------------Our Generic Functions-------------------------------------//
// Just a few boring tests for size compatability for certain operators
void testLegitInitSizes(int matrixLength, int matrixWidth) {
    if (matrixLength < 0 || matrixWidth < 0) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
}

void testCompSizesNorm(int matrix1Length, int matrix1Width, int matrix2Length, int matrix2Width) {
    if (matrix1Length != matrix2Length || matrix1Width != matrix2Width) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
}

void testCompSizesMult(int matrix1Length, int matrix1Width, int matrix2Length, int matrix2Width) {
    if (matrix1Width != matrix2Length) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
}

void testLegitIndex(int i, int j, int matrixLength, int matrixWidth) {
    if (i < 0 || j < 0 || i >= matrixLength || j >= matrixWidth) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
}

bool testSizesEqual(int matrix1Length, int matrix1Width, int matrix2Length, int matrix2Width) {
    if (matrix1Length != matrix2Length || matrix1Width != matrix2Width) {
        return false;
    }
    return true;
};