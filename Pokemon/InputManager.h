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

		Input() = default;
		~Input() = default;

		void Init();
		void Update();

	private:
		bool is_key_up;
		bool is_key_down;
		bool is_key_left;
		bool is_key_right;
	};

private:

	static Input input;

	InputManager() = delete;
	~InputManager() = delete;

public:

	static int GetHorizontal();
	static int GetVertical();

	static void Update() { input.Update(); }
	static void Init() { input.Init(); }

	static bool GetKeyUp(int _key) { return GetAsyncKeyState(_key) & 0x0001 ? true : false; }
};

#define IM            InputManager

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
