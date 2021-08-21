#include "Timer.h"

Timer::Time Timer::timer = Timer::Time();

void Timer::Time::Init()
{
	QueryPerformanceFrequency(&countTime);
	QueryPerformanceCounter(&curTime);
	QueryPerformanceCounter(&prevTime);
}

void Timer::Time::Update()
{
	QueryPerformanceCounter(&curTime);
	deltaTime = (static_cast<float>(curTime.QuadPart) - static_cast<float>(prevTime.QuadPart)) / static_cast<float>(countTime.QuadPart);
	prevTime = curTime;
}
