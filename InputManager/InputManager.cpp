#include "pch.h"
#include "framework.h"
#include "InputManager.h"

void InputManager::CheckKeyboardInput()
{
	up = false;
	down = false;
	left = false;
	right = false;
	space = false;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		space = true;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		left = true;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		right = true;

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		down = true;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		up = true;
}

void InputManager::Update()
{
	DWORD newTime = GetTickCount();
	static DWORD oldTime = newTime;

	if (newTime - oldTime < 16)
		return;

	oldTime = newTime;

	CheckKeyboardInput();
}

bool InputManager::GetUp() const
{
	return up;
}

bool InputManager::GetDown() const
{
	return down;
}

bool InputManager::GetLeft() const
{
	return left;
}

bool InputManager::GetRight() const
{
	return right;
}

bool InputManager::GetSpace() const
{
	return space;
}

int InputManager::GetHorizontal() const
{
	int ret = 0;

	if (left)
		ret = -1;
	else if (right)
		ret = 1;

	return ret;
}

int InputManager::GetVertical() const
{
	int ret = 0;

	if (up)
		ret = -1;
	else if (down)
		ret = 1;

	return ret;
}

bool InputManager::GetKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	return false;
}

bool InputManager::GetKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x0001)
		return true;

	return false;
}

bool InputManager::GetKeyHold(int key)
{
	if (GetAsyncKeyState(key) & 0x8001)
		return true;

	return false;
}
