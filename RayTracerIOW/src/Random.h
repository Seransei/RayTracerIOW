#pragma once
#include <functional>
#include <random>

inline double randomDouble()
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	static std::function<double()> rand_generator = std::bind(distribution, generator);
	return rand_generator();
}

Vector3 randomInUnitSphere() 
{
	Vector3 p;
	do {
		p = 2.0f * Vector3(randomDouble(), randomDouble(), randomDouble()) - Vector3(1, 1, 1);
	} while (p.squared_magnitude() >= 1.0f);
	return p;
}