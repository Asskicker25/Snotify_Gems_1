#pragma once
#include <chrono>


#define TIMER_CALL(x)	Profiler::GetInstance().StartTimer();\
						x;\
						Profiler::GetInstance().EndTimer();\
						std::cout << "Elapsed Time : " <<Profiler::GetInstance().GetElapsedTime() << std::endl;

class Profiler
{
public:

	static Profiler& GetInstance();

	Profiler() = default; 

	void StartTimer();
	void EndTimer();

	double GetElapsedTime();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> mEndTime;

};

