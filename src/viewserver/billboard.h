#pragma once
#include "texturable.h"
#include "mob.h"

class Billboard :
	public Mob, public Texturable
{
private:
	HRESULT loadVertexBuffer();
public:
	Billboard(XMMATRIX position,
		XMFLOAT3 scaling,
		LPCWSTR textureFile,
		WCHAR* shaderfile,
		Renderer* renderer);

	Billboard(XMFLOAT3 position,
		XMFLOAT3 scaling,
		LPCWSTR textureFile,
		WCHAR* shaderfile,
		Renderer* renderer);
	~Billboard();
	void onTick();
	void render(XMMATRIX view, XMMATRIX projection);
};

