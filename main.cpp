#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

// Processes a Matrix object from the provided input stream at size
Matrix process_matrix(std::ifstream& input, const unsigned int& size) {
    // Inner matrix object
    std::vector<std::vector<int>> matrix;
    matrix.resize(size);
    std::string string; // Reused to contain each entire row of input
    std::string num;
    // For each row in size, from 0 to size - 1
    for (unsigned int i = 0; i < size; i++) {
        matrix[i].reserve(size); // Allocates memory for numbers, but doesn't create defaults
        std::getline(input, string);
        if (string.length() <= 0) {
            std::cout << "Failed to read matrix row!\n";
            return Matrix();
        }
        std::stringstream stream(string);
        // Iterate through every number, separated by spaces
        while (std::getline(stream, num, ' ')) {
            // Ignore spaces
            if (num.length() > 0) {
                int value = std::stoi(num);
                matrix[i].push_back(value);
            }
        }
        if (matrix[i].size() != size) { // Row contained too few or too many elements
            std::cout << "Matrix row is invalid length!\n";
            return Matrix();
        }
        // Re-use allocations for each string
        string.clear();
        num.clear();
    }
    return Matrix(size, matrix);
}

int main() {
    std::string filename;
    std::cout << "Enter input filename: ";
    std::cin >> filename;
    if (filename.length() <= 0) { // Blank filename
        std::cout << "Filename not valid!\n";
        return 1;
    }
    std::ifstream input(filename);
    if (input.fail()) { // Couldn't open file (doesn't exist, system error, etc)
        std::cout << "Failed to open file!\n";
        return 1;
    }
    int size = 0;
    std::string size_input;
    std::getline(input, size_input);
    if (size_input.length() <= 0) { // Size did not exist
        std::cout << "Matrix size not valid!\n";
        return 1;
    }
    size = std::stoi(size_input);
    if (size < 1) { // Negative or zero size
        std::cout << "Matrix size not valid!\n";
        return 1;
    }
    Matrix matrix_a = process_matrix(input, size);
    if (matrix_a.getSize() == 0) { // Something happened when processing the matrix
        return 1;
    }
    Matrix matrix_b = process_matrix(input, size);
    if (matrix_b.getSize() == 0) { // Something happened when processing the matrix
        return 1;
    }
    int row1, row2, column1, column2, x_pos, y_pos, new_value;
    std::string rcinput; // Re-used for each input
    std::cout << "Enter first row to swap: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) { // Pressed enter immediately or an error occurred
        std::cout << "Row value not valid!\n";
        return 1;
    }
    row1 = std::stoi(rcinput);
    if (row1 < 0 || row1 > size-1) { // Out of bounds
        std::cout << "Row value not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter second row to swap: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) { // Pressed enter immediately or an error occurred
        std::cout << "Row value not valid!\n";
        return 1;
    }
    row2 = std::stoi(rcinput);
    if (row2 < 0 || row2 > size-1) { // Out of bounds
        std::cout << "Row value not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter first column to swap: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) { // Pressed enter immediately or an error occurred
        std::cout << "Column value not valid!\n";
        return 1;
    }
    column1 = std::stoi(rcinput);
    if (column1 < 0 || column1 > size-1) { // Out of bounds
        std::cout << "Column value not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter second column to swap: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) { // Pressed enter immediately or an error occurred
        std::cout << "Column value not valid!\n";
        return 1;
    }
    column2 = std::stoi(rcinput);
    if (column2 < 0 || column2 > size-1) { // Out of bounds
        std::cout << "Column value not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter X position to set: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) { // Pressed enter immediately or an error occurred
        std::cout << "X position not valid!\n";
        return 1;
    }
    x_pos = std::stoi(rcinput);
    if (x_pos < 0 || x_pos > size-1) { // Out of bounds
        std::cout << "X position not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter Y position to set: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) { // Pressed enter immediately or an error occurred
        std::cout << "Y position not valid!\n";
        return 1;
    }
    y_pos = std::stoi(rcinput);
    if (y_pos < 0 || y_pos > size-1) { // Out of bounds
        std::cout << "Y position not valid!\n";
        return 1;
    }
    rcinput.clear();
    std::cout << "Enter new value to set: ";
    std::cin >> rcinput;
    if (rcinput.length() <= 0) { // Pressed enter immediately or an error occurred
        std::cout << "New value not valid!\n";
        return 1;
    }
    new_value = std::stoi(rcinput);
    if (new_value < 0) { // Out of bounds
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
