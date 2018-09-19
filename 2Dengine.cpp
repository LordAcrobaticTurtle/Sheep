#include <Windows.h>
#include "2Dengine.h"
#include "GL.H"
#include "GLU.H"
#include "glut.h"

position::position() {
	x = 0;
	y = 0;
}

double position::getx() {
	return x;
}

double position::gety() {
	return y;
}

void position::setx(double x) {
	this->x = x;
}
void position::sety(double y) {
	this->y = y;
}

void position::shuffleX(double x) {
	this->x += x;
}
void position::shuffleY(double y) {
	this->y += y;
}