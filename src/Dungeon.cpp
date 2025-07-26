// ===================================================================================
// Dungeon.cpp
//
// Implementation file for the Dungeon class.
// This file contains all the logic for dungeon generation and pathfinding algorithms.
// ===================================================================================

#include "Dungeon.h"      // The corresponding header for this implementation
#include <iostream>       // Required for std::cout and std::cin

// --- Constructor ---
// Initializes the Dungeon object. It prompts the user for a random seed
// and then initializes the grid to be full of walls.
Dungeon::Dungeon() {
    // Prompt user for a seed to make generation unique each time.
    unsigned int seed_val;
    std::cout << "Enter a number to seed the random generator: ";
    std::cin >> seed_val;
    prng.setSeed(seed_val);

    // Start with a dungeon full of walls.
    initialize(WALL_CHAR);
}

// --- initialize ---
// Fills the entire grid with a specified character.
void Dungeon::initialize(char fillChar) {
    for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
        for (int x = 0; x < DUNGEON_WIDTH; ++x) {
            grid[y][x] = fillChar;
        }
    }
}

// --- print ---
// Prints the current state of the dungeon to the console, complete with
// coordinate axes and a border for better readability.
void Dungeon::print() {
    std::cout << "\n";
    // Print X-axis header (tens digit)
    std::cout << "    "; // Indent for Y-axis labels
    for (int x = 0; x < DUNGEON_WIDTH; ++x) {
        if (x % 10 == 0) {
            std::cout << x / 10;
        } else {
            std::cout << " ";
        }
    }
    std::cout << "\n";

    // Print X-axis header (units digit)
    std::cout << "    "; // Indent for Y-axis labels
    for (int x = 0; x < DUNGEON_WIDTH; ++x) {
        std::cout << x % 10;
    }
    std::cout << "\n";

    // Print top border
    std::cout << "   +";
    for (int x = 0; x < DUNGEON_WIDTH; ++x) {
        std::cout << "-";
    }
    std::cout << "+\n";

    // Print grid with Y-axis labels
    for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
        // Print Y-axis label, padded to 2 digits
        if (y < 10) std::cout << " ";
        std::cout << y << " |";

        for (int x = 0; x < DUNGEON_WIDTH; ++x) {
            std::cout << grid[y][x];
        }
        std::cout << "|\n";
    }

    // Print bottom border
    std::cout << "   +";
    for (int x = 0; x < DUNGEON_WIDTH; ++x) {
        std::cout << "-";
    }
    std::cout << "+\n\n";
}

// --- isInBounds ---
// Checks if a given coordinate is within the dungeon's boundaries.
bool Dungeon::isInBounds(int x, int y) {
    return x >= 0 && x < DUNGEON_WIDTH && y >= 0 && y < DUNGEON_HEIGHT;
}

// --- setChar ---
// Safely places a character on the grid at the specified coordinates.
void Dungeon::setChar(int x, int y, char c) {
    if (isInBounds(x, y)) {
        grid[y][x] = c;
    }
}

// --- generateCellularAutomata ---
// Generates a cave-like dungeon using cellular automata rules.
void Dungeon::generateCellularAutomata(int iterations, int wallProbability) {
    initialize(WALL_CHAR);

    // Step 1: Randomly fill the grid based on probability.
    for (int y = 1; y < DUNGEON_HEIGHT - 1; ++y) {
        for (int x = 1; x < DUNGEON_WIDTH - 1; ++x) {
            if (prng.randInt(0, 100) < wallProbability) {
                grid[y][x] = WALL_CHAR;
            } else {
                grid[y][x] = FLOOR_CHAR;
            }
        }
    }

    // Step 2: Apply simulation rules for several iterations.
    for (int i = 0; i < iterations; ++i) {
        char tempGrid[DUNGEON_HEIGHT][DUNGEON_WIDTH];
        for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
            for (int x = 0; x < DUNGEON_WIDTH; ++x) {
                tempGrid[y][x] = grid[y][x];
            }
        }

        for (int y = 1; y < DUNGEON_HEIGHT - 1; ++y) {
            for (int x = 1; x < DUNGEON_WIDTH - 1; ++x) {
                int wallCount = 0;
                // Check 8 neighbors
                for (int ny = y - 1; ny <= y + 1; ++ny) {
                    for (int nx = x - 1; nx <= x + 1; ++nx) {
                        if (ny == y && nx == x) continue;
                        if (grid[ny][nx] == WALL_CHAR) {
                            wallCount++;
                        }
                    }
                }

                // Rule: A wall becomes a floor if it has < 4 wall neighbors.
                // Rule: A floor becomes a wall if it has > 4 wall neighbors.
                if (grid[y][x] == WALL_CHAR) {
                    if (wallCount < 4) tempGrid[y][x] = FLOOR_CHAR;
                } else {
                    if (wallCount > 4) tempGrid[y][x] = WALL_CHAR;
                }
            }
        }
        
        // Copy temp grid back to main grid
        for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
            for (int x = 0; x < DUNGEON_WIDTH; ++x) {
                grid[y][x] = tempGrid[y][x];
            }
        }
    }
    std::cout << "Dungeon generated with Cellular Automata.\n";
}

// --- generateRecursiveBacktracker ---
// Generates a perfect maze using a depth-first search (DFS) approach.
void Dungeon::generateRecursiveBacktracker() {
    initialize(WALL_CHAR);
    PointStack stack;

    // Start at a random odd-numbered coordinate
    Point startPos = {prng.randInt(0, DUNGEON_WIDTH / 2) * 2 + 1, prng.randInt(0, DUNGEON_HEIGHT / 2) * 2 + 1};
    grid[startPos.y][startPos.x] = FLOOR_CHAR;
    stack.push(startPos);

    while (!stack.isEmpty()) {
        Point current = stack.peek();
        
        // Get unvisited neighbors (2 cells away)
        Point neighbors[4];
        int neighborCount = 0;
        int dx[] = {0, 0, 2, -2};
        int dy[] = {2, -2, 0, 0};

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (isInBounds(nx, ny) && grid[ny][nx] == WALL_CHAR) {
                neighbors[neighborCount++] = {nx, ny};
            }
        }

        if (neighborCount > 0) {
            // Choose a random neighbor
            Point next = neighbors[prng.randInt(0, neighborCount - 1)];
            
            // Carve path to the neighbor
            grid[next.y][next.x] = FLOOR_CHAR;
            grid[current.y + (next.y - current.y) / 2][current.x + (next.x - current.x) / 2] = FLOOR_CHAR;

            stack.push(next);
        } else {
            // Backtrack
            stack.pop();
        }
    }
    std::cout << "Dungeon generated with Recursive Backtracker.\n";
}

// --- findPath ---
// The core pathfinding logic using A* or Dijkstra's algorithm.
void Dungeon::findPath(Point start, Point end, bool useAStar) {
    PathNode nodes[DUNGEON_HEIGHT][DUNGEON_WIDTH];
    for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
        for (int x = 0; x < DUNGEON_WIDTH; ++x) {
            nodes[y][x].pos = {x, y};
            nodes[y][x].gCost = 1000000; // Infinity
            nodes[y][x].hCost = 0;
            nodes[y][x].fCost = 1000000; // Infinity
            nodes[y][x].parent = NULL;
            nodes[y][x].isOpen = false;
            nodes[y][x].isClosed = false;
        }
    }

    PathNode* openList[DUNGEON_WIDTH * DUNGEON_HEIGHT];
    int openListSize = 0;

    nodes[start.y][start.x].gCost = 0;
    if (useAStar) {
        int dx_h = end.x - start.x;
        int dy_h = end.y - start.y;
        nodes[start.y][start.x].hCost = (dx_h > 0 ? dx_h : -dx_h) + (dy_h > 0 ? dy_h : -dy_h); // Manhattan
    }
    nodes[start.y][start.x].fCost = nodes[start.y][start.x].gCost + nodes[start.y][start.x].hCost;
    
    openList[openListSize++] = &nodes[start.y][start.x];
    nodes[start.y][start.x].isOpen = true;

    while (openListSize > 0) {
        int bestNodeIndex = 0;
        for (int i = 1; i < openListSize; ++i) {
            if (openList[i]->fCost < openList[bestNodeIndex]->fCost) {
                bestNodeIndex = i;
            }
        }
        PathNode* current = openList[bestNodeIndex];

        openList[bestNodeIndex] = openList[--openListSize];
        current->isOpen = false;
        current->isClosed = true;

        if (current->pos.x == end.x && current->pos.y == end.y) {
            reconstructPath(current);
            std::cout << "Path found!\n";
            return;
        }

        int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
        int dy[] = {1, -1, 0, 0, 1, 1, -1, -1};

        for (int i = 0; i < 8; ++i) {
            int nx = current->pos.x + dx[i];
            int ny = current->pos.y + dy[i];

            if (!isInBounds(nx, ny) || grid[ny][nx] == WALL_CHAR || nodes[ny][nx].isClosed) {
                continue;
            }
            
            int tentativeGCost = current->gCost + 1;

            if (tentativeGCost < nodes[ny][nx].gCost) {
                nodes[ny][nx].parent = current;
                nodes[ny][nx].gCost = tentativeGCost;
                if (useAStar) {
                    int dx_h = end.x - nx;
                    int dy_h = end.y - ny;
                    nodes[ny][nx].hCost = (dx_h > 0 ? dx_h : -dx_h) + (dy_h > 0 ? dy_h : -dy_h);
                }
                nodes[ny][nx].fCost = nodes[ny][nx].gCost + nodes[ny][nx].hCost;

                if (!nodes[ny][nx].isOpen) {
                    openList[openListSize++] = &nodes[ny][nx];
                    nodes[ny][nx].isOpen = true;
                }
            }
        }
    }
    
    std::cout << "Path not found.\n";
}

// --- reconstructPath ---
// Private helper to trace the path backwards from the end node and draw it.
void Dungeon::reconstructPath(PathNode* endNode) {
    if (endNode == NULL) return;

    PathNode* successor = NULL;
    PathNode* current = endNode;

    while (current != NULL) {
        PathNode* predecessor = current->parent;

        if (successor != NULL && predecessor != NULL) {
            Point p_prev = predecessor->pos;
            Point p_curr = current->pos;
            Point p_succ = successor->pos;
            if (grid[p_curr.y][p_curr.x] == FLOOR_CHAR) {
                grid[p_curr.y][p_curr.x] = getPathCharacter(p_prev, p_curr, p_succ);
            }
        }

        successor = current;
        current = predecessor;
    }
}

// --- getPathCharacter ---
// Private helper to select the correct box-drawing character for a path segment.
char Dungeon::getPathCharacter(Point prev, Point current, Point next) {
    bool from_up = (prev.y < current.y);
    bool from_down = (prev.y > current.y);
    bool from_left = (prev.x < current.x);
    
    bool to_up = (next.y < current.y);
    bool to_down = (next.y > current.y);
    bool to_left = (next.x < current.x);
    bool to_right = (next.x > current.x);

    if ((from_up && to_down) || (from_down && to_up)) return (char)179; // │
    if ((from_left && to_right) || (to_left && !from_left)) return (char)196; // ─

    if ((from_down && to_right) || (from_left && to_up)) return (char)192; // └
    if ((from_down && to_left) || (!from_left && to_up)) return (char)217; // ┘
    if ((from_up && to_right) || (from_left && to_down)) return (char)218; // ┌
    if ((from_up && to_left) || (!from_left && to_down)) return (char)191; // ┐

    return '+'; // Fallback
}
