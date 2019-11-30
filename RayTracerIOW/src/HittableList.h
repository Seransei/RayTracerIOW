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
	virtual bool boundingBox(float t0, float t1, AABB& box) const;
};

bool HittableList::boundingBox(float t0, float t1, AABB& box) const
{
	if (count < 1)
		return false;
	AABB tmpBox;
	bool firstTrue = list[0]->boundingBox(t0, t1, tmpBox);
	if (!firstTrue)
		return false;
	else
		box = tmpBox;

	for (int i = 1; i < count; i++)
	{
		if (list[i]->boundingBox(t0, t1, tmpBox))
			box = surroundingBox(box, tmpBox);
		else
			return false;
	}
	return true;
}