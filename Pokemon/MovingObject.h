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

	bool isPlaying;

	bool twinkleSwitch;

private:

	void _Moving(PointF target, float time);
	void _Twinkling();
	void _AttackMotion(int dir);

public:

	MovingObject();
	MovingObject(Image* _image, PointF _pos, Point _screenSize, Rect _imagePos);

	void SetPos(float _x, float _y);
	void SetScreenSize(int _w, int _h);
	void SetImage(Image* _image);
	void SetImagePos(Rect _rect);

	virtual void Draw(Graphics& g);

	bool IsPlaying();

	void Moving(PointF target, float time);
	void Twinkling();
	void AttackMotion(int dir);

	void _FallDown();
	void FallDown();
};

#endif // !__ANIMATIONOBJECT_H__
