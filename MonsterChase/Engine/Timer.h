#pragma once
#include <time.h>

extern float gameTime;

class Timer
{
private:
		 bool isTimeAcquired = false;
		 float timeDifference = 0;


public:
	float TimeDiff();
	void Init();
};