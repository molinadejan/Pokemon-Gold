#pragma once

#ifndef __DIALOGSHOW_H__
#define __DIALOGSHOW_H__

#include "framework.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

using namespace Gdiplus;

class DialogShow 
{
private:

	const float FRAME_TIME = 0.05f;
	const float WAITING_TIME = 0.1f;
	const RectF dialogRect = { REAL(0.5f * MUL), REAL(6.1f * MUL), REAL(9 * MUL), REAL(3 * MUL) };

private:

	vector<string> texts;

	int textLen;
	int textIdx;

	float frameTimer;
	float waitingTimer;

	TCHAR buffer1[128];
	TCHAR buffer2[128];

	bool isPlaying;
	bool isAuto;
	bool isWaiting;

public:

	DialogShow() = default;
	~DialogShow() = default;

	void Reset();
	void Push(string text);
	int RemainCount();

	void SetIsAuto(bool _isAuto);
	bool IsAuto();

	bool IsPlaying();

	void Start();
	void Update();
	void Draw(Graphics& g);
};

#endif // !__DIALOGSHOW_H__
