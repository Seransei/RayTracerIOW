#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Random.h"

#include <iostream>
#include <fstream>
#include <float.h>

Vector3 color(const Ray& r, Hittable *world)
{
	HitRecord hrec;
	if (world->hit(r, 0.001f, FLT_MAX, hrec))
	{
		Vector3 target = hrec.point + hrec.normal + randomInUnitSphere();
		return 0.5f* color(Ray(hrec.point, target - hrec.point), world);
	} else
	{
		Vector3 unitDir = r.direction().normalized();
		float t = 0.5f * (unitDir.y() + 1.0f);
		return (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
	}
}

int main() 
{
	int
		nX = 400,
		nY = 400,
		nS = 100;

	std::ofstream file;
	file.open("outputs/output.ppm");

	Hittable* list[2];
	list[0] = new Sphere(Vector3(0.f, 0.f, -1.f), 0.5);
	list[1] = new Sphere(Vector3(0.f, -100.5f, -1.f), 100);
	Hittable* world = new HittableList(list, 2);

	Camera cam;
	file << "P3\n" << nX << " " << nY << "\n255\n";

	for (int y = nY - 1; y >= 0; y--) 
	{
		for (int x = 0; x < nX; x++) 
		{
			Vector3 col(0, 0, 0);
			for (int s = 0; s < nS; s++) {
				float u = float(x + randomDouble()) / float(nX);
				float v = float(y + randomDouble()) / float(nY);
				Ray r = cam.getRay(u, v);
				col += color(r, world);
			}
			col /= float(nS);
			col = Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int
				ir = int(255.99 * col[0]),
				ig = int(255.99 * col[1]),
				ib = int(255.99 * col[2]);
			file << ir << " " << ig << " " << ib << "\n";
		}
	}
}