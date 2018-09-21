#pragma once
#include "2Dengine.h"
#include "Shape.h"
#include "GL.H"
#include "GLU.H"
#include "glut.h"

class Mechanics {
public:
	//bool Collision(Shape *s, Shape *p);
	double time();
	std::vector<Shape*> objects;
	// LAZERS AND COLLISIONS
};