// ===================================================================================
// DataStructures.h
//
// This file declares the data structures used throughout the project, such as
// coordinate points, pathfinding nodes, and the stack for maze generation.
// ===================================================================================

#pragma once // A modern header guard to prevent this file from being included multiple times

#include "Constants.h" // Needed for DUNGEON_WIDTH and DUNGEON_HEIGHT in PointStack

// --- Point Struct ---
// Represents a simple 2D coordinate on the grid.
struct Point {
    int x;
    int y;
};

// --- Pathfinding Node Struct ---
// A structure to hold all the necessary data for a single node during pathfinding
// algorithms like A* and Dijkstra's.
struct PathNode {
    Point pos;       // The node's (x, y) position on the grid.
    int gCost;       // The movement cost from the start node to this node.
    int hCost;       // The estimated heuristic cost from this node to the end node.
    int fCost;       // The total cost (gCost + hCost), used to prioritize nodes.
    PathNode* parent;  // A pointer to the node that came before this one in the path.
    bool isOpen;     // Flag indicating if the node is currently in the "open list" to be evaluated.
    bool isClosed;   // Flag indicating if the node has already been evaluated.
};

// --- Stack for Recursive Backtracker ---
// A simple LIFO (Last-In, First-Out) stack implementation for Point objects.
// This is required for the depth-first search nature of the recursive backtracker algorithm.
class PointStack {
public:
    // --- Constructor ---
    // Initializes the stack to be empty.
    PointStack();

    // --- Public Methods ---

    // Checks if the stack contains no elements.
    // Returns true if the stack is empty, false otherwise.
    bool isEmpty();

    // Adds a Point to the top of the stack.
    void push(Point p);

    // Removes and returns the Point from the top of the stack.
    // Returns a {-1, -1} point if the stack is empty (should not happen in our usage).
    Point pop();

    // Returns the Point from the top of the stack without removing it.
    // Returns a {-1, -1} point if the stack is empty.
    Point peek();

private:
    // --- Private Members ---

    // A fixed-size array to store the stack items. The size is the maximum
    // number of cells in the dungeon.
    Point items[DUNGEON_WIDTH * DUNGEON_HEIGHT];

    // An index that points to the top element of the stack.
    int top;
};
