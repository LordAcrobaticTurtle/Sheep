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
Rocket * Player2 = new Rocket(2);
Rocket * Player1 = new Rocket(1);
blob * Test2 = new blob(0.5, 0.05);
blob * Test3 = new blob(0.5, 0.05);
blob * Test4 = new blob(0.5, 0.05);
blob * Test5 = new blob(0.5, 0.05);
Mechanics * mech = new Mechanics;

//===================================


void borderPatrol(Rocket * s);
void borderPatrol(blob * Test);
void reshape(GLsizei width, GLsizei height);

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Test5->pos->setx(0.7);
	Test3->pos->sety(0.9);
	Test3->vel->setx(0.1);
	Test2->pos->setx(-0.4);
	Test4->vel->setx(-0.6);
	Test4->pos->setx(-0.7);
	mech->Asteroids[0] = Test2;
	mech->Asteroids[1] = Test3;
	mech->Asteroids[2] = Test4;
	mech->Asteroids[3] = Test5;
	Test2->setcolour(1, 0, 0);
	Test3->setcolour(0, 0, 1);
	Test4->setcolour(1, 1, 1);
	Test5->setcolour(1, 1, 0);
}

void idle() {
	
	mech->PlayerControls(Player1);
	borderPatrol(Player1);
	int i = 0;
	while (i < 4) {
		borderPatrol(mech->Asteroids[i]);
		i++;
	}

	mech->AsteroidGrav(Test2, Test3);
	mech->AsteroidGrav(Test2, Test4);
	mech->AsteroidGrav(Test2, Test5);
	mech->AsteroidGrav(Test3, Test4);
	mech->AsteroidGrav(Test3, Test5);
	mech->AsteroidGrav(Test4, Test5);
	


	if (mech->Collision(Test2, Test3)) {
		mech->nom(Test2, Test3);
	}
	if (mech->Collision(Test3, Test4)) {
		mech->nom(Test3, Test4);
	}
	if (mech->Collision(Test2, Test4)) {
		mech->nom(Test2, Test4);
	}
	if (mech->Collision(Test5, Test4)) {
		mech->nom(Test5, Test4);
	}
	if (mech->Collision(Test3, Test5)) {
		mech->nom(Test3, Test5);
	}
	if (mech->Collision(Test2, Test5)) {
		mech->nom(Test2, Test5);
	}
	static double previousTime = mech->time();
	const double currTime = mech->time();
	const double elapsedTime = currTime - previousTime;
	if (Player1->pew->shoot != 1) {
		Player1->pew->vel->setx(cos(Player1->getrotation()*PI/180));
		Player1->pew->vel->sety(sin(Player1->getrotation()*PI/180));
		Player1->pew->pos->setx(Player1->pos->getx());
		Player1->pew->pos->sety(Player1->pos->gety());
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
	if (mech->Collision(Test5, Player1->pew)) {
		mech->Destroy(Test5);
	}
	if (mech->Collision(Player1, Test5)) {
		Player1->setHeatlh(Player1->getHealth() - 1);
		mech->bounce(Player1);
	}
	if (mech->Collision(Player1, Test4)) {
		Player1->setHeatlh(Player1->getHealth() - 1);
		mech->bounce(Player1);
	}
	if (mech->Collision(Player1, Test3)) {
		Player1->setHeatlh(Player1->getHealth() - 1);
		mech->bounce(Player1);
	}
	if (mech->Collision(Player1, Test2)) {
		Player1->setHeatlh(Player1->getHealth() - 1);
		mech->bounce(Player1);
	}
	
	// ====================================
	previousTime = currTime;
	Player1->update(elapsedTime);
	Test2->update(elapsedTime);
	Test3->update(elapsedTime);
	Test4->update(elapsedTime);
	Test5->update(elapsedTime);
	glutPostRedisplay();
}
void drawBackground() {
	glColor3d(1, 1, 0.5);
	glPushMatrix();
	glTranslated(-0.9, 0.5,0);
	gluDisk(gluNewQuadric(), 0, 0.01, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(1.9, -0.5, 0);
	gluDisk(gluNewQuadric(), 0, 0.01, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(1.7, 0.4, 0);
	gluDisk(gluNewQuadric(), 0, 0.01, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1.6, -0.5, 0);
	gluDisk(gluNewQuadric(), 0, 0.01, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0.95, 0);
	gluDisk(gluNewQuadric(), 0, 0.01, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-0.05, -0.8, 0);
	gluDisk(gluNewQuadric(), 0, 0.01, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.2, -0.2, 0);
	gluDisk(gluNewQuadric(), 0, 0.01, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1.8, 0.8, 0);
	gluDisk(gluNewQuadric(), 0, 0.01, 10, 10);
	glPopMatrix();
	glColor3d(0, 0.5, 1);
	glPushMatrix();
	glTranslated(1, 0.5, 0);
	gluDisk(gluNewQuadric(), 0, 0.15, 15, 15);
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_POLYGON);

}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawBackground();
	Player1->draw();
	Player1->pew->draw();
	
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
	if (Test->pew->pos->getx() > 1.92 || Test->pew->pos->getx() < -1.92) {
		Test->pew->shoot = 0;
		Test->pew->pos->setx(Test->pos->getx());
		Test->pew->pos->sety(Test->pos->gety());
		Test->pew->vel->setx(Test->pos->getx());
		Test->pew->vel->sety(Test->pos->gety());
	}
	if (Test->pew->pos->gety() > 1 || Test->pew->pos->gety() < -1) {
		Test->pew->shoot = 0;
		Test->pew->pos->sety(Test->pos->gety());
		Test->pew->pos->setx(Test->pos->getx());
		Test->pew->vel->setx(Test->pos->getx());
		Test->pew->vel->sety(Test->pos->gety());
	}
}
