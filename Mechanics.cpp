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

	Player->accel.setx(scalestickX(LThumb));
	Player->accel.sety(scalestickY(LThumb));
	Player->shuffleRotation(-scalestickX(RThumb));

}
double Mechanics::scalestickX(GamePad::Coordinate * ptr) {
	return (ptr->GetX() / 5000.0);

}
double Mechanics::scalestickY(GamePad::Coordinate * ptr) {
	return (ptr->GetY() / 5000.0);
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

