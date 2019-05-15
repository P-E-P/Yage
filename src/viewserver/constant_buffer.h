#pragma once

#include <xnamath.h>
#include "material.h"


/* Keep this constant synced with it's shader counterpart */
#define MAX_LIGHT 1

struct VS_CONSTANT_BUFFER
{
	float mouse_x;
	float mouse_y;
	float some_variable_c;
	float some_variable_d;
	float div_tex_x;	//dividing of the texture coordinates in x
	float div_tex_y;	//dividing of the texture coordinates in x
	float slice_x;		//which if the 4x4 images
	float slice_y;		//which if the 4x4 images
	XMMATRIX world;//model: per object position and rotation and scaling of the object
	XMMATRIX view;//camera: position and rotation of the camera
	XMMATRIX projection;//perspective: angle of view, near plane / far plane
};

struct MATERIAL_CONSTANT_BUFFER
{
	XMFLOAT4 diffuse_color;
	XMFLOAT4 ambient_color;
	XMFLOAT4 specular_color;
};


struct LIGHT_CONSTANT_BUFFER
{
	XMFLOAT4 lightPos[MAX_LIGHT];
	XMFLOAT4 lightColor[MAX_LIGHT];
};