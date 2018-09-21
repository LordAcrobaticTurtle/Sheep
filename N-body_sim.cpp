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
#include "lazor.h"

#include "Mechanics.h"
#define PI 3.1415926535

Rocket Test(3);
XInputWrapper ptr;
GamePad::XBoxController P1(&ptr, 0);
Mechanics * mech = new Mechanics;
void borderPatrol();
double scalestickX(GamePad::Coordinate * ptr);
double scalestickY(GamePad::Coordinate * ptr);
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);



}
void reshape() {

}
void idle() {
	XInputGetState(0, P1.GetState());
	P1.SetDeadzone(5000);
	GamePad::Coordinate * LThumb;
	GamePad::Coordinate * RThumb;
	LThumb = &P1.LeftThumbLocation();
	RThumb = &P1.RightThumbLocation();


	Test.accel.setx(scalestickX(LThumb));
	Test.accel.sety(scalestickY(LThumb));
	Test.shuffleRotation(-scalestickX(RThumb));

	borderPatrol(); // -> Let it take in parameters of type shape * and use border patrol on every shape in vector
	const float sleep_time_between_frames_in_seconds = 0.025;
	static double previousTime = mech->time();
	const double currTime = mech->time();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	Test.update(elapsedTime);
	glutPostRedisplay();
}
double scalestickX(GamePad::Coordinate * ptr) {
	return ptr->GetX() / 15000.0;

}
double scalestickY(GamePad::Coordinate * ptr) {
	return ptr->GetY() / 15000.0;
}
void borderPatrol() {
	/*if (P1.PressedA()) {
		Test.pos.setx(0);
		Test.pos.sety(0);
	}*/
	if (Test.pos.getx() > 1) {
		Test.pos.setx(-1);
	}
	else if (Test.pos.getx() < -1) {
		Test.pos.setx(1);
	}
	if (Test.pos.gety() > 1) {
		Test.pos.sety(-1);
	}
	else if (Test.pos.gety() < -1) {
		Test.pos.sety(1);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
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

