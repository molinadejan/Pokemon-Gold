#include "RunManager.h"
#include "InputManager.h"
#include "MyUtils.h"
#include "DataLoadManager.h"
#include "Timer.h"
#include <thread>
#include <chrono>
#include <mutex>

using std::thread;
using namespace std::chrono;

RunManager::Run RunManager::run = RunManager::Run();
float RunManager::tp = 0.0f;

RunManager::Run::Run() 
	: target(NULL), oldTarget(NULL), isChange(false), isFading(false)
{ }
RunManager::Run::~Run() { }

void RunManager::Run::setFunc()
{
	auto funcUpdate = &BaseClass::Update;
	update = static_cast<void(BaseClass::*)()>(funcUpdate);

	auto funcDraw = &BaseClass::Draw;
	draw = static_cast<void(BaseClass::*)(Graphics&)>(funcDraw);
}

void RunManager::Run::_setTarget(BaseClass * _base, float _fadeTime)
{
	double timer = 0.0f;
	double half = _fadeTime / 2;
	bool check = false;

	auto prevClock = high_resolution_clock::now();

	std::mutex m;



	while (timer < _fadeTime)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		timer += deltaTime;

		if (timer < half)
		{
			tp = timer / half * 255;
		}
		else
		{
			if (!check)
			{
				m.lock();

				check = true;
				
				oldTarget = target;

				target = _base;
				target->Init();
				setFunc();

				if (oldTarget != NULL)
					oldTarget->Reset();

				isChange = false;

				m.unlock();
			}

			tp = (1 - (timer - half) / half) * 255;
			tp = tp < 0.0f ? 0.0f : tp;
		}
		
		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 80 - (frameClock - nextClock).count() / 1e9;

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	isFading = false;
}

void RunManager::Run::setTarget(BaseClass * _base, float _fadeTime)
{
	if (!isFading)
	{
		isChange = true;
		isFading = true;

		thread t(&RunManager::Run::_setTarget, this, _base, _fadeTime);
		t.detach();
	}
}

void RunManager::Run::reset()
{
	update = NULL;
	draw = NULL;
	target = NULL;
	oldTarget = NULL;
}

void RunManager::Reset()
{
	run.reset();
}

void RunManager::SetTarget(BaseClass * _base, float _fadeTime)
{
	run.setTarget(_base, _fadeTime);
}

void RunManager::SetTargetWithoutFade(BaseClass* _base)
{
	if(run.target != NULL)
		run.target->Reset();

	run.target = _base;
	run.target->Init();
	run.setFunc();
}

void RunManager::Update()
{
	if (run.target == NULL)
		return;

	if(!run.isChange)
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

	if (run.isFading)
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
