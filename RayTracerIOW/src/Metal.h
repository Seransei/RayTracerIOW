#pragma once
#include "Material.h"

class Metal : public Material
{
public:
	Vector3 albedo;
	float fuzz;

	Metal(const Vector3& a, float f) : albedo(a) 
	{
		if (f < 1)
			fuzz = f;
		else
			fuzz = 1;
	}

	virtual bool scatter(const Ray& r_in, const HitRecord& hrec, Vector3& attenuation, Ray& scattered) const
	{
		Vector3 reflected = reflect(r_in.direction().normalized(), hrec.normal);
		scattered = Ray(hrec.point, reflected + fuzz * randomInUnitSphere());
		attenuation = albedo;
		return scattered.direction().dot(hrec.normal) > 0;
	}
};