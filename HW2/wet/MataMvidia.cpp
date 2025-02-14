#include "MataMvidia.h"
#include "Matrix.h"
#include "Utilities.h"

//---------------------------------------Our Constructors---------------------------------------//
MataMvidia::MataMvidia
        (const std::string title, const std::string author, Matrix *frames, const int length)
        : title(title), author(author), frames(new Matrix[length]), length(length) {
    // Important -- if nullptr -- this case used to just init an empty movie.
    // with the understanding that it may contain trash value.
    // ofc could have made a new constructor for that, but it works just fine, good enough for HW.
    for (int i = 0; i < length && frames != nullptr; ++i) {
        this->frames[i] = frames[i];
    }
}

MataMvidia::MataMvidia(const MataMvidia &otherMataMvidia) :
        title(otherMataMvidia.title), author(otherMataMvidia.author),
        length(otherMataMvidia.length) {
    this->frames = new Matrix[this->length];
    for (int i = 0; i < this->length; ++i) {
        frames[i] = otherMataMvidia.frames[i];
    }
}

MataMvidia::~MataMvidia() {
    delete[] this->frames;
}

//------------------------------------Our Operators------------------------------------//

//Assignment Operator
MataMvidia &MataMvidia::operator=(const MataMvidia &otherMataMvidia) {
    if (this == &otherMataMvidia) {
        return *this;
    }
    this->title = otherMataMvidia.title;
    this->author = otherMataMvidia.author;
    this->length = otherMataMvidia.length;
    delete[] this->frames;
    this->frames = new Matrix[otherMataMvidia.length];
    for (int i = 0; i < otherMataMvidia.length; ++i) {
        this->frames[i] = otherMataMvidia.frames[i];
    }
    return *this;
}

//+ Operator
MataMvidia operator+(const MataMvidia &mataMvidia1, const MataMvidia &mataMvidia2) {
    int newLength = mataMvidia1.length + mataMvidia2.length;
    MataMvidia newMataMvidia(mataMvidia1.title, mataMvidia1.author, nullptr,
                             newLength);
    for (int i = 0; i < mataMvidia1.length; ++i) {
        newMataMvidia.frames[i] = mataMvidia1.frames[i];
    }
    for (int i = 0; i < mataMvidia2.length; ++i) {
        newMataMvidia.frames[mataMvidia1.length + i] = mataMvidia2.frames[i];
    }

    return newMataMvidia;
}

//+= Operator(+= otherMataMvidia)
MataMvidia &MataMvidia::operator+=(const MataMvidia &otherMataMvidia) {
    (*this) = ((*this) + otherMataMvidia);
    return *this;
}

//+= Operator(+= matrix)
MataMvidia &MataMvidia::operator+=(const Matrix &matrix) {
    Matrix array[1];
    array[0] = matrix;
    MataMvidia newMovie("", "", array, 1);

    // using the operator+ for: (MataMvidia) + (MataMvidia)
    (*this) = (*this) + newMovie;
    return *this;
}

//<< operator
std::ostream &operator<<(std::ostream &os, const MataMvidia &mataMvidia) {
    os << "Movie Name: " << mataMvidia.title << std::endl;
    os << "Author: " << mataMvidia.author << std::endl << std::endl;
    for (int i = 0; i < mataMvidia.length; ++i) {
        os << "Frame " << i << ":" << std::endl;
        os << mataMvidia.frames[i] << std::endl;
    }
    os << "-----End of Movie-----" << std::endl;
    return os;
}

//[] operator with ability to change - so RETURN by REF
Matrix &MataMvidia::operator[](int i) {
    return this->frames[i];
}

//[] operator without ability to change - so RETURN by VAL
Matrix MataMvidia::operator[](int i) const {
    return (this->frames[i]);
}

