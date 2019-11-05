#ifndef Matrix_H
#define Marix_H

#include <cstddef>
#include <stdexcept>
#include <iterator>

class Matrix {

    int *ptr;
    std::size_t rows;
    std::size_t columns;

    class Iterator {
        int *ptr;
        std::size_t columns;
    public:
        Iterator(int *ptr, std::size_t columns);
        int &operator[](std::size_t i);
        const int &operator[](std::size_t i) const;
    };

public:

    Matrix(std::size_t rows, std::size_t columns);

    std::size_t getRows() const;
    std::size_t getColumns() const;

    Iterator operator[](std::size_t i);
    const Iterator operator[](std::size_t i) const;

    Matrix &operator*=(int mul);

    bool operator==(const Matrix& M) const;
    bool operator!=(const Matrix& M) const;

    ~Matrix();
};

#endif