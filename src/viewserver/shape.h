#pragma once
#include "mob.h"
#include "texturable.h"

class Shape :
	public Mob, public Texturable
{
public:
	Shape(XMMATRIX position,
		XMFLOAT3 scaling,
		LPCWSTR textureFile,
		WCHAR* shaderfile,
		ID3D11Buffer* vertexBuffer,
		int n_vertices,
		Renderer* renderer);

	Shape(XMFLOAT3 position,
		XMFLOAT3 scaling,
		LPCWSTR textureFile,
		WCHAR* shaderfile,
		ID3D11Buffer* vertexBuffer,
		int n_vertices,
		Renderer* renderer);
	~Shape();

	void onTick();
	void render(XMMATRIX view, XMMATRIX projection);
};

