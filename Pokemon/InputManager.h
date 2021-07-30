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

		Input()
		{
			Reset();
		}

		~Input() = default;

		void Reset()
		{
			is_key_up = false;
			is_key_down = false;
			is_key_left = false;
			is_key_right = false;

			is_key_z = false;
			is_key_x = false;
			is_key_enter = false;
		}

		void Update()
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

	static bool GetUp   () { return s_MainInput.is_key_up;   }
	static bool GetDown () { return s_MainInput.is_key_down; }
	static bool GetLeft () { return s_MainInput.is_key_left; }
	static bool GetRight() { return s_MainInput.is_key_right;}
	static bool GetZ    () { return s_MainInput.is_key_z;    }
	static bool GetX    () { return s_MainInput.is_key_x;    }
	static bool GetEnter() { return s_MainInput.is_key_enter;}

	static int GetHorizontal() 
	{
		int ret = 0;

		if (s_MainInput.is_key_left)
			ret = -1;
		else if(s_MainInput.is_key_right)
			ret = 1;

		return ret;
	}

	static int GetVertical()
	{
		int ret = 0;

		if (s_MainInput.is_key_up)
			ret = -1;
		else if(s_MainInput.is_key_down)
			ret = 1;

		return ret;
	}

	static void Update  () { s_MainInput.Update();           }

	static void Reset   () { s_MainInput.Reset();            }
};

#endif // !__IN
