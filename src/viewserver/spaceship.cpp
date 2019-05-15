#include "spaceship.h"


Spaceship::Spaceship(XMFLOAT3 position,
	XMFLOAT3 scaling, Renderer* renderer) : Model(position, scaling, "alduin.obj", L"alduin.jpg", L"shader.fx", renderer)
{
	setUnitPerSec(5.5f);
}


Spaceship::~Spaceship()
{
}

void Spaceship::onTick()
{
	Model::onTick();
}

void Spaceship::onMove()
{
	/* Doesn't this code with delta time add input lag?
	 * // TODO: Check input lag on a powerful machine
	 */

#define DELTA 0.1f
	 /*
	 if (Keyboard::getInstance().getKeyState(VK_UP)) {
		 XMStoreFloat4x4(&position, XMLoadFloat4x4(&position) * XMMatrixTranslation(0.0f, DELTA, 0.0f));
	 }
	 if (Keyboard::getInstance().getKeyState(VK_DOWN)) {
		 XMStoreFloat4x4(&position, XMLoadFloat4x4(&position) * XMMatrixTranslation(0.0f, -DELTA, 0.0f));
	 }
	 if (Keyboard::getInstance().getKeyState(VK_RIGHT)) {
		 XMStoreFloat4x4(&position, XMLoadFloat4x4(&position) * XMMatrixTranslation(DELTA, 0.0f, 0.0f));
	 }
	 if (Keyboard::getInstance().getKeyState(VK_LEFT)) {
		 XMStoreFloat4x4(&position, XMLoadFloat4x4(&position) * XMMatrixTranslation(-DELTA, 0.0f, 0.0f));
	 }*/

	if (Keyboard::getInstance().getKeyState('W')) {
		XMStoreFloat4x4(&position, XMLoadFloat4x4(&position) * XMMatrixTranslation(0.0f, getPYDeltaPos(), 0.0f));
	}
	if (Keyboard::getInstance().getKeyState('S')) {
		XMStoreFloat4x4(&position, XMLoadFloat4x4(&position) * XMMatrixTranslation(0.0f, -getPYDeltaPos(), 0.0f));
	}
	if (Keyboard::getInstance().getKeyState('D')) {
		XMStoreFloat4x4(&position, XMLoadFloat4x4(&position) * XMMatrixTranslation(getPXDeltaPos(), 0.0f, 0.0f));
	}
	if (Keyboard::getInstance().getKeyState('A')) {
		XMStoreFloat4x4(&position, XMLoadFloat4x4(&position) * XMMatrixTranslation(-getPXDeltaPos(), 0.0f, 0.0f));
	}
	//Scale up
	if (Keyboard::getInstance().getKeyState('J')) {
		XMStoreFloat4x4(&scaling, XMMatrixScaling(0.003f, 0.003f, 0.003f));
	}

	//Scale down
	if (Keyboard::getInstance().getKeyState('K')) {
		XMStoreFloat4x4(&scaling, XMMatrixScaling(0.001f, 0.001f, 0.001f));
	}

}
