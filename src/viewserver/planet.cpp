#include "planet.h"

Planet::Planet(XMFLOAT3 position,
	XMFLOAT3 scaling,
	XMFLOAT3 scaling2,
	float delta_angle,
	LPCWSTR day_filename,
	LPCWSTR night_filename,
	Renderer* renderer) 
	: Planet(XMMatrixTranslation(position.x, position.y, position.z),
		scaling,
		scaling2,
		delta_angle,
		day_filename,
		night_filename,
		renderer) { }

Planet::Planet(XMFLOAT3 position,
	XMFLOAT3 scaling,
	XMFLOAT3 scaling2,
	XMFLOAT3 offset,
	XMFLOAT3 revolution,
	float delta_angle,
	LPCWSTR day_filename,
	LPCWSTR night_filename,
	Renderer* renderer)
	: Planet(XMMatrixTranslation(position.x, position.y, position.z),
		scaling,
		scaling2,
		offset,
		revolution,
		delta_angle,
		day_filename,
		night_filename,
		renderer) { }

Planet::Planet(XMMATRIX position,
	XMFLOAT3 scaling,
	XMFLOAT3 scaling2,
	XMFLOAT3 offset,
	XMFLOAT3 revolution,
	float delta_angle,
	LPCWSTR day_filename,
	LPCWSTR night_filename,
	Renderer* renderer) : Planet(position,
		scaling,
		scaling2,
		delta_angle,
		day_filename,
		night_filename,
		renderer)
{
	addIntermediateTransformation(XMMatrixTranslation(offset.x, offset.y, offset.z));
	XMStoreFloat4x4(&this->deltaRev, XMMatrixRotationX(revolution.x) * XMMatrixRotationY(revolution.y) * XMMatrixRotationZ(revolution.z));
}


Planet::Planet(XMMATRIX position, XMFLOAT3 scaling, XMFLOAT3 scaling2, float delta_angle, LPCWSTR day_filename, LPCWSTR night_filename, Renderer* renderer)
{
	this->renderer = renderer;
	this->delta_angle = delta_angle;
	XMStoreFloat4x4(&this->lastScale, XMMatrixScaling(scaling.x, scaling.y, scaling.z));
	XMStoreFloat4x4(&this->deltaRev,XMMatrixIdentity());
	compileVertexShader(L"shader.fx", "PLANET_VShader");
	compilePixelShader(L"shader.fx", "PLANET_PS");
	loadModel("sphere.3ds");
	loadTexture(day_filename);
	load2ndTexture(night_filename);

	stride = sizeof(SimpleVertex);
	offset = 0;
	XMStoreFloat4x4(&this->revolution, XMMatrixIdentity());
	XMStoreFloat4x4(&this->scaling,XMMatrixScaling(scaling2.x, scaling2.y, scaling2.z));
	XMStoreFloat4x4(&this->position, position);
	XMStoreFloat4x4(&this->rotation, XMMatrixRotationX(XM_PIDIV2));

	scaleUp = true;
	
}


Planet::~Planet() {}

void Planet::onTick()
{

	XMStoreFloat4x4(&rotation, XMLoadFloat4x4(&rotation) * XMMatrixRotationY(delta_angle));
	XMStoreFloat4x4(&transformation,XMLoadFloat4x4(&scaling) *  XMLoadFloat4x4(&rotation));
	for (auto &c_trans : transformations)
	{
		XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&transformation) * XMLoadFloat4x4(&c_trans));
	}
	XMStoreFloat4x4(&revolution, XMLoadFloat4x4(&revolution) * XMLoadFloat4x4(&deltaRev));
	XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&transformation) * XMLoadFloat4x4(&revolution) * XMLoadFloat4x4(&position));

}

void Planet::render(XMMATRIX view, XMMATRIX projection)
{
	renderer->vsConstData.world = XMLoadFloat4x4(&transformation);
	renderer->vsConstData.view = view;
	renderer->vsConstData.projection = projection;

	/* Set shaders */
	renderer->immContext->VSSetShader(vertexShader, NULL, 0);
	renderer->immContext->PSSetShaderResources(0, 1, &tex);


	renderer->immContext->PSSetShaderResources(1, 1, &ntex);
	renderer->immContext->UpdateSubresource(renderer->constantBuffer, 0, 0, &renderer->vsConstData, 0, 0);	//copying it freshly into the GPU buffer from VsConstData
	
	/* Set constant buffers */
	renderer->immContext->VSSetConstantBuffers(0, 1, &renderer->constantBuffer);					//setting it enable for the VertexShader
	renderer->immContext->PSSetConstantBuffers(0, 1, &renderer->constantBuffer);					//setting it enable for the PixelShader
	
	renderer->immContext->PSSetShader(pixelShader, NULL, 0);
	renderer->immContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//g_pImmediateContext->RSSetState(rs_Wire);//reset to default
	renderer->immContext->Draw(n_vertices, 0);
}

void Planet::load2ndTexture(LPCWSTR filename)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(renderer->device, filename, NULL, NULL, &ntex, NULL);
	if (FAILED(hr))
		textureLoadErr(L"Texturable.cpp", (std::wstring(L"Failed to load additional texture ") + filename).c_str());
}


void Planet::onMove()
{
	//Scale up
	if (Keyboard::getInstance().getKeyState('J')) {
		if (scaleUp) {
			XMMATRIX tmp = XMLoadFloat4x4(&this->lastScale);
			XMStoreFloat4x4(&this->lastScale,XMLoadFloat4x4(&scaling));
			XMStoreFloat4x4(&scaling, tmp);
			scaleUp = !scaleUp;
		}
	}

	//Scale down
	if (Keyboard::getInstance().getKeyState('K')) {
		if (!scaleUp) {
			XMMATRIX tmp = XMLoadFloat4x4(&this->lastScale);
			XMStoreFloat4x4(&this->lastScale, XMLoadFloat4x4(&scaling));
			XMStoreFloat4x4(&scaling, tmp);
			scaleUp = !scaleUp;
		}
	}

}
