#pragma once
#include "camera.h"
#include "texturable.h"
#include "mob.h"

class Skybox : public Mob, public Texturable
{
private:
	Camera* cam;
	ID3D11RasterizerState *rs_CCW, *rs_CW;
	ID3D11DepthStencilState *ds_off, *ds_on;
public:
	Skybox(Camera* cam,
		LPCWSTR tex,
		Renderer* renderer,
		ID3D11RasterizerState* rs_CCW,
		ID3D11DepthStencilState* ds_off,
		ID3D11RasterizerState* rs_CW,
		ID3D11DepthStencilState* ds_on);
	~Skybox();

	void onTick();
	void render(XMMATRIX view, XMMATRIX projection);
};

