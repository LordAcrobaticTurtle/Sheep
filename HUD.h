#pragma once
#include "Shape.h"
#include "GL.H"
#include "GLU.H"
#include "glut.h"
#include "Rocket.h"
class HUD {
public:
	static void PrintHealth(int Health);
	static void DeathMessage(int hp);
	static void PrintScore(int num);

};
