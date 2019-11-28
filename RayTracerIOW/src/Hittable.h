#pragma once
#include "Ray.h"

class Material;

struct HitRecord {
	float t;
	Vector3 point;
	Vector3 normal;
	Material* mat;
};

class Hittable {
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};