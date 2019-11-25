#pragma once
#include <iostream>
#include <math.h>
#include <cstdlib>

template<typename T>
class Vector3
{
public:
	T values[3];

	Vector3() {};
	Vector3(T xx, T yy, T zz) { values[0] = xx, values[1] = yy, values[2] = zz; }

	// Getters explicit for coordinates
	inline T x() const { return values[0]; }
	inline T y() const { return values[1]; }
	inline T z() const { return values[2]; }

	// Getters explicit for colors
	inline T r() const { return values[0]; }
	inline T g() const { return values[1]; }
	inline T b() const { return values[2]; }

	// Getter operators
	inline const Vector3<T>& operator+() const { return *this; }
	inline const Vector3<T>& operator-() const { return Vector3<T>(-values[0], -values[1], -values[2]); }
	inline float operator[](int i) const { return values[i]; }
	inline float& operator[](int i) { return values[i]; }

	// Math operations on Vector3
	inline Vector3<T>& operator+=(const Vector3<T>& v);
	inline Vector3<T>& operator-=(const Vector3<T>& v);
	inline Vector3<T>& operator*=(const Vector3<T>& v);
	inline Vector3<T>& operator/=(const Vector3<T>& v);
	inline Vector3<T>& operator*=(const float t);
	inline Vector3<T>& operator/=(const float t);

	inline float magnitude()const { return sqrt(values[0] * values[0] + values[1] * values[1] + values[2] * values[2]); }
	inline float squared_magnitude()const { return values[0] * values[0] + values[1] * values[1] + values[2] * values[2]; }
	inline void normalize();
	inline Vector3<T> normalized() const { return this / magnitude; }
	inline float dot(const Vector3<T>& v) const { return x * v.x + y * v.y + z * v.z; }
	inline float dot2()const { return this->dot(*this); }
};

