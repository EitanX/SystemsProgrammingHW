#pragma once

#include "Matrix.h"


class MataMvidia {
private:
    std::string title;
    std::string author;
    Matrix *frames = nullptr;
    int length = 0;
public:
    //----------------------------------Our Constructors-------------------------------------//
    //Default Constructor
    MataMvidia() = default;

    //Default Destructor
    ~MataMvidia();

    //Constructors
    MataMvidia(std::string title, std::string author, Matrix *frames, int length);

    //Copy Constructor
    MataMvidia(const MataMvidia &otherMataMvidia);

    //---------------------------------Our Operators-----------------------------------//
    //Assignment Operator
    MataMvidia &operator=(const MataMvidia &otherMataMvidia);

    friend MataMvidia operator+(const MataMvidia &mataMvidia1, const MataMvidia &mataMvidia2);

    MataMvidia &operator+=(const MataMvidia &otherMataMvidia);

    MataMvidia &operator+=(const Matrix &matrix);

    friend std::ostream &operator<<(std::ostream &os, const MataMvidia &mataMvidia);

    Matrix &operator[](int i);

    Matrix operator[](int i) const;
};
