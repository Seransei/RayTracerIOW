#include "Vector3.h"

#include <iostream>
#include <fstream>

int main() 
{
	std::ofstream file;
	file.open("outputs/output.ppm");

	int
		nX = 400,
		nY = 400;

	file << "P3\n" << nX << " " << nY << "\n255\n";
	for (int y = nY - 1; y >= 0; y--) 
	{
		for (int x = 0; x < nX; x++) 
		{
			Vector3<float> pix(float(x) / float(nX), float(y) / float(nY), 0.2);
			int
				ir = int(255.99 * pix[0]),
				ig = int(255.99 * pix[1]),
				ib = int(255.99 * pix[2]);
			file << ir << " " << ig << " " << ib << "\n";
		}
	}
}