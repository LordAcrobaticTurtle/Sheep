#pragma once
#include "2Dengine.h"
#include "Shape.h"
#include <Windows.h>
#include "GL.H"
#include "GLU.H"
#include "glut.h"
#include "XboxHeader.h"
#include "XInputWrapper.h"
#include <Xinput.h>
#include "Lazor.h"

class Rocket : public Shape {
private:
	XInputWrapper ptr;
protected:
	int health;
	int PlayedID;
public:
	lazor * pew;
	double radius;
	Rocket();
	Rocket(int hp);
	void update(double dt);
	void draw();
	GamePad::XBoxController * Player;
};