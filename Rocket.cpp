#include "Rocket.h"
Rocket::Rocket() {
	Player = new GamePad::XBoxController(&ptr, PlayedID);
	radius = 0.05;
	
}
Rocket::Rocket(int PID) {
	Player = new GamePad::XBoxController(&ptr, PID - 1);
	PlayedID = PID;
	radius = 0.05;
	pew = new lazor();
	pew->pos->setx(0);
	pew->pos->sety(0);
}



void Rocket::update(double dt) {
	vel->shuffleX(accel->getx()*dt);
	vel->shuffleY(accel->gety()*dt);

	vel->setx(clamp(-2, vel->getx(), 2));
	vel->sety(clamp(-2, vel->gety(), 2));

	pos->shuffleX(vel->getx()*dt);
	pos->shuffleY(vel->gety()*dt);
	if (rotation > 360) rotation = 0;
	if (rotation < -360) rotation = 0;
	if (pew->shoot == 1) {
		pew->update(dt);
	}

	accel->scale(0);
}
double Rocket::getHealth() {
	return health;
}
void Rocket::setHeatlh(double hp) {
	health = hp;
}
void Rocket::draw() {
	glPushMatrix();
	glColor3d(1, 0, 1);
	glMove();
	glBegin(GL_QUADS);
	glVertex2d(-0.03, 0.03);
	glVertex2d(-0.03, -0.03);
	glVertex2d(0.03,-0.03);
	glVertex2d(0.03, 0.03);
	glEnd();
	// NOSECONE
	glBegin(GL_TRIANGLES);
	glVertex2d(0.03,0.03);
	glVertex2d(0.03, -0.03);
	glVertex2d(0.07, 0);
	
	//FINS
	glVertex2d(-0.03, 0.03);
	glVertex2d(0, 0.03);
	glVertex2d(-0.035, 0.04);

	glVertex2d(-0.03, -0.03);
	glVertex2d(0, -0.03);
	glVertex2d(-0.035, -0.04);
	glEnd();
	glPopMatrix();
	if (pew->shoot == 1) {
		pew->draw();
	}
	
}