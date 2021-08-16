#pragma once

#ifndef __INTRO_H_
#define __INTRO_H_

#include "BaseClass.h"
#include "CSound.h"

class Intro : public BaseClass
{
private:

	Image* introImg;

	float backgroundTimer;
	float turquiseTimer;
	int cloudPosX;

	vector<Rect> turquoiseVec;
	int turquiseFrameCnt;

	PointF particles[5] = { PointF(R(5 * MUL), R(3.5 * MUL)), PointF(R(5 * MUL), R(4 * MUL)) , PointF(R(5 * MUL), R(5 * MUL)) , PointF(R(4 * MUL), R(5 * MUL)), PointF(R(4.5f* MUL), R(5 * MUL)) };
	PointF pos[5];
	PointF dirs[5] = {PointF(R(0.77f), R(0.63f)), PointF(R(0.83f), R(0.54f)), PointF(R(0.74f), R(0.67f)), PointF(R(0.7f), R(0.7f)), PointF(R(0.44f), R(0.89f))};

private:

	const Rect TitleRect = {0, 0, 10 * MUL, 6 * MUL};
	const Rect CompanyRect = {0, 8 * MUL, 10 * MUL, MUL};
	const Rect CloudRect = {0, 6 * MUL, 10 * MUL, 2 * MUL};
	const Rect turquiseRect = { 3 * MUL, 3 * MUL, 4 * MUL, 4 * MUL };

public:

	Intro();

	void Init() override;
	void Reset() override;

	void Update() override;
	void Draw(Graphics& g) override;
};

#endif // !__INTRO_H_

