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
	bool Collision(blob *s, blob *p);
	bool Collision(Rocket * player, blob * p);
	bool Collision(blob * s, lazor * p);
	double time();
	//void bounce(blob * body1, blob * body2);
	void bounce(Rocket * body);	
	void nom(blob * b1, blob * b2);
	void AsteroidGrav(blob* Test2, blob* Test3);
	void Destroy(blob * b);
	void PlayerControls(Rocket * ship);
	double scalestickX(GamePad::Coordinate * ptr);
	double scalestickY(GamePad::Coordinate * ptr);
	double scalerotation(GamePad::Coordinate * ptr);
	
	
};