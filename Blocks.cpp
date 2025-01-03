#include "Block.h"
#include "Position.h"

// Definition of the L-shaped block
class LBlock : public Block {
public:
    LBlock() {
        id = 1; // Unique identifier for LBlock
        // Define the block's shape in four rotations
        cells[0] = { Position(0,2),Position(1,0),Position(1,1),Position(1,2) };
        cells[1] = { Position(0,1),Position(1,1),Position(2,1),Position(2,2) };
        cells[2] = { Position(1,0),Position(1,1),Position(1,2),Position(2,0) };
        cells[3] = { Position(0,0),Position(0,1),Position(1,1),Position(2,1) };
        Move(0, 3); // Initial positioning on the grid
    }
};

// Definition of the J-shaped block
class JBlock : public Block {
public:
    JBlock() {
        id = 2; // Unique identifier for JBlock
        // Define the block's shape in four rotations
        cells[0] = { Position(0,0),Position(1,0),Position(1,1),Position(1,2) };
        cells[1] = { Position(0,1),Position(1,2),Position(1,1),Position(2,1) };
        cells[2] = { Position(1,0),Position(1,1),Position(1,2),Position(2,2) };
        cells[3] = { Position(0,1),Position(1,1),Position(2,1),Position(2,1) };
        Move(0, 3); // Initial positioning on the grid
    }
};

// Definition of the I-shaped block
class IBlock : public Block {
public:
    IBlock() {
        id = 3; // Unique identifier for IBlock
        // Define the block's shape in four rotations
        cells[0] = { Position(1,0),Position(1,1),Position(1,2),Position(1,3) };
        cells[1] = { Position(0,2),Position(1,2),Position(2,2),Position(3,2) };
        cells[2] = { Position(2,0),Position(2,1),Position(2,2),Position(2,3) };
        cells[3] = { Position(0,1),Position(1,1),Position(2,1),Position(3,1) };
        Move(-1, 3); // Adjusted initial position for better alignment
    }
};

// Definition of the O-shaped block
class OBlock : public Block {
public:
    OBlock() {
        id = 4; // Unique identifier for OBlock
        // OBlock has only one rotation (no rotation needed)
        cells[0] = { Position(0,0),Position(0,1),Position(1,0),Position(1,1) };
        Move(0, 4); // Initial positioning on the grid
    }
};

// Definition of the S-shaped block
class SBlock : public Block {
public:
    SBlock() {
        id = 5; // Unique identifier for SBlock
        // Define the block's shape in four rotations
        cells[0] = { Position(0,1),Position(0,2),Position(1,0),Position(1,1) };
        cells[1] = { Position(0,1),Position(1,1),Position(1,2),Position(2,2) };
        cells[2] = { Position(1,1),Position(1,2),Position(2,0),Position(2,1) };
        cells[3] = { Position(0,0),Position(1,0),Position(1,1),Position(2,1) };
        Move(0, 3); // Initial positioning on the grid
    }
};

// Definition of the T-shaped block
class TBlock : public Block {
public:
    TBlock() {
        id = 6; // Unique identifier for TBlock
        // Define the block's shape in four rotations
        cells[0] = { Position(0,1),Position(1,0),Position(1,1),Position(1,2) };
        cells[1] = { Position(0,1),Position(1,1),Position(1,2),Position(2,1) };
        cells[2] = { Position(1,0),Position(1,1),Position(1,2),Position(2,1) };
        cells[3] = { Position(0,1),Position(1,0),Position(1,1),Position(2,1) };
        Move(0, 3); // Initial positioning on the grid
    }
};

// Definition of the Z-shaped block
class ZBlock : public Block {
public:
    ZBlock() {
        id = 7; // Unique identifier for ZBlock
        // Define the block's shape in four rotations
        cells[0] = { Position(0,0),Position(0,1),Position(1,1),Position(1,2) };
        cells[1] = { Position(0,2),Position(1,1),Position(1,2),Position(2,1) };
        cells[2] = { Position(1,0),Position(1,1),Position(2,1),Position(2,2) };
        cells[3] = { Position(0,1),Position(1,0),Position(1,1),Position(2,0) };
        Move(0, 3); // Initial positioning on the grid
    }
};
