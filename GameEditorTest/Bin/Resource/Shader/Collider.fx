
#include "Share.fx"

struct VS_INPUT_COLOR
{
	float3	vPos	: POSITION;
	matrix	matWVP	: WORLD;
	float4	vDiffuse	: DIFFUSE;
	float3	vPivot		: PIVOT;
	float	vEmpty : EMPTY;
};

struct VS_OUTPUT_COLOR
{
	float4	vPos	: SV_POSITION;
	float4	vColor	: COLOR;
};

VS_OUTPUT_COLOR ColliderVS(VS_INPUT_COLOR input)
{
	VS_OUTPUT_COLOR	output = (VS_OUTPUT_COLOR)0;

	float3	vPos = input.vPos - input.vPivot * g_vMeshSize;

	output.vPos = mul(float4(vPos, 1.f), input.matWVP);
	output.vColor = input.vDiffuse;

	return output;
}

struct PS_OUTPUT_SINGLE
{
	float4	vColor	: SV_TARGET;
};

PS_OUTPUT_SINGLE ColliderPS(VS_OUTPUT_COLOR input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	output.vColor = input.vColor;

	return output;
}
