#include "SolidShape3D.h"

SolidShape3D::SolidShape3D() {
	center.setXYZ(0, 0, 0);
	velocity.setXYZ(0, 0, 0);

	setMTL();
}

SolidShape3D::SolidShape3D(const SolidShape3D& sh3d) {
	setCenter(sh3d.center);
	setVelocity(sh3d.velocity);
	
	mtl.setMTL(sh3d.mtl);
}

void SolidShape3D::setCenter(float x, float y, float z) {
	center[0] = x;
	center[1] = y;
	center[2] = z;
}

void SolidShape3D::setCenter(const Vector3& c) {
	center = c;
}

Vector3 SolidShape3D::getCenter() const {
	return center;
}

void SolidShape3D::setVelocity(float x, float y, float z) {
	velocity[0] = x;
	velocity[1] = y;
	velocity[2] = z;
}

void SolidShape3D::setVelocity(const Vector3& v) {
	velocity = v;
}

Vector3 SolidShape3D::getVelocity() const {
	return velocity;
}

void SolidShape3D::move() {
	center = center + velocity;
}

void SolidShape3D::setMTL() {
	mtl.setEmission(0.1, 0.1, 0.1, 1);
	mtl.setAmbient(0.3, 0.3, 0.3, 1);
	mtl.setDiffuse(0.5, 0.5, 0.5, 1);
	mtl.setSpecular(1.0, 1.0, 1.0, 1);
	mtl.setShininess(10);
}