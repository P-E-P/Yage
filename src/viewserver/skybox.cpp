#include "skybox.h"



Skybox::Skybox(Camera* cam,
	LPCWSTR tex,
	Renderer* renderer,
	ID3D11RasterizerState* rs_CCW,
	ID3D11DepthStencilState* ds_off,
	ID3D11RasterizerState* rs_CW,
	ID3D11DepthStencilState* ds_on)


{
	this->cam = cam;

	this->rs_CCW = rs_CCW;
	this->rs_CW = rs_CW;
	this->ds_off = ds_off;
	this->ds_on = ds_on;
	this->renderer = renderer;

	compileVertexShader(L"shader.fx", "VShader");
	compilePixelShader(L"shader.fx", "PS");
	loadTexture(tex);
	loadModel("sphere.3ds");

	stride = sizeof(SimpleVertex);
	offset = 0;

	XMStoreFloat4x4(&this->scaling, XMMatrixScaling(0.008, 0.008, 0.008));
	XMStoreFloat4x4(&this->position, XMMatrixTranslation(cam->pos.x, cam->pos.y, -cam->pos.z));

}


Skybox::~Skybox() { }

void Skybox::onTick()
{
	XMStoreFloat4x4(&this->position, XMMatrixTranslation(cam->pos.x, cam->pos.y, -cam->pos.z));

	XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&scaling));
	XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&transformation) * XMLoadFloat4x4(&position));
}

void Skybox::render(XMMATRIX view, XMMATRIX projection)
{

	renderer->vsConstData.world = XMLoadFloat4x4(&transformation);
	renderer->vsConstData.view = view;
	renderer->vsConstData.projection = projection;
	
	/* Set shaders */
	renderer->immContext->VSSetShader(vertexShader, NULL, 0);
	renderer->immContext->PSSetShader(pixelShader, NULL, 0);


	renderer->immContext->RSSetState(rs_CW);
	renderer->immContext->UpdateSubresource(renderer->constantBuffer, 0, 0, &renderer->vsConstData, 0, 0);
	
	/* Set constant buffers */
	renderer->immContext->VSSetConstantBuffers(0, 1, &renderer->constantBuffer);
	renderer->immContext->PSSetConstantBuffers(0, 1, &renderer->constantBuffer);
	renderer->immContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	
	renderer->immContext->PSSetShaderResources(0, 1, &tex);

	renderer->immContext->RSSetState(rs_CCW);//to see it from the inside
	renderer->immContext->OMSetDepthStencilState(ds_off, 1);//no depth writing
	renderer->immContext->Draw(n_vertices, 0);		//render sky
	renderer->immContext->RSSetState(rs_CW);//reset to default
	renderer->immContext->OMSetDepthStencilState(ds_on, 1);//reset to default
}
