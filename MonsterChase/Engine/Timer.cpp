#include <time.h>
#include "Timer.h"
#include <iostream>
#include <chrono>
#include <Windows.h>
#include <cassert>

float gameTime = 0;
DWORD prevTime = 0;
LARGE_INTEGER PerformanceFrequency = { 0 };

void Timer::Init()
{
	QueryPerformanceFrequency(&PerformanceFrequency);
}


DWORD GetCurrentTickCounter()
{
	LARGE_INTEGER CurrentFrameCounter;

	BOOL success = QueryPerformanceCounter(&CurrentFrameCounter);
	assert(success == true);

	return CurrentFrameCounter.QuadPart;
}


float Timer::TimeDiff()
{
	if (prevTime == 0)
	{
		prevTime = GetCurrentTickCounter();
		return 0.02f;
	}

	auto begin_time = GetCurrentTickCounter();

	timeDifference = (1000 * static_cast<float>(begin_time - prevTime)) / PerformanceFrequency.QuadPart;
	prevTime = begin_time;

	if (!isTimeAcquired)
	{
		gameTime = timeDifference;
		isTimeAcquired = true;
	}

	return timeDifference;
}