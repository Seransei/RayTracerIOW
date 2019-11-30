#pragma once
#include "AABB.h"

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
	virtual bool boundingBox(float t0, float t1, AABB& box) const = 0;
};