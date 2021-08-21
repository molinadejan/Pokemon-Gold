// https://psk7142.github.io/blog/post/2019-12-23-delta_time/

#pragma once

#ifndef __TIMER_H__
#define __TIMER_H__

#include <Windows.h>

class Timer
{
private:

	class Time
	{
		friend Timer;

	private:

		Time() = default;
		~Time() = default;

		void Init();
		void Update();

	private:

		LARGE_INTEGER countTime;
		LARGE_INTEGER curTime;
		LARGE_INTEGER prevTime;

		float deltaTime;
	};

private:

	static Time timer;

	Timer() = delete;
	~Timer() = delete;

public:

	static float DeltaTime() { return timer.deltaTime; }
	static void Update() { timer.Update(); }
	static void Init() { timer.Init(); }
};

#endif // !__DELTA_TIME_H__