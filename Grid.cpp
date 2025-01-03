#include "Grid.h"
#include <iostream>
#include "Colors.h"

// Constructor initializes grid properties and prepares the cell colors.
Grid::Grid() {
    numRows = 20; // Set the number of rows.
    numCols = 10; // Set the number of columns.
    cellSize = 30; // Set the size of each cell in pixels.
    Initialize(); // Clear all cells (set to empty).
    colors = GetCellColors(); // Initialize cell colors based on predefined settings.
}

// Clears all grid cells by setting them to 0 (empty).
void Grid::Initialize() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            grid[row][column] = 0;
        }
    }
}

// Prints the current grid state to the console (for debugging purposes).
void Grid::Print() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

// Draws the grid and its cells on the screen using Raylib.
void Grid::Draw() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

// Returns true if the specified cell is outside the grid boundaries.
bool Grid::IsCellOutside(int row, int column) {
    return !(row >= 0 && row < numRows && column >= 0 && column < numCols);
}

// Returns true if the specified cell is empty (value is 0).
bool Grid::IsCellEmpty(int row, int column) {
    return grid[row][column] == 0;
}

// Clears all full rows and returns the number of rows cleared.
int Grid::ClearFullRows() {
    int Completed = 0; // Counter for cleared rows.
    for (int row = numRows - 1; row >= 0; row--) {
        if (IsRowFull(row)) {
            ClearRow(row);
            Completed++;
        }
        else if (Completed > 0) {
            MoveRowDown(row, Completed);
        }
    }
    return Completed;
}

// Checks if a specific row is full (no empty cells).
bool Grid::IsRowFull(int row) {
    for (int columns = 0; columns < numCols; columns++) {
        if (grid[row][columns] == 0) {
            return false;
        }
    }
    return true;
}

// Clears a specific row by setting all its cells to 0.
void Grid::ClearRow(int row) {
    for (int column = 0; column < numCols; column++) {
        grid[row][column] = 0;
    }
}

// Moves a row down by the specified number of rows.
void Grid::MoveRowDown(int row, int numRows) {
    for (int column = 0; column < numCols; column++) {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}
