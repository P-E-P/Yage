#pragma once

#include <chrono>

#include "Entity.h"
#include "keyboard.h"
#include "mouse.h"
class Mob :
	virtual public Entity
{
private:
	// The amount of unit the model should de translated each sec.
	float unitPerSecPX, unitPerSecPY, unitPerSecPZ;
	float unitPerSecNX, unitPerSecNY, unitPerSecNZ;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastTickTime;
	std::chrono::duration<float> deltaTime;
protected:
	// Speed variables
	XMFLOAT4X4 sPosition, sRotation, sScaling;
	// Acceleration variables
	XMFLOAT4X4 aPosition, aRotation, aScaling;
public:
	virtual void onTick() = 0;
	void preTick();
	void postTick();
	virtual void tick();

	float getPXDeltaPos();
	float getPYDeltaPos();
	float getPZDeltaPos();

	float getNXDeltaPos();
	float getNYDeltaPos();
	float getNZDeltaPos();

	float getUnitPerSecPX() const;
	float getUnitPerSecPY() const;
	float getUnitPerSecPZ() const;
	float getUnitPerSecNX() const;
	float getUnitPerSecNY() const;
	float getUnitPerSecNZ() const;

	void setUnitPerSec(float units);

	void move();
	void preMove();
	void postMove();
	virtual void onMove();
};

