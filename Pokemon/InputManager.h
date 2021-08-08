#pragma once

#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include <wtypes.h> // USE DWORD

class InputManager
{
private:

	class Input
	{
		friend InputManager;

	private:

		Input();
		~Input() = default;

		void Reset();
		void Update();

	private:
		bool is_key_up;
		bool is_key_down;
		bool is_key_left;
		bool is_key_right;

		bool is_key_z;
		bool is_key_x;
		bool is_key_enter;
	};

private:

	static Input s_MainInput;

public:

	static bool GetUp();
	static bool GetDown();
	static bool GetLeft();
	static bool GetRight();
	static bool GetZ();
	static bool GetX();
	static bool GetEnter();

	static int GetHorizontal();
	static int GetVertical();
	static void Update();
	static void Reset();

	static bool GetKeyUp(int _key);
};

#define IM        InputManager

#define GET_KEY_Z     InputManager::GetKeyUp('Z')
#define GET_KEY_X     InputManager::GetKeyUp('X')
#define GET_KEY_ENTER InputManager::GetKeyUp(VK_RETURN)
#define GET_KEY_UP    InputManager::GetKeyUp(VK_UP)
#define GET_KEY_DOWN  InputManager::GetKeyUp(VK_DOWN)
#define GET_KEY_LEFT  InputManager::GetKeyUp(VK_LEFT)
#define GET_KEY_RIGHT InputManager::GetKeyUp(VK_RIGHT)

#define GET_KEY_HORIZONTAL InputManager::GetHorizontal()
#define GET_KEY_VERTICAL   InputManager::GetVertical()

#endif // !__IN
