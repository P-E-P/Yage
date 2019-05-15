#include "texturable.h"

void Texturable::loadTexture(LPCWSTR filename)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(renderer->device, filename, NULL, NULL, &tex, NULL);
	if (FAILED(hr))
		textureLoadErr(L"Texturable.cpp", (std::wstring(L"Failed to load texture ") + filename).c_str());
}

void Texturable::textureLoadErr(LPCWSTR classname, LPCWSTR message)
{
	MessageBox(NULL, (std::wstring(L"In") + classname + L":" + message).c_str(), L"Cannot load texture", MB_OK);
}
