#pragma once

#include "ground.h"
#include "mob.h"

class Camera : public Mob
{
protected:
	float angle_y;
	float angle_x;
	XMFLOAT4X4 view, start, projection;
public:
	XMFLOAT3 pos;
	Camera(XMVECTOR Eye, XMVECTOR At, XMVECTOR Up, XMMATRIX projection);
	~Camera();
	void onTick();

	XMMATRIX getView() const;
	XMMATRIX getProjection() const;
};
