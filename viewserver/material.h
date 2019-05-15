#pragma once

#include "ground.h"

struct Material
{
	XMFLOAT4 diffuseColor;
	XMFLOAT4 ambientColor;
	XMFLOAT4 specularColor;
};

static  const struct Material defaultMaterial = {
	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
};