#pragma once
#include <Windows.h>
#include "2Dengine.h"
#include "Shape.h"
#include "GL.H"
#include "GLU.H"
#include "glut.h"

class lazor : public Shape {
public:
	lazor();
	void update(double dt);
	double maxV = 2.5;
	int shoot;
	void draw();
};