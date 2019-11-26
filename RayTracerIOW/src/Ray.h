#pragma once
#include "Vector3.h"

class Ray
{
public:
	Vector3 orig;
	Vector3 dir;

	Ray() {}
	Ray(const Vector3& a, const Vector3& b) { orig = a; dir = b; }

	Vector3 origin() const { return orig; }
	Vector3 direction() const { return dir; }
	Vector3 pointAtParam(float t) const { return origin() + t * direction(); }
};

