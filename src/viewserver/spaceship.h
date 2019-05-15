#pragma once

#include "model.h"
#include "mob.h"

class Spaceship :
	public Model
{
public:
	Spaceship(XMFLOAT3 position,
		XMFLOAT3 scaling,
		Renderer* renderer);
	~Spaceship();
	void onMove();
	void onTick();
};

