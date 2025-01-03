/*
 * Tetris Game
 * Author: Saeed Soukiah
 * Date: 3/1/2025
 *
 * Features:
 * - Classic Tetris gameplay with blocks that fall and fit into a grid.
 * - Seven block types: I, O, T, S, Z, J, and L, each with unique rotations.
 * - Grid management that handles collisions, clearing full rows, and scoring.
 * - Smooth animations and visual rendering using the Raylib library.
 * - Background music and sound effects to enhance the gaming experience.
 * - Scoring system that tracks the player's progress.
 * - "Next block" preview to plan upcoming moves.
 * - Game over detection when blocks stack above the grid.
 * - Responsive keyboard input for block control.
 */

#include <iostream>
#include "raylib.h"
#include "Game.h"
#include "Colors.h"

double lastUpdateTime = 0; // Tracks the last update time for timed events.

// Determines if a specific time interval has passed.
bool EventTriggered(double interval) {
    double CurrentTime = GetTime();
    if (CurrentTime - lastUpdateTime >= interval) {
        lastUpdateTime = CurrentTime;
        return true;
    }
    return false;
}

int main() {
    InitWindow(500, 620, "Tetris"); // Initialize the game window.
    SetTargetFPS(60);              // Set the target frame rate.

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0); // Load custom font.

    Game game = Game(); // Initialize the game instance.

    while (!WindowShouldClose()) {
        UpdateMusicStream(game.music); // Update the background music.

        game.HandleInput(); // Process player input.

        if (EventTriggered(0.2)) {
            game.MoveBlockDown(); // Move the active block down periodically.
        }

        BeginDrawing();
        ClearBackground(darkBlue); // Clear the screen with a dark blue color.

        DrawTextEx(font, "Score", { 365, 15 }, 38, 2, WHITE); // Display the score.
        DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE); // Display the next block.

        if (game.GameOver) {
            DrawTextEx(font, "GAME OVER", { 320, 450 }, 38, 2, WHITE); // Display "Game Over".
        }

        DrawRectangleRounded({ 320, 55, 170, 60 }, 0.3, 6, lightBlue); // Score background.

        char scoreText[10];
        sprintf_s(scoreText, "%d", game.Score); // Convert score to string.

        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);

        DrawRectangleRounded({ 320, 215, 170, 180 }, 0.3, 6, lightBlue); // Next block background.

        game.Draw(); // Draw the game components.

        EndDrawing();
    }

    CloseWindow(); // Close the game window when exiting.
}
