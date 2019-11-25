#include <vector>
#include <math.h>
#include <iostream>
#include "SolidSphere.h"
#include "Map.h"
using namespace std;


extern vector<Map> map;
extern SolidSphere* flying;
extern bool cease_fire;
extern bool game_over;
vector<int> stack;


void drop(int current) {
	cout << "분기 1" << endl;
	if (map[current].get_connected() == 1) return;

	cout << "분기 2" << endl;
	if (map[current].get_assign() == true) map[current].set_connected(1);
	else {
		map[current].set_connected(0);
		return;
	}
	cout << "분기 3" << endl;

	if (map[current].get_line() == 0) { // 첫번째 줄인 경우
		if (map[current].get_end() == -1) { // 가장 왼쪽인 경우
			drop(current + 1);
			drop(current + 10);
		}
		else if (map[current].get_end() == 1) { // 가장 오른쪽인 경우
			drop(current - 1);
			drop(current + 9);
		}
		else {
			drop(current - 1);
			drop(current + 1);
			drop(current + 9);
			drop(current + 10);
		}
	}
	else if (map[current].get_line() == 11) { // 마지막 줄인 경우
		if (map[current].get_end() == -1) { // 가장 왼쪽인 경우
			drop(current + 1);
			drop(current - 10);
			drop(current - 9);
		}
		else if (map[current].get_end() == 1) { // 가장 오른쪽인 경우
			drop(current - 1);
			drop(current - 9);
			drop(current - 10);
		}
		else {
			drop(current - 1);
			drop(current + 1);
			drop(current - 9);
			drop(current - 10);
		}
	}
	else { // line 1~10
		if (map[current].get_end() == 0) { // 가장 일반적인 경우
			drop(current - 1);
			drop(current + 1);
			drop(current - 9);
			drop(current - 10);
			drop(current + 9);
			drop(current + 10);
		}
		else if (map[current].get_end() == -1) { // 왼쪽 끝자락일때
			if (map[current].get_line() % 2 == 0) { // 홀수번째줄
				drop(current + 1);
				drop(current - 9);
				drop(current + 10);
			}
			else { // 짝수번째줄
				drop(current + 1);
				drop(current - 9);
				drop(current - 10);
				drop(current + 9);
				drop(current + 10);
			}
		}
		else { // 오른쪽 끝자락일 때
			if (map[current].get_line() % 2 == 0) { // 홀수번째줄
				drop(current - 1);
				drop(current - 10);
				drop(current + 9);
			}
			else { // 짝수번째줄
				drop(current - 1);
				drop(current - 9);
				drop(current - 10);
				drop(current + 9);
				drop(current + 10);
			}
		}
	}
	return;
}

void remove(int current, int color, bool first) {
	// remove : 같은 색깔이면 stack에 넣고 recursion을 돌린다.
	// first가 필요한가? yes
	if (first == true) {
		remove(current, color, false);
		if (stack.size() >= 3) {
			for (int i = 0; i < stack.size(); i++) {
				delete map[stack[i]].holding_sphere;
				map[stack[i]].holding_sphere = nullptr;
				map[stack[i]].set_assign(false);
				map[stack[i]].set_color(-1);
			}
			
		}
		while (stack.size() > 0) stack.pop_back();
		for (int i = 0; i < map.size(); i++) map[i].set_search(false);
		return;
	}
	else {
		if (map[current].get_assign() == false || map[current].get_search() == true) return; // assign이 안되어있거나 이미 서치했으면 아무것도 안하고
		else { // 아닌 경우 주변부로 서치를 확장한다
			map[current].set_search(true);
			if (color == map[current].get_color()) {
				stack.push_back(current);
				if (map[current].get_line() == 0) { // 첫번째 줄인 경우
					if (map[current].get_end() == -1) { // 가장 왼쪽인 경우
						remove(current + 1, color, false);
						remove(current + 10, color, false);
					}
					else if (map[current].get_end() == 1) { // 가장 오른쪽인 경우
						remove(current - 1, color, false);
						remove(current + 9, color, false);
					}
					else {
						remove(current - 1, color, false);
						remove(current + 1, color, false);
						remove(current + 9, color, false);
						remove(current + 10, color, false);
					}
				}
				else if (map[current].get_line() == 11) { // 마지막 줄인 경우
					if (map[current].get_end() == -1) { // 가장 왼쪽인 경우
						remove(current + 1, color, false);
						remove(current - 10, color, false);
						remove(current - 9, color, false);
					}
					else if (map[current].get_end() == 1) { // 가장 오른쪽인 경우
						remove(current - 1, color, false);
						remove(current - 9, color, false);
						remove(current - 10, color, false);
					}
					else {
						remove(current - 1, color, false);
						remove(current + 1, color, false);
						remove(current - 9, color, false);
						remove(current - 10, color, false);
					}
				}
				else { // line 1~10
					if (map[current].get_end() == 0) { // 가장 일반적인 경우
						remove(current - 1, color, false);
						remove(current + 1, color, false);
						remove(current - 9, color, false);
						remove(current - 10, color, false);
						remove(current + 9, color, false);
						remove(current + 10, color, false);
					}
					else if (map[current].get_end() == -1) { // 왼쪽 끝자락일때
						if (map[current].get_line() % 2 == 0) { // 홀수번째줄
							remove(current + 1, color, false);
							remove(current - 9, color, false);
							remove(current + 10, color, false);
						}
						else { // 짝수번째줄
							remove(current + 1, color, false);
							remove(current - 9, color, false);
							remove(current - 10, color, false);
							remove(current + 9, color, false);
							remove(current + 10, color, false);
						}
					}
					else { // 오른쪽 끝자락일 때
						if (map[current].get_line() % 2 == 0) { // 홀수번째줄
							remove(current - 1, color, false);
							remove(current - 10, color, false);
							remove(current + 9, color, false);
						}
						else { // 짝수번째줄
							remove(current - 1, color, false);
							remove(current - 9, color, false);
							remove(current - 10, color, false);
							remove(current + 9, color, false);
							remove(current + 10, color, false);
						}
					}
				}

			}
			else return;
		}
	}
}
float length_(Vector3 input1, Vector3 input2) {
	return sqrt(dotProduct(input1 - input2, input1 - input2));
}

SolidSphere::SolidSphere(float r, int sl, int st, int color) : SolidShape3D() {
	properties.setXYZ(r, sl, st);
	setMTL(color);
	set_color(color);
}

SolidSphere::SolidSphere(const SolidSphere& sph) : SolidShape3D(sph) {
	properties = sph.properties;
	color = sph.get_color();
}

Vector3 SolidSphere::getProperties() const{
	return properties;
}

bool SolidSphere::collisionDetection(const SolidSphere* sph) {
	/* Implementation: collision detection */
	Vector3 c1 = getCenter();
	Vector3 c2 = (*sph).getCenter();
	return (sqrt(dotProduct(c1 - c2, c1 - c2)) < properties[0] + (*sph).getProperties()[0]);
}

void SolidSphere::collisionHandling(SolidSphere* sph) {
	if (collisionDetection(sph)) {
		this->setVelocity(0, 0, 0);
		int position = 0;
		Vector3 this_c = getCenter(); // 날아가던 공이 멈춘 위치를 잡고
		Vector3 that_c = (*sph).getCenter();
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
		int position_JM = position + (*sph).get_map(); // 찐막 포지션
		if (position_JM >= 114) game_over = true;
		else {
			map[position_JM].set_assign(true);
			map[position_JM].holding_sphere = this;
			this->set_map(position_JM);
			this->setCenter(map[position_JM].getXYZ());
			this->set_map(position_JM);
			map[position_JM].set_color(this->get_color());
			flying = nullptr;
			cease_fire = false;
			remove(position_JM, this->get_color(), true);
			for (int i = 0; i < 10; i++) drop(i);
			for (int i = 0; i < map.size(); i++) if (map[i].get_connected() == 0) map[i].holding_sphere->setVelocity(0, -100, 0);
			return;
		}
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
	map[temp].holding_sphere = this;
	this->set_map(temp);
	this->setCenter(map[temp].getXYZ());
	this->set_map(temp);
	map[temp].set_color(this->get_color());
	flying = nullptr;
	cease_fire = false;
	remove(temp, this->get_color(), true);
	for (int i = 0; i < 10; i++) drop(i);
	cout << false;
	for (int i = 0; i < map.size(); i++) if (map[i].get_connected() == 0) map[i].holding_sphere->setVelocity(0, -100, 0);
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
	else if (color == 1) { // GOLD
		mtl.setEmission(0.1, 0.1, 0.1, 1);
		mtl.setAmbient(0.24725, 0.1995, 0.0745, 1.0);
		mtl.setDiffuse(0.75164, 0.60648, 0.22648, 1);
		mtl.setSpecular(0.628281, 0.555802, 0.366065, 1);
		mtl.setShininess(51.2);
	}
	else if (color == 2) { // RUBY
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