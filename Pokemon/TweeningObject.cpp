#include "TweeningObject.h"
#include "Timer.h"
#include <cmath>
#include <thread>

using std::thread;
using namespace std::chrono;

TweeningObject::TweeningObject()
	: target(0), isPlaying(false), goalValue(0), timer(0.0f), time(0.1f), decrease(true)
{ }

void TweeningObject::SetTarget(int* _target)
{
	target = _target;
}

void TweeningObject::SetGoalValue(int _goalValue)
{
	goalValue = (float)_goalValue;
}

void TweeningObject::SetTime(float _time)
{
	time = _time;
}

void TweeningObject::Update()
{
	if (isPlaying)
	{
		if (decrease)
		{
			curValue -= Timer::DeltaTime() * 10.0f;
			(*target) = (int)curValue;

			diff = fabs(goalValue - curValue);

			if (fabs(curValue - goalValue) < 0.1f || diff > prevDiff)
			{
				curValue = goalValue;
				(*target) = (int)curValue;

				isPlaying = false;
			}

			prevDiff = diff;
		}
		else
		{
			curValue += Timer::DeltaTime() * 10.0f;
			(*target) = (int)curValue;

			diff = fabs(goalValue - curValue);

			if (fabs(curValue - goalValue) < 0.1f || diff > prevDiff)
			{
				curValue = goalValue;
				(*target) = (int)curValue;

				isPlaying = false;
			}

			prevDiff = diff;
		}
	}
}

void TweeningObject::Start()
{
	curValue = (float)(*target);
	prevDiff = fabs((float)goalValue - curValue);

	if (goalValue < curValue)
		decrease = true;
	else
		decrease = false;

	isPlaying = true;
}

bool TweeningObject::IsPlaying()
{
	return isPlaying;
}

void TweeningObject::_Tween(int* target, float goal)
{
	double frameTimer = 0.0f;

	float curValue = float(*target);
	float diff = fabs(curValue - goal);

	float amount = curValue < goal ? 1.0f : -1.0f;

	auto prevClock = high_resolution_clock::now();

	while (true)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		frameTimer += deltaTime;

		if (frameTimer >= 0.16f)
		{
			frameTimer = 0.0f;

			curValue += amount;
			(*target) = int(curValue);

			if (diff < 0.05f || diff < fabs(curValue - goal))
				break;

			diff = fabs(curValue - goal);
		}

		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 80 - (frameClock - nextClock).count() / 1e9;

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	(*target) = (int)goal;

	isPlaying = false;
}

void TweeningObject::Tween(int* target, float goal)
{
	isPlaying = true;

	thread t(&TweeningObject::_Tween, this, target, goal);
	t.detach();
}
