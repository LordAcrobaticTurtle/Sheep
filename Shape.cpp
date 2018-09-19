
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
void Shape::setspeed(double s) {
	speed = s;
}
void Shape::setposX(double x) {
	pos.setx(x);
}
void Shape::setposY(double y) {
	pos.sety(y);
}
void Shape::glMove() {
	glTranslated(pos.getx(), pos.gety(),0);
}
/*
void Shape::addshape(Shape *s) {
	image.push_back(s);
}
*/