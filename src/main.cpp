// ===================================================================================
// main.cpp
//
// The main entry point for the Procedural Dungeon Generator and Pathfinding Visualizer.
// This file contains the user interface loop and handles user input to drive the
// dungeon generation and pathfinding processes.
// ===================================================================================

#include <iostream>     // For console input and output (cin, cout)
#include "Dungeon.h"      // The main header for the Dungeon class and all its functionality

// --- printMenu ---
// Displays the main menu of options to the user.
void printMenu() {
    std::cout << "=====================================================\n";
    std::cout << "  Procedural Dungeon & Pathfinding Visualizer\n";
    std::cout << "=====================================================\n";
    std::cout << "1. Generate Dungeon (Cellular Automata)\n";
    std::cout << "2. Generate Dungeon (Recursive Backtracker)\n";
    std::cout << "3. Find Path (A* Search)\n";
    std::cout << "4. Find Path (Dijkstra's Algorithm)\n";
    std::cout << "5. Print Current Dungeon\n";
    std::cout << "6. Exit\n";
    std::cout << "-----------------------------------------------------\n";
    std::cout << "Enter your choice: ";
}

// --- main ---
// The primary function where the program execution begins.
int main() {
    // Create the main dungeon object. This will prompt for a seed upon creation.
    Dungeon dungeon;
    bool dungeonGenerated = false;
    int choice;

    // The main application loop. It continues until the user chooses to exit.
    do {
        printMenu();
        std::cin >> choice;

        // Process the user's choice.
        switch (choice) {
            case 1: // Generate with Cellular Automata
                dungeon.generateCellularAutomata();
                dungeon.print();
                dungeonGenerated = true;
                break;

            case 2: // Generate with Recursive Backtracker
                dungeon.generateRecursiveBacktracker();
                dungeon.print();
                dungeonGenerated = true;
                break;

            case 3: // Find Path with A*
            case 4: // Find Path with Dijkstra's
                if (!dungeonGenerated) {
                    std::cout << "\nPlease generate a dungeon first (option 1 or 2).\n\n";
                } else {
                    Point start, end;
                    std::cout << "Enter Start X Y (e.g., 1 1): ";
                    std::cin >> start.x >> start.y;
                    std::cout << "Enter End X Y (e.g., " << DUNGEON_WIDTH - 2 << " " << DUNGEON_HEIGHT - 2 << "): ";
                    std::cin >> end.x >> end.y;

                    // Validate user input coordinates.
                    if (!dungeon.isInBounds(start.x, start.y) || !dungeon.isInBounds(end.x, end.y)) {
                         std::cout << "\nError: One or both coordinates are out of bounds.\n\n";
                         break;
                    }
                    
                    // Create a temporary copy of the dungeon to run pathfinding on.
                    // This preserves the original, path-free dungeon for future use.
                    Dungeon pathfindingCopy = dungeon;
                    
                    // Run the chosen pathfinding algorithm.
                    pathfindingCopy.findPath(start, end, (choice == 3)); // 'true' for A*, 'false' for Dijkstra
                    
                    // Place 'S' and 'E' markers on the grid for better visualization.
                    pathfindingCopy.setChar(start.x, start.y, START_CHAR);
                    pathfindingCopy.setChar(end.x, end.y, END_CHAR);

                    // Print the result.
                    pathfindingCopy.print();
                }
                break;

            case 5: // Print the current state of the original dungeon
                dungeon.print();
                break;

            case 6: // Exit
                std::cout << "Exiting program. Goodbye!\n";
                break;

            default: // Handle invalid input
                std::cout << "\nInvalid choice. Please enter a number from 1 to 6.\n\n";
        }
    } while (choice != 6);

    return 0; // Indicate successful execution
}
