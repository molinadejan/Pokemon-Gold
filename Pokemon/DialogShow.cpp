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

	memset(buffer1, 0, sizeof(buffer1));
	memset(buffer2, 0, sizeof(buffer2));
}

// -1 : 아직 진행중
// 나머지는 남은 대화의 수
// 다른 클래스에서 값을 받아 각각한 처리를 해주면 됩니다.
int DialogShow::UpdateDlg()
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

			return texts.size() - textIdx;
		}
	}

	return -1;
}

void DialogShow::Draw(Graphics& g)
{
	StringFormat fm;
	fm.SetAlignment(StringAlignmentNear);
	fm.SetLineAlignment(StringAlignmentCenter);

	SolidBrush black(Color(255, 0, 0, 0));

	g.DrawString(buffer2, -1, DM::GetFontB(), rect, &fm, &black);
}
