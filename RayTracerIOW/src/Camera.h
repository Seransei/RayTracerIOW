#pragma once

#include "Ray.h"

class Camera {
public:
	Vector3 origin;
	Vector3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;

	Camera() {
		lower_left_corner = Vector3(-2.0, -1.0, -1.0);
		horizontal = Vector3(4.0, 0.0, 0.0);
		vertical = Vector3(0.0, 4.0, 0.0);
		origin = Vector3(0.0, 0.0, 0.0);
	}

	Ray getRay(float u, float v) {
		return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}
};