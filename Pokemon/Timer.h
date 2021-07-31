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

		Time();
		~Time() = default;

		void Reset();
		float Update();

	private:
		LARGE_INTEGER m_CountTime;
		LARGE_INTEGER m_CurTime;
		LARGE_INTEGER m_PrevTime;
		double m_dDeltaTime;
		float m_fDeltaTime;
	};

private:
	static Time s_MainTimer;

public:
	Timer() = delete;
	~Timer() = delete;

	static float DeltaTime();
	static void Update();
	static void Reset();
};

#endif // !__DELTA_TIME_H__