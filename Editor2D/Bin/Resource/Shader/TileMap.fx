
#include "Share.fx"

struct VS_INPUT_INSTANCING_TEX
{
	float3	vPos	: POSITION;
	float2	vUV		: TEXCOORD;
	matrix	matWVP	: WORLD;
	float2	vImgStart	: START;
	float2	vImgEnd		: END;
	float2	vImgSize	: IMGSIZE;
	int		iImgFrame	: IMGFRAME;
	int		iImgType	: IMGTYPE;
	int iTileOption : TILEOPTION;
    int iTileType : TILETYPE;
};

struct VS_OUTPUT_INSTANCING_TEX
{
	float4	vPos	: SV_POSITION;
	float2	vUV		: TEXCOORD;
	float2 vOriginUV :	TEXCOORD1;
	int iTileOption :	TEXCOORD2;
	int iImgType :		TEXCOORD3;
	int iImgFrame :		TEXCOORD4;
    int iTileType : TEXCOORD5;
};

struct PS_OUTPUT_SINGLE
{
	float4	vColor	: SV_TARGET;
};

#define	IMAGE_ATLAS	0
#define	IMAGE_ARRAY	1

#define TILE_NONE 0
#define TILE_NOMOVE 1

#define TILE_RECT 1
#define TILE_ISOMETRIC 2

cbuffer TileMap	: register(b10)
{
	float2	g_vImgStart;
	float2	g_vImgEnd;
	float2	g_vImgSize;
	int		g_iImgFrame;
	int		g_iImgType;
};

Texture2DArray g_FrameTex : register(t10);

float2 ComputeTileMapUV(float2 vUV, float2 vStart, float2 vEnd, float2 vSize)
{
	float2	vNewUV = (float2)0.f;

	if (vUV.x == 0.f)
		vNewUV.x = vStart.x / vSize.x;

	else
		vNewUV.x = vEnd.x / vSize.x;

	if (vUV.y == 0.f)
		vNewUV.y = vStart.y / vSize.y;

	else
		vNewUV.y = vEnd.y / vSize.y;

	return vNewUV;
}

VS_OUTPUT_INSTANCING_TEX TileMapVS(VS_INPUT_INSTANCING_TEX input)
{
	VS_OUTPUT_INSTANCING_TEX	output = (VS_OUTPUT_INSTANCING_TEX)0;

	float3	vPos = input.vPos - g_vMeshSize * g_vMeshPivot;

	output.vPos = mul(float4(vPos, 1.f), input.matWVP);
	output.vUV = input.vUV;

	output.vOriginUV = input.vUV;
	output.iTileOption = input.iTileOption;

	if(input.iImgType == IMAGE_ATLAS)
		output.vUV = ComputeTileMapUV(input.vUV, input.vImgStart, input.vImgEnd, input.vImgSize);
	else
	{
		output.vUV = input.vUV;
	}

	output.iImgType = input.iImgType;
	output.iImgFrame = input.iImgFrame;
    output.iTileType = input.iTileType;


	return output;
}

PS_OUTPUT_SINGLE TileMapPS(VS_OUTPUT_INSTANCING_TEX input)
{
	PS_OUTPUT_SINGLE	output = (PS_OUTPUT_SINGLE)0;

	float4 vColor = (float4)0.f;

	if (IMAGE_ATLAS == input.iImgType)
	{
		vColor = g_BaseTexture.Sample(g_LinearSmp, input.vUV);
	}
	else
	{
		vColor = g_FrameTex.Sample(g_LinearSmp, float3(input.vUV, input.iImgFrame));
	}



	vColor = g_BaseTexture.Sample(g_LinearSmp, input.vUV);

    if (input.iTileOption == TILE_NOMOVE)
    {
        if (input.iTileType == TILE_RECT)
        {
            if (input.vOriginUV.x <= 0.03f)
                vColor = float4(1.f, 0.f, 0.f, 1.f);
            else if (input.vOriginUV.x >= 0.97f)
                vColor = float4(1.f, 0.f, 0.f, 1.f);
            else if (input.vOriginUV.y <= 0.03f)
                vColor = float4(1.f, 0.f, 0.f, 1.f);
            else if (input.vOriginUV.y >= 0.97f)
                vColor = float4(1.f, 0.f, 0.f, 1.f);
        }
        else
        {
            vColor *= float4(1.f, 0.f, 0.f, 1.f);
        }
    }
    else if (input.iTileOption == TILE_NONE)
    {
        if (input.iTileType == TILE_RECT)
        {
            if (input.vOriginUV.x <= 0.03f)
                vColor = float4(0.f, 1.f, 0.f, 1.f);
            else if (input.vOriginUV.x >= 0.97f)
                vColor = float4(0.f, 1.f, 0.f, 1.f);
            else if (input.vOriginUV.y <= 0.03f)
                vColor = float4(0.f, 1.f, 0.f, 1.f);
            else if (input.vOriginUV.y >= 0.97f)
                vColor = float4(0.f, 1.f, 0.f, 1.f);
        }
        else
        {
            vColor *= float4(0.f, 1.f, 0.f, 1.f);
        }
    }

    output.vColor = vColor;

    return output;
}
