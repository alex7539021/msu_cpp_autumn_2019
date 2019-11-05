#include "Matrix.h"

Matrix::Iterator::Iterator(int *ptr, std::size_t columns) : ptr(ptr), columns(columns) {}

int &Matrix::Iterator::operator[](std::size_t i) {
    if (i >= columns) {
        throw std::out_of_range("");
    }
    return ptr[i]; 
}

const int &Matrix::Iterator::operator[](std::size_t i) const {
    if (i >= columns) {
        throw std::out_of_range("");
    }
    return ptr[i]; 
}

Matrix::Matrix(std::size_t rows, std::size_t columns) : rows(rows), columns(columns) {
    ptr = new int [rows * columns];
}

Matrix::~Matrix() {
    delete[] ptr;
}

Matrix::Iterator Matrix::operator[](std::size_t i) {
    if (i >= rows) {
        throw std::out_of_range("");
    }
    return Iterator(ptr + i * columns, columns);
}

const Matrix::Iterator Matrix::operator[](std::size_t i) const {
    if (i >= rows) {
        throw std::out_of_range("");
    }
    return Iterator(ptr + i * columns, columns);
}

Matrix &Matrix::operator*=(int mul) {
    for (int i = 0; i < rows * columns; ++i) {
        ptr[i] *= mul;
    }
    return *this;
}

bool Matrix::operator==(const Matrix &M) const {
    if ((columns != M.getColumns()) || (rows != M.getRows())) {
        return false;
    }
    for (int i = 0; i < columns * rows; ++i) {
        if (ptr[i] != M.ptr[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &M) const {
    if (*this == M) {
        return false;
    }
    return true;
}


std::size_t Matrix::getRows() const {
    return rows;
}

std::size_t Matrix::getColumns() const {
    return columns;
}


