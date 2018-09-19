#include "Rocket.h"
Rocket::Rocket() {
}
Rocket::Rocket(int hp) {
	health = hp;
}
void Rocket::draw() {
	
	glPushMatrix();
	glMove();
	glBegin(GL_TRIANGLES);
	glVertex2d(-0.05, 0);
	glVertex2d(0.05, 0);
	glVertex2d(0, 0.1);
	glEnd();
	glPopMatrix();
}