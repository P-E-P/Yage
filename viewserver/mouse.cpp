#include "mouse.h"



Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

Mouse& Mouse::getInstance()
{
	// Guaranteed to be destroyed.
	// Instantiated on first use.
	static Mouse instance;
						
	return instance;
}

UINT Mouse::getButtonState() const
{
	return keyFlags;
}

int Mouse::getX() const
{
	return mouseX;
}

int Mouse::getY() const
{
	return mouseY;
}

void Mouse::setCoords(int mouseX, int mouseY)
{
	this->mouseX = mouseX;
	this->mouseY = mouseY;
}

void Mouse::setKeyFlags(UINT keyflags)
{
	this->keyFlags = keyFlags;
}