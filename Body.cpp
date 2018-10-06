#include "Body.h"
#include <cstdlib>
blob::blob(double m, double r) {
	this->mass = m;
	this->radius = r;
	rgb[0] = 0;
	rgb[1] = 1;
	rgb[2] = 0;

}
/*
blob::blob() {
	mass = 1;
	radius = 0.1;
	rgb[0] = 0;
	rgb[1] = 1;
	rgb[2] = 0;

}*/
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
void blob::update(double dt) {
	vel->shuffleX(accel->getx()*dt);
	vel->shuffleY(accel->gety()*dt);
	double scalef = 1 / mass;
	vel->setx(clamp(-scalef , vel->getx(), scalef));
	vel->sety(clamp(-scalef, vel->gety(), scalef));

	pos->shuffleX(vel->getx()*dt);
	pos->shuffleY(vel->gety()*dt);

	accel->scale(0);
}
void blob::draw() {
	glPushMatrix();
	glMove();
	glColor3d(rgb[0],rgb[1],rgb[2]);
	gluDisk(gluNewQuadric(), 0, radius, 20, 10);
	glPopMatrix();
}