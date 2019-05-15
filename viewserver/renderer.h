#pragma once

#include <D3D11.h>
#include <D3DX11tex.h>

#include "constant_buffer.h"

class Renderer
{
public:
	ID3D11Device* device;
	VS_CONSTANT_BUFFER vsConstData;
	LIGHT_CONSTANT_BUFFER lightConstData;
	MATERIAL_CONSTANT_BUFFER matConstData;
	ID3D11DeviceContext* immContext;
	ID3D11Buffer* constantBuffer, *matConstantBuffer, *lightConstantBuffer;

	Renderer(ID3D11Device* device, VS_CONSTANT_BUFFER& vsConstData, MATERIAL_CONSTANT_BUFFER& matConstData, ID3D11DeviceContext* immContext);
	~Renderer();
};

