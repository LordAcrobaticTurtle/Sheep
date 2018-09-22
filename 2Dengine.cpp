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
position::position(double x_, double y_) {
	this->x = x_;
	this->y = y_;
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

position position::subtract(position a, position b) {
	position vector;
	vector.setx(a.getx() - b.getx());
	vector.sety(a.gety() - b.gety());
	return vector;
}

void position::scale(double n) {
	x = x * n;
	y = x * n;
}

double position::mag() {
	return sqrt((x)*(x) + (y)*(y));
}
void position::normalise() {
	x = x / mag();
	y = y / mag();
}