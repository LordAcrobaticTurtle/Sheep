#pragma once
class position {
protected:
	double x;
	double y;
public:
	position();
	double getx();
	double gety();

	void setx(double x);
	void sety(double y);

	void shuffleX(double x);
	void shuffleY(double y);

	
};