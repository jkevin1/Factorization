#pragma once

#include <chrono>

using namespace std::chrono;

class Timer {
	high_resolution_clock::time_point time;
public:
	Timer() { start(); }
	void start();
	double getTime();
};