// N-body_sim.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <iostream>
#include <Xinput.h>
#include <cmath>

#include "GL.H"
#include "GLU.H"
#include "glut.h"

#include "Body.h"
#include "2Dengine.h"
#include "XInputWrapper.h"
#include "XboxHeader.h"
#include "Rocket.h"

Rocket Test(3);
XInputWrapper ptr;
GamePad::XBoxController P1(&ptr, 0);



void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void reshape() {

}
void idle() {
	glutPostRedisplay();
}
double scalestickX(GamePad::Coordinate * ptr) {
	return ptr->GetX() / 5000000.0;

}
double scalestickY(GamePad::Coordinate * ptr) {
	return ptr->GetY() / 5000000.0;
}
void borderPatrol() {
	if (P1.PressedA()) {
		Test.pos.setx(0);
		Test.pos.sety(0);
	}
	if (Test.pos.getx() > 1 || Test.pos.getx() < -1) {
		Test.pos.setx(-1 * Test.pos.getx());
	}
	if (Test.pos.gety() > 1 || Test.pos.gety() < -1) {
		Test.pos.sety(-1 * Test.pos.gety());
	}
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*Test.setradius(Test.getradius() + 0.0001);
	if (Test.getradius() > 1) {
		Test.setradius(0);
	}*/
	XInputGetState(0, P1.GetState());
	P1.SetDeadzone(5000);
	GamePad::Coordinate * LThumb;
	LThumb = &P1.LeftThumbLocation();
	
	Test.pos.shuffleX(scalestickX(LThumb));
	Test.pos.shuffleY(scalestickY(LThumb));
	borderPatrol();
	Test.draw();

	glFlush();
	glutSwapBuffers();

}
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Opengl stuff");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();

    return 0;
}

