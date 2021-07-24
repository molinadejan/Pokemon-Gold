// DeltaTime.h
#pragma once

#ifndef __TIMER_H__
#define __TIMER_H__

#include <Windows.h>

// static class
class Timer final
{
private:
	class Time
	{
		// friend로 Timer에게만 공개합니다.
		friend Timer;
	private:
		Time()
		{
			reset();
		}

		~Time() = default;

		void reset()
		{
			// 진동수
			QueryPerformanceFrequency(&m_CountTime);
			
			QueryPerformanceCounter(&m_CurTime);
			QueryPerformanceCounter(&m_PrevTime);
		}

		float update()
		{
			QueryPerformanceCounter(&m_CurTime);

			// delta time = current time - previous time
			m_dDeltaTime = (static_cast<double>(m_CurTime.QuadPart) - static_cast<double>(m_PrevTime.QuadPart)) / static_cast<double>(m_CountTime.QuadPart);

			m_fDeltaTime = static_cast<float>(m_dDeltaTime);
			m_PrevTime = m_CurTime;

			return m_fDeltaTime;
		}

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

	static double DeltaTime()
	{
		return s_MainTimer.m_dDeltaTime;
	}

	static void Update()
	{
		s_MainTimer.update();
	}

	static void Reset()
	{
		s_MainTimer.reset();
	}
};

#endif // !__DELTA_TIME_H__