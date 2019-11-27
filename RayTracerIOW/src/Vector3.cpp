#include "Vector3.h"

Vector3& Vector3::operator+=(const Vector3& v)
{
	values[0] += v.values[0];
	values[1] += v.values[1];
	values[2] += v.values[2];
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	values[0] -= v.values[0];
	values[1] -= v.values[1];
	values[2] -= v.values[2];
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
	values[0] *= v.values[0];
	values[1] *= v.values[1];
	values[2] *= v.values[2];
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v)
{
	values[0] /= v.values[0];
	values[1] /= v.values[1];
	values[2] /= v.values[2];
	return *this;
}

Vector3& Vector3::operator*=(const float t)
{
	values[0] *= t;
	values[1] *= t;
	values[2] *= t;
	return *this;
}

Vector3& Vector3::operator/=(const float t)
{
	values[0] /= t;
	values[1] /= t;
	values[2] /= t;
	return *this;
}

inline void Vector3::normalize()
{	
	float k = 1.0f / magnitude();
	values[0] *= k;
	values[1] *= k;
	values[2] *= k;
}

Vector3 Vector3::normalized() const
{
	return Vector3(values[0] / magnitude(), values[1] / magnitude(), values[2] / magnitude());
}

inline Vector3 Vector3::cross(const Vector3& v)
{
	return Vector3(values[1] * v.values[2] - values[2] * v.values[1],
					  values[2] * v.values[0] - values[0] * v.values[2],
					  values[0] * v.values[1] - values[1] * v.values[0]);
}
