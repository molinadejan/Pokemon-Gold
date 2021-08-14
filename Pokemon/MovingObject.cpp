#include "MovingObject.h"
#include "Timer.h"

MovingObject::MovingObject()
	: image(NULL), pos{ 0, 0 }, screenSize{ 0, 0 }, imagePos{ 0,0,0,0 }, dir{ 0, 0 }, isPlaying(false), timer(0), time(0), dest{ 0, 0 }
{ }

MovingObject::MovingObject(Image * _image, PointF _pos, Point _screenSize, Rect _imagePos)
	: image(_image), pos(_pos), screenSize(_screenSize), imagePos(_imagePos), dir{ 0, 0 }, isPlaying(false), timer(0), time(0), dest{ 0, 0 } 
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

bool MovingObject::IsTwinkle()
{
	return isTwinkle;
}

void MovingObject::Draw(Graphics & g)
{
	if (isTwinkle && twinkleCnt % 2 == 1)
		return;

	g.DrawImage(image, Rect(pos.X, pos.Y, screenSize.X, screenSize.Y), imagePos.X, imagePos.Y, imagePos.Width, imagePos.Height, UnitPixel);
}

void MovingObject::Start()
{
	isPlaying = true;
}

void MovingObject::Twinkle()
{
	if (isTwinkle)
	{
		timer += Timer::DeltaTime();

		if (timer >= time)
		{
			timer = 0.0f;
			++twinkleCnt;

			if (twinkleCnt == 10)
				isTwinkle = false;
		}
	}
}

void MovingObject::TwinkleStart()
{
	isTwinkle = true;
	time = 0.07f;
	timer = 0.0f;
	twinkleCnt = 0;
}

void MovingObject::MoveToInit(PointF _dest, float _time)
{
	dest = _dest;
	time = _time;
	timer = 0.0f;

	dir.X = (dest.X - pos.X) / time;
	dir.Y = (dest.Y - pos.Y) / time;
}

void MovingObject::MoveTo()
{
	if (isPlaying)
	{
		timer += Timer::DeltaTime();

		pos.X += dir.X * Timer::DeltaTime();
		pos.Y += dir.Y * Timer::DeltaTime();

		if (timer >= time)
		{
			pos = dest;
			timer = 0.0f;
			isPlaying = false;
		}
	}
}
