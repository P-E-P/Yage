#include "shape.h"

Shape::Shape(XMMATRIX position,
	XMFLOAT3 scaling,
	LPCWSTR textureFile,
	WCHAR* shaderfile,
	ID3D11Buffer* vertexBuffer,
	int n_vertices,
	Renderer* renderer)
{
	this->renderer = renderer;

	compileVertexShader(shaderfile, "VShader");
	compilePixelShader(shaderfile, "PS");
	loadTexture(textureFile);

	this->n_vertices = n_vertices;
	this->vertexBuffer = vertexBuffer;

	stride = sizeof(SimpleVertex);
	offset = 0;

	XMStoreFloat4x4(&this->scaling, XMMatrixScaling(scaling.x, scaling.y, scaling.z));
	XMStoreFloat4x4(&this->position, position);
}

Shape::Shape(XMFLOAT3 position,
	XMFLOAT3 scaling,
	LPCWSTR textureFile,
	WCHAR* shaderfile,
	ID3D11Buffer* vertexBuffer,
	int n_vertices,
	Renderer* renderer) :
	Shape(XMMatrixTranslation(position.x, position.y, position.z),
		scaling,
		textureFile,
		shaderfile,
		vertexBuffer,
		n_vertices,
		renderer) { }


Shape::~Shape()
{
}


void Shape::onTick()
{
	XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&scaling));
	for (auto &c_trans : transformations)
	{
		XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&transformation) * XMLoadFloat4x4(&c_trans));
	}
	XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&transformation) * XMLoadFloat4x4(&position));
}

void Shape::render(XMMATRIX view, XMMATRIX projection)
{

	/* Set shaders */
	renderer->immContext->VSSetShader(vertexShader, NULL, 0);
	renderer->immContext->PSSetShader(pixelShader, NULL, 0);

	/* Set constant buffers */
	renderer->immContext->VSSetConstantBuffers(0, 1, &renderer->constantBuffer);
	renderer->immContext->PSSetConstantBuffers(0, 1, &renderer->constantBuffer);
	renderer->immContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);


	renderer->vsConstData.world = XMLoadFloat4x4(&transformation);

	renderer->vsConstData.view = view;
	renderer->vsConstData.projection = projection;
	renderer->immContext->UpdateSubresource(renderer->constantBuffer, 0, 0, &renderer->vsConstData, 0, 0);
	
	renderer->immContext->PSSetShaderResources(0, 1, &tex);

	
	//g_pImmediateContext->RSSetState(rs_Wire);//reset to default
	renderer->immContext->Draw(n_vertices, 0);
}
