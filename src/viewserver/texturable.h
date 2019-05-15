#pragma once

#include "modelisable.h"

class Texturable :
	public Modelisable
{
protected:
	ID3D11ShaderResourceView* tex;
	void loadTexture(LPCWSTR filename);

	void textureLoadErr(LPCWSTR, LPCWSTR);

};

