// ===================================================================================
// DataStructures.cpp
//
// Implementation file for the data structures declared in DataStructures.h.
// Currently, this only contains the implementation for the PointStack class.
// ===================================================================================

#include "DataStructures.h" // Include the corresponding header file

// --- PointStack Constructor ---
// Initializes the stack's top index to -1, indicating that it is empty.
PointStack::PointStack() {
    top = -1;
}

// --- isEmpty ---
// Checks if the stack is empty.
bool PointStack::isEmpty() {
    return top == -1;
}

// --- push ---
// Adds a new Point to the top of the stack if there is space.
void PointStack::push(Point p) {
    // Check for stack overflow
    if (top < (DUNGEON_WIDTH * DUNGEON_HEIGHT) - 1) {
        items[++top] = p;
    }
}

// --- pop ---
// Removes and returns the Point from the top of the stack.
Point PointStack::pop() {
    // Check for stack underflow
    if (!isEmpty()) {
        return items[top--];
    }
    // Return a sentinel value if the stack is empty
    return {-1, -1}; 
}

// --- peek ---
// Returns the top Point of the stack without removing it.
Point PointStack::peek() {
    // Check for stack underflow
    if (!isEmpty()) {
        return items[top];
    }
    // Return a sentinel value if the stack is empty
    return {-1, -1};
}
