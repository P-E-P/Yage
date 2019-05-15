#include "model.h"


Model::Model(XMFLOAT3 position,
	XMFLOAT3 scaling,
	char* modelFile,
	LPCWSTR textureFile,
	WCHAR* shaderfile,
	Renderer* renderer) :
	Model(XMMatrixTranslation(position.x, position.y, position.z),
		scaling,
		modelFile,
		textureFile,
		shaderfile,
		renderer) { }


Model::Model(XMMATRIX position,
	XMFLOAT3 scaling,
	char* modelFile,
	LPCWSTR textureFile,
	WCHAR* shaderfile,
	Renderer* renderer) :
	Model(position,
		scaling,
		modelFile,
		textureFile,
		shaderfile,
		"PLANET_VShader",
		"PS",
		renderer) { }

Model::Model(XMFLOAT3 position,
	XMFLOAT3 scaling,
	char* modelFile,
	LPCWSTR textureFile,
	WCHAR* shaderfile,
	const char* vShaderName,
	const char* pShaderName,
	Renderer* renderer) : 

	Model(XMMatrixTranslation(position.x, position.y, position.z),
		scaling,
		modelFile,
		textureFile,
		shaderfile,
		vShaderName,
		pShaderName,
		renderer) { }

Model::Model(XMMATRIX position,
	XMFLOAT3 scaling,
	char* modelFile,
	LPCWSTR textureFile,
	WCHAR* shaderfile,
	const char* vShaderName,
	const char* pShaderName,
	Renderer* renderer)
{
	this->renderer = renderer;

	compileVertexShader(shaderfile, vShaderName);
	compilePixelShader(shaderfile, pShaderName);
	loadTexture(textureFile);
	loadModel(modelFile);

	stride = sizeof(SimpleVertex);
	offset = 0;
	XMStoreFloat4x4(&this->rotation, XMMatrixIdentity());
	XMStoreFloat4x4(&this->scaling, XMMatrixScaling(scaling.x, scaling.y, scaling.z));
	XMStoreFloat4x4(&this->position, position);
}


Model::~Model()
{
}

void Model::onTick()
{
	XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&scaling));
	for (auto &c_trans : transformations)
	{
		XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&transformation) * XMLoadFloat4x4(&c_trans));
	}
	XMStoreFloat4x4(&transformation, XMLoadFloat4x4(&transformation) * XMLoadFloat4x4(&position));
}

void Model::render(XMMATRIX view, XMMATRIX projection)
{
	renderer->vsConstData.div_tex_x = 100.0f;
	renderer->vsConstData.div_tex_y = 100.0f;
	renderer->vsConstData.world = XMLoadFloat4x4(&transformation);
	renderer->vsConstData.view = view;
	renderer->vsConstData.projection = projection;

	renderer->immContext->UpdateSubresource(renderer->lightConstantBuffer, 0, 0, &renderer->lightConstData, 0, 0);
	renderer->immContext->UpdateSubresource(renderer->constantBuffer, 0, 0, &renderer->vsConstData, 0, 0);	//copying it freshly into the GPU buffer from VsConstData

	

	/* Set shaders */
	renderer->immContext->VSSetShader(vertexShader, NULL, 0);
	renderer->immContext->PSSetShaderResources(0, 1, &tex);

	
	/* Set constant buffers */
	renderer->immContext->VSSetConstantBuffers(0, 1, &renderer->constantBuffer);					//setting it enable for the VertexShader
	renderer->immContext->PSSetConstantBuffers(0, 1, &renderer->constantBuffer);					//setting it enable for the PixelShader

	renderer->immContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	renderer->immContext->PSSetShader(pixelShader, NULL, 0);
	//g_pImmediateContext->RSSetState(rs_Wire);//reset to default
	renderer->immContext->Draw(n_vertices, 0);
}
