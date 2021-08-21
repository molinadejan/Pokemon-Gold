#pragma once

#ifndef __ANIMATIONOBJECT_H__
#define __ANIMATIONOBJECT_H__

#include "MovingObject.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class AnimationObject : public MovingObject
{
private:

	int frameCnt;
	vector<Rect>* imagePosVec;

public:

	AnimationObject();

	void Draw(Graphics &g) override;

	void _Playing();
	void Playing(string animName);
};

#endif // !__ANIMATIONOBJECT_H__
