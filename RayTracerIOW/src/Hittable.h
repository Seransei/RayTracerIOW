#pragma once
#include "AABB.h"

class Material;

AABB surroundingBox(AABB box0, AABB box1)
{
	Vector3 small(
		ffmin(box0.min.x(), box1.min.x()),
		ffmin(box0.min.y(), box1.min.y()),
		ffmin(box0.min.z(), box1.min.z()));
	Vector3 big(
		ffmax(box0.max.x(), box1.max.x()),
		ffmax(box0.max.y(), box1.max.y()),
		ffmax(box0.max.z(), box1.max.z()));
	return AABB(small, big);
}

struct HitRecord 
{
	float t;
	Vector3 point;
	Vector3 normal;
	Material* mat;
};

class Hittable 
{
public:
	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
	virtual bool boundingBox(float t0, float t1, AABB& box) const = 0;
};