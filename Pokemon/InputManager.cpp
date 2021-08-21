#include "InputManager.h"

InputManager::Input InputManager::input = InputManager::Input();

void InputManager::Input::Init()
{
	is_key_up = false;
	is_key_down = false;
	is_key_left = false;
	is_key_right = false;
}

void InputManager::Input::Update()
{
	Init();

	DWORD newTime = GetTickCount();
	static DWORD oldTime = newTime;

	if (newTime - oldTime < 32)
		return;

	oldTime = newTime;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		is_key_left = true;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		is_key_right = true;

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		is_key_down = true;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		is_key_up = true;
}

int InputManager::GetHorizontal()
{
	int ret = 0;

	if (input.is_key_left)
		ret = -1;
	else if (input.is_key_right)
		ret = 1;

	return ret;
}

int InputManager::GetVertical()
{
	if (input.is_key_left || input.is_key_right)
		return 0;

	int ret = 0;

	if (input.is_key_up)
		ret = -1;
	else if (input.is_key_down)
		ret = 1;

	return ret;
}
