#pragma once
#include <random>

inline void seedRandom(unsigned int seed) { srand(seed); }

inline float randomf() { return rand() / (float)RAND_MAX; }

inline float randomf(float min, float max) { return min + randomf() * (max - min); }