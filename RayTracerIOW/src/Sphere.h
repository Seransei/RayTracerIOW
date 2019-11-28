#pragma once
#include "Hittable.h"

class Sphere : public Hittable {
public:
	Vector3 center;
	float radius;
	Material* mat;

	Sphere() {}
	Sphere(Vector3 cen, float r, Material* m) : center(cen), radius(r), mat(m) {};
	virtual bool hit(const Ray& r, float tmin, float tmax, HitRecord& hrec) const;
};

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& hrec) const {
	Vector3 oc = r.origin() - center;
	float a = r.direction().dot2();
	float b = oc.dot(r.direction());
	float c = oc.dot2() - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			hrec.t = temp;
			hrec.point = r.pointAtParam(hrec.t);
			hrec.normal = (hrec.point - center) / radius;
			hrec.mat = mat;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			hrec.t = temp;
			hrec.point = r.pointAtParam(hrec.t);
			hrec.normal = (hrec.point - center) / radius;
			hrec.mat = mat;
			return true;
		}
	}
	return false;
}