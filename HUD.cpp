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

void HUD::PrintScore(int num) {
	if (num < 0) {
		glPushMatrix();
		glColor3d(1, 1, 1);
		glRasterPos2d(-0.6, -1);
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
	// hundreds column
	glPushMatrix();
	glColor3d(1, 1, 1);
	glRasterPos2d(-0.55, -1);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, hundreds + 48);
	glPopMatrix();
	// Tens column
	glPushMatrix();
	glColor3d(1, 1, 1);
	glRasterPos2d(-0.5,-1);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tens + 48);
	glPopMatrix();
	// ones column
	glPushMatrix();
	glColor3d(1, 1, 1);
	glRasterPos2d(-0.45,-1);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ones + 48);
	glPopMatrix();
}