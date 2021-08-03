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

#endif // !__IN
