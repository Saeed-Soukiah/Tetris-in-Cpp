#pragma once
#include <vector>
#include "raylib.h"
using namespace std;

// The Grid class represents the Tetris game grid and manages its cells, rendering, and row clearing.
class Grid {
public:
    Grid(); // Constructor to initialize the grid with default settings.
    void Initialize(); // Resets the grid cells to empty.
    void Print(); // Prints the current grid state to the console (for debugging purposes).
    void Draw(); // Draws the grid and its cells on the screen.
    int grid[20][20]; // 2D array representing the grid cells (20 rows x 10 columns).

    // Checks if a cell is outside the grid bounds.
    bool IsCellOutside(int row, int column);

    // Checks if a cell is empty.
    bool IsCellEmpty(int row, int column);

    // Clears all full rows and returns the number of rows cleared.
    int ClearFullRows();

private:
    int numRows; // Total number of rows in the grid.
    int numCols; // Total number of columns in the grid.
    int cellSize; // Size of each cell in pixels.
    vector<Color> colors; // Colors associated with cell values.

    // Helper functions for managing rows.
    bool IsRowFull(int row); // Checks if a row is completely filled.
    void ClearRow(int row); // Clears the cells in a specific row.
    void MoveRowDown(int row, int numRows); // Moves rows down by the specified number of rows.
};
