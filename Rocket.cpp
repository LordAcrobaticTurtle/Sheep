#include "Rocket.h"

Rocket::Rocket() {
	Player = new GamePad::XBoxController(&ptr, PlayedID);
	radius = 0.07;
	
}
Rocket::Rocket(int PID) {
	Player = new GamePad::XBoxController(&ptr, PID - 1);
	PlayedID = PID;
	radius = 0.05;
	pew = new lazor();
	pew->pos->setx(0);
	pew->pos->sety(0);
	health = 3;
	shield = new blob(0.5, radius);
	shield->setcolour(0, 0.5, 1);
}



void Rocket::update(double dt) {
	vel->shuffleX(accel->getx()*dt);
	vel->shuffleY(accel->gety()*dt);

	vel->setx(clamp(-2, vel->getx(), 2));
	vel->sety(clamp(-2, vel->gety(), 2));

	pos->shuffleX(vel->getx()*dt);
	pos->shuffleY(vel->gety()*dt);

	shield->pos->setx(pos->getx());
	shield->pos->sety(pos->gety());

	if (pew->shoot != 1) {
		pew->vel->setx(1.2*cos(getrotation()*PI / 180));
		pew->vel->sety(1.2*sin(getrotation()*PI / 180));
		pew->pos->setx(pos->getx());
		pew->pos->sety(pos->gety());
	}

	if (rotation > 360) rotation = 0;
	if (rotation < -360) rotation = 0;
	if (pew->shoot == 1) {
		pew->update(dt);
	}

	accel->scale(0);
}
int Rocket::getHealth() {
	return health;
}
void Rocket::setHeatlh(double hp) {
	health = hp;
}
void Rocket::draw() {
	if (Player->PressedA()) {
		shield->draw();
	}
	glPushMatrix();
	glMove();
	glPushMatrix();
	glColor3d(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2d(-0.03, 0.03);
	glVertex2d(-0.03, -0.03);
	glVertex2d(0.03,-0.03);
	glVertex2d(0.03, 0.03);
	glEnd();
	// NOSECONE
	glColor3d(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2d(0.03,0.03);
	glVertex2d(0.03, -0.03);
	glVertex2d(0.07, 0);
	
	//FINS
	glColor3d(1, 0, 0);
	glVertex2d(-0.03, 0.03);
	glVertex2d(0, 0.03);
	glVertex2d(-0.035, 0.04);

	glVertex2d(-0.03, -0.03);
	glVertex2d(0, -0.03);
	glVertex2d(-0.035, -0.04);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	if (pew->shoot == 1) {
		pew->draw();
	}
	
}