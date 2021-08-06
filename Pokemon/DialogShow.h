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

	float FRAME_LIMIT = 0.05f;

private:

	vector<string> texts;
	RectF rect;

	int textLen;
	int textIdx;

	float frameTimer;

	TCHAR buffer1[256];
	TCHAR buffer2[256];

public:

	DialogShow();
	~DialogShow() = default;

	void Init(vector<string> _dialogText, RectF _rect);

	bool UpdateDlg();
	void Draw(Graphics& g);
};

#endif // !__DIALOGSHOW_H__
