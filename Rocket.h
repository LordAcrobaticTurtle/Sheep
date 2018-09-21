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
	Rocket();
	Rocket(int hp);
	void draw();
	GamePad::XBoxController * Player;
};