#include "Lazor.h"
lazor::lazor() {
	pos->setx(0);
	pos->sety(0);
	rgb[0] = 0;
	rgb[1] = 1;
	rgb[2] = 0;
	shoot = 0;
	vel->setx(0);
	vel->sety(0);
}
void lazor::update(double dt) {
	//vel->setx(cos(rotation));
	//vel->sety(sin(rotation));
	pos->shuffleX(maxV*vel->getx()*dt);
	pos->shuffleY(maxV*vel->gety()*dt);
}

void lazor::draw() {
	glPushMatrix();
	glMove();
	glColor3d(rgb[0],rgb[1],rgb[2]);
	gluDisk(gluNewQuadric(), 0, 0.01, 10, 10);
	glPopMatrix();
	
}