#include "DialogShow.h"
#include "DataLoadManager.h"
#include "GdiplusElement.h"
#include "Timer.h"

void DialogShow::Reset()
{
	texts.clear();

	textIdx = 0;
	textLen = 1;

	isAuto = false;
	isPlaying = false;

	memset(buffer1, 0, sizeof(buffer1));
	memset(buffer2, 0, sizeof(buffer2));
}

void DialogShow::Push(string text)
{
	texts.push_back(text);
}

int DialogShow::RemainCount()
{
	return (int)texts.size() - textIdx;
}

void DialogShow::SetIsAuto(bool _isAuto)
{
	isAuto = _isAuto;
}

bool DialogShow::IsAuto()
{
	return isAuto;
}

bool DialogShow::IsPlaying()
{
	return isPlaying || isWaiting;
}

void DialogShow::Start()
{
	isWaiting = false;
	isPlaying = true;

	waitingTimer = 0.0f;
	frameTimer = 0.0f;
}

void DialogShow::Update()
{
	if (isWaiting)
	{
		waitingTimer += Timer::DeltaTime();

		if (waitingTimer >= WAITING_TIME)
		{
			waitingTimer = 0.0f;
			isWaiting = false;
		}
	}
	else if (isPlaying)
	{
		frameTimer += Timer::DeltaTime();

		if (frameTimer >= FRAME_TIME)
		{
			++textLen;
			frameTimer = 0.0f;

			int len = int(texts[textIdx].size());

			_tcscpy_s(buffer1, CA2T(texts[textIdx].c_str()));
			_tcsncpy_s(buffer2, buffer1, textLen);

			if (textLen == len)
			{
				++textIdx;
				textLen = 1;

				if (isAuto && textIdx < (int)texts.size())
					isPlaying = true;
				else
					isPlaying = false;

				isWaiting = true;
			}
		}
	}
	
}

void DialogShow::Draw(Graphics& g)
{
	g.DrawString(buffer2, -1, FONT_BIG, dialogRect, LEFT_ALIGN, BLACK);
}
