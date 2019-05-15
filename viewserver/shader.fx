Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

#define MAX_LIGHT 1

cbuffer VS_CONSTANT_BUFFER : register(b0)
{
	float mx;
	float my;
	float scale;
	float trans;
	float div_tex_x;	//dividing of the texture coordinates in x
	float div_tex_y;	//dividing of the texture coordinates in x
	float slice_x;		//which if the 4x4 images
	float slice_y;		//which if the 4x4 images
	matrix world;
	matrix view;
	matrix projection;
};

cbuffer MAT_CONSTANT_BUFFER : register(b1)
{
	float4 diffuse_color;
	float4 ambient_color;
	float4 specular_color;
}
cbuffer LIGHT_CONSTANT_BUFFER : register(b2)
{
	float4 lightPos[MAX_LIGHT];
	float4 lightColor[MAX_LIGHT];
}

struct SimpleVertex
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	float3 Norm : NORMAL;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float3 WorldPos : POSITION1;
	float2 Tex : TEXCOORD0;
	float3 Norm : NORMAL;
};
//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VShader(SimpleVertex input)
{
	PS_INPUT output;
	float4 pos = input.Pos;

	pos = mul(world, pos);	
	output.WorldPos = pos.xyz;
	pos = mul(view, pos);
	pos = mul(projection, pos);	
	
	matrix w = world;
	w._14 = 0;
	w._24 = 0;
	w._34 = 0;

	float4 norm;
	norm.xyz = input.Norm;
	norm.w = 1;
	norm = mul(w, norm);
	norm.x *= -1;
	output.Norm = normalize(norm.xyz);

	output.Pos = pos;
	output.Tex = input.Tex;
	return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------

float4 PS(PS_INPUT input) : SV_Target
{
	float4 color = tex.Sample(samLinear, input.Tex);
	return color;
}

float4 GRADIENT_PS(PS_INPUT input) : SV_Target
{
	float d = input.WorldPos.x * 1.25 + 1.6f;
	return lerp(float4(0.0f,1.0f,0.0f,1.0f), float4(1.0f,0.0f,1.0f,1.0f), d);
}
