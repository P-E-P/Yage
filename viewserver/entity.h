#pragma once

#include <vector>

#include <D3D11.h>
#include <xnamath.h>

class Entity
{
protected:
	XMFLOAT4X4 position, scaling, rotation;
	std::vector<XMFLOAT4X4> transformations;

	XMFLOAT4X4 transformation;

public:

	inline const XMFLOAT4X4 getPosition() const;
	inline void setPosition(XMFLOAT4X4 position);
	inline void setScaling(XMFLOAT4X4 scaling);
	inline void setRotation(XMFLOAT4X4 rotation);

	void addIntermediateTransformation(XMMATRIX transformation);
};

