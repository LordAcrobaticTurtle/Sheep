#include "HUD.h"
#include <string>
void HUD::PrintHealth(int Health) {
	glPushMatrix();
	glColor3d(1, 1, 1);
	glRasterPos2i(1, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Health + 48);
	glPopMatrix();
}
void HUD::DeathMessage(int Hp) {
	if (Hp <= 0) {
		char Death[] = "You died";
		double x = 1;
		glPushMatrix();
		for (int i = 0; i < strlen(Death); i++) {
			glRasterPos2d(x, -0.5);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Death[i]);
			x += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, Death[i]);

		}
		glPopMatrix();
		//getchar();
	}
}

void HUD::PrintScore(Rocket * r) {
	position initial_position;

	if (r->getID() == 1) {
		initial_position.setx(-0.55);
		initial_position.sety(-1);
	}
	else if (r->getID() == 2) {
		initial_position.setx(-0.55);
		initial_position.sety(0.9);
	}
	else if (r->getID() == 3) {
		initial_position.setx(0.55);
		initial_position.sety(-1);
	}
	else if (r->getID() == 4) {
		initial_position.setx(0.55);
		initial_position.sety(0.9);
	}

	int num = r->getscore();
	if (num < 0) {
		glPushMatrix();
		glColor3d(1, 1, 1);
		glRasterPos2d(initial_position.getx()-0.05, initial_position.gety());
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 45);
		glPopMatrix();
		num = num * -1;
	}
	int hundreds = 0;
	int tens = 0;
	int ones = 0;
	ones = num % 10;
	num = num / 10;
	tens = num % 10;
	num = num / 10;
	hundreds = num % 10;
	int score[3] = {hundreds, tens, ones};
	
	// hundreds column
	glPushMatrix();
	glColor3d(1, 1, 1);
	for (unsigned int i = 0; i < 3; i++) {
		glRasterPos2d(initial_position.getx(),initial_position.gety());
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i] + 48);
		initial_position.shuffleX(0.05);
	}
	
	glPopMatrix();
}