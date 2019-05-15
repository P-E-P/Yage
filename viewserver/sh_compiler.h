#pragma once

#include "ground.h"

#define VERTEX_SHADER_VERSION "vs_4_0"
#define PIXEL_SHADER_VERSION "ps_4_0"

HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);