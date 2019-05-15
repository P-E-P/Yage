#pragma once
#include <D3D11.h>
#include <D3DX11tex.h>
#include <iostream>

#include "load.h"
#include "renderable.h"
#include "sh_compiler.h"
#include "material.h"

class Modelisable :
	public Renderable
{
protected:
	UINT stride, offset;
	ID3DBlob *pPSBlob, *pVSBlob;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* vertexLayout;
	Material material = defaultMaterial;
	void loadModel(char*);

	void modelLoadErr(LPCWSTR classname, LPCWSTR message);
	void vertexShaderCompileErr(WCHAR* filename);
	void pixelShaderCompileErr(WCHAR* filename);
	HRESULT compilePixelShader(WCHAR* filename, const char* shadername);
	HRESULT compileVertexShader(WCHAR* filename, const char* shadername);
	int n_vertices;
	ID3D11Buffer* vertexBuffer;
};

