#pragma once

#include <Windows.h>

class Keyboard
{
private:
	bool keys[0xFE];
	Keyboard();
public:
	static Keyboard& getInstance();
	void upKey(UINT vk);
	void downKey(UINT vk);

	bool getKeyState(UINT vk);

	Keyboard(Keyboard const&) = delete;
	void operator=(Keyboard const&) = delete;
};

