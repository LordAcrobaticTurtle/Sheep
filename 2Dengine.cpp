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

void position::setx(double x_) {
	x = x_;
}
void position::sety(double y_) {
	y = y_;
}

void position::shuffleX(double x_) {
	x += x_;
}
void position::shuffleY(double y_) {
	y += y_;
}

void position::add(position * v) {
	x += v->x;
	y += v->y;
}
position * position::subtract(position * a, position * b) {
	position * vector = new position(a->x - b->x, a->y - b->y);

	return vector;
}

void position::scale(double n) {
	x = x * n;
	y = y * n;
}

double position::mag() {
	return sqrt((x)*(x) + (y)*(y));
}

double position::mag2() {
	return (x)*(x)+(y)*(y);
}
void position::normalise() {
	x = x / mag();
	y = y / mag();
}
double position::angle() {
	return atan2(y,x);
}
double position::dot(position * a, position * b) {
	return a->x*b->x + a->y*b->y;
}