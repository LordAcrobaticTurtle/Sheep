#pragma once

class position {
protected:
	double x;
	double y;
	
public:
	position();
	position(double x_, double y_);
	double getx();
	double gety();

	void setx(double x);
	void sety(double y);

	void shuffleX(double x);
	void shuffleY(double y);

	void add(position * v);
	static position * subtract(position * a, position * b);
	void scale(double n);
	void normalise();
	double mag();
	double mag2();
	double angle();
	static double dot(position * a, position * b);
	
	
};