#include "matrix.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cmath>

Matrix::Matrix(const int& size, std::vector<std::vector<int>>& inner) {
    this->size = size;
    std::swap(this->inner, inner);
}

int Matrix::getSize() {
    return this->size;
}

const std::string Matrix::toString() {
    std::ostringstream string;
    int width = std::log10(std::abs(this->size)) + 1;
    for (const std::vector<int>& row : this->inner) {
        for (const int value : row) {
            string << std::setw(4) << value;
        }
        string << std::endl;
    }
    return string.str();
}

Matrix Matrix::operator+(const Matrix& other) {
    std::vector<std::vector<int>> inner;
    inner.resize(this->size);
    for (int i = 0; i < this->size; i++) {
        for (int col = 0; col < this->size; col++) {
            inner[i].push_back(this->inner[i][col] + other.inner[i][col]);
        }
    }
    return Matrix(this->size, inner);
}

Matrix Matrix::operator*(Matrix& other) {
    std::vector<std::vector<int>> inner;
    inner.resize(this->size);
    for (int i = 0; i < this->size; i++) {
        int row_sum = this->sumRow(i);
        for (int col = 0; col < this->size; col++) {
            inner[i].push_back(row_sum + other.sumCol(col));
        }
    }
    return Matrix(this->size, inner);
}

int Matrix::sumDiagonals(const bool& flip) {
    int sum = 0;
    for (int i = 0; i < this->size; i++) {
        if (flip) {
            std::cout << "adding " << this->inner[i][this->size-1-i] << std::endl;
            sum += this->inner[i][this->size-1-i];
        } else {
            sum += this->inner[i][i];
        }
    }
    return sum;
}

int Matrix::sumRow(const int& row) {
    int sum = 0;
    for (int i = 0; i < this->size; i++) {
        sum += this->inner[row][i];
    }
    return sum;
}

int Matrix::sumCol(const int& col) {
    int sum = 0;
    for (int i = 0; i < this->size; i++) {
        sum += this->inner[i][col];
    }
    return sum;
}

Matrix Matrix::swapRows(const int& first, const int& second) {
    Matrix new_matrix = *this;
    std::swap(new_matrix.inner[first], new_matrix.inner[second]);
    return new_matrix;
}

Matrix Matrix::swapColumns(const int& first, const int& second) {
    Matrix new_matrix = *this;
    for (int i = 0; i < new_matrix.size; i++) {
        std::swap(new_matrix.inner[i][first], new_matrix.inner[i][second]);
    }
    return new_matrix;
}

Matrix Matrix::setValue(const int& x, const int& y, const int& value) {
    Matrix new_matrix = *this;
    if (x < 0 || x > new_matrix.size-1) {
        return Matrix();
    } else if (y < 0 || y > new_matrix.size-1) {
        return Matrix();
    }
    new_matrix.inner[x][y] = value;
    return new_matrix;
}