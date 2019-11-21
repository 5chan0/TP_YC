#pragma once

#include "SolidShape3D.h"
#include "Map.h"

class SolidSphere : public SolidShape3D
{
public:
	SolidSphere(float r, int sl, int st, int color);
	SolidSphere(const SolidSphere& sph);
	Vector3 getProperties() const;
	bool collisionDetection(const SolidSphere& sph);
	void collisionHandling(SolidSphere& sph);
	void collisionHandling();
	void draw() const;
	void setMTL(int color);

private:
	Vector3 properties;
};

