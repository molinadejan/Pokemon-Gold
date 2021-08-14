#include "RunManager.h"
#include "InputManager.h"
#include "MyUtils.h"
#include "DataLoadManager.h"
#include "Timer.h"

RunManager::Run RunManager::run = RunManager::Run();
bool RunManager::isSceneChange = false;
float RunManager::sceneChangeTimer = 0.0f;
float RunManager::tp = 0.0f;
float RunManager::fadeSpeed;

RunManager::Run::Run() { }
RunManager::Run::~Run() { }

void RunManager::Run::reset()
{
	update = NULL;
	draw = NULL;
	target = NULL;
	newTarget = NULL;

	isSceneChange = false;
	sceneChangeTimer = 0.0f;
}

void RunManager::SetFunc()
{
	auto funcUpdate = &BaseClass::Update;
	run.update = static_cast<void(BaseClass::*)()>(funcUpdate);

	auto funcDraw = &BaseClass::Draw;
	run.draw = static_cast<void(BaseClass::*)(Graphics&)>(funcDraw);
}

void RunManager::Reset()
{
	run.reset();
}

void RunManager::SetTarget(BaseClass * _base, float _fadeSpeed)
{
	if (run.target == NULL)
	{
		run.target = _base;
		run.target->Init();
		SetFunc();
	}
	else
	{
		fadeSpeed = _fadeSpeed;
		sceneChangeTimer = 0.0f;
		isSceneChange = true;
		run.newTarget = _base;
	}
}

void RunManager::SetTargetWithoutFade(BaseClass* _base)
{
	run.target->Reset();
	run.target = _base;
	run.target->Init();
	SetFunc();
}

void RunManager::Update()
{
	if (run.target == NULL)
		return;

	if (isSceneChange)
	{
		tp += Timer::DeltaTime() * fadeSpeed;

		if (tp >= 255.0f)
		{
			tp = 255.0f;
			fadeSpeed *= -1;

			run.target->Reset();
			run.target = run.newTarget;
			SetFunc();
			run.target->Init();
		}
		else if (tp <= 0.0f)
		{
			tp = 0.0f;
			isSceneChange = false;
			fadeSpeed *= -1;
		}
	}
	else (run.target->*(run.update))();
}

void RunManager::Draw(HWND hWnd)
{
	if (run.target == NULL)
		return;

	HDC hdc, memDC;
	HBITMAP oldBit, newBit;

	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics graphic(memDC);

	// ÇÈ¼¿ Èå·ÁÁü ¹æÁö
	graphic.SetInterpolationMode(InterpolationMode::InterpolationModeNearestNeighbor);
	graphic.SetPixelOffsetMode(PixelOffsetMode::PixelOffsetModeHalf);

	(run.target->*(run.draw))(graphic);

	if (isSceneChange)
	{
		SolidBrush brush(Color((int)tp, 248, 248, 248));
		graphic.FillRectangle(&brush, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	}

	BitBlt(hdc, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);

	EndPaint(hWnd, &ps);
}
