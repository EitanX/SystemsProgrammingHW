#pragma once

#include <iostream>


class Matrix {
    // Length - Row - i
    // Width - Col - j
    int length = 0;
    int width = 0;
    int *matrixData = nullptr;

public:
    // Constructors:
    Matrix() = default;

    ~Matrix();

    Matrix(int length, int width);

    Matrix(const Matrix &matrix);

    // Operators:
    Matrix &operator=(const Matrix &otherMatrix);

    int &operator()(int i, int j);

    int operator()(int i, int j) const;

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

    friend Matrix operator+(const Matrix &matrix1, const Matrix &matrix2);

    Matrix &operator+=(const Matrix &otherMatrix);

    friend Matrix operator-(const Matrix &matrix1, const Matrix &matrix2);

    Matrix &operator-=(const Matrix &otherMatrix);

    friend Matrix operator*(const Matrix &matrix1, const Matrix &matrix2);

    Matrix &operator*=(const Matrix &otherMatrix);

    friend Matrix operator-(const Matrix &matrix);

    friend Matrix operator*(int scalar, const Matrix &matrix);

    // CHECK HERE IF KEEPING FRIEND IS OK WHEN MATRIX IS ON THE LEFT
    friend Matrix operator*(const Matrix &matrix, int scalar);

    // CHECK HERE IF NEEDS TO BE AS FRIEND
    Matrix &operator*=(int scalar);

    friend bool operator==(const Matrix &matrixA, const Matrix &matrixB);

    friend bool operator!=(const Matrix &matrixA, const Matrix &matrixB);

    // Methods:
    Matrix transpose();

    Matrix rotateClockwise();

    Matrix rotateCounterClockwise();
};


