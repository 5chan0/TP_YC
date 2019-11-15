#pragma once

#include "SolidShape3D.h"

class SolidSphere : public SolidShape3D
{
public:
	SolidSphere(float r, int sl, int st);
	SolidSphere(const SolidSphere& sph);
	Vector3 getProperties() const;
	bool collisionDetection(const SolidSphere& sph);
	void collisionHandling(SolidSphere& sph);
	void draw() const;

private:
	Vector3 properties;
};

