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

Rocket * Player1 = new Rocket(3);
blob * Test2 = new blob(0.5, 0.05);
blob * Test3 = new blob(0.5, 0.05);
blob * Test4 = new blob(0.5, 0.05);
lazor * pew = new lazor();
//blob * Test5 = new blob(0.5, 0.05);
Mechanics * mech = new Mechanics;
//===================================


void borderPatrol(Rocket * s);
void borderPatrol(blob * Test);
void reshape(GLsizei width, GLsizei height);

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Test5->pos->setx(-0.7);
	Test3->pos->sety(0.9);
	Test3->vel->setx(0.1);
	Test2->pos->setx(-0.4);
	Test4->vel->setx(-0.6);
}

void idle() {
	
	mech->PlayerControls(Player1);
	borderPatrol(Player1); // BorderPatrol overloaded for Rockets and blobs
	borderPatrol(Test3);
	borderPatrol(Test2);
	borderPatrol(Test4);
	Test2->setcolour(1, 0, 0);
	Test3->setcolour(0, 0, 1);
	Test4->setcolour(1, 1, 1);
	

	mech->AsteroidGrav(Test2, Test3);
	mech->AsteroidGrav(Test4, Test2);
	mech->AsteroidGrav(Test4, Test3);
	if (mech->Collision(Test2, Test3)) {
		mech->nom(Test2, Test3);
	}
	if (mech->Collision(Test3, Test4)) {
		mech->nom(Test3, Test4);
	}
	if (mech->Collision(Test2, Test4)) {
		mech->nom(Test2, Test4);
	}
	static double previousTime = mech->time();
	const double currTime = mech->time();
	const double elapsedTime = currTime - previousTime;
	if (Player1->pew->shoot != 1) {
		Player1->pew->vel->setx(cos(Player1->getrotation()*PI/180));
		Player1->pew->vel->sety(sin(Player1->getrotation()*PI/180));
	}
	
	if (mech->Collision(Test2, Player1->pew)) {
		mech->Destroy(Test2);
	}
	if (mech->Collision(Test3, Player1->pew)) {
		mech->Destroy(Test3);
	}
	if (mech->Collision(Test4, Player1->pew)) {
		mech->Destroy(Test4);
	}
	previousTime = currTime;
	Player1->update(elapsedTime);
	Test2->update(elapsedTime);
	Test3->update(elapsedTime);
	Test4->update(elapsedTime);
	glutPostRedisplay();
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Player1->draw();
	if (Player1->pew->shoot == 1) {
		Player1->pew->draw();
	}
	Test2->draw();
	Test3->draw();
	Test4->draw();
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
void borderPatrol(blob * Test) {
	if (Test->pos->getx() > 1.92) {
		Test->pos->setx(-1.92);
	}
	else if (Test->pos->getx() < -1.92) {
		Test->pos->setx(1.92);
	}
	if (Test->pos->gety() > 1) {
		Test->pos->sety(-1);
	}
	else if (Test->pos->gety() < -1) {
		Test->pos->sety(1);
	}
}
void borderPatrol(Rocket * Test) {
	if (Test->Player->PressedA()) {
		Test->pos->setx(0);
		Test->pos->sety(0);
		Test->vel->setx(0);
		Test->vel->sety(0);
	} 
	if (Test->Player->PressedB()) {
		Test->vel->setx(0);
		Test->vel->sety(0);
	}
	if (Test->pos->getx() > 1.92) {
		Test->pos->setx(-1.92);
	}
	else if (Test->pos->getx() < -1.92) {
		Test->pos->setx(1.92);
	}
	if (Test->pos->gety() > 1) {
		Test->pos->sety(-1);
	}
	else if (Test->pos->gety() < -1) {
		Test->pos->sety(1);
	}
	if (Test->pew->pos->getx() == 1.92 || Test->pew->pos->getx() == -1.92) {
		Test->pew->shoot = 0;
		Test->pew->pos->setx(Test->pos->getx());
		Test->pew->pos->sety(Test->pos->gety());
		Test->pew->vel->setx(Test->pos->getx());
		Test->pew->vel->sety(Test->pos->gety());
	}
	if (Test->pew->pos->gety() == 1 || Test->pew->pos->gety() == -1) {
		Test->pew->shoot = 0;
		Test->pew->pos->sety(Test->pos->gety());
		Test->pew->pos->setx(Test->pos->getx());
		Test->pew->vel->setx(Test->pos->getx());
		Test->pew->vel->sety(Test->pos->gety());
	}
}
