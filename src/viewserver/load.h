#pragma once

#include "ground.h"

// loads a 3DS file into a vertex buffer:
bool Load3DS(char *filename, ID3D11Device* g_pd3dDevice, ID3D11Buffer **ppVertexBuffer, int *vertex_count, bool gouraurd);
// loads an OBJ file into a vertex buffer:
bool LoadOBJ(char * filename, ID3D11Device * g_pd3dDevice, ID3D11Buffer ** ppVertexBuffer, int * vertex_count);
