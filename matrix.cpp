#include "matrix.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cmath>

// Copy constructor
Matrix::Matrix(const int& size, std::vector<std::vector<int>>& inner) {
    this->size = size;
    std::swap(this->inner, inner);
}

// Returns copy of size
int Matrix::getSize() {
    return this->size;
}

// Formats the matrix as a multi-line string
const std::string Matrix::toString() {
    std::ostringstream string;
    for (const std::vector<int>& row : this->inner) {
        for (const int value : row) {
            string << std::setw(6) << value; // Each number guaranteed to be 6 digits wide
        }
        string << std::endl; // Move on to next line
    }
    return string.str();
}

// + operator overload, adds this matrix with another one
Matrix Matrix::operator+(const Matrix& other) {
    std::vector<std::vector<int>> inner;
    inner.resize(this->size);
    for (int i = 0; i < this->size; i++) { // For every row 0 to matrix size
        for (int col = 0; col < this->size; col++) { // For every column 0 to matrix size
            inner[i].push_back(this->inner[i][col] + other.inner[i][col]);
        }
    }
    return Matrix(this->size, inner);
}

// * operator overload, cross multiplies this matrix with another one
Matrix Matrix::operator*(Matrix& other) {
    std::vector<std::vector<int>> inner;
    inner.resize(this->size);
    for (int i = 0; i < this->size; i++) { // For every row 0 to matrix size
        int row_sum = this->sumRow(i); // Summarizes row i of Matrix A
        for (int col = 0; col < this->size; col++) { // For every column 0 to matrix size
            inner[i].push_back(row_sum + other.sumCol(col)); // Summarizes column col of Matrix B
        }
    }
    return Matrix(this->size, inner);
}

// Summarizes a diagonal of matrix object, depending on value of flip
int Matrix::sumDiagonals(const bool& flip) {
    int sum = 0;
    for (int i = 0; i < this->size; i++) { // For every row 0 to matrix size
        if (flip) { // Add from top right to bottom left
            sum += this->inner[i][this->size-1-i];
        } else { // Add from top left to bottom right
            sum += this->inner[i][i];
        }
    }
    return sum;
}

// Summarizes a row of matrix object
int Matrix::sumRow(const int& row) {
    int sum = 0;
    for (int i = 0; i < this->size; i++) { // For every row 0 to matrix size
        sum += this->inner[row][i];
    }
    return sum;
}

// Summarizes a column of matrix object
int Matrix::sumCol(const int& col) {
    int sum = 0;
    for (int i = 0; i < this->size; i++) { // For every row 0 to matrix size
        sum += this->inner[i][col];
    }
    return sum;
}

// Swaps two rows within a matrix object
Matrix Matrix::swapRows(const int& first, const int& second) {
    Matrix new_matrix = *this; // Copy matrix to a new matrix
    std::swap(new_matrix.inner[first], new_matrix.inner[second]); // Swap first and second vectors, avoids copying
    return new_matrix;
}

// Swaps two columns within a matrix object
Matrix Matrix::swapColumns(const int& first, const int& second) {
    Matrix new_matrix = *this; // Copy matrix to a new matrix
    for (int i = 0; i < new_matrix.size; i++) { // For every row to matrix size
        std::swap(new_matrix.inner[i][first], new_matrix.inner[i][second]); // Swaps first and second vectors, avoids copying
    }
    return new_matrix;
}

// Sets value at (x, y)
Matrix Matrix::setValue(const int& x, const int& y, const int& value) {
    Matrix new_matrix = *this; // Copy matrix to a new matrix
    if (x < 0 || x > new_matrix.size-1) { // Out of bounds
        return Matrix();
    } else if (y < 0 || y > new_matrix.size-1) { // Out of bounds
        return Matrix();
    }
    new_matrix.inner[x][y] = value;
    return new_matrix;
}
