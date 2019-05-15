#pragma once

#include "mob.h"
#include "texturable.h"


class Model :
	public Mob, public Texturable
{
public:
	Model(XMMATRIX position,
		XMFLOAT3 scaling, 
		char* modelFile,
		LPCWSTR textureFile,
		WCHAR* shaderfile,
		Renderer* renderer);

	Model(XMFLOAT3 position,
		XMFLOAT3 scaling,
		char* modelFile,
		LPCWSTR textureFile,
		WCHAR* shaderfile,
		Renderer* renderer);

	Model(XMMATRIX position,
		XMFLOAT3 scaling,
		char* modelFile,
		LPCWSTR textureFile,
		WCHAR* shaderfile,
		const char* vShaderName,
		const char* pShaderName,
		Renderer* renderer);

	Model(XMFLOAT3 position,
		XMFLOAT3 scaling,
		char* modelFile,
		LPCWSTR textureFile,
		WCHAR* shaderfile,
		const char* vShaderName,
		const char* pShaderName,
		Renderer* renderer);

	~Model();
	void onTick();
	void render(XMMATRIX view, XMMATRIX projection);
};