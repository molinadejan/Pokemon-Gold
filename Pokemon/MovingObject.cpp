#include "MovingObject.h"
#include "Timer.h"
#include <thread>
#include <chrono>

using std::thread;
using namespace std::chrono;

MovingObject::MovingObject()
	: image(NULL), pos{ 0, 0 }, screenSize{ 0, 0 }, imagePos{ 0,0,0,0 }, isPlaying(false), twinkleSwitch(false)
{ }

MovingObject::MovingObject(Image * _image, PointF _pos, Point _screenSize, Rect _imagePos)
	: image(_image), pos(_pos), screenSize(_screenSize), imagePos(_imagePos), isPlaying(false)
{ }

void MovingObject::SetPos(float _x, float _y)
{
	pos = { _x, _y };
}

void MovingObject::SetScreenSize(int _w, int _h)
{
	screenSize = { _w, _h };
}

void MovingObject::SetImage(Image* _image)
{
	image = _image;
}

void MovingObject::SetImagePos(Rect _rect)
{
	imagePos = _rect;
}

bool MovingObject::IsPlaying()
{
	return isPlaying;
}

void MovingObject::Draw(Graphics & g)
{
	if(!twinkleSwitch)
		g.DrawImage(image, Rect(INT(pos.X), INT(pos.Y), screenSize.X, screenSize.Y), imagePos.X, imagePos.Y, imagePos.Width, imagePos.Height, UnitPixel);
}

void MovingObject::_Moving(PointF target, float time)
{
	PointF dir = target - pos;

	dir.X /= time;
	dir.Y /= time;

	double timer = 0.0f;

	auto prevClock = high_resolution_clock::now();

	while (true)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		timer += deltaTime;

		pos.X += dir.X * float(deltaTime);
		pos.Y += dir.Y * float(deltaTime);

		if (timer >= time)
			break;

		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 80 - (frameClock - nextClock).count() / 1e9;

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	pos = target;

	isPlaying = false;
}

void MovingObject::Moving(PointF target, float time)
{
	isPlaying = true;

	thread t(&MovingObject::_Moving, this, target, time);
	t.detach();
}

void MovingObject::_Twinkling()
{
	double frameTimer = 0.0;
	int twinkleCnt = 0;

	auto prevClock = high_resolution_clock::now();

	while (twinkleCnt < 10)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		frameTimer += deltaTime;

		if (frameTimer >= 0.05f)
		{
			frameTimer = 0.0f;
			++twinkleCnt;

			twinkleSwitch = !twinkleSwitch;
		}

		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 80 - (frameClock - nextClock).count() / 1e9;

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	isPlaying = false;
}

void MovingObject::Twinkling()
{
	isPlaying = true;
	
	thread t(&MovingObject::_Twinkling, this);
	t.detach();
}

void MovingObject::_AttackMotion(int dir)
{
	PointF curPos = pos;

	double frameTimer = 0.0f;
	double speed = 500.0f;

	bool check = false;

	auto prevClock = high_resolution_clock::now();

	while (frameTimer < 0.2f)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		frameTimer += deltaTime;

		if (frameTimer >= 0.1f && !check)
		{
			check = true;
			dir *= -1;
		}

		pos.X += float(deltaTime * speed * dir);

		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 80 - (frameClock - nextClock).count() / 1e9;

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	pos = curPos;

	isPlaying = false;
}

void MovingObject::AttackMotion(int dir)
{
	isPlaying = true;

	thread t(&MovingObject::_AttackMotion, this, dir);
	t.detach();
}

void MovingObject::_FallDown()
{
	int curY = INT(pos.Y);
	int targetY = INT(pos.Y + screenSize.Y);

	auto prevClock = high_resolution_clock::now();

	while (pos.Y < targetY)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		pos.Y += 16;
		screenSize.Y -= 16;

		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 80 - (frameClock - nextClock).count() / 1e9;

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	pos.Y = float(targetY);

	isPlaying = false;
}

void MovingObject::FallDown()
{
	isPlaying = true;

	thread t(&MovingObject::_FallDown, this);
	t.detach();
}
