// N-body_sim.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <iostream>
#include <Xinput.h>
#include <cmath>
#include <chrono>
#include <random>


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
#include "HUD.h"

#define PI 3.1415926535
// EVIL VARIABLES
//===================================
Rocket * Player1 = new Rocket(1);
blob * Asteroids[5];

int score = 0;

//===================================


void reshape(GLsizei width, GLsizei height);
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < 5; i++) {
		Asteroids[i] = new blob(0.8, 0.08);
		Asteroids[i]->setcolour(0.5, 0.5, 0.5);
	}
	Asteroids[0]->pos->setx(1);
	Asteroids[1]->pos->setx(-1);
	Asteroids[2]->pos->sety(0.9);
	Asteroids[3]->pos->sety(-0.9);
	Asteroids[4]->pos->setx(-0.7);
	Asteroids[4]->pos->sety(0.7);
	
}

void idle() {
	// Obtain player controls
	Mechanics::PlayerControls(Player1);
	// Border patrol -> Bounces off walls
	Mechanics::borderPatrol(Player1);
	int i = 0;
	// Border patrol for asteroids -> Fly through walls to other side of map
	while (i < 5) {
		Mechanics::borderPatrol(Asteroids[i]);
		i++;
	}

	// Creates asteroid gravity
	for (i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (j != i) {
				Mechanics::AsteroidGrav(Asteroids[i], Asteroids[j]);
			}
		}
	}
	// Handles asteroid collision
	for (i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (j != i) {
				if (Mechanics::Collision(Asteroids[i], Asteroids[j])) {
					Mechanics::nom(Asteroids[i], Asteroids[j]);
				}
			}
		}
	}
	// Obtain time between current frame and previous frame
	static double previousTime = Mechanics::time();
	const double currTime = Mechanics::time();
	const double elapsedTime = currTime - previousTime;
	
	// Give the laser the player's position and velocity 
	if (Player1->pew->shoot != 1) {
		Player1->pew->vel->setx(cos(Player1->getrotation()*PI/180));
		Player1->pew->vel->sety(sin(Player1->getrotation()*PI/180));
		Player1->pew->pos->setx(Player1->pos->getx());
		Player1->pew->pos->sety(Player1->pos->gety());
	}
	
	// Handles Asteroid laser collisions
	for (i = 0; i < 5; i++) {
		if (Mechanics::Collision(Asteroids[i], Player1->pew)) {
			Mechanics::Destroy(Asteroids[i]);
			score += 1;
		}
	}
	// Handles player Asteroid collisions
	for (i = 0; i < 5; i++) {
		if (Mechanics::Collision(Player1, Asteroids[i])) {
			Player1->setHeatlh(Player1->getHealth() - 1);
			Mechanics::bounce(Player1);
		}
	}
	
	// ====================================
	
	// Position/vel/accel/rotation update for each object
	previousTime = currTime;
	Player1->update(elapsedTime);
	for (i = 0; i < 5; i++) {
		Asteroids[i]->update(elapsedTime);
	}
	
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

}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawBackground();
	Player1->draw();
	Player1->pew->draw();
	for (int i = 0; i < 5; i++) {
		Asteroids[i]->draw();
	}
	/*
	Test2->draw();
	Test3->draw();
	Test4->draw();
	Test5->draw();
	*/
	HUD::DeathMessage(Player1->getHealth());
	HUD::PrintHealth(Player1->getHealth());
	HUD::PrintScore(score);
	glFlush();
	glutSwapBuffers();

}
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
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
