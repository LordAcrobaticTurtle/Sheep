#include "Lazor.h"
lazor::lazor() {
	
}
void lazor::draw() {
	glPushMatrix();
	glMove();
	glBegin(GL_QUADS);
	glVertex2d(0.01, 0.005);
	glVertex2d(-0.01, 0.005);
	glVertex2d(-0.01, -0.005);
	glVertex2d(0.01, -0.005);
	glEnd();
	glPopMatrix();
}