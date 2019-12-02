#pragma once
#include "Ray.h"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class AABB {
public:
	Vector3 min;
	Vector3 max;

	AABB() {}
	AABB(const Vector3& a, const Vector3& b) { min = a; max = b; }

	inline bool hit(const Ray& r, float tmin, float tmax) const 
	{
		for (int a = 0; a < 3; a++) {
			float invD = 1.0f / r.direction()[a];
			float t0 = (min[a] - r.origin()[a]) * invD;
			float t1 = (max[a] - r.origin()[a]) * invD;
			if (invD < 0.0f)
				std::swap(t0, t1);
			tmin = t0 > tmin ? t0 : tmin;
			tmax = t1 < tmax ? t1 : tmax;
			if (tmax <= tmin)
				return false;
		}
		return true;
	}
};