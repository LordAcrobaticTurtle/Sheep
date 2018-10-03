#include "Mechanics.h"
#include "Body.h"
#include <cstdlib>

Mechanics::Mechanics() {
	score = 0;
}
void Mechanics::PlayerControls(Rocket * ctrl) {
	XInputGetState(0, ctrl->Player->GetState());
	ctrl->Player->SetDeadzone(5000);
	GamePad::Coordinate * LThumb = &ctrl->Player->LeftThumbLocation();
	GamePad::Coordinate * RThumb = &ctrl->Player->RightThumbLocation();
	if (ctrl->Player->PressedY()) {
		getchar();
	}
	ctrl->accel->setx(scalestickX(LThumb));
	ctrl->accel->sety(scalestickY(LThumb));
	ctrl->shuffleRotation(-scalerotation(RThumb));
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
	position * distance = new position(0,0);
	distance = position::subtract(Test2->pos, Test3->pos);
	double magnitude = 0;
	distance->scale(-1);
	magnitude = 0.2*Test2->getmass()*Test3->getmass() / distance->mag2();
	position *force = new position(distance->getx(),distance->gety());
	force->scale(magnitude / Test2->getmass());
	Test2->accel->add(force);
	force->scale(-1 * Test2->getmass() / Test3->getmass());
	Test3->accel->add(force);
	delete force;
	delete distance;
	
}
double Mechanics::scalestickX(GamePad::Coordinate * ptr) {
	return (ptr->GetX() / 10000.0);

}

double Mechanics::scalestickY(GamePad::Coordinate * ptr) {
	return (ptr->GetY() / 10000.0);
}

double Mechanics::scalerotation(GamePad::Coordinate * ptr) {
	return (ptr->GetX() / 50000.0);
}

bool Mechanics::Collision(Rocket * player, blob * p) {
	position * distance = position::subtract(player->pos, p->pos);
	if (distance->mag2() < (player->radius + p->getradius())*(player->radius + p->getradius())) {
		delete distance;
		return true;
	}
	delete distance;
	return false;

}
void Mechanics::bounce(Rocket * p) {
	p->vel->scale(-1);
}
bool Mechanics::Collision(blob * body1, blob * body2) {
	position* distance = position::subtract(body1->pos, body2->pos);
	
	if (distance->mag2() < (body1->getradius() + body2->getradius()) * (body1->getradius() + body2->getradius())) {
		delete distance;
		return true;
	}
	delete distance;
	return false;
}
bool Mechanics::Collision(blob * body, lazor * pew) {
	position * distance = position::subtract(body->pos, pew->pos);
	if (pew->shoot == 1) {
		if (distance->mag2() < (body->getradius() + 0.01) * (body->getradius() + 0.01)) {
			pew->shoot = 0;
			delete distance;
			return true;
		}
	}
	delete distance;
	return false;

}
void Mechanics::Destroy(blob * body) {
	body->setmass(body->clamp(0.02,0.7*body->getmass(),1));
	body->setradius((body->clamp(0.008, 0.7*body->getradius(), 0.4)));
}
void Mechanics::bounce(blob * b1, blob * b2) {
	position * centre = position::subtract(b2->pos, b1->pos);
	centre->normalise();
	double mag = b2->vel->mag();
	b2->accel->scale(0);
	b2->vel->sety(centre->gety());
	b2->vel->setx(centre->getx());
	b2->vel->scale(mag);
	delete centre;
}
void Mechanics::nom(blob * b1, blob * b2) {
	if (b1->getmass() >= b2->getmass()) {
		
		b1->setmass(b1->clamp(0.02, b1->getmass() + 0.01, 1));
		b1->setradius((b1->clamp(0.08, b1->getradius() + 0.01, 0.4)));
		b1->vel->add(b2->vel);
		b2->pos->scale(-5);
		
	}
	else if (b2->getmass() > b1->getmass()) {
		b2->setmass(b2->clamp(0.02, b2->getmass() + 0.01, 1));
		b2->setradius((b2->clamp(0.008, b2->getradius() + 0.01, 0.4)));
		b2->vel->add(b2->vel);
		b2->pos->scale(-5);
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
int Mechanics::getscore() {
	return score;
}
void Mechanics::shufflescore(int num) {
	score += num;
}


