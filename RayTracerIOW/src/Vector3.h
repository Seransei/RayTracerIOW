#pragma once
#include <iostream>
#include <math.h>
#include <cstdlib>

class Vector3
{
public:
	float values[3];

	Vector3() {};
	Vector3(float xx, float yy, float zz) { values[0] = xx, values[1] = yy, values[2] = zz; }

	// Getters explicit for coordinates
	inline float x() const { return values[0]; }
	inline float y() const { return values[1]; }
	inline float z() const { return values[2]; }

	// Getters explicit for colors
	inline float r() const { return values[0]; }
	inline float g() const { return values[1]; }
	inline float b() const { return values[2]; }

	// Getter operators
	inline const Vector3& operator+() const { return *this; }
	inline const Vector3& operator-() const { return Vector3(-values[0], -values[1], -values[2]); }
	inline float operator[](int i) const { return values[i]; }
	inline float& operator[](int i) { return values[i]; }

	// Math operations on Vector3
	inline Vector3& operator+=(const Vector3& v);
	inline Vector3& operator-=(const Vector3& v);
	inline Vector3& operator*=(const Vector3& v);
	inline Vector3& operator/=(const Vector3& v);
	inline Vector3& operator*=(const float t);
	inline Vector3& operator/=(const float t);

	inline float magnitude() const { return sqrt(values[0] * values[0] + values[1] * values[1] + values[2] * values[2]); }
	inline float squared_magnitude()const { return values[0] * values[0] + values[1] * values[1] + values[2] * values[2]; }
	inline void normalize();
	inline Vector3 normalized() const { return *this / this->magnitude(); }
	inline float dot(const Vector3& v) const { return values[0] * v.values[0] + values[1] * v.values[1] + values[2] * v.values[2]; }
	inline float dot2()const { return this->dot(*this); }
	inline Vector3 cross(const Vector3& v);
};

inline std::istream& operator>>(std::istream& is, Vector3& t)
{
	is >> t.values[0] >> t.values[1] >> t.values[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, Vector3& t)
{
	os << t.values[0] << t.values[1] << t.values[2];
	return os;
}

inline Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1.values[0] + v2.values[0], v1.values[1] + v2.values[1], v1.values[2] + v2.values[2]);
}

inline Vector3 operator-(const Vector3 & v1, const Vector3 & v2) {
	return Vector3(v1.values[0] - v2.values[0], v1.values[1] - v2.values[1], v1.values[2] - v2.values[2]);
}

inline Vector3 operator*(const Vector3 & v1, const Vector3 & v2) {
	return Vector3(v1.values[0] * v2.values[0], v1.values[1] * v2.values[1], v1.values[2] * v2.values[2]);
}

inline Vector3 operator*(float t, const Vector3 & v) {
	return Vector3(t * v.values[0], t * v.values[1], t * v.values[2]);
}

inline Vector3 operator*(const Vector3 & v, float t) {
	return Vector3(t * v.values[0], t * v.values[1], t * v.values[2]);
}

inline Vector3 operator/(const Vector3 & v1, const Vector3 & v2) {
	return Vector3(v1.values[0] / v2.values[0], v1.values[1] / v2.values[1], v1.values[2] / v2.values[2]);
}

inline Vector3 operator/(Vector3 v, float t) {
	return Vector3(v.values[0] / t, v.values[1] / t, v.values[2] / t);
}
