#include "Vector3.h"

template<typename T>
inline std::istream& operator>>(std::istream& is, Vector3<T>& t)
{
	is >> t.values[0] >> t.values[1] >> t.values[2];
	return is;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, Vector3<T>& t)
{
	os << t.values[0] << t.values[1] << t.values[2];
	return os;
}

template<typename T>
inline Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2) {
	return Vector3<T>(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

template<typename T>
inline Vector3<T> operator-(const Vector3<T> & v1, const Vector3<T> & v2) {
	return Vector3<T>(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T> & v1, const Vector3<T> & v2) {
	return Vector3<T>(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

template<typename T>
inline Vector3<T> operator*(float t, const Vector3<T> & v) {
	return Vector3<T>(t * v.e[0], t * v.e[1], t * v.e[2]);
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T> & v, float t) {
	return Vector3<T>(t * v.e[0], t * v.e[1], t * v.e[2]);
}

template<typename T>
inline Vector3<T> operator/(const Vector3<T> & v1, const Vector3<T> & v2) {
	return Vector3<T>(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

template<typename T>
inline Vector3<T> operator/(Vector3<T> v, float t) {
	return Vector3<T>(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& v)
{
	values[0] += v.values[0];
	values[1] += v.values[1];
	values[2] += v.values[2];
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& v)
{
	values[0] -= v.values[0];
	values[1] -= v.values[1];
	values[2] -= v.values[2];
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& v)
{
	values[0] *= v.values[0];
	values[1] *= v.values[1];
	values[2] *= v.values[2];
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& v)
{
	values[0] /= v.values[0];
	values[1] /= v.values[1];
	values[2] /= v.values[2];
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const float t)
{
	values[0] *= t;
	values[1] *= t;
	values[2] *= t;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(const float t)
{
	values[0] /= t;
	values[1] /= t;
	values[2] /= t;
	return *this;
}

template<typename T>
inline void Vector3<T>::normalize()
{	
	float k = 1.0 / magnitude();
	values[0] *= k;
	values[1] *= k;
	values[2] *= k;
}