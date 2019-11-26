#pragma once
#include "Hittable.h"

class HittableList : public Hittable 
{
public:
	Hittable** list;
	int count;

	HittableList() {}
	HittableList(Hittable** l, int n) { list = l; count = n; }
	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& hrec) const;
};