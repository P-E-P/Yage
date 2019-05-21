#pragma once

#include <string>
#include <chrono>

#include "ground.h"
#include "constant_buffer.h"
#include "renderer.h"
#include "scene_manager.h"
#include "scene.h"

class Engine
{
private:
	D3D_DRIVER_TYPE g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL g_featureLevel = D3D_FEATURE_LEVEL_11_0;

	ID3D11SamplerState* g_Sampler = NULL;
	IDXGISwapChain*         g_pSwapChain = NULL;
	//screen <- thats our render target
	ID3D11RenderTargetView* g_pRenderTargetView = NULL;

	//depth stencil buffer
	ID3D11Texture2D*                    g_pDepthStencil = NULL;
	ID3D11DepthStencilView*             g_pDepthStencilView = NULL;

	//for transparency:
	ID3D11BlendState*					g_BlendState;


	const double ns = 1000000000.0 / 64.0;
	double delta = 0;
	int frames = 0;
	int ticks = 0;
	long lastTime;
	long timer;

	SceneManager* manager;

public:
	Renderer* renderer;
	
	//we will copy that periodically to its twin on the GPU, with mouse_x/b for the mouse coordinates
	//note: we can only copy chunks of 16 byte to the GPU
	VS_CONSTANT_BUFFER VsConstData;
	MATERIAL_CONSTANT_BUFFER MatConstData;
	Engine(HWND window, UINT width, UINT height);
	~Engine();

	void addScene(Scene* scene);
	void tick();
	void discreteTick();
	void render();
};

