#include <vector>
#include <time.h>
#include <iostream>
#include <math.h>
#include "SolidSphere.h"
#include "Light.h"
#include "Map.h"

using namespace std;

#define WIDTH 500
#define HEIGHT 750
#define boundaryX WIDTH/2
#define boundaryY HEIGHT/2
#define TOP_END 243
#define BOTTOM_END -273
#define pi 3.14159

vector<SolidSphere> spheres;
Light* light;
vector<Map> map;
SolidSphere* next_sphere = nullptr;
SolidSphere* ready_sphere = nullptr;
SolidSphere* flying = nullptr;
bool cease_fire = false;
float angle = 0.0;


clock_t start_clock = clock();
clock_t end_clock;
const float fps = 1000 / 240.0; // framerate 조정

/****************************SPECS(PX)
sphere radius : 25
waiting sphere center : 50, 717
ready-to-fire sphere center : 250, 686
TOP-END : 117-127
BOTTOM-END : 643-653
**********************************/


void assign_map() {
	float root3 = sqrt(3);
	float odd_x[10]; // = { -225, -175, -125, -75, -25, 25, 75, 125, 175, 225 };
	for (int i = 0; i < 10; i++) odd_x[i] = -225 + (50 * i);
	float even_x[9]; // = { -200, -150, -100, -50, 0, 50, 100, 150, 200 };
	for (int i = 0; i < 9; i++) even_x[i] = -200 + (50 * i);
	float y[12]; // = { 223, 179.69, 136.39, 93.09, 49.79, 6.49, -36.80, -80.10, -123.41, -166.71, -210.01, -253.31 };
	for (int i = 0; i < 12; i++) y[i] = 223 - (25 * root3 * i);
	for (int j = 0; j < 12; j++) {
		if (j % 2 == 0)
			for (int i = 0; i < 10; i++) {
				Map temp(odd_x[i],y[j]);
				temp.set_line(j);
				temp.my_index = map.size();
				if (i == 0) temp.set_end(-1);
				else if (i == 9) temp.set_end(1);
				map.push_back(temp);
			}
		else 
			for (int i = 0; i < 9; i++) {
				Map temp(even_x[i], y[j]);
				temp.set_line(j);
				temp.my_index = map.size();
				if (i == 0) temp.set_end(-1);
				else if (i == 8) temp.set_end(1);
				map.push_back(temp);
			}
	}
}
void assign_sphere() {
	int color = rand() % 4;
	next_sphere = new SolidSphere(25, 100, 100, color);
	next_sphere->setCenter(-200, -342, 0);
}
void draw_characters(void* font, const char* c, float x, float y) {
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(c); i++)
		glutBitmapCharacter(font, c[i]);
}
void draw_characters_yellow(void* font, const char* c, float x, float y) {
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(c); i++)
		glutBitmapCharacter(font, c[i]);
}void shift_to_fire() {	next_sphere->setCenter(0, -342, 0);	ready_sphere = next_sphere;	assign_sphere();}void fire() {	cease_fire = true;	flying = ready_sphere;	flying->setVelocity(10.0 * cos((90 + angle) * pi / 180.0), 10.0 * sin((90 + angle) * pi / 180.0), 0);	shift_to_fire();	cout << endl;}void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 32 && cease_fire == false) { // SPACEBAR
		fire();
	}
}void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		// IMPLEMENT LEFT_KEY_FUNC()
		if (angle < 80) angle += 5;
		break;
	case GLUT_KEY_RIGHT:
		// IMPLEMENT RIGHT_KEY_FUNC()
		if (angle > -80) angle -= 5;
		break;
	default:
		break;
	}
}
void init() {
	light = new Light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
	light->setAmbient(0.5, 0.5, 0.5, 1.0);
	light->setDiffuse(0.7, 0.7, 0.7, 1.0);
	light->setSpecular(1.0, 1.0, 1.0, 1.0);

	assign_map(); // map을 초기화하고
	assign_sphere(); // 첫번째 sphere를 넣어준다.
	shift_to_fire();
}

void idle() { // idlefunc는 animation을 위해 사용한다.
	end_clock = clock();
	if (end_clock - start_clock > fps) { //FPS 제한부분 주석처리
		// collision handling
		if (flying != nullptr) {
			for (int i = 0; i < spheres.size(); i++) if (flying != nullptr) flying->collisionHandling(spheres[i]); // 다른 sphere 들에 부딪히는지 확인
			if (flying != nullptr) {
				if ((flying->getCenter())[0] + (flying->getProperties())[0] >= boundaryX || (flying->getCenter())[0] - (flying->getProperties())[0] <= -boundaryX) {
					Vector3 temp = flying->getVelocity();
					temp[0] *= -1;
					flying->setVelocity(temp);
				}
				else if ((flying->getCenter())[1] + (flying->getProperties())[0] >= TOP_END) {
					flying->collisionHandling();
				}
				if (flying != nullptr) flying->move();
			}
		}
		start_clock = end_clock;
	}
	glutPostRedisplay();
}

void renderScene() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	draw_characters(GLUT_BITMAP_HELVETICA_18, "SCORE", -224, 337);	draw_characters(GLUT_BITMAP_HELVETICA_18, "TIME", 0, 337);	draw_characters(GLUT_BITMAP_HELVETICA_18, "NEXT", -224, -305);	draw_characters_yellow(GLUT_BITMAP_HELVETICA_12, "points", -135, 303);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glColor3f(1,1,1);
	glVertex3f(-250, 253, 0);
	glVertex3f(250, 253, 0);
	glVertex3f(-250, -273, 0);
	glVertex3f(250, -273, 0);
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	light->draw();

	for (auto sph : spheres) sph.draw();
	if(flying != nullptr) flying->draw();
	if(ready_sphere != nullptr) ready_sphere->draw();
	if(next_sphere != nullptr) next_sphere->draw();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	srand((unsigned int)time(0));
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Puzzle Bubble");
	init();

	// register callbacks
	glutDisplayFunc(renderScene);	glutKeyboardFunc(processNormalKeys);	glutSpecialFunc(processSpecialKeys);
	glutIdleFunc(idle);	

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
