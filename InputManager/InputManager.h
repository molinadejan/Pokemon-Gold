#pragma once

#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

class InputManager
{
private:

	bool up;
	bool down;
	bool left;
	bool right;
	bool space;

	void CheckKeyboardInput();

public:

	void Update();

	bool GetUp() const;
	bool GetDown() const;
	bool GetLeft() const;
	bool GetRight() const;
	bool GetSpace() const;

	int  GetHorizontal() const;
	int  GetVertical() const;

	static bool GetKeyDown(int key);
	static bool GetKeyUp(int key);
	static bool GetKeyHold(int key);
};

#endif // !__IN