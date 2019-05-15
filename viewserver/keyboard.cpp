#include "keyboard.h"

Keyboard::Keyboard()
{

}

Keyboard& Keyboard::getInstance()
{
	static Keyboard instance;	// Guaranteed to be destroyed.
								// Instantiated on first use.
	return instance;
}

void Keyboard::downKey(UINT vk)
{
	keys[vk] = true;
}

void Keyboard::upKey(UINT vk)
{
	keys[vk] = false;
}

bool Keyboard::getKeyState(UINT vk)
{
	return keys[vk];
}