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

public:
	blob();
	blob(double m, double r);
	void draw();
	double getmass();
	double getradius();
	void setradius(double num);
	void setmass(double fat);
};
