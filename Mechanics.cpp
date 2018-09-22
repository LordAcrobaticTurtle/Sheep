#include "Mechanics.h"
#include "Body.h"
/*
bool Mechanics::Collision(Shape *s, Shape *p) {
	if (s = dynamic_cast<blob*>(s) || p = dynamic_cast<blob*>(p)) {
		// Peform circle hitbox detections
	}
	else {
		// Perform rectangular hitbox detections?
	}
}
void Mechanics::addshape(Rocket * s) {
	Players.push_back(s);
}

void Mechanics::addshape(blob * t) {
	Asteroids
}
*/
void Mechanics::PlayerControls(Rocket * Player) {
	XInputGetState(0, Player->Player->GetState());
	Player->Player->SetDeadzone(5000);
	GamePad::Coordinate * LThumb;
	GamePad::Coordinate * RThumb;
	LThumb = &Player->Player->LeftThumbLocation();
	RThumb = &Player->Player->RightThumbLocation();
	if (Player->Player->PressedY()) {
		getchar();
	}
	Player->accel.setx(scalestickX(LThumb));
	Player->accel.sety(scalestickY(LThumb));
	Player->shuffleRotation(-scalestickX(RThumb));

}
void Mechanics::AsteroidGrav(blob* Test2, blob* Test3) {
	position distance;
	distance.sety(Test2->pos.gety() - Test3->pos.gety());
	distance.setx(Test2->pos.getx() - Test3->pos.getx());
	double magnitude = 0;
	magnitude = (Test2->getmass()*Test3->getmass()) / (distance.mag()*distance.mag());
	position force;
	double g = 1 / Test3->getmass();
	force.scale(g);
	force.setx(magnitude*distance.getx());
	force.sety(magnitude*distance.gety());
	Test3->accel.add(force);
}
double Mechanics::scalestickX(GamePad::Coordinate * ptr) {
	return (ptr->GetX() / 5000.0);

}
double Mechanics::scalestickY(GamePad::Coordinate * ptr) {
	return (ptr->GetY() / 5000.0);
}

double Mechanics::time() {


	return 0;
}

