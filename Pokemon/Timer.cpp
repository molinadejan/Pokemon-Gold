#include "Timer.h"

Timer::Time Timer::s_MainTimer = Timer::Time();

Timer::Time::Time()
{
	Reset();
}

void Timer::Time::Reset()
{
	QueryPerformanceFrequency(&m_CountTime);
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_PrevTime);
}

float Timer::Time::Update()
{
	QueryPerformanceCounter(&m_CurTime);

	// delta time = current time - previous time
	m_dDeltaTime = (static_cast<double>(m_CurTime.QuadPart) - static_cast<double>(m_PrevTime.QuadPart)) / static_cast<double>(m_CountTime.QuadPart);
	m_fDeltaTime = static_cast<float>(m_dDeltaTime);

	m_PrevTime = m_CurTime;

	return m_fDeltaTime;
}

float Timer::DeltaTime()
{
	return s_MainTimer.m_fDeltaTime;
}

void Timer::Update()
{
	s_MainTimer.Update();
}

void Timer::Reset()
{
	s_MainTimer.Reset();
}
