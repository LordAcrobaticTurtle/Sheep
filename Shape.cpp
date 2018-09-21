
#include "Shape.h"


Shape::Shape() {
//	pos.setx(0);
//	pos.sety(0);
	speed = 0;
	rotation = 0;
}
Shape::~Shape() {
	// Create loop that deletes items from vector list
}
bool Shape::getAlive() {
	return Alive;
}

void Shape::setAlive(int m) {
	if (m == 1) {
		Alive = true;
	}
	else if (m == 0) {
		Alive = false;
	}
}

double Shape::getrotation() {
	return rotation;
}
/*
position Shape::getpos() {
	return pos;
}
*/
double Shape::getspeed() {
	return speed;
}

void Shape::setcolour(double r, double g, double b) {
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}

void Shape::setrotation(double r) {
	rotation = r;
}
void Shape::shuffleRotation(double r) {
	rotation += r;
}
void Shape::setspeed(double s) {
	speed = s;
}
void Shape::setposX(double x) {
	pos.setx(x);
}
void Shape::setposY(double y) {
	pos.sety(y);
}
void Shape::update(double speed, double dt) {
	double dx = 0;
	double dy = 0;
	dx = speed * cos(-rotation * 3.1415926535 /180) * dt;
	dy = speed * sin(rotation * 3.1415926535 / 180) * dt;
	pos.shuffleX(dx);
	pos.shuffleY(dy);
}
void Shape::update(double dt) {
	vel.shuffleX(accel.getx()*dt);
	vel.shuffleY(accel.gety()*dt);

	pos.shuffleX(vel.getx()*dt);
	pos.shuffleY(vel.gety()*dt);
	

}
void Shape::glMove() {
	glTranslated(pos.getx(), pos.gety(),0);
	glRotated(rotation, 0, 0, 1);
}
/*
void Shape::addshape(Shape *s) {
	image.push_back(s);
}
*/