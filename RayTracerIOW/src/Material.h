#pragma once
#include "Hittable.h"

class material
{
public:
	virtual bool scatter(const Ray& r_in, const HitRecord& hrec, Vector3& attenuation, Ray& scattered) const = 0;
};