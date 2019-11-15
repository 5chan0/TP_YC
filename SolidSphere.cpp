#include "SolidSphere.h"
#include <math.h>

SolidSphere::SolidSphere(float r, int sl, int st) : SolidShape3D() {
	properties.setXYZ(r, sl, st);
}

SolidSphere::SolidSphere(const SolidSphere& sph) : SolidShape3D(sph) {
	properties = sph.properties;
}

Vector3 SolidSphere::getProperties() const{
	return properties;
}

bool SolidSphere::collisionDetection(const SolidSphere& sph) {
	/* Implementation: collision detection */
	if (sqrt(pow(getCenter()[0] - sph.getCenter()[0], 2)
		+ pow(getCenter()[1] - sph.getCenter()[1], 2) 
		+ pow(getCenter()[2] - sph.getCenter()[2], 2)) 
		<= properties[0] + sph.getProperties()[0])
		return true;
	else return false;
}

void SolidSphere::collisionHandling(SolidSphere& sph) {
	if (collisionDetection(sph)) {
		/* Implementation: collision handling */
		Vector3 v1 = getVelocity();
		Vector3 v2 = sph.getVelocity();

		Vector3 c1 = getCenter();
		Vector3 c2 = sph.getCenter();

		Vector3 result1 = v1 - dotProduct(v1 - v2, c1 - c2) / (pow(c1.getXYZ()[0] - c2.getXYZ()[0], 2) + pow(c1.getXYZ()[1] - c2.getXYZ()[1], 2) + pow(c1.getXYZ()[2] - c2.getXYZ()[2], 2)) * (c1 - c2);
		Vector3 result2 = v2 - dotProduct(v2 - v1, c2 - c1) / (pow(c1.getXYZ()[0] - c2.getXYZ()[0], 2) + pow(c1.getXYZ()[1] - c2.getXYZ()[1], 2) + pow(c1.getXYZ()[2] - c2.getXYZ()[2], 2)) * (c2 - c1);
		this->setVelocity(result1);
		sph.setVelocity(result2);
	}
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