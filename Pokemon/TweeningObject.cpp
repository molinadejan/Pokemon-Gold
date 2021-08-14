#include "TweeningObject.h"
#include "Timer.h"
#include <cmath>

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
