#pragma once
#include <vector>          // Used to include the vector container class for storing objects
#include <map>             // Used to include the map container class for storing key-value pairs
#include "Position.h"      // Including the Position class to handle row and column information
#include "Colors.h"        // Including color definitions for use with the blocks

using namespace std;

class Block
{
public:
    Block(); // Constructor for Block object, initializes member variables.

    void Draw(int offsetX, int offSetY);  // Function to draw the block on the screen, offsetX and offSetY adjust its position.

    void Move(int rows, int columns);     // Function to move the block by a specific number of rows and columns.

    vector<Position> GetCellPosition();   // Function that returns the positions of all the cells that make up the block.

    int id;                               // Unique identifier for the block (used to determine its type).

    map<int, vector<Position>> cells;     // Stores different rotations of the block by mapping rotation states to positions.

    void Rotate();                        // Function to rotate the block to the next state.

    void UndoRotation();                  // Function to undo a block's rotation (i.e., revert to the previous rotation state).

private:
    int cellSize;                         // Size of each block cell (in pixels).
    int rotationState;                    // Current rotation state (index to the rotation state).
    vector <Color> colors;                // Colors associated with each block.
    int rowOffset;                        // Row offset to adjust the block's position.
    int columnOffset;                     // Column offset to adjust the block's position.
};
