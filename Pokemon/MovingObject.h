#pragma once

#ifndef __MOVINGOBJECT_H__
#define __MOVINGOBJECT_H__

#include "framework.h"

using namespace Gdiplus;

class MovingObject
{
protected:

	Image* image;
	
	PointF pos;
	Point screenSize;
	Rect imagePos;

	PointF dir;

	bool isPlaying;
	bool isTwinkle;

	float timer;
	float time;

	PointF dest;

	int twinkleCnt;

public:

	MovingObject();
	MovingObject(Image* _image, PointF _pos, Point _screenSize, Rect _imagePos);

	void SetPos(float _x, float _y);
	void SetScreenSize(int _w, int _h);
	void SetImage(Image* _image);
	void SetImagePos(Rect _rect);

	bool IsPlaying();
	bool IsTwinkle();

	virtual void Draw(Graphics& g);

	void Start();

	void Twinkle();
	void TwinkleStart();

	void MoveToInit(PointF dest, float time);
	void MoveTo();
};

#endif // !__ANIMATIONOBJECT_H__
