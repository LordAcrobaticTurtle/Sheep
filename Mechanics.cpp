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
}*/
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

