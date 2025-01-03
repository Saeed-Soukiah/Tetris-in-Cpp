#pragma once

// Represents the position of a cell within the grid.
class Position {
public:
    Position(int row, int column); // Constructor to initialize a position.
    int row;    // Row index of the position.
    int column; // Column index of the position.
};
