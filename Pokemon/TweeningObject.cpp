#include "TweeningObject.h"
#include "Timer.h"

TweeningObject::TweeningObject()
	: target(0), isPlaying(false), goalValue(0), timer(0.0f), time(0.1f), decrease(true)
{ }

void TweeningObject::SetTarget(int* _target)
{
	target = _target;
}

void TweeningObject::SetGoalValue(int _goalValue)
{
	goalValue = _goalValue;
}

void TweeningObject::SetTime(float _time)
{
	time = _time;
}

void TweeningObject::Update()
{
	if (isPlaying)
	{
		timer += Timer::DeltaTime();

		if (timer >= time)
		{
			timer = 0.0f;

			if (decrease)
				(*target) = (*target) - 1;
			else
				(*target) = (*target) + 1;

			if (*target == goalValue)
				isPlaying = false;
		}
	}
}

void TweeningObject::Start()
{
	isPlaying = true;
}

bool TweeningObject::IsPlaying()
{
	return isPlaying;
}
