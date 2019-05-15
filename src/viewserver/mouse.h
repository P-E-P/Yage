#pragma once

#include <Windows.h>

class Mouse
{
private:
	UINT keyFlags;
	int mouseX, mouseY;
	Mouse();
public:

	static Mouse& getInstance();
	~Mouse();

	Mouse(Mouse const&) = delete;
	void operator=(Mouse const&) = delete;
	UINT getButtonState() const;
	int getX() const;
	int getY() const;

	void setCoords(int x, int y);
	void setKeyFlags(UINT keyFlags);
};

