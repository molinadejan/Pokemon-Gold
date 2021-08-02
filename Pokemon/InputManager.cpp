#include "InputManager.h"

InputManager::Input InputManager::s_MainInput = InputManager::Input();

InputManager::Input::Input()
{
	Reset();
}

void InputManager::Input::Reset()
{
	is_key_up = false;
	is_key_down = false;
	is_key_left = false;
	is_key_right = false;

	is_key_z = false;
	is_key_x = false;
	is_key_enter = false;
}

void InputManager::Input::Update()
{
	Reset();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		is_key_left = true;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		is_key_right = true;

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		is_key_down = true;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		is_key_up = true;


	if (GetAsyncKeyState('Z') & 0x8000)
		is_key_z = true;

	if (GetAsyncKeyState('X') & 0x8000)
		is_key_x = true;

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		is_key_enter = true;
}

bool InputManager::GetUp()
{
	return s_MainInput.is_key_up;
}

bool InputManager::GetDown()
{
	return s_MainInput.is_key_down;
}

bool InputManager::GetLeft()
{
	return s_MainInput.is_key_left;
}

bool InputManager::GetRight()
{
	return s_MainInput.is_key_right;
}

bool InputManager::GetZ()
{
	return s_MainInput.is_key_z;
}

bool InputManager::GetX()
{
	return s_MainInput.is_key_x;
}

bool InputManager::GetEnter()
{
	return s_MainInput.is_key_enter;
}

int InputManager::GetHorizontal()
{
	int ret = 0;

	if (s_MainInput.is_key_left)
		ret = -1;
	else if (s_MainInput.is_key_right)
		ret = 1;

	return ret;
}

int InputManager::GetVertical()
{
	if (s_MainInput.is_key_left || s_MainInput.is_key_right)
		return 0;

	int ret = 0;

	if (s_MainInput.is_key_up)
		ret = -1;
	else if (s_MainInput.is_key_down)
		ret = 1;

	return ret;
}

void InputManager::Update()
{
	s_MainInput.Update();
}

void InputManager::Reset()
{
	s_MainInput.Reset();
}
