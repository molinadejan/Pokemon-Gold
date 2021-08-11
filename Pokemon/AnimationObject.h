#pragma once

#ifndef __ANIMATIONOBJECT_H__
#define __ANIMATIONOBJECT_H__

#include "MovingObject.h"
#include <vector>

using std::vector;

class AnimationObject : public MovingObject
{
private:

	float frameTime;
	float frameTimer;

	int frameCount;
	vector<Rect> imagePosVec;

public:

	AnimationObject();
	AnimationObject(Image* _image, PointF _pos, Point _screenSize, vector<Rect> _imagePosVec);

	void SetImagePosVec(vector<Rect> _imagePosVec);
	void Update();
	void Reset();
	int GetRemainCount();
	void Draw(Graphics &g) override;
};

#endif // !__ANIMATIONOBJECT_H__
