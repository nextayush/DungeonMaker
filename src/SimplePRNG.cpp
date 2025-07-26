// ===================================================================================
// SimplePRNG.cpp
//
// Implementation file for the SimplePRNG class.
// This file contains the logic for the pseudo-random number generator.
// ===================================================================================

#include "SimplePRNG.h" // Include the corresponding header file

// --- Constructor ---
// Initializes the pseudo-random number generator with a default seed.
// This seed can be changed later using the setSeed() method.
SimplePRNG::SimplePRNG() {
    // A common way to get a "random" seed is from user interaction or the system clock.
    // For reproducibility and simplicity, we start with a fixed value.
    seed = 12345;
}

// --- setSeed ---
// Allows the user to set a new seed for the generator, which will produce
// a different sequence of random numbers.
void SimplePRNG::setSeed(unsigned int newSeed) {
    seed = newSeed;
}

// --- randInt ---
// Generates and returns a pseudo-random integer within the specified range [min, max].
// It uses a Linear Congruential Generator (LCG) algorithm.
int SimplePRNG::randInt(int min, int max) {
    // These specific LCG parameters are from the POSIX standard for rand().
    // The formula is: X_{n+1} = (a * X_n + c) mod m
    // Here, 'a' is 1103515245, 'c' is 12345, and 'm' is 2^32 (implied by unsigned int).
    seed = 1103515245 * seed + 12345;

    // To map the large generated number to the desired range [min, max],
    // we use the modulo operator.
    // (seed / 65536) is used to get the upper 16 bits, which have better
    // random properties than the lower bits in many LCGs.
    if (max < min) {
        return min; // Safety check for invalid range
    }
    return min + (seed / 65536) % (max - min + 1);
}
