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
	shield = new blob(0.5, 0.071);
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
int Rocket::getscore() {
	return score;
}
void Rocket::addscore(double num) {
	score += num;
}
int Rocket::getID() {
	return PlayedID;
}
void Rocket::draw() {
	// Player shield 
	if (Player->PressedA()) {
		glPushMatrix();
		glTranslated(0.015*cos(rotation*PI/180), 0.015*sin(rotation*PI/180), 0);
		shield->draw();
		glPopMatrix();
	}
	glPushMatrix();
	glMove();
	glPushMatrix();
	glColor3d(1, 1, 1);
	// BODY
	glBegin(GL_QUADS);
	glVertex2d(-0.03, 0.03);
	glVertex2d(-0.03, -0.03);
	glVertex2d(0.03,-0.03);
	glVertex2d(0.03, 0.03);
	glEnd();
	if (PlayedID == 1) {
		glColor3d(1, 0, 0);
	}
	else if (PlayedID == 2) {
		glColor3d(0, 1, 0);
	}
	else if (PlayedID == 3) {
		glColor3d(0, 0, 1);
	}
	else if (PlayedID == 4) {
		glColor3d(1, 0, 1);
	}
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
	glPopMatrix();
	if (pew->shoot == 1) {
		pew->draw();
	}
	
}