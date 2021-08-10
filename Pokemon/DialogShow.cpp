#include "DialogShow.h"
#include "DataLoadManager.h"
#include "GdiplusElement.h"
#include "Timer.h"

DialogShow::DialogShow() : isPlaying(false) { }

void DialogShow::Reset()
{
	texts.clear();

	textIdx = 0;
	textLen = 1;

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

bool DialogShow::IsPlaying()
{
	return isPlaying;
}

void DialogShow::Start()
{
	isPlaying = true;
}

// -1 : 아직 진행중
// 나머지는 남은 대화의 수
// 다른 클래스에서 값을 받아 각각한 처리를 해주면 됩니다.
void DialogShow::Update()
{
	if (isPlaying)
	{
		frameTimer -= Timer::DeltaTime();

		if (frameTimer <= 0.0f)
		{
			++textLen;
			frameTimer = FRAME_LIMIT;

			int len = int(texts[textIdx].size());

			_tcscpy_s(buffer1, CA2T(texts[textIdx].c_str()));
			_tcsncpy_s(buffer2, buffer1, textLen);

			if (textLen == len)
			{
				++textIdx;
				textLen = 1;
				isPlaying = false;
			}
		}
	}
}

void DialogShow::Draw(Graphics& g)
{
	g.DrawString(buffer2, -1, FONT_BIG, dialogRect, LEFT_ALIGN, BLACK);
}
