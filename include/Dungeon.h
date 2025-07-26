// ===================================================================================
// Dungeon.h
//
// Header file for the Dungeon class.
// This class manages the dungeon grid, its generation, and pathfinding within it.
// It acts as the main engine for the entire project.
// ===================================================================================

#pragma once // A modern header guard to prevent this file from being included multiple times

#include "DataStructures.h" // Includes Point, PathNode, and PointStack
#include "SimplePRNG.h"     // Includes the random number generator
#include "Constants.h"      // Includes grid dimensions and characters

class Dungeon {
public:
    // --- Constructor ---
    // Initializes the Dungeon object, including the random number generator.
    Dungeon();

    // --- Public Methods for Grid Management and Display ---

    // Fills the entire grid with a specified character.
    void initialize(char fillChar);

    // Prints the current state of the dungeon to the console, including axes and borders.
    void print();

    // Checks if a given coordinate (x, y) is within the valid bounds of the dungeon grid.
    bool isInBounds(int x, int y);

    // Safely sets a character at a specific (x, y) coordinate on the grid.
    void setChar(int x, int y, char c);

    // --- Public Methods for Dungeon Generation ---

    // Generates a cave-like dungeon using the Cellular Automata algorithm.
    void generateCellularAutomata(int iterations = 5, int wallProbability = 45);

    // Generates a perfect maze with long corridors using the Recursive Backtracker algorithm.
    void generateRecursiveBacktracker();

    // --- Public Method for Pathfinding ---

    // Finds a path from a start point to an end point using either A* or Dijkstra's algorithm.
    // If useAStar is true, it uses the A* heuristic; otherwise, it functions like Dijkstra's.
    void findPath(Point start, Point end, bool useAStar);

private:
    // --- Private Members ---

    // The 2D array representing the dungeon grid itself.
    char grid[DUNGEON_HEIGHT][DUNGEON_WIDTH];

    // An instance of the pseudo-random number generator for all random operations.
    SimplePRNG prng;

    // --- Private Helper Methods for Pathfinding ---

    // Backtracks from the end node to the start node to draw the final path on the grid.
    void reconstructPath(PathNode* endNode);

    // Determines the correct box-drawing character (e.g., │, ─, ┌) for a segment of the path
    // based on the previous, current, and next points in the sequence.
    char getPathCharacter(Point prev, Point current, Point next);
};
