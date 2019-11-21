#include <vector>
#include <math.h>
#include <iostream>
#include "SolidSphere.h"
#include "Map.h"
using namespace std;


extern vector<Map> map;
extern vector<SolidSphere> spheres;
extern SolidSphere* flying;
extern bool cease_fire;

float length_(Vector3 input1, Vector3 input2) {
	return sqrt(dotProduct(input1 - input2, input1 - input2));
}

SolidSphere::SolidSphere(float r, int sl, int st, int color) : SolidShape3D() {
	properties.setXYZ(r, sl, st);
	setMTL(color);
}

SolidSphere::SolidSphere(const SolidSphere& sph) : SolidShape3D(sph) {
	properties = sph.properties;
}

Vector3 SolidSphere::getProperties() const{
	return properties;
}

bool SolidSphere::collisionDetection(const SolidSphere& sph) {
	/* Implementation: collision detection */
	Vector3 c1 = getCenter();
	Vector3 c2 = sph.getCenter();
	return (sqrt(dotProduct(c1 - c2, c1 - c2)) < properties[0] + sph.getProperties()[0]);
}

void SolidSphere::collisionHandling(SolidSphere& sph) {
	if (collisionDetection(sph)) {
		this->setVelocity(0, 0, 0);
		int position = 0;
		Vector3 this_c = getCenter(); // 날아가던 공이 멈춘 위치를 잡고
		Vector3 that_c = sph.getCenter();
		float x_grad = this_c[0] - that_c[0];
		float y_grad = this_c[1] - that_c[1];

		float grad = y_grad / x_grad;
		float root_3_2 = sqrt(3) / 2;
		if (-root_3_2 <= grad && grad <= root_3_2) {
			if (x_grad >= 0) position = +1;
			else position = -1;
		}
		else if (grad >= root_3_2) {
			if (y_grad >= 0) position = -9;
			else position = +9;
		}
		else if (grad <= -root_3_2) {
			if (y_grad >= 0) position = -10;
			else position = +10;
		}
		else {
			cout << "ERROR" << endl;
			exit(123);
		}

		int position_JM = position + sph.get_map(); // 찐막 포지션
		spheres.push_back(*this);
		spheres.back().setCenter(map[position_JM].getXYZ());
		spheres.back().set_map(position_JM);
		map[position_JM].set_assign(true);
		flying = nullptr;
		cease_fire = false;
	}
}
void SolidSphere::collisionHandling() { // TOP_END에 이른 경우 이 함수를 call한다.
	this->setVelocity(0, 0, 0);
	Vector3 c = this->getCenter();

	int temp = -1;
	int length_tmp = 100000;
	for (int i = 0; i < 10; i++) {
		if (length_(c, map[i].getXYZ()) <= length_tmp) {
			temp = i;
			length_tmp = length_(c, map[i].getXYZ());
		}
	}

	//cout << this->get_assigned_map() << endl;
	map[temp].set_assign(true);
	spheres.push_back(*flying);
	spheres.back().setCenter(map[temp].getXYZ());
	spheres.back().set_map(temp);
	flying = nullptr;
	cease_fire = false;
	return;
}

void SolidSphere::draw() const {
	glPushMatrix();

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());

	glTranslatef(center[0], center[1], center[2]);
	glutSolidSphere(properties[0], properties[1], properties[2]);
	glPopMatrix();
}

void SolidSphere::setMTL(int color) {
	if (color == 0) { // PEARL
		mtl.setEmission(0.1, 0.1, 0.1, 1);
		mtl.setAmbient(0.25, 0.20705, 0.20705, 0.922);
		mtl.setDiffuse(1.0, 0.829, 0.829, 0.922);
		mtl.setSpecular(0.296648, 0.296648, 0.296648, 0.922);
		mtl.setShininess(11.264);
	}
	if (color == 1) { // GOLD
		mtl.setEmission(0.1, 0.1, 0.1, 1);
		mtl.setAmbient(0.24725, 0.1995, 0.0745, 1.0);
		mtl.setDiffuse(0.75164, 0.60648, 0.22648, 1);
		mtl.setSpecular(0.628281, 0.555802, 0.366065, 1);
		mtl.setShininess(51.2);
	}
	if (color == 2) { // RUBY
		mtl.setEmission(0.1, 0.1, 0.1, 1);
		mtl.setAmbient(0.1745, 0.01175, 0.01175, 0.55);
		mtl.setDiffuse(0.61424, 0.04136, 0.04136, 0.55);
		mtl.setSpecular(0.727811, 0.626959, 0.626959, 0.55);
		mtl.setShininess(76.8);
	}
	else { // EMERALD
		mtl.setEmission(0.1, 0.1, 0.1, 1);
		mtl.setAmbient(0.0215, 0.1745, 0.0215, 0.55);
		mtl.setDiffuse(0.07568, 0.61424, 0.07568, 0.55);
		mtl.setSpecular(0.633, 0.727811, 0.633, 0.55);
		mtl.setShininess(76.8);
	}
}