#pragma once

#include "SolidShape3D.h"

class SolidSphere : public SolidShape3D
{
public:
	SolidSphere(float r, int sl, int st, int color);
	SolidSphere(const SolidSphere& sph);
	Vector3 getProperties() const;
	bool collisionDetection(const SolidSphere* sph);
	void collisionHandling(SolidSphere* sph);
	void collisionHandling();
	void draw() const;
	void setMTL(int color);
	int get_color() const { return color; }
	void set_color(int color) { this->color = color; }
private:
	Vector3 properties;
	int color;
};

