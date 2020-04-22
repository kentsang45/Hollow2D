
#pragma once

#define	DIRECTINPUT_VERSION	0x8000

#include <d3d11.h>
#include <d3dcompiler.h>
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <typeinfo>
#include <dinput.h>
#include <functional>
#include <math.h>
#include <algorithm>

#include <dwrite.h>
#include <d2d1.h>

#include "fmod.hpp"

using namespace FMOD;

using namespace std;

#ifdef _WIN64
#pragma comment(lib, "fmod64_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif // _WIN64


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d2d1.lib")

#include "Macro.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#ifdef _DEBUG
#define	new	new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG


#define BOOM assert(false);




typedef struct _tagResolution
{
	int		iWidth;
	int		iHeight;
}Resolution, *PResolution;

typedef struct _tagVertexBuffer
{
	ID3D11Buffer*	pBuffer;
	int				iSize;	// 정점 1개의 크기
	int				iCount;	// 정점 수
	D3D11_USAGE		eUsage;
}VertexBuffer, *PVertexBuffer;

typedef struct _tagIndexBuffer
{
	ID3D11Buffer*	pBuffer;
	int				iSize;	// 정점 1개의 크기
	int				iCount;	// 정점 수
	D3D11_USAGE		eUsage;
	DXGI_FORMAT		eFmt;
}IndexBuffer, *PIndexBuffer;

typedef struct _tagVertexColor
{
	Vector3	vPos;
	Vector4	vColor;

	_tagVertexColor()
	{
	}

	_tagVertexColor(const Vector3& vP, const Vector4& vC)
	{
		vPos = vP;
		vColor = vC;
	}
}VertexColor, *PVertexColor;

typedef struct _tagVertexUV
{
	Vector3	vPos;
	Vector2	vUV;

	_tagVertexUV()
	{
	}

	_tagVertexUV(const Vector3& vP, const Vector2& vTex)
	{
		vPos = vP;
		vUV = vTex;
	}
}VertexUV, *PVertexUV;

typedef struct _tagCBuffer
{
	ID3D11Buffer*	pBuffer;
	int		iSize;
	int		iRegister;
	int		iShaderType;

	_tagCBuffer()
	{
		pBuffer = nullptr;
		iSize = 0;
		iRegister = 0;
		iShaderType = 0;
	}

	~_tagCBuffer()
	{
		SAFE_RELEASE(pBuffer);
	}
}CBuffer, *PCBuffer;

typedef struct _tagTransformCBuffer
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;
	Matrix	matWV;
	Matrix	matWVP;
	Vector3	vPivot;
	int	iEmpty;
	Vector3	vMeshSize;
	float	fEmpty1;
}TransformCBuffer, *PTransformCBuffer;

typedef struct _tagMaterialCBuffer
{
	Vector4	vDif;
	bool bPaperBurn;
	bool bEmpty1;
	bool bEmpty2;
	bool bEmpty3;
	Vector3 vEmpty;
}MaterialCBuffer, *PMaterialCBuffer;

typedef struct _tagAnimation2DCBuffer
{
	Vector2	vStart;
	Vector2	vEnd;
	int		iAnimType;
	float	fImageWidth;
	float	fImageHeight;
	float	fEmpty;
}Animation2DCBuffer, *PAnimation2DCBuffer;

typedef struct _tagCollisionChannel
{
	string	strName;
	COLLISION_TYPE	eType;

	_tagCollisionChannel()
	{
		eType = CT_BLOCK;
	}
}CollisionChannel, *PCollisionChannel;

typedef struct _tagCollisionProfile
{
	string	strName;
	string	strChannelName;
	list<CollisionChannel>	ChannelList;
}CollisionProfile, *PCollisionProfile;

typedef struct _tagBarCBuffer
{
	float	fPercent;
	int		iBarDir;
	float	fNextPercent;
	int		iNext;
}BarCBuffer, *PBarCBuffer;

typedef struct _tagOutLineCBuffer
{
	Vector2	vScale;
	Vector2	vImageSize;
	int		iPixelSize;
	Vector3	vEmpty;
}OutLineCBuffer, *POutLineCBuffer;

typedef struct _tagCBufferNode
{
	string	strName;
	int	iRegister;
	int	iSize;
	void*	pBuffer;
}CBufferNode, *PCBufferNode;

typedef struct _tagImageFrame
{
	Vector2	vStart;
	Vector2	vEnd;
	Vector2	vImageSize;
	int		iFrame;
	int		iImageType;
}ImageFrame, *PImageFrame;

typedef struct _tagInstancingBuffer
{
	ID3D11Buffer*	pBuffer;
	int				iSize;
	int				iCount;
	D3D11_USAGE	eUsage;
}InstancingBuffer, *PInstancingBuffer;

typedef struct _tagTileMapInstancingData
{
	Matrix	matWVP;
	Vector2	vStart;
	Vector2	vEnd;
	Vector2	vImageSize;
	int		iFrame;
	int		iImageType;
	int		iTileOption;
	int iTileType;
}TileMapInstancingData, *PTileMapInstancingData;

typedef struct _tagStaticInstancingData
{
	Matrix	matWVP;
	Vector4	vDiffuse;
	Vector3	vPivot;
	float	fEmpty;
}StaticInstancingData, *PStaticInstancingData;

typedef struct _tagAnim2DInstancingData
{
	Matrix	matWVP;
	Vector4	vDiffuse;
	Vector2	vStart;
	Vector2	vEnd;
	int		iAnimType;
	float	fImageWidth;
	float	fImageHeight;
}Anim2DInstancingData, *PAnim2DInstancingData;

typedef struct _tagPaperBurnCBuffer
{
	float	fFilter;
	Vector3	vColorOut;
	Vector3	vColorCenter;
	bool	bInverse;
	bool	bEmpty1;
	bool	bEmpty2;
	bool	bEmpty3;
	Vector3	vColorIn;
	float	fEmpty2;
}PaperBurnCBuffer, *PPaperBurnCBuffer;