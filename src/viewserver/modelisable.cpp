#include "modelisable.h"

void Modelisable::loadModel(char* filename) {

	char* ext = filename + (strlen(filename) - 4);

	if (strcmp(ext, ".obj") == 0) {
		LoadOBJ(filename, renderer->device, &vertexBuffer, &n_vertices);
	}
	else if (strcmp(ext, ".3ds") == 0) {
		Load3DS(filename, renderer->device, &vertexBuffer, &n_vertices, FALSE);
	}
	else {
		modelLoadErr(L"Modelisable.cpp", L"Unknown 3D file format");
	}
	
}

HRESULT Modelisable::compilePixelShader(WCHAR* filename, const char* shadername) {
	// Compile the pixel shader
	HRESULT hr = CompileShaderFromFile(filename, shadername, PIXEL_SHADER_VERSION, &pPSBlob);
	if (FAILED(hr))
	{
		pixelShaderCompileErr(filename);
		return hr;
	}

	// Create the pixel shader
	hr = renderer->device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &pixelShader);
	pPSBlob->Release();
	if (FAILED(hr))
		return hr;
}

HRESULT Modelisable::compileVertexShader(WCHAR* filename, const char* shadername) {
	HRESULT hr = CompileShaderFromFile(filename, shadername, VERTEX_SHADER_VERSION, &pVSBlob);
	if (FAILED(hr))
	{
		vertexShaderCompileErr(filename);
		return hr;
	}

	// Create the vertex shader
	hr = renderer->device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &vertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = renderer->device->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &vertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Set the input layout
	renderer->immContext->IASetInputLayout(vertexLayout);

	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;
	// Create vertex buffer, the billboard
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


	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 6;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	hr = renderer->device->CreateBuffer(&bd, &InitData, &vertexBuffer);
	if (FAILED(hr))
		return hr;

}



void Modelisable::modelLoadErr(LPCWSTR classname, LPCWSTR message)
{
	MessageBox(NULL, (std::wstring(L"In") + classname + L":" + message).c_str(), L"Cannot load texture", MB_OK);
}

void Modelisable::vertexShaderCompileErr(WCHAR* filename)
{
	MessageBox(NULL, (std::wstring(L"In") + filename + L" vertex shader cannot be compiled.  Please run this executable from the directory that contains the FX file.").c_str(), L"Error", MB_OK);
}

void Modelisable::pixelShaderCompileErr(WCHAR* filename)
{
	MessageBox(NULL, (std::wstring(L"In") + filename +  L" pixel shader cannot be compiled.  Please run this executable from the directory that contains the FX file.").c_str(), L"Error", MB_OK);
}