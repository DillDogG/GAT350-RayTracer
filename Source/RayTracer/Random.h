#pragma once
#include <random>

inline void seedRandom(unsigned int seed) { srand(seed); }

inline float randomf() { return rand() / (float)RAND_MAX; }

inline float randomf(float min, float max) { return min + randomf() * (max - min); }

inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max) { return glm::vec3{ randomf(min.x, max.x), randomf(min.y, max.y), randomf(min.z, max.z) }; }

inline glm::vec3 randomInUnitSphere() {
	glm::vec3 v;
	// generate random vectors between -1 <-> +1, return vector if length is less than 1
	do {
		v = random(glm::vec3{ -1 }, glm::vec3{ 1 });
	} while (glm::length(v) >= 1.0f);

	return v;
}