#include "AnimationObject.h"
#include "Timer.h"

AnimationObject::AnimationObject()
	: MovingObject(), frameTime(0.1f), frameTimer(0.0f), frameCount(0)
{ }

AnimationObject::AnimationObject(Image * _image, PointF _pos, Point _screenSize, vector<Rect> _imagePosVec)
	: MovingObject(_image, _pos, _screenSize, Rect(0, 0, 0, 0)), imagePosVec(_imagePosVec), frameTime(0.1f), frameTimer(0.0f), frameCount(0)
{ }

void AnimationObject::Reset()
{
	frameCount = 0;
}

int AnimationObject::GetRemainCount()
{
	return (int)imagePosVec.size() - frameCount;
}

void AnimationObject::SetImagePosVec(vector<Rect> _imagePosVec)
{
	imagePosVec = _imagePosVec;
}

void AnimationObject::Update()
{
	if (isPlaying)
	{
		frameTimer += Timer::DeltaTime();

		if (frameTimer >= frameTime)
		{
			++frameCount;
			frameTimer = 0.0f;

			if (frameCount == (int)imagePosVec.size())
			{
				--frameCount;
				isPlaying = false;
			}
		}
	}
}

void AnimationObject::Draw(Graphics & g)
{
	Rect& curRect = imagePosVec[frameCount];
	g.DrawImage(image, Rect(pos.X, pos.Y, screenSize.X, screenSize.Y), curRect.X, curRect.Y, curRect.Width, curRect.Height, UnitPixel);
}
