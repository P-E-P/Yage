#include "Mob.h"


void Mob::preMove()
{
	deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - lastTickTime);
}

void Mob::postMove()
{
	lastTickTime = std::chrono::high_resolution_clock::now();
}

void Mob::onMove()
{

}

void Mob::move()
{
	preMove();
	onMove();
	postMove();
}


void Mob::preTick()
{

}

void Mob::postTick()
{
	move();
}

void Mob::tick()
{
	preTick();
	onTick();
	postTick();
}

void Mob::setUnitPerSec(float units)
{
	unitPerSecPX = units;
	unitPerSecPY = units;
	unitPerSecPZ = units;
	unitPerSecNX = units;
	unitPerSecNY = units;
	unitPerSecNZ = units;
}

float Mob::getUnitPerSecPX() const
{
	return unitPerSecPX;
}

float Mob::getUnitPerSecPY() const
{
	return unitPerSecPY;
}

float Mob::getUnitPerSecPZ() const
{
	return unitPerSecPZ;
}

float Mob::getUnitPerSecNX() const
{
	return unitPerSecNX;
}

float Mob::getUnitPerSecNY() const
{
	return unitPerSecNY;
}

float Mob::getUnitPerSecNZ() const
{
	return unitPerSecNZ;
}


float Mob::getPXDeltaPos()
{
	return getUnitPerSecPX() * deltaTime.count();
}
float Mob::getPYDeltaPos()
{
	return getUnitPerSecPY() * deltaTime.count();
}
float Mob::getPZDeltaPos()
{
	return getUnitPerSecPZ() * deltaTime.count();
}

float Mob::getNXDeltaPos()
{
	return getUnitPerSecNX() * deltaTime.count();
}
float Mob::getNYDeltaPos()
{
	return getUnitPerSecNY() * deltaTime.count();
}
float Mob::getNZDeltaPos()
{
	return getUnitPerSecNZ() * deltaTime.count();
}
