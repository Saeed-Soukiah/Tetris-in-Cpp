#pragma once
#include "Grid.h"
#include <vector>
#include "Blocks.cpp"  // Including the block classes which represent different block shapes.

using namespace std;

class Game
{
public:
    Game();  // Constructor to initialize the game state.
    ~Game(); // Destructor to clean up resources.

    void Draw();  // Function to draw the game grid and blocks on screen.
    void HandleInput();  // Function to handle user input (keyboard keys).
    void MoveBlockDown();  // Move the current block down the screen.

    bool GameOver;  // Flag to indicate if the game is over.
    int Score;      // Variable to store the current score.
    Music music;    // Music object for background music.

private:
    Grid grid;  // The game grid where blocks will fall.
    void MoveBlockLeft();  // Move the block left.
    void HardDrop();       // Make the block fall instantly to the bottom.
    void MoveBlockRight(); // Move the block right.
    Block GetRandomBlock(); // Get a random block type.
    vector<Block> GetAllBlocks(); // Get a list of all available block types.
    bool IsBlockOutside();  // Check if the block is outside the grid bounds.
    void RotateBlock();     // Rotate the block.
    void LockBlock();       // Lock the current block into place.
    bool BlockFits();       // Check if the block fits in its current position.

    vector<Block> blocks;  // Store the different block types.
    Block currentBlock;    // The current block being controlled by the player.
    Block nextBlock;       // The next block that will appear.

    void Reset();  // Reset the game to its initial state.
    void UpdateScore(int LinesCleared, int MoveDownPoints);  // Update the score based on cleared lines and points earned.
    Sound RotateSound;  // Sound effect for rotating blocks.
    Sound ClearSound;   // Sound effect for clearing lines.
    Sound hardDropSound; // Sound effect for a hard drop.
};
