
#include "Share.fx"

cbuffer Anim2D	: register(b10)
{
	float2	g_vANim2DStart;
	float2	g_vANim2DEnd;
	int		g_iAnim2DType;
	float	g_fAnim2DImageWidth;
	float	g_fAnim2DImageHeight;
	float	g_fAnim2DEmpty;
};

cbuffer	Bar	: register(b11)
{
	float	g_fBarPercent;
	int		g_iBarDir;
	float	g_fBarNextPercent;
	int		g_iNext;
};

#define	ANIM_ATLAS	0
#define	ANIM_FRAME	1

#define	BAR_LEFTFROMRIGHT	0
#define	BAR_RIGHTFROMLEFT	1
#define	BAR_TOPFROMBOTTOM	2
#define	BAR_BOTTOMFROMTOP	3

//struct VS_INPUT_TEX
//{
//	float3	vPos	: POSITION;
//	float2	vUV		: TEXCOORD;
//};
//
//struct VS_OUTPUT_TEX
//{
//	float4	vPos	: SV_POSITION;
//	float2	vUV		: TEXCOORD;
//};

struct PS_OUTPUT_SINGLE
{
	float4	vColor	: SV_TARGET;
};

VS_OUTPUT_TEX UIVS(VS_INPUT_TEX input)
{
	VS_OUTPUT_TEX	output = (VS_OUTPUT_TEX)0;

	float3	vPos = input.vPos - g_vMeshSize * g_vMeshPivot;

	output.vPos = mul(float4(vPos, 1.f), g_matWVP);
	output.vUV = input.vUV;

	return output;
}

PS_OUTPUT_SINGLE UIPS(VS_OUTPUT_TEX input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	float4	vColor = g_BaseTexture.Sample(g_LinearSmp, input.vUV);

	output.vColor = vColor * g_vMtrlDif;

	return output;
}

float2 ComputeAnimation2DUV(float2 vUV)
{
	float2	vNewUV = (float2)0.f;

	if (vUV.x == 0.f)
		vNewUV.x = g_vANim2DStart.x / g_fAnim2DImageWidth;

	else
		vNewUV.x = g_vANim2DEnd.x / g_fAnim2DImageWidth;

	if (vUV.y == 0.f)
		vNewUV.y = g_vANim2DStart.y / g_fAnim2DImageHeight;

	else
		vNewUV.y = g_vANim2DEnd.y / g_fAnim2DImageHeight;

	return vNewUV;
}

VS_OUTPUT_TEX UIAnim2DVS(VS_INPUT_TEX input)
{
	VS_OUTPUT_TEX	output = (VS_OUTPUT_TEX)0;

	float3	vPos = input.vPos - g_vMeshSize * g_vMeshPivot;

	output.vPos = mul(float4(vPos, 1.f), g_matWVP);

	float2	vUV = input.vUV;

	if (g_iAnim2DType == ANIM_ATLAS)
	{
		vUV = ComputeAnimation2DUV(input.vUV);
	}

	output.vUV = vUV;

	return output;
}

PS_OUTPUT_SINGLE UIAnim2DPS(VS_OUTPUT_TEX input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	float4	vColor = g_BaseTexture.Sample(g_LinearSmp, input.vUV);

	// clip 함수는 -1을 넣으면 픽셀을 차폐한다. 이 픽셀을 안쓰겠다는 의미이다.
	// 깊이도 안쓴다.
	/*if (vColor.r >= 0.9f && vColor.g >= 0.9f && vColor.b >= 0.9f)
		clip(-1);*/

	output.vColor = vColor;

	return output;
}

VS_OUTPUT_TEX UIBarVS(VS_INPUT_TEX input)
{
	VS_OUTPUT_TEX	output = (VS_OUTPUT_TEX)0;

	float3	vPos = input.vPos - g_vMeshSize * g_vMeshPivot;

	output.vPos = mul(float4(vPos, 1.f), g_matWVP);
	output.vUV = input.vUV;

	return output;
}

PS_OUTPUT_SINGLE UIBarPS(VS_OUTPUT_TEX input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	float		fLight = 1.f;

	if(g_iBarDir == BAR_LEFTFROMRIGHT)
	{
		if(input.vUV.x > g_fBarPercent)
			clip(-1);

		if(input.vUV.x > g_fBarNextPercent && g_iNext == 1)
			fLight	= 0.4f;
	}

	float4	vColor = g_BaseTexture.Sample(g_LinearSmp, input.vUV);

	output.vColor.rgb = vColor.rgb * fLight;
	output.vColor.a = vColor.a;

	return output;
}
