#include "AnimationObject.h"
#include "Timer.h"
#include "DataLoadManager.h"
#include <thread>
#include <chrono>

using std::thread;
using namespace std::chrono;

AnimationObject::AnimationObject()
	: MovingObject(), frameCnt(0)
{ }

void AnimationObject::Draw(Graphics & g)
{
	if (isPlaying)
	{
		Rect& curRect = (*imagePosVec)[frameCnt];
		g.DrawImage(image, Rect(pos.X, pos.Y, screenSize.X, screenSize.Y), curRect.X, curRect.Y, curRect.Width, curRect.Height, UnitPixel);
	}
}

void AnimationObject::_Playing()
{
	double frameTimer = 0.0f;

	auto prevClock = high_resolution_clock::now();

	while (frameCnt < (int)imagePosVec->size() - 1)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 80 - (frameClock - nextClock).count() / 1e9;

		frameTimer += deltaTime;

		if (frameTimer >= 0.1f)
		{
			frameTimer = 0.0f;
			++frameCnt;
		}

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	isPlaying = false;
}

void AnimationObject::Playing(string animName)
{
	isPlaying = true;

	imagePosVec = DM::GetAnimRect(animName);
	thread t(&AnimationObject::_Playing, this);
	t.detach();
}
