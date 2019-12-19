#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Random.h"
#include "Metal.h"
#include "Lambertian.h"
#include "BVHNode.h"

#include <iostream>
#include <fstream>
#include <float.h>
#include <ctime>

int nInter = 0;
const int nSph = 1000;

Vector3 color(const Ray& r, Hittable* world, int depth)
{
	HitRecord hrec;
	if (world->hit(r, 0.001f, FLT_MAX, hrec))
	{
		Ray scattered;
		Vector3 attenuation;
		if (depth < 1/*maxDepth*/ && hrec.mat->scatter(r, hrec, attenuation, scattered)) 
		{
			nInter++;
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

Hittable* randomScene() {
	Hittable** list = new Hittable * [nSph + 1];
	int i = 0;
	for (int a = -1; a < 0; a++) {
		for (int b = -50; b < 50; b++) {
			float choose_mat = randomDouble();
			Vector3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());
			if ((center - Vector3(4, 0.2, 0)).magnitude() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					list[i++] = new Sphere(
						center, 0.2,
						new Lambertian(
							Vector3(randomDouble() * randomDouble(),
								randomDouble() * randomDouble(),
								randomDouble() * randomDouble())
						)
					);
				}
				else { // metal
					list[i++] = new Sphere(
						center, 0.2,
						new Metal(
							Vector3(0.5 * (1 + randomDouble()),
								0.5 * (1 + randomDouble()),
								0.5 * (1 + randomDouble())),
							0.5 * randomDouble()
						)
					);
				}
			}
		}
	}

	//return new HittableList(list, i);
	return new BVHNode(list, i, 0.0f, 1.0f);
}

int main() 
{
	int
		nX = 400,
		nY = 400,
		nS = 100;

	std::ofstream file;
	file.open("outputs/output.ppm");

	auto begin = clock();

	Hittable* world = randomScene();

	Camera cam;
	file << "P3\n" << nX << " " << nY << "\n255\n";

	auto endBVH = clock();
	auto elapsedTime = (endBVH - begin) / CLOCKS_PER_SEC;
	std::cout << "BVH : " << elapsedTime << " secondes" << std::endl;

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
	
	auto end = clock();
	elapsedTime = (end - begin) / CLOCKS_PER_SEC;

	std::cout << "Total : " << elapsedTime << " secondes" << std::endl;
	std::cout << nInter << " intersections" << std::endl;
}