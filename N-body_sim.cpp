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
//===================================
Rocket * Player1 = new Rocket(1);
blob * Test2 = new blob(5, 0.05);
blob * Test3 = new blob(4, 0.05);
Mechanics * mech = new Mechanics;
//===================================


void borderPatrol(Rocket * s);
void borderPatrol(blob * Test);


void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Test3->pos.setx(0.5);
	Test3->vel.sety(-10);
}

void idle() {
	
	mech->PlayerControls(Player1);
	borderPatrol(Player1); // -> Let it take in parameters of type shape * and use border patrol on every shape in vector
	borderPatrol(Test2);
	borderPatrol(Test3);
	Test3->setcolour(1, 0, 1);

//=====================================
// GRAVITY ATTEMPT
	position force = position::subtract(Test2->pos, Test3->pos);
	double distance = force.mag();
	force.normalise();
	force.scale(Test3->getmass() * Test2->getmass() / (distance));
	Test3->accel.add(force);

//====================================
	//const float sleep_time_between_frames_in_seconds = 0.025;
	//static double previousTime = mech->time();
	const double currTime = mech->time();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;
	Player1->update(elapsedTime);
	Test2->update(elapsedTime);
	Test3->update(elapsedTime);
	mech->Players[0] = Player1;
	mech->Asteroids[0] = Test2;
	mech->Asteroids[1] = Test3;
	glutPostRedisplay();
	
	
}
void borderPatrol(blob * Test) {
	if (Test->pos.getx() > 1) {
		Test->pos.setx(-1);
	}
	else if (Test->pos.getx() < -1) {
		Test->pos.setx(1);
	}
	if (Test->pos.gety() > 1) {
		Test->pos.sety(-1);
	}
	else if (Test->pos.gety() < -1) {
		Test->pos.sety(1);
	}
}
// WRITE ANOTHER SCALE FUNCTION FOR ROTATION
void borderPatrol(Rocket * Test) {
	if (Test->Player->PressedA()) {
		Test->pos.setx(0);
		Test->pos.sety(0);
		Test->vel.setx(0);
		Test->vel.sety(0);
	} 
	if (Test->Player->PressedB()) {
		Test->vel.setx(0);
		Test->vel.sety(0);
	}
	if (Test->pos.getx() > 1) {
		Test->pos.setx(-1);
	}
	else if (Test->pos.getx() < -1) {
		Test->pos.setx(1);
	}
	if (Test->pos.gety() > 1) {
		Test->pos.sety(-1);
	}
	else if (Test->pos.gety() < -1) {
		Test->pos.sety(1);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//std::cout << Test->vel.getx() << "	" << Test.vel.gety() << std::endl;
	int i = 0;
	while (i < 1) {
		mech->Players[i]->draw();
		i++;
	}
	int j = 0;
	while (j < 2) {
		mech->Asteroids[j]->draw();
		j++;
	}
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

