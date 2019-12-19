#pragma once
#include "Material.h"

class Lambertian : public Material
{
public:
	Vector3 albedo;

	Lambertian(const Vector3& a) : albedo(a) {}

	virtual bool scatter(const Ray& r_in, const HitRecord& hrec, Vector3& attenuation, Ray& scattered) const
	{
		Vector3 target = hrec.point + hrec.normal + randomInUnitSphere();
		scattered = Ray(hrec.point, target - hrec.point);
		attenuation = albedo;
		return true;
	}
};