
cbuffer Transform	: register(b0)
{
	matrix	g_matWorld;
	matrix	g_matView;
	matrix	g_matProj;
	matrix	g_matWV;
	matrix	g_matWVP;
	float3	g_vMeshPivot;
    int     g_iTrEmpty;
	float3	g_vMeshSize;
	float	g_fTrEmpty1;
};

cbuffer	Material	: register(b1)
{
	float4	g_vMtrlDif;

	bool	g_bPaperBurn;
	bool	g_bMtrlEmpty1;
	bool	g_bMtrlEmpty2;
	bool	g_bMtrlEmpty3;
	float3	g_vMtrlEmpty1;
}


cbuffer PaperBurn : register(b6)
{
	float	g_fPaperBurnFilter;
	float3	g_vPaperBurnColorOutLine;
	float3	g_vPaperBurnColorCenter;
	bool	g_bPaperBurnInverse;
	bool	g_bPaperBurnEmpty1;
	bool	g_bPaperBurnEmpty2;
	bool	g_bPaperBurnEmpty3;
	float3	g_vPaperBurnColorInLine;
	float	g_fPaperBurnEmpty2;
}


Texture2D	g_BaseTexture : register(t0);
Texture2D	g_BurnTexture : register(t6);


SamplerState	g_LinearSmp	: register(s0);

//SamplerState	g_LinearSmp
//{
//	Filter = MIN_MAG_MIP_LINEAR;
//	AddressU = Wrap;
//	AddressV = Wrap;
//};


static const float2	g_vNullPos[4] =
{
	float2(-1.f, 1.f),
	float2(1.f, 1.f),
	float2(-1.f, -1.f),
	float2(1.f, -1.f)
};

static const float2	g_vNullUV[4] =
{
	float2(0.f, 0.f),
	float2(1.f, 0.f),
	float2(0.f, 1.f),
	float2(1.f, 1.f)
};

struct VS_INPUT_TEX
{
	float3	vPos	: POSITION;
	float2	vUV		: TEXCOORD;
};

struct VS_OUTPUT_TEX
{
	float4	vPos	: SV_POSITION;
	float2	vUV		: TEXCOORD;
};

VS_OUTPUT_TEX FullScreenVS(uint iVertexID : SV_VertexID)
{
	VS_OUTPUT_TEX	output = (VS_OUTPUT_TEX)0;

	output.vPos = float4(g_vNullPos[iVertexID], 0.f, 1.f);
	output.vUV = g_vNullUV[iVertexID];

	return output;
}



float4 PaperBurn(float4 vColor, float2 vUV)
{
	if (!g_bPaperBurn)
		return vColor;

	float4	vResult = vColor;

	float4	vBurnColor = g_BurnTexture.Sample(g_LinearSmp, vUV);

	if (!g_bPaperBurnInverse)
	{
		if (g_fPaperBurnFilter >= vBurnColor.r)
			vResult.a = 0.f;

		else
		{
			if (g_fPaperBurnFilter - 0.05f <= vBurnColor.r && vBurnColor.r <= g_fPaperBurnFilter + 0.05f)
				vResult.rgb = g_vPaperBurnColorOutLine;

			if (g_fPaperBurnFilter - 0.03f <= vBurnColor.r && vBurnColor.r <= g_fPaperBurnFilter + 0.03f)
				vResult.rgb = g_vPaperBurnColorCenter;

			if (g_fPaperBurnFilter - 0.02f <= vBurnColor.r && vBurnColor.r <= g_fPaperBurnFilter + 0.02f)
				vResult.rgb = g_vPaperBurnColorInLine;
		}
	}

	else
	{
		if (g_fPaperBurnFilter < vBurnColor.r)
			vResult.a = 0.f;

		else
		{
			if (g_fPaperBurnFilter - 0.05f <= vBurnColor.r && vBurnColor.r <= g_fPaperBurnFilter + 0.05f)
				vResult.rgb = g_vPaperBurnColorOutLine;

			if (g_fPaperBurnFilter - 0.03f <= vBurnColor.r && vBurnColor.r <= g_fPaperBurnFilter + 0.03f)
				vResult.rgb = g_vPaperBurnColorCenter;

			if (g_fPaperBurnFilter - 0.02f <= vBurnColor.r && vBurnColor.r <= g_fPaperBurnFilter + 0.02f)
				vResult.rgb = g_vPaperBurnColorInLine;
		}
	}

	return vResult;
}