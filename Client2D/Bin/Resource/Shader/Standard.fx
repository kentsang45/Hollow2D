
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

cbuffer OutLine	: register(b11)
{
	float2	g_vOutLineScale;
	float2	g_vOutLineImgSize;
	int		g_iOutLinePixelSize;
	float3	g_vOutLineEmpty;
};

#define	ANIM_ATLAS	0
#define	ANIM_FRAME	1

struct VS_INPUT_COLOR
{
	float3	vPos	: POSITION;
	float4	vColor	: COLOR;
};

struct VS_OUTPUT_COLOR
{
	float4	vPos	: SV_POSITION;
	float4	vColor	: COLOR;

	float2 vUV : TEXCOORD;
};

VS_OUTPUT_COLOR StandardColorVS(VS_INPUT_COLOR input)
{
	VS_OUTPUT_COLOR	output = (VS_OUTPUT_COLOR)0;

	float3	vPos = input.vPos - g_vMeshSize * g_vMeshPivot;

	output.vPos = mul(float4(vPos, 1.f), g_matWVP);
	output.vColor = input.vColor;


	if (input.vPos.x <= 0.f)
		output.vUV.x = 0.f;

	else
		output.vUV.x = 1.f;

	if (input.vPos.y <= 0.f)
		output.vUV.y = 1.f;

	else
		output.vUV.y = 0.f;


	return output;
}

struct PS_OUTPUT_SINGLE
{
	float4	vColor	: SV_TARGET;
};

PS_OUTPUT_SINGLE StandardColorPS(VS_OUTPUT_COLOR input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	float4 vColor = PaperBurn(input.vColor, input.vUV);

	output.vColor = vColor;

	return output;
}

//
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

VS_OUTPUT_TEX StandardTexVS(VS_INPUT_TEX input)
{
	VS_OUTPUT_TEX	output = (VS_OUTPUT_TEX)0;

	float3	vPos = input.vPos - g_vMeshSize * g_vMeshPivot;

	output.vPos = mul(float4(vPos, 1.f), g_matWVP);
	output.vUV = input.vUV;

	return output;
}

PS_OUTPUT_SINGLE StandardTexPS(VS_OUTPUT_TEX input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	float4	vColor = g_BaseTexture.Sample(g_LinearSmp, input.vUV);

	output.vColor = vColor;

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

VS_OUTPUT_TEX StandardAnim2DVS(VS_INPUT_TEX input)
{
	VS_OUTPUT_TEX	output = (VS_OUTPUT_TEX)0;

	float3	vPos = input.vPos - g_vMeshSize * g_vMeshPivot;

	output.vPos = mul(float4(vPos, 1.f), g_matWVP);

	float2	vUV = input.vUV;

	if (g_iAnim2DType == ANIM_ATLAS)
	{
		vUV = ComputeAnimation2DUV(input.vUV);
	}
    
    // 반전
    if (-1 == g_iTrEmpty)
    {
        vUV.x = 1 - vUV.x;
    }


	output.vUV = vUV;

	return output;
}

PS_OUTPUT_SINGLE StandardAnim2DPS(VS_OUTPUT_TEX input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	float4	vColor = g_BaseTexture.Sample(g_LinearSmp, input.vUV);

	output.vColor = vColor;

	return output;
}

bool CheckNearPixel(float2 vUV)
{
	float4	vColor = g_BaseTexture.Sample(g_LinearSmp, vUV);

	if(vColor.a > 0.f)
		return false;

	// 이미지크기와 스케일된 크기의 비율을 구한다.
	float2	vPercent = g_vOutLineImgSize / g_vOutLineScale;

	// 1픽셀당 UV증가값을 구한다.
	float2	vPixelUV = float2(1.f, 1.f) / g_vOutLineScale * vPercent;

	float2	vConvertUV;

	float4	vCheck;

	for (int i = 1; i <= 3; ++i)
	{
		vConvertUV	= vUV;
		vConvertUV.x -= (vPixelUV.x * i);

		if(vConvertUV.x >= 0.f)
		{
			vCheck = g_BaseTexture.Sample(g_LinearSmp, vConvertUV);

			if (vCheck.a > 0.f)
				return true;
		}

		vConvertUV = vUV;
		vConvertUV.x += (vPixelUV.x * i);

		if (vConvertUV.x <= 1.f)
		{
			vCheck = g_BaseTexture.Sample(g_LinearSmp, vConvertUV);

			if (vCheck.a > 0.f)
				return true;
		}

		vConvertUV = vUV;
		vConvertUV.y -= (vPixelUV.y * i);

		if (vConvertUV.y >= 0.f)
		{
			vCheck = g_BaseTexture.Sample(g_LinearSmp, vConvertUV);

			if (vCheck.a > 0.f)
				return true;
		}

		vConvertUV = vUV;
		vConvertUV.y += (vPixelUV.x * i);

		if (vConvertUV.y <= 1.f)
		{
			vCheck = g_BaseTexture.Sample(g_LinearSmp, vConvertUV);

			if (vCheck.a > 0.f)
				return true;
		}
	}

	return false;
}

PS_OUTPUT_SINGLE StandardTexOutLine2DPS(VS_OUTPUT_TEX input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	float4	vColor;

	if (CheckNearPixel(input.vUV))
	{
		vColor	= float4(1.f, 0.f, 0.f, 1.f);
	}

	else
	{
		vColor = g_BaseTexture.Sample(g_LinearSmp, input.vUV);
	}

	output.vColor = vColor;

	return output;
}

struct VS_INPUT_STATIC_INSTANCING
{
	float3	vPos	: POSITION;
	float2	vUV		: TEXCOORD;
	matrix	matWVP	: WORLD;
	float4	vDiffuse	: DIFFUSE;
	float3	vPivot		: PIVOT;
	float	vEmpty		: EMPTY;
};

struct VS_OUTPUT_STATIC_INSTANCING
{
	float4	vPos	: SV_POSITION;
	float2	vUV		: TEXCOORD;
	float4	vDiffuse	: DIFFUSE;
};

struct VS_INPUT_ANIM2D_INSTANCING
{
	float3	vPos	: POSITION;
	float2	vUV		: TEXCOORD;
	matrix	matWVP	: WORLD;
	float4	vDiffuse	: DIFFUSE;
	float3	vPivot		: PIVOT;
	float2	vStart	: START;
	float2	vEnd	: END;
	int		iAnimType	: ANIMTYPE;
	float	fImageWidth	: IMGWIDTH;
	float	fImageHeight	: IMGHEIGHT;
};

VS_OUTPUT_STATIC_INSTANCING StandardStaticInstancingVS(VS_INPUT_STATIC_INSTANCING input)
{
	VS_OUTPUT_STATIC_INSTANCING	output = (VS_OUTPUT_STATIC_INSTANCING)0;

	float3	vPos = input.vPos - g_vMeshSize * input.vPivot;

	output.vPos = mul(float4(vPos, 1.f), input.matWVP);
	output.vUV = input.vUV;
	output.vDiffuse = input.vDiffuse;

	return output;
}

PS_OUTPUT_SINGLE StandardStaticInstancingPS(VS_OUTPUT_STATIC_INSTANCING input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	float4	vColor = g_BaseTexture.Sample(g_LinearSmp, input.vUV);

	output.vColor = vColor * input.vDiffuse;

	return output;
}

float2 ComputeAnimation2DInstancingUV(float2 vUV, float2 vStart, float2 vEnd, float fWidth,
	float fHeight)
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

VS_OUTPUT_STATIC_INSTANCING StandardAnim2DInstancingVS(VS_INPUT_ANIM2D_INSTANCING input)
{
	VS_OUTPUT_STATIC_INSTANCING	output = (VS_OUTPUT_STATIC_INSTANCING)0;

	float3	vPos = input.vPos - g_vMeshSize * input.vPivot;

	output.vPos = mul(float4(vPos, 1.f), input.matWVP);

	float2	vUV = input.vUV;

	if (input.iAnimType == ANIM_ATLAS)
	{
		vUV = ComputeAnimation2DInstancingUV(input.vUV, input.vStart, input.vEnd,
			input.fImageWidth, input.fImageHeight);
	}

	output.vUV = vUV;
	output.vDiffuse	= input.vDiffuse;

	return output;
}

PS_OUTPUT_SINGLE StandardAnim2DInstancingPS(VS_OUTPUT_STATIC_INSTANCING input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	float4	vColor = g_BaseTexture.Sample(g_LinearSmp, input.vUV);

	output.vColor = vColor * input.vDiffuse;

	return output;
}
