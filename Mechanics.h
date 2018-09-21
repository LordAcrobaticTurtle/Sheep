#pragma once
#include "2Dengine.h"
#include "Shape.h"
#include "GL.H"
#include "GLU.H"
#include "glut.h"
#include "Rocket.h"
#include "Body.h"

class Mechanics {
public:
	//bool Collision(Shape *s, Shape *p);
	double time();
	Rocket * Players[4];
	blob * Asteroids[10];
	// GRAVITY
	void PlayerControls(Rocket * ship);
	double scalestickX(GamePad::Coordinate * ptr);
	double scalestickY(GamePad::Coordinate * ptr);
	
	void addshape(Rocket * s);
	void addshape(blob * t);
	// LAZERS AND COLLISIONS
};