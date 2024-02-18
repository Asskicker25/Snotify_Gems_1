#include "Profiler.h"
#include <ctime>
#include <iostream>

void Profiler::StartTimer()
{
	mStartTime = std::chrono::high_resolution_clock::now();
	std::cout << "Timer Start" << std::endl;
}

void Profiler::EndTimer()
{
	mEndTime = std::chrono::high_resolution_clock::now();
	std::cout << "Timer End" << std::endl;
}

double Profiler::GetElapsedTime()
{
	return std::chrono::duration<double>(mEndTime - mStartTime).count();
}
