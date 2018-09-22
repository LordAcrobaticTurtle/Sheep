#include "Rocket.h"
Rocket::Rocket() {
	Player = new GamePad::XBoxController(&ptr, PlayedID);
}
Rocket::Rocket(int PID) {
	Player = new GamePad::XBoxController(&ptr, PID - 1);
	PlayedID = PID;
}
void Rocket::update(double dt) {
	vel.shuffleX(accel.getx()*dt);
	vel.shuffleY(accel.gety()*dt);

	vel.setx(clamp(-2.5, vel.getx(), 2.5));
	vel.sety(clamp(-2.5, vel.gety(), 2.5));

	pos.shuffleX(vel.getx()*dt);
	pos.shuffleY(vel.gety()*dt);

	accel.scale(0);
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