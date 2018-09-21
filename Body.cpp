#include "Body.h"
#include <cstdlib>
blob::blob(double m, double r) {
	this->mass = m;
	this->radius = r;
	rgb[0] = 0;
	rgb[1] = 1;
	rgb[2] = 0;
	//pos.setx(0);
	//pos.sety(0);
	

}
blob::blob() {
	mass = 1;
	radius = 0.1;
	rgb[0] = 0;
	rgb[1] = 1;
	rgb[2] = 0;

}
double blob::getmass() {
	return mass;
}
double blob::getradius() {
	return radius;
}
void blob::setradius(double num) {
	this->radius = num;
}
void blob::setmass(double fat) {
	this->mass = fat;
}
void blob::draw() {
	glPushMatrix();
	glMove();
	glColor3d(1,1,1);
	gluDisk(gluNewQuadric(), 0, radius, 50, 20);
	glPopMatrix();
}