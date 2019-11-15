#include "Vector3.h"

Vector3::Vector3() {}
Vector3::Vector3(float x, float y, float z) { setXYZ(x, y, z); }
void Vector3::setXYZ(float x, float y, float z) {
	xyz[0] = x; xyz[1] = y; xyz[2] = z;
}
const float* Vector3::getXYZ() const {
	return xyz;
}

Vector3& Vector3::operator=(const Vector3& vec3) {
	for (int i = 0; i < 3; i++) xyz[i] = vec3.xyz[i];
	return (*this);
}

float& Vector3::operator[](const int i) {
	return xyz[i];
}
float Vector3::operator[](const int i) const {
	return xyz[i];
}


Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}
Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	return Vector3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}
Vector3 operator-(const Vector3& v) {
	return Vector3(-1 * v[0], -1 * v[1], -1 * v[2]);
}
Vector3 operator*(const float s, const Vector3& vec3) {
	return Vector3(s * vec3[0], s * vec3[1], s * vec3[2]);
}
float dotProduct(const Vector3& v1, const Vector3& v2) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}