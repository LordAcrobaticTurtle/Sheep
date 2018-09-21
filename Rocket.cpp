#include "Rocket.h"
Rocket::Rocket() {
}
Rocket::Rocket(int hp) {
	health = hp;
}
/*
void Rocket::laserz(GamePad::XBoxController * ctrl) {
	if (ctrl->PressedA()) {
		lazor * pew = new lazor();
		pew->setrotation(getrotation());
		pew->pos.setx(this->pos.getx());
		pew->pos.sety(this->pos.gety());
		pew->draw();
		
	}
}
*/
void Rocket::draw() {
	
	glPushMatrix();
	glColor3d(pos.getx()*1000, 1000*pos.gety(), 1000*pos.getx()* pos.gety());
	glMove();
	glBegin(GL_TRIANGLES);
	glVertex2d(-0.05, 00.05);
	glVertex2d(-0.05, -0.05);
	glVertex2d(0.1,0);
	glEnd();
	glPopMatrix();
}