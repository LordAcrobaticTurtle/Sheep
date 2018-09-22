// N-body_sim.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <iostream>
#include <Xinput.h>
#include <cmath>
#include <chrono>

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
// EVIL VARIABLES
//===================================
Rocket * Player1 = new Rocket(1);
blob * Test2 = new blob(0.5, 0.05);
blob * Test3 = new blob(0.5, 0.05);
blob * Test4 = new blob(0.5, 0.05);
blob * Test5 = new blob(0.5, 0.05);
Mechanics * mech = new Mechanics;
//===================================


void borderPatrol(Rocket * s);
void borderPatrol(blob * Test);
double getTime();
void reshape(GLsizei width, GLsizei height);

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Test3->pos.sety(0.1);
	Test3->pos.setx(0.6);
	//Test3->vel.sety(1.5);
	Test4->pos.setx(-0.9);
	Test5->pos.sety(-0.9);
}

void idle() {
	
	mech->PlayerControls(Player1);
	borderPatrol(Player1); // BorderPatrol overloaded for Rockets and blobs
	borderPatrol(Test2);
	borderPatrol(Test3);
	borderPatrol(Test4);
	borderPatrol(Test5);
	Test4->setcolour(1, 0, 0);
	Test5->setcolour(0.5, 0, 0.5);
	Test3->setcolour(0, 0, 1);
//	mech->AsteroidGrav(Test2, Test3);
	mech->AsteroidGrav(Test2, Test4);
	mech->AsteroidGrav(Test2, Test5);
//	mech->AsteroidGrav(Test3, Test2);
	mech->AsteroidGrav(Test3, Test4);
	mech->AsteroidGrav(Test3, Test5);
	mech->AsteroidGrav(Test4, Test2);
	mech->AsteroidGrav(Test4, Test3);
	//mech->AsteroidGrav(Test4, Test5);
	mech->AsteroidGrav(Test5, Test2);
	mech->AsteroidGrav(Test5, Test3);
	//mech->AsteroidGrav(Test5, Test4);
	
	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;



	Player1->update(elapsedTime);
	Test2->update(elapsedTime);
	Test3->update(elapsedTime);
	Test4->update(elapsedTime);
	Test5->update(elapsedTime);
	
	mech->Players[0] = Player1;
	mech->Asteroids[0] = Test2;
	mech->Asteroids[1] = Test3;
	mech->Asteroids[2] = Test4;
	mech->Asteroids[3] = Test5;


	glutPostRedisplay();
}
void borderPatrol(blob * Test) {
	if (Test->pos.getx() > 1.92) {
		Test->pos.setx(-1.92);
	}
	else if (Test->pos.getx() < -1.92) {
		Test->pos.setx(1.92);
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
	if (Test->pos.getx() > 1.92) {
		Test->pos.setx(-1.92);
	}
	else if (Test->pos.getx() < -1.92) {
		Test->pos.setx(1.92);
	}
	if (Test->pos.gety() > 1) {
		Test->pos.sety(-1);
	}
	else if (Test->pos.gety() < -1) {
		Test->pos.sety(1);
	}
}
double getTime() {



#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if (QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//std::cout << Test->vel.getx() << "	" << Test.vel.gety() << std::endl;
	/*
	mech->Players[0]->draw();
	mech->Asteroids[0]->draw();
	mech->Asteroids[1]->draw();
	mech->Asteroids[2]->draw();
	mech->Asteroids[3]->draw();
	*/
	Player1->draw();
	Test2->draw();
	Test3->draw();
	Test4->draw();
	Test5->draw();
	glFlush();
	glutSwapBuffers();

}
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(1920, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Opengl stuff");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutMainLoop();

    return 0;
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
												// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix
	if (width >= height) {
		// aspect >= 1, set the height from -1 to 1, with larger width
		gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
	}
	else {
		// aspect < 1, set the width to -1 to 1, with larger height
		gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
	}
}
