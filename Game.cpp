#include "Game.h"
#include <random>
#include <vector>
using namespace std;

// Constructor for Game class
Game::Game()
{
    grid = Grid();  // Initialize the grid for the game.
    blocks = GetAllBlocks();  // Get all possible block types (IBlock, JBlock, etc.)
    currentBlock = GetRandomBlock();  // Get a random block to start with.
    nextBlock = GetRandomBlock();  // Get the next block.
    GameOver = false;  // Initialize the game as not over.
    Score = 0;  // Initialize score to 0.

    // Initialize audio for the game
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");  // Load background music.
    PlayMusicStream(music);  // Play background music.

    // Load sound effects
    RotateSound = LoadSound("Sounds/rotate.mp3");
    ClearSound = LoadSound("Sounds/clear.mp3");
    hardDropSound = LoadSound("Sounds/hard_drop.mp3");

    // Adjust sound volumes for different sound effects
    SetSoundVolume(RotateSound, 0.8f);   // 80% volume for rotation sound
    SetSoundVolume(ClearSound, 0.7f);    // 70% volume for clear sound
    SetSoundVolume(hardDropSound, 0.5f); // 50% volume for hard drop sound
}

// Destructor for Game class
Game::~Game()
{
    // Unload sound effects and music when the game is destroyed
    UnloadSound(RotateSound);
    UnloadSound(ClearSound);
    UnloadMusicStream(music);  // Properly unload music stream
    UnloadSound(hardDropSound);

    // Close the audio device to clean up resources
    CloseAudioDevice();
}

// Function to get a random block
Block Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();  // Refill blocks if they run out
        shuffle(blocks.begin(), blocks.end(), default_random_engine(rand()));  // Shuffle the blocks
    }

    Block block = blocks.back();  // Get the last block
    blocks.pop_back();  // Remove the last block from the vector
    return block;
}

// Function to get all block types
vector<Block> Game::GetAllBlocks()
{
    return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

// Draw the game grid and current/next blocks
void Game::Draw()
{
    grid.Draw();  // Draw the grid
    currentBlock.Draw(11, 11);  // Draw the current block at a given position
    // Draw the next block based on its type
    switch (nextBlock.id)
    {
    case 3:  // If next block is a TBlock
        nextBlock.Draw(255, 290);
        break;
    case 4:  // If next block is an OBlock
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);  // Default positioning
        break;
    }
}

// Handle user input for moving or rotating blocks
void Game::HandleInput() {
    int keyPressed = GetKeyPressed();  // Get the key pressed by the user
    if (GameOver && keyPressed != 0) {  // If game is over and a key is pressed, reset the game
        GameOver = false;
        Reset();
    }
    // Handle key events based on user input
    switch (keyPressed) {
    case KEY_LEFT:
        MoveBlockLeft();  // Move the block left
        break;
    case KEY_RIGHT:
        MoveBlockRight();  // Move the block right
        break;
    case KEY_DOWN:
        MoveBlockDown();  // Move the block down
        UpdateScore(0, 1);  // Update score when block moves down
        break;
    case KEY_UP:
        RotateBlock();  // Rotate the block
        break;
    case KEY_SPACE:  // Hard drop (move the block to the bottom)
        HardDrop();
        break;
    }
}

// Hard drop function: Move the block straight to the bottom of the grid
void Game::HardDrop() {
    if (!GameOver) {
        PlaySound(hardDropSound);  // Play the hard drop sound
        while (!IsBlockOutside() && BlockFits()) {
            currentBlock.Move(1, 0);  // Keep moving the block down until it can't fit
        }
        currentBlock.Move(-1, 0);  // Move it back one step
        LockBlock();  // Lock the block in place
    }
}

// Move the block left
void Game::MoveBlockLeft()
{
    if (!GameOver) {
        currentBlock.Move(0, -1);  // Move block left
        if (IsBlockOutside() || BlockFits() == false) {
            currentBlock.Move(0, 1);  // Undo move if it goes outside the grid
        }
    }
}

// Move the block right
void Game::MoveBlockRight()
{
    if (!GameOver) {
        currentBlock.Move(0, 1);  // Move block right
        if (IsBlockOutside() || BlockFits() == false) {
            currentBlock.Move(0, -1);  // Undo move if it goes outside the grid
        }
    }
}

// Move the block down
void Game::MoveBlockDown()
{
    if (!GameOver) {
        currentBlock.Move(1, 0);  // Move block down
        if (IsBlockOutside() || BlockFits() == false) {
            currentBlock.Move(-1, 0);  // Undo move if it doesn't fit
            LockBlock();  // Lock block in place if it doesn't fit
        }
    }
}

// Check if the block is outside the grid boundaries
bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column)) {  // Check if any cell is outside the grid
            return true;
        }
    }
    return false;
}

// Rotate the block
void Game::RotateBlock() {
    if (!GameOver) {
        currentBlock.Rotate();  // Rotate the block
        if (IsBlockOutside() || !BlockFits()) {
            // Wall kick logic to adjust position after rotation failure
            vector<Position> wallKickOffsets = {
                Position(0, -1),  // Shift left
                Position(0, 1),   // Shift right
                Position(-1, 0),  // Shift up
                Position(1, 0)    // Shift down
            };

            bool rotationSuccess = false;
            // Try wall kick offsets for valid rotation
            for (Position offset : wallKickOffsets) {
                currentBlock.Move(offset.row, offset.column);  // Try the offset move
                if (!IsBlockOutside() && BlockFits()) {  // If the block fits
                    rotationSuccess = true;
                    break;
                }
                currentBlock.Move(-offset.row, -offset.column);  // Undo the offset move
            }

            if (!rotationSuccess) {
                currentBlock.UndoRotation();  // Undo the rotation if no valid position was found
            }
            else {
                PlaySound(RotateSound);  // Play rotation sound only if it succeeds
            }
        }
        else {
            PlaySound(RotateSound);  // Play rotation sound if the initial rotation succeeds
        }
    }
}

// Lock the block in place on the grid
void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;  // Lock block to grid
    }
    currentBlock = nextBlock;  // Get the next block
    if (BlockFits() == false) {
        GameOver = true;  // Game over if the next block doesn't fit
    }
    nextBlock = GetRandomBlock();  // Generate a new random next block
    int rowsCleared = grid.ClearFullRows();  // Clear any full rows
    if (rowsCleared > 0) {
        PlaySound(ClearSound);  // Play sound when rows are cleared
        UpdateScore(rowsCleared, 0);  // Update score based on cleared rows
    }
}

// Check if the block can fit into its new position
bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPosition();
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false) {
            return false;  // Return false if any cell isn't empty
        }
    }
    return true;  // Return true if all cells are empty and the block fits
}

// Reset the game
void Game::Reset()
{
    grid.Initialize();  // Reset the grid
    blocks = GetAllBlocks();  // Reset the blocks
    currentBlock = GetRandomBlock();  // Get a new random block
    nextBlock = GetRandomBlock();  // Get a new next block
    Score = 0;  // Reset score
}

// Update the score based on lines cleared
void Game::UpdateScore(int LinesCleared, int MoveDownPoints)
{
    switch (LinesCleared) {
    case 1:
        Score += 100;  // Score for clearing 1 line
        break;
    case 2:
        Score += 500;  // Score for clearing 2 lines
        break;
    case 3:
        Score += 500;  // Score for clearing 3 lines
        break;
    default:
        break;
    }
    Score += MoveDownPoints;  // Add points for moving down
}
