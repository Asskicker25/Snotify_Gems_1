#include "Profiler.h"
#include <ctime>

void Profiler::StartTimer()
{
	mStartTime = std::chrono::high_resolution_clock::now();
}

void Profiler::EndTimer()
{
	mEndTime = std::chrono::high_resolution_clock::now();
}

double Profiler::GetElapsedTime()
{
	return std::chrono::duration<double>(mEndTime - mStartTime).count();
}
