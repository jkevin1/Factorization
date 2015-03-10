#include "Timer.h"

void Timer::start() {
	time = high_resolution_clock::now();
}

double Timer::getTime() {
	high_resolution_clock::time_point now = high_resolution_clock::now();
	duration<double> value = duration_cast<duration<double>>(now - time);
	return value.count();
}