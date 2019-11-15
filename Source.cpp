#include <vector>
#include <time.h>
#include "SolidSphere.h"
#include "Light.h"

using namespace std;

#define WIDTH 500
#define HEIGHT 750

#define boundaryX WIDTH/2
#define boundaryY HEIGHT/2

vector<SolidSphere> spheres;
Light* light;


clock_t start_clock = clock();
clock_t end_clock;
const float fps = 1000 / 60.0;

/****************************SPECS(PX)
sphere radius : 25
waiting sphere center : 50, 717
ready-to-fire sphere center : 250, 686
TOP-END : 117-127
BOTTOM-END : 643-653
**********************************/

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
}
void init() {
	light = new Light(boundaryX, boundaryY, boundaryX / 2, GL_LIGHT0);
	light->setAmbient(0.5, 0.5, 0.5, 1.0);
	light->setDiffuse(0.7, 0.7, 0.7, 1.0);
	light->setSpecular(1.0, 1.0, 1.0, 1.0);

	


}

void idle() {

	/***************************************************************************************************************** collision chk & boundary chk algorithm
	end_clock = clock();
	if (end_clock - start_clock > fps) {
	// collision handling
	for (int i = 0; i < spheres.size(); i++)
		for (int j = i + 1; j < spheres.size(); j++)
			spheres[i].collisionHandling(spheres[j]);


		// update object


		for (int i = 0; i < 3; i++) {
			if ((spheres[i].getCenter())[0] + (spheres[i].getProperties())[0] >= WIDTH / 2
				|| (spheres[i].getCenter())[0] - (spheres[i].getProperties())[0] <= -WIDTH / 2) {
				Vector3 temp = spheres[i].getVelocity();
				temp[0] *= -1;
				spheres[i].setVelocity(temp);
			}
			else if((spheres[i].getCenter())[1] + (spheres[i].getProperties())[0] >= HEIGHT / 2
				|| (spheres[i].getCenter())[1] - (spheres[i].getProperties())[0] <= -HEIGHT / 2) {
				Vector3 temp = spheres[i].getVelocity();
				temp[1] *= -1;
				spheres[i].setVelocity(temp);
			}
			spheres[i].move();
		}

		start_clock = end_clock;
	}

	*********************************************************************************************************************/
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	light->draw();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);


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

	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Puzzle Bubble");
	init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}
