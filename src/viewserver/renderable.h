#pragma once
#include <D3D11.h>
#include <D3DX11tex.h>

#include "constant_buffer.h"
#include "renderer.h"
#include "entity.h"

class Renderable : 
	virtual public Entity
{
protected:
	Renderer* renderer;
public:
	virtual void render(XMMATRIX view, XMMATRIX projection) = 0;
};