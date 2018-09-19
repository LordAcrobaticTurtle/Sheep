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
public:
	Shape();
	~Shape();

	double getrotation();
	double getspeed();
	position pos;	// X,Y coords of object
	//void addshape(Shape *s);
	
	void setcolour(double r, double g, double b);
	void setrotation(double r);
	void setspeed(double s);
	void setposX(double x);
	void setposY(double y);


	virtual void draw() = 0;
	void glMove();
};