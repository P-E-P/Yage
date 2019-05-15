#include "billboard.h"

Billboard::Billboard(XMMATRIX position,
	XMFLOAT3 scaling,
	LPCWSTR textureFile,
	WCHAR* shaderfile,
	Renderer* renderer)
{
	this->renderer = renderer;

	compileVertexShader(shaderfile, "VShader");
	compilePixelShader(shaderfile, "PS");
	loadTexture(textureFile);

	loadVertexBuffer();

	stride = sizeof(SimpleVertex);
	offset = 0;

	XMStoreFloat4x4(&this->scaling, XMMatrixScaling(scaling.x, scaling.y, scaling.z));
	XMStoreFloat4x4(&this->position, position);
}

Billboard::Billboard(XMFLOAT3 position,
	XMFLOAT3 scaling,
	LPCWSTR textureFile,
	WCHAR* shaderfile,
	Renderer* renderer) :
	Billboard(XMMatrixTranslation(position.x, position.y, position.z),
		scaling,
		textureFile,
		shaderfile,
		renderer) { }


Billboard::~Billboard()
{
}



void Billboard::onTick()
{
	XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&scaling));
	for (auto &c_trans : transformations)
	{
		XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&transformation) * XMLoadFloat4x4(&c_trans));
	}
	XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&transformation) * XMLoadFloat4x4(&position));
}

void Billboard::render(XMMATRIX view, XMMATRIX projection)
{

	XMMATRIX Vc = view;
	Vc._41 = 0;
	Vc._42 = 0;
	Vc._43 = 0;
	XMVECTOR f;
	Vc = XMMatrixInverse(&f, Vc);

	renderer->vsConstData.world = Vc * XMLoadFloat4x4(&transformation);
	renderer->vsConstData.view = view;
	renderer->vsConstData.projection = projection;

	/* Set shaders */
	renderer->immContext->VSSetShader(vertexShader, NULL, 0);
	renderer->immContext->PSSetShaderResources(0, 1, &tex);


	renderer->immContext->UpdateSubresource(renderer->constantBuffer, 0, 0, &renderer->vsConstData, 0, 0);

	/* Set constant buffers */
	renderer->immContext->VSSetConstantBuffers(0, 1, &renderer->constantBuffer);
	renderer->immContext->PSSetConstantBuffers(0, 1, &renderer->constantBuffer);

	renderer->immContext->PSSetShader(pixelShader, NULL, 0);
	renderer->immContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//g_pImmediateContext->RSSetState(rs_Wire);//reset to default
	renderer->immContext->Draw(n_vertices, 0);
}

HRESULT Billboard::loadVertexBuffer()
{
	// Create vertex buffer, the triangle
	SimpleVertex vertices[6];
	vertices[0].Pos = XMFLOAT3(-1, 1, 1);	//left top
	vertices[1].Pos = XMFLOAT3(1, -1, 1);	//right bottom
	vertices[2].Pos = XMFLOAT3(-1, -1, 1); //left bottom
	vertices[0].Tex = XMFLOAT2(0.0f, 0.0f);
	vertices[1].Tex = XMFLOAT2(1.0f, 1.0f);
	vertices[2].Tex = XMFLOAT2(0.0f, 1.0f);

	vertices[3].Pos = XMFLOAT3(-1, 1, 1);	//left top
	vertices[4].Pos = XMFLOAT3(1, 1, 1);	//right top
	vertices[5].Pos = XMFLOAT3(1, -1, 1);	//right bottom
	vertices[3].Tex = XMFLOAT2(0.0f, 0.0f);			//left top
	vertices[4].Tex = XMFLOAT2(1.0f, 0.0f);			//right top
	vertices[5].Tex = XMFLOAT2(1.0f, 1.0f);			//right bottom



	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;


	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	HRESULT hr = renderer->device->CreateBuffer(&bd, &InitData, &vertexBuffer);
	
	n_vertices = 6;

	return hr;
}