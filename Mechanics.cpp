#include "Mechanics.h"
#include "Body.h"
#include <cstdlib>
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
void Mechanics::PlayerControls(Rocket * ctrl) {
	XInputGetState(0, ctrl->Player->GetState());
	ctrl->Player->SetDeadzone(5000);
	GamePad::Coordinate * LThumb;
	GamePad::Coordinate * RThumb;
	LThumb = &ctrl->Player->LeftThumbLocation();
	RThumb = &ctrl->Player->RightThumbLocation();
	if (ctrl->Player->PressedY()) {
		getchar();
	}
	ctrl->accel->setx(scalestickX(LThumb));
	ctrl->accel->sety(scalestickY(LThumb));
	ctrl->shuffleRotation(-scalestickX(RThumb));
	if (ctrl->Player->PressedLeftShoulder()) {
		ctrl->pew->shoot = 1;
	} 
	if (ctrl->Player->PressedRightShoulder()) {
		ctrl->pew->shoot = 0;
		ctrl->pew->pos->setx(ctrl->pos->getx());
		ctrl->pew->pos->sety(ctrl->pos->gety());
	}

}
void Mechanics::AsteroidGrav(blob* Test2, blob* Test3) {
	position distance;
	distance.sety(Test2->pos->gety() - Test3->pos->gety());
	distance.setx(Test2->pos->getx() - Test3->pos->getx());
	double magnitude = 0;
	magnitude = (Test2->getmass()*Test3->getmass()) / (distance.mag()*distance.mag());
	position force;
	force.scale(1 / Test3->getmass());
	force.setx(magnitude*distance.getx());
	force.sety(magnitude*distance.gety());
	Test3->accel->add(force);
	
	force.scale(-1*Test3->getmass()/Test2->getmass());
	Test2->accel->add(force);

}
double Mechanics::scalestickX(GamePad::Coordinate * ptr) {
	return (ptr->GetX() / 5000.0);

}
double Mechanics::scalestickY(GamePad::Coordinate * ptr) {
	return (ptr->GetY() / 5000.0);
}
bool Mechanics::Collision(Rocket * player, blob * p) {
	position distance = position::subtract(player->pos, p->pos);
	if (distance.mag() - player->radius - p->getradius() < 0) {
		return true;
	}
	return false;
}
bool Mechanics::Collision(blob * body1, blob * body2) {
	position distance = position::subtract(body1->pos, body2->pos);
	
	if (distance.mag() - body1->getradius() - body2->getradius() < 0) {
		return true;
	}
	return false;
}
bool Mechanics::Collision(blob * body, lazor * pew) {
	position distance = position::subtract(body->pos, pew->pos);

	if (distance.mag() - body->getradius() - 0.01 < 0) {
		return true;
	}
}
void Mechanics::Destroy(blob * body) {
	body->setmass(body->getmass());
	body->setradius(body->getradius());
	printf("Hit!");
}
void Mechanics::nom(blob * b1, blob * b2) {
	if (b1->getmass() >= b2->getmass()) {
		b1->setmass(b1->getmass() + 0.01);
		b1->setradius((b1->getradius() + 0.01));
		b2->pos->setx(rand()% 100);
		b2->pos->sety(rand()%100);
	}
	else if (b2->getmass() > b1->getmass()) {
		b2->setmass(b2->getmass() + 0.01);
		b2->setradius(b2->getradius() + 0.01);
		b1->pos->setx(rand()%100);
		b1->pos->sety(rand()%100);
	}
}

double Mechanics::time() {
#if defined(WIN32)
		LARGE_INTEGER freqli;
		LARGE_INTEGER li;
		if (QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
			return double(li.QuadPart) / double(freqli.QuadPart);
		}
		else {
			static ULONGLONG start = GetTickCount64();
			return (GetTickCount64() - start) / 1000.0;
		}
#else
		struct timeval t;
		gettimeofday(&t, NULL);
		return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}



