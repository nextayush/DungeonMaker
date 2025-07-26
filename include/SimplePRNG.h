// ===================================================================================
// SimplePRNG.h
//
// Header file for the SimplePRNG class.
// This file declares the interface for a simple pseudo-random number generator.
// ===================================================================================

#pragma once // A modern header guard to prevent this file from being included multiple times

class SimplePRNG {
public:
    // --- Constructor ---
    // Initializes the pseudo-random number generator.
    SimplePRNG();

    // --- Public Methods ---

    // Sets a new seed for the generator to start a new random sequence.
    void setSeed(unsigned int newSeed);

    // Returns a pseudo-random integer within the inclusive range [min, max].
    int randInt(int min, int max);

private:
    // --- Private Members ---

    // The current seed value. This state is updated with each call to randInt().
    unsigned int seed;
};
