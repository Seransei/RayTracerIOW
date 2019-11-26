#include "HittableList.h"

bool HittableList::hit(const Ray& r, float t_min, float t_max, HitRecord& hrec) const
{
	HitRecord tmp_hrec;
	bool anyHit = false;
	double closest = t_max;
	for (int i = 0; i < count; i++) {
		if (list[i]->hit(r, t_min, closest, tmp_hrec))
		{
			anyHit = true;
			closest = tmp_hrec.t;
			hrec = tmp_hrec;
		}
	}
	return anyHit;
}
