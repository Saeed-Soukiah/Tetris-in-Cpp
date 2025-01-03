#pragma once
#include "raylib.h"  // To include the raylib library for color and graphics.
#include <vector>     // Used to store a list of colors.

using namespace std;

// Define color constants used in the game.
extern const Color darkGrey;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;
extern const Color lightBlue;
extern const Color darkBlue;

// Function to return a list of colors for the blocks.
vector <Color> GetCellColors();
