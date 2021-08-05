#include "RunManager.h"
#include "InputManager.h"
#include "MyUtils.h"
#include "DataLoadManager.h"

RunManager::Run RunManager::run = RunManager::Run();

RunManager::Run::Run() { }
RunManager::Run::~Run() { }

void RunManager::Run::reset()
{
	update = NULL;
	draw = NULL;
	target = NULL;
}

void RunManager::Reset()
{
	run.reset();
}

void RunManager::SetTarget(BaseClass * _base)
{
	run.target = _base;

	auto funcUpdate = &BaseClass::Update;
	run.update = static_cast<void(BaseClass::*)()>(funcUpdate);

	auto funcDraw = &BaseClass::Draw;
	run.draw = static_cast<void(BaseClass::*)(Graphics&)>(funcDraw);
}

void RunManager::Update()
{
	if (run.target == NULL)
		return;

	(run.target->*(run.update))();
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

	BitBlt(hdc, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);

	EndPaint(hWnd, &ps);
}
