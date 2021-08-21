#include "ValueVariation.h"
#include "Timer.h"
#include <cmath>
#include <thread>

using std::thread;
using namespace std::chrono;

ValueVariation::ValueVariation()
	: target(0), isPlaying(false), goalValue(0), decrease(true)
{ }

void ValueVariation::SetTarget(int* _target)
{
	target = _target;
}

void ValueVariation::SetGoalValue(int _goalValue)
{
	goalValue = (float)_goalValue;
}

bool ValueVariation::IsPlaying()
{
	return isPlaying;
}

void ValueVariation::_Variation(int* target, float goal)
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

void ValueVariation::Variation(int* target, float goal)
{
	isPlaying = true;

	thread t(&ValueVariation::_Variation, this, target, goal);
	t.detach();
}
