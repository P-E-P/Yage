#pragma once
#include "mob.h"
#include "texturable.h"

class Planet :
	public Mob, public Texturable
{
private:
	float delta_angle;
	XMFLOAT4X4 revolution, deltaRev;
	XMFLOAT4X4 lastScale;
	bool scaleUp;

	void load2ndTexture(LPCWSTR filename);
public:
	ID3D11ShaderResourceView* ntex;

	Planet(XMMATRIX position,
		XMFLOAT3 scaling,
		XMFLOAT3 scaling2,
		float delta_angle,
		LPCWSTR dTex,
		LPCWSTR nTex,
		Renderer* renderer);

	Planet(XMFLOAT3 position,
		XMFLOAT3 scaling,
		XMFLOAT3 scaling2,
		float delta_angle,
		LPCWSTR dTex,
		LPCWSTR nTex,
		Renderer* renderer);

	Planet(XMFLOAT3 position,
		XMFLOAT3 scaling,
		XMFLOAT3 scaling2,
		XMFLOAT3 offset,
		XMFLOAT3 revolution,
		float delta_angle,
		LPCWSTR dTex,
		LPCWSTR nTex,
		Renderer* renderer);

	Planet(XMMATRIX position,
		XMFLOAT3 scaling,
		XMFLOAT3 scaling2,
		XMFLOAT3 offset,
		XMFLOAT3 revolution,
		float delta_angle,
		LPCWSTR dTex,
		LPCWSTR nTex,
		Renderer* renderer);


	~Planet();
	void onTick();
	void onMove();
	void render(XMMATRIX view, XMMATRIX projection);
};