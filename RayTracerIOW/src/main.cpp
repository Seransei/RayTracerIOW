#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Random.h"
#include "Metal.h"
#include "Lambertian.h"

#include <iostream>
#include <fstream>
#include <float.h>

Vector3 color(const Ray& r, Hittable *world, int depth)
{
	HitRecord hrec;
	if (world->hit(r, 0.001f, FLT_MAX, hrec))
	{
		Ray scattered;
		Vector3 attenuation;
		if (depth < 5/*maxDepth*/ && hrec.mat->scatter(r, hrec, attenuation, scattered)) 
		{
			return attenuation * color(scattered, world, depth + 1);
		} else
		{
			return Vector3(0, 0, 0);
		}
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

	Hittable* list[4];
	list[0] = new Sphere(Vector3(0.f, 0.f, -1.f), 0.5f, new Lambertian(Vector3(0.8f, 0.3f, 0.3f)));
	list[1] = new Sphere(Vector3(0.f, -100.5f, -1.f), 100.f, new Lambertian(Vector3(0.8f, 0.8f, 0.f)));
	list[2] = new Sphere(Vector3(1.f, 0.f, -1.f), 0.5f, new Metal(Vector3(0.8f, 0.6f, 0.2f), 0.3f));
	list[3] = new Sphere(Vector3(-1.f, 0.f, -1.f), 0.5f, new Metal(Vector3(0.8f, 0.8f, 0.8f), 1.0f));
	Hittable* world = new HittableList(list, 4);

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
				col += color(r, world, 0);
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