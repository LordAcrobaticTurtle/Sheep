#pragma once
#include "2Dengine.h"
#include "Shape.h"
#include <Windows.h>
#include "GL.H"
#include "GLU.H"
#include "glut.h"

class Rocket : public Shape {
protected:
	int health;
public:
	Rocket();
	Rocket(int hp);
	void draw();

};