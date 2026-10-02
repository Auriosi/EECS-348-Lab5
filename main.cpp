#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Matrix process_matrix(std::ifstream& input, const unsigned int& size) {
    std::vector<std::vector<int>> matrix;
    matrix.resize(size);
    std::string string;
    std::string num;
    for (unsigned int i = 0; i < size; i++) {
        matrix[i].reserve(size);
        std::getline(input, string);
        if (string.length() <= 0) {
            std::cout << "Failed to read matrix row!\n";
            return Matrix();
        }
        std::stringstream stream(string);
        while (std::getline(stream, num, ' ')) {
            if (num.length() > 0) {
                int value = std::stoi(num);
                matrix[i].push_back(value);
            }
        }
        if (matrix[i].size() != size) {
            std::cout << "Matrix row is invalid length!\n";
            return Matrix();
        }
        string.clear();
        num.clear();
    }
    return Matrix(size, matrix);
}

int main() {
    std::string filename;
    std::cout << "Enter input filename: ";
    std::cin >> filename;
    if (filename.length() <= 0) {
        std::cout << "Filename not valid!\n";
        return 1;
    }
    std::ifstream input(filename);
    if (input.fail()) {
        std::cout << "Failed to open file!\n";
        return 1;
    }
    int size = 0;
    std::string size_input;
    std::getline(input, size_input);
    if (size_input.length() <= 0) {
        std::cout << "Matrix size not valid!\n";
        return 1;
    }
    size = std::stoi(size_input);
    if (size < 1) {
        std::cout << "Matrix size not valid!\n";
        return 1;
    }
    Matrix matrix_a = process_matrix(input, size);
    if (matrix_a.getSize() == 0) {
        return 1;
    }
    Matrix matrix_b = process_matrix(input, size);
    if (matrix_b.getSize() == 0) {
        return 1;
    }
    int row1, row2, column1, column2, x_pos, y_pos, new_value;
    std::string rcinput;
    std::cout << "Enter first row to swap: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) {
        std::cout << "Row value not valid!\n";
        return 1;
    }
    row1 = std::stoi(rcinput);
    if (row1 < 0 || row1 > size-1) {
        std::cout << "Row value not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter second row to swap: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) {
        std::cout << "Row value not valid!\n";
        return 1;
    }
    row2 = std::stoi(rcinput);
    if (row2 < 0 || row2 > size-1) {
        std::cout << "Row value not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter first column to swap: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) {
        std::cout << "Column value not valid!\n";
        return 1;
    }
    column1 = std::stoi(rcinput);
    if (column1 < 0 || column1 > size-1) {
        std::cout << "Column value not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter second column to swap: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) {
        std::cout << "Column value not valid!\n";
        return 1;
    }
    column2 = std::stoi(rcinput);
    if (column2 < 0 || column2 > size-1) {
        std::cout << "Column value not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter X position to set: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) {
        std::cout << "X position not valid!\n";
        return 1;
    }
    x_pos = std::stoi(rcinput);
    if (x_pos < 0 || x_pos > size-1) {
        std::cout << "X position not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter Y position to set: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) {
        std::cout << "Y position not valid!\n";
        return 1;
    }
    y_pos = std::stoi(rcinput);
    if (y_pos < 0 || y_pos > size-1) {
        std::cout << "Y position not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter new value to set: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) {
        std::cout << "New value not valid!\n";
        return 1;
    }
    new_value = std::stoi(rcinput);
    if (new_value < 0) {
        std::cout << "New value not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Matrix A:\n" << matrix_a.toString() << std::endl;
    std::cout << "Matrix B:\n" << matrix_b.toString() << std::endl;
    std::cout << "A + B:\n" << (matrix_a + matrix_b).toString() << std::endl;
    std::cout << "A * B:\n" << (matrix_a * matrix_b).toString() << std::endl;
    std::cout << "Diagonal sums for Matrix A:\n";
    std::cout << "Main diagonal sum: " << matrix_a.sumDiagonals(false) << std::endl;
    std::cout << "Secondary diagonal sum: " << matrix_a.sumDiagonals(true) << "\n\n";
    std::cout << "Problem 5 - Rows " << row1 << " and " << row2 << " swapped:\n" << matrix_a.swapRows(row1, row2).toString() << std::endl;
    std::cout << "Problem 6 - Columns " << column1 << " and " << column2 << " swapped:\n" << matrix_a.swapColumns(column1,column2).toString() << std::endl;
    std::cout << "Problem 7 - Updated matrix:\n" << matrix_a.setValue(x_pos, y_pos, new_value).toString() << std::endl;
    return 0;
}