#include "Vector3.h"
#include "Ray.h"

#include <iostream>
#include <fstream>

Vector3 color(const Ray& r)
{
	Vector3 unitDir = r.direction().normalized();
	float t = 0.5f * (unitDir.y() + 1.0f);
	return (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
}

int main() 
{
	int
		nX = 400,
		nY = 400;

	std::ofstream file;
	file.open("outputs/output.ppm");

	file << "P3\n" << nX << " " << nY << "\n255\n";
	Vector3 lower_left_corner(-2.0, -1.0, -1.0);
	Vector3 horizontal(4.0, 0.0, 0.0);
	Vector3 vertical(0.0, 4.0, 0.0);
	Vector3 origin(0.0, 0.0, 0.0);

	for (int y = nY - 1; y >= 0; y--) 
	{
		for (int x = 0; x < nX; x++) 
		{
			float u = float(x) / float(nX);
			float v = float(y) / float(nY);
			Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			Vector3 pix = color(r);
			int
				ir = int(255.99 * pix[0]),
				ig = int(255.99 * pix[1]),
				ib = int(255.99 * pix[2]);
			file << ir << " " << ig << " " << ib << "\n";
		}
	}
}