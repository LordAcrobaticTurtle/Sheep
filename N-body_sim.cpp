// N-body_sim.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include <iostream>
#include <Xinput.h>
#include <cmath>
#include <chrono>
#include <random>
#include <vector>

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
#define AssNum 1
#define NumberofPlayers 2
// EVIL VARIABLES
// Create a static frame counter variable . It would increase by one each time the idle function is called
// Then create another static/const variable that remembers which frame it happened at
// Take the difference between the current frame and the static variable. 
//===================================
std::vector<Rocket *> Players;
std::vector<blob *> Asteroids;
int score = 0;
int level = 1;

//===================================

bool LevelComplete();
void reshape(GLsizei width, GLsizei height);
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	for (unsigned int i = 0; i < AssNum; i++) {
		Asteroids.push_back(new blob(1, 0.1));
		Asteroids[i]->setcolour(0.5, 0.5, 0.5);
	}
	
	for (unsigned int j = 0; j < NumberofPlayers; j++) {
		Players.push_back(new Rocket(j+1));

	}

	Asteroids[0]->pos->setx(-1.9);
	/*
	Asteroids[1]->pos->setx(1);
	Asteroids[2]->pos->sety(-0.9);
	Asteroids[3]->pos->sety(0.9);
	Asteroids[4]->pos->setx(0.7);
	Asteroids[4]->pos->sety(-0.7);
	*/
	//Players[1]->pos->sety(0.5);
	Players[0]->pos->sety(-0.5);

}

void idle() {
	// Obtain player controls
	for (unsigned int i = 0; i < Players.size(); i++) {
		Mechanics::PlayerControls(Players[i]);
	}
	// Border patrol -> Fly through walls to opposite side
	for (unsigned int i = 0; i < Players.size(); i++) {
		Mechanics::borderPatrol(Players[i]);
	}
	unsigned int i = 0;
	// Border patrol for asteroids -> Fly through walls to other side of map
	while (i < Asteroids.size()) {
		Mechanics::borderPatrol(Asteroids[i]);
		i++;
	}
	static int condition = 0;
	// Up / down on dpad controls whether gravity is on or off
	if (Players[0]->Player->PressedUpDpad()) {
		condition = 1;
	}
	if (Players[0]->Player->PressedDownDpad()) {
		condition = 0;
	}
	// Creates asteroid gravity between Asteroids and players
	if (!condition) {
		for (i = 0; i < Asteroids.size(); i++) {
			for (unsigned int j = 0; j < Asteroids.size(); j++) {
				if (j != i) {
					Mechanics::AsteroidGrav(Asteroids[i], Asteroids[j]);
				}
			}
		}
		
		for (i = 0; i < Asteroids.size(); i++) {
			for (unsigned int j = 0; j < Players.size(); j++) {
				Mechanics::AsteroidGrav(Asteroids[i], Players[j]);
			}
		}
	}
	// Handles asteroid collision
	for (i = 0; i < Asteroids.size(); i++) {
		for (unsigned int j = 0; j < Asteroids.size(); j++) {
			if (j != i) {
				if (Mechanics::Collision(Asteroids[i], Asteroids[j])) {
					Mechanics::bounce(Asteroids[i], Asteroids[j]);
				}
			}
		}
	}
	// Obtain time between current frame and previous frame
	static double previousTime = Mechanics::time();
	const double currTime = Mechanics::time();
	const double elapsedTime = currTime - previousTime;
	
	
	// Handles Asteroid / laser collisions
	for (unsigned int j = 0; j < Players.size(); j++) {
		for (i = 0; i < Asteroids.size(); i++) {
			if (Mechanics::Collision(Asteroids[i], Players[j]->pew)) {
				Mechanics::Destroy(Asteroids[i]);
				Players[j]->addscore(10.0 / Asteroids[i]->getmass());
			}
		}
	}
	// Handles player / Asteroid collisions
	for (unsigned j = 0; j < Players.size(); j++) {
		for (i = 0; i < Asteroids.size(); i++) {
			if (Mechanics::Collision(Players[j], Asteroids[i])) {
				Players[j]->setHeatlh(Players[j]->getHealth() - 1);
				Mechanics::bounce(Players[j], Asteroids[i]);
				Players[j]->addscore(-5);
			}
		}
	}
	
	// Position/vel/accel/rotation update for each object
	previousTime = currTime;
	for (unsigned int i = 0; i < Players.size(); i++) {
		Players[i]->update(elapsedTime);
	}
	for (i = 0; i < Asteroids.size(); i++) {
		Asteroids[i]->update(elapsedTime);
	}
	
	// =============================================
	if (LevelComplete()) {
		srand(Mechanics::time());
		Asteroids.push_back(new blob(1, 0.1, rand()%2,rand()%2));
		for (i = 0; i < Asteroids.size(); i++) {
			Asteroids[i]->setmass(1);
			Asteroids[i]->setradius(0.1);
			level++;
		}
	// =============================================
	}
	glutPostRedisplay();
}
bool LevelComplete() {
	int counter = 0;
	for (unsigned int i = 0; i < Asteroids.size(); i++) {
		if (Asteroids[i]->getradius() == 0.02) {
			counter++;
		}
	}
	if (counter == Asteroids.size()) {
		return true;
	}
	return false;
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
	glColor3d(0.5, 1, 0.5);
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
	for (unsigned int i = 0; i < Players.size(); i++) {
		Players[i]->draw();
		Players[i]->pew->draw();
	}
	for (unsigned int i = 0; i < Asteroids.size(); i++) {
		Asteroids[i]->draw();
	}
	
	for (unsigned int i = 0; i < Players.size(); i++) {
		HUD::PrintScore(Players[i]);
	}
	
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

// 1349 lines of code counted 9/10/18