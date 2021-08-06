#include "DialogShow.h"
#include "DataLoadManager.h"
#include "Timer.h"

DialogShow::DialogShow() { }

void DialogShow::Init(vector<string> _dialogText, RectF _rect)
{
	texts = _dialogText;
	rect = _rect;

	textIdx = 0;
	textLen = 1;
}

// 출력할 대화가 끝났다는 의미로 true를 반환합니다.
// false 면 출력할 대화가 남아있지만 잠시 멈춘 상태
// 다른 클래스에서 이에 대한 처리를 해주면 됩니다.
bool DialogShow::UpdateDlg()
{
	frameTimer -= Timer::DeltaTime();

	if (frameTimer <= 0.0f)
	{
		++textLen;
		frameTimer = FRAME_LIMIT;

		int len = texts[textIdx].size();

		_tcscpy_s(buffer1, CA2T(texts[textIdx].c_str()));
		_tcsncpy_s(buffer2, buffer1, textLen);

		if (textLen == len)
		{
			++textIdx;
			textLen = 1;

			if (textIdx == texts.size())
				return true;
		}
	}

	return false;
}

void DialogShow::Draw(Graphics& g)
{
	//g.DrawString(buffer, -1, fontB, rect, leftAlign, black);
}
