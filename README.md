# PathMorph: Procedural Dungeon and Pathfinding Visualizer

This is a C++ console application that demonstrates procedural content generation and classic pathfinding algorithms. Users can generate complex dungeons using two different methods and then visualize the shortest path between any two points using either A* or Dijkstra's algorithm.

The project is built entirely from scratch, using only the `<iostream>` library for console I/O, making it a self-contained demonstration of fundamental data structures and algorithms.

## Features

* **Procedural Dungeon Generation:**
    * **Cellular Automata:** Creates organic, cave-like structures.
    * **Recursive Backtracker:** Generates perfect mazes with long, winding corridors.
* **Pathfinding Algorithms:**
    * **A\* Search:** The industry-standard algorithm that uses heuristics to find the shortest path efficiently.
    * **Dijkstra's Algorithm:** A classic algorithm that guarantees the shortest path from a single source to all other nodes.
* **Visual Interface:**
    * Renders the dungeon in the console with clear coordinate axes.
    * Uses box-drawing characters to display a continuous, easy-to-follow path.
* **Custom-Built Components:**
    * All data structures (Stack, Node) and utilities (PRNG) are implemented from scratch.

## Project Structure

The project is organized into a clean and scalable directory structure that separates interfaces (`.h`) from implementations (`.cpp`).

```bash
ProceduralDungeon/
|
|-- include/
|   |-- Constants.h
|   |-- DataStructures.h
|   |-- SimplePRNG.h
|   |-- Dungeon.h
|
|-- src/
|   |-- DataStructures.cpp
|   |-- SimplePRNG.cpp
|   |-- Dungeon.cpp
|   |-- main.cpp
|
|-- bin/
|   `-- (This directory is created during compilation)
|
|-- Makefile
```

## How to Build and Run

### Prerequisites

You will need a C++ compiler that supports the C++11 standard. The `Makefile` is configured to use `g++`, which is standard on most Linux distributions and macOS. Windows users can use `g++` via MinGW or WSL.

### Instructions

The included `Makefile` automates the entire build process. Simply run the following commands from the root directory of the project (`ProceduralDungeon/`).

**1. To Compile the Project:**

This command compiles all the `.cpp` source files and links them to create an executable file in the `bin/` directory.

```bash
make

2. To Run the Application:

This command will first compile the project (if it hasn't been already) and then execute the program.

make run

3. To Clean the Project:

This command removes all compiled files (the bin/ directory and its contents), which is useful for a fresh rebuild.

make clean
