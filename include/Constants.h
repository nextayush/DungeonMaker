// ===================================================================================
// Constants.h
//
// This file contains global constants used throughout the dungeon generation
// and pathfinding project. Centralizing them here makes them easy to modify.
// ===================================================================================

#pragma once // A modern header guard to prevent this file from being included multiple times

// --- Dungeon Dimensions ---
// Use odd numbers for width and height for best results with the Recursive Backtracker algorithm.
const int DUNGEON_WIDTH = 79;
const int DUNGEON_HEIGHT = 25;

// --- Visual Representation Characters ---
// Using extended ASCII characters for a more visually appealing dungeon.
// Note: The console must support code page 437 (or a similar character set)
// for these characters to be rendered correctly.

const char WALL_CHAR = (char)219; // Represents a solid wall block '█'
const char FLOOR_CHAR = ' ';      // Represents an open floor space
const char START_CHAR = 'S';      // Marks the starting point of the path
const char END_CHAR = 'E';        // Marks the ending point of the path

// The path itself is drawn using box-drawing characters, which are determined
// dynamically in the Dungeon::reconstructPath method, so there is no single PATH_CHAR.
