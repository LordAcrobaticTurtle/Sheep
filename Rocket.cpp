#include "Rocket.h"
Rocket::Rocket() {
	Player = new GamePad::XBoxController(&ptr, PlayedID);
}
Rocket::Rocket(int PID) {
	Player = new GamePad::XBoxController(&ptr, PID - 1);
	PlayedID = PID;
}
void Rocket::draw() {
	
	glPushMatrix();
	glColor3d(1, 0, 1);
	glMove();
	glBegin(GL_TRIANGLES);
	glVertex2d(-0.05, 0.05);
	glVertex2d(-0.05, -0.05);
	glVertex2d(0.1,0);
	glEnd();
	glPopMatrix();
}