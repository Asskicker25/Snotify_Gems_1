#pragma once
#include <chrono>

class Profiler
{
public:

	Profiler() = default; 

	void StartTimer();
	void EndTimer();

	double GetElapsedTime();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> mEndTime;

};

