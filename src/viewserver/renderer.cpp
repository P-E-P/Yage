#include "renderer.h"



Renderer::Renderer(ID3D11Device* device,
	VS_CONSTANT_BUFFER& vsConstData,
	MATERIAL_CONSTANT_BUFFER& matConstData,
	ID3D11DeviceContext* immContext)
{
	this->device = device;
	this->vsConstData = vsConstData;
	this->matConstData = matConstData;
	this->immContext = immContext;


	

	/* Create constant buffer */

	D3D11_SUBRESOURCE_DATA InitData;
	// Fill in a buffer description.
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(cbDesc));
	cbDesc.ByteWidth = sizeof(VS_CONSTANT_BUFFER);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &vsConstData;
	// Create the buffer.
	device->CreateBuffer(&cbDesc, &InitData, &constantBuffer);


	ZeroMemory(&cbDesc, sizeof(cbDesc));
	cbDesc.ByteWidth = sizeof(MATERIAL_CONSTANT_BUFFER);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &matConstData;
	// Create the buffer.
	device->CreateBuffer(&cbDesc, &InitData, &matConstantBuffer);

	ZeroMemory(&cbDesc, sizeof(cbDesc));
	cbDesc.ByteWidth = sizeof(LIGHT_CONSTANT_BUFFER);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &matConstData;
	// Create the buffer.
	device->CreateBuffer(&cbDesc, &InitData, &lightConstantBuffer);
	
}


Renderer::~Renderer()
{
}
