#pragma once
#include <string>
#include <vector>

class Matrix {
    private:
    int size;

    public:
    std::vector<std::vector<int>> inner;
    Matrix() : size(0), inner() {};
    Matrix(const int& size, std::vector<std::vector<int>>& inner);
    Matrix(const Matrix& other) : size(other.size), inner(other.inner) {};

    int getSize();
    const std::string toString();

    Matrix operator+(const Matrix& other);
    Matrix operator*(Matrix& other);
    int sumDiagonals(const bool& flip);
    int sumRow(const int& row);
    int sumCol(const int& col);
    Matrix swapRows(const int& first, const int& second);
    Matrix swapColumns(const int& first, const int& second);
    Matrix setValue(const int& x, const int& y, const int& value);
};