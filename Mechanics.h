#pragma once
#include "2Dengine.h"
#include "Shape.h"
#include "GL.H"
#include "GLU.H"
#include "glut.h"
#include "Rocket.h"
#include "Body.h"
class Mechanics {
private:
	//static int score;
public:
	Mechanics();
	static bool Collision(blob *s, blob *p);
	static bool Collision(Rocket * player, blob * p);
	static bool Collision(blob * s, lazor * p);
	static double time();
	//static int getscore();
	//static void shufflescore(int num);
	static void borderPatrol(blob * Test);
	static void borderPatrol(Rocket * Test);
	static void bounce(Rocket * p, blob * b);	
	static void bounce(blob * b1, blob * b2);
	static void nom(blob * b1, blob * b2);
	static void AsteroidGrav(blob* Test2, blob* Test3);
	static void AsteroidGrav(blob * b, Rocket * p);
	static void Destroy(blob * b);
	static void PlayerControls(Rocket * ship);
	static double scalestickX(GamePad::Coordinate ptr);
	static double scalestickY(GamePad::Coordinate ptr);
	static double scalerotation(GamePad::Coordinate ptr);
	
	
};