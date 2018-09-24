#pragma once
#include "2Dengine.h"
#include <Windows.h>
#include "GL.h"
#include "GLU.H"
#include "glut.h"
#include <vector>
class Shape {
protected:
	double rotation;	// what direction is the object facing
	double speed;	// How fast is the object moving
	double rgb[3]; // Colour 
//	std::vector<Shape*> image; //-> For drawing
	bool Alive;

public:
	Shape();
	~Shape();
	double getrotation();
	double getspeed();
	position *pos;	// X,Y coords of object
	position *vel;	// velocity of object in x and y terms
	position *accel; // Accleration in x y terms
	double clamp(double a, double b, double c);
	bool getAlive();
	void setAlive(int m);

	void setcolour(double r, double g, double b);
	void setrotation(double r);
	void setspeed(double s);

	void shuffleRotation(double r);
	virtual void update(double speed, double dt);
	virtual void update(double dt);
	virtual void draw() = 0;
	void glMove();
};