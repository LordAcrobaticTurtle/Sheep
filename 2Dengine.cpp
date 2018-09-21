#include <Windows.h>
#include "2Dengine.h"
#include "GL.H"
#include "GLU.H"
#include "glut.h"
#include <cmath>

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

void position::add(position v) {
	x += v.x;
	y += v.y;
}

void position::subtract(position v) {
	x -= v.x;
	y -= v.y;
}
void position::scale(double n) {
	x = x * n;
	y = x * n;
}

double position::mag(position v) {
	return sqrt((x - v.x)*(x - v.x) + (y - v.y)*(y - v.y));
}