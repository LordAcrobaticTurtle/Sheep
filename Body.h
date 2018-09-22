#pragma once
#include "2Dengine.h"
#include <Windows.h>
#include "Body.h"
#include "GL.H"
#include "GLU.H"
#include "glut.h"
#include "Shape.h"
class blob : public Shape {
protected:
	double mass;
	double radius;
	double hitbox;
public:
	blob() = default;
	blob(double m, double r);
	void draw();
	void update(double dt);
	double getmass();
	double getradius();
	void setradius(double num);
	void setmass(double fat);
};
