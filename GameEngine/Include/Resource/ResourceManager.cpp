#include "ResourceManager.h"
#include "StaticMesh.h"
#include "AnimationMesh.h"
#include "ShaderManager.h"
#include "Texture.h"
#include "Material.h"
#include "../Device.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"
#include "Animation2DSequence.h"

#include "Sound.h"
#include "../PathManager.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
	SAFE_RELEASE_MAP(m_mapSound);
	SAFE_RELEASE_MAP(m_mapAnim2DSequence);
	SAFE_RELEASE_MAP(m_mapRenderState);
	SAFE_RELEASE_MAP(m_mapMaterial);
	SAFE_RELEASE_NORMAL_MAP(m_mapSampler);
	SAFE_RELEASE_MAP(m_mapTexture);
	SAFE_RELEASE_MAP(m_mapMesh);

	m_pSystem->close();
	m_pSystem->release();

	DESTROY_SINGLE(CShaderManager);
}

void CResourceManager::ClearMaterialIterator()
{
	m_MaterialIter = m_mapMaterial.begin();
}

CMaterial * CResourceManager::GetCurrentMaterial()
{
	if (m_mapMaterial.end() == m_MaterialIter)
	{
		return nullptr;
	}

	return m_MaterialIter->second;
}

void CResourceManager::NextMaterial()
{
	if (m_mapMaterial.end() != m_MaterialIter)
	{
		++m_MaterialIter;
	}
}

bool CResourceManager::Init()
{
	// Shader 초기화
	if (!GET_SINGLE(CShaderManager)->Init())
		return false;

	// Sound 생성
	System_Create(&m_pSystem);

	m_pSystem->init(512, FMOD_INIT_NORMAL, nullptr);

	m_pSystem->getMasterChannelGroup(&m_pMasterGroup);

	CreateSoundChannelGroup("BGM");
	CreateSoundChannelGroup("Normal");





	VertexColor	tColorTri[3]	=
	{
		VertexColor(Vector3(0.f, 0.5f, 0.f), Vector4::Red),
		VertexColor(Vector3(0.5f, -0.5f, 0.f), Vector4::Green),
		VertexColor(Vector3(-0.5f, -0.5f, 0.f), Vector4::Blue)
	};

	short	sColorTriIdx[3] = { 0, 1, 2 };

	if (!CreateMesh(POS_COLOR_LAYOUT, "ColorTri", tColorTri, sizeof(VertexColor), 3,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		sColorTriIdx, sizeof(short), 3, D3D11_USAGE_IMMUTABLE,
		DXGI_FORMAT_R16_UINT))
		return false;

	m_DefaultMeshList.push_back("ColorTri");

	VertexUV	tTexTri[3] =
	{
		VertexUV(Vector3(0.f, 0.5f, 0.f), Vector2(0.5f, 0.f)),
		VertexUV(Vector3(0.5f, -0.5f, 0.f), Vector2(1.f, 1.f)),
		VertexUV(Vector3(-0.5f, -0.5f, 0.f), Vector2(0.f, 1.f))
	};

	if (!CreateMesh(POS_UV_LAYOUT, "TexTri", tTexTri, sizeof(VertexUV), 3,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		sColorTriIdx, sizeof(short), 3, D3D11_USAGE_IMMUTABLE,
		DXGI_FORMAT_R16_UINT))
		return false;

	m_DefaultMeshList.push_back("TexTri");

	VertexUV	tTexRect[4] =
	{
		VertexUV(Vector3(0.f, 1.f, 0.f), Vector2(0.f, 0.f)),
		VertexUV(Vector3(1.f, 1.f, 0.f), Vector2(1.f, 0.f)),
		VertexUV(Vector3(0.f, 0.f, 0.f), Vector2(0.f, 1.f)),
		VertexUV(Vector3(1.f, 0.f, 0.f), Vector2(1.f, 1.f)),
	};

	short	sRectIdx[6] = { 0, 1, 3, 0, 3, 2 };

	if (!CreateMesh(POS_UV_LAYOUT, "TexRect", tTexRect, sizeof(VertexUV), 4,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		sRectIdx, sizeof(short), 6, D3D11_USAGE_IMMUTABLE,
		DXGI_FORMAT_R16_UINT))
		return false;

	m_DefaultMeshList.push_back("TexRect");

	Vector3	tColliderRect[5] =
	{
		Vector3(0.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(1.f, 1.f, 0.f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 0.f, 0.f)
	};

	if (!CreateMesh(STATIC_INSTANCING_LAYOUT, "ColliderRect", tColliderRect, sizeof(Vector3), 5,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP))
		return false;

	m_DefaultMeshList.push_back("ColliderRect");

	Vector3	tColliderSphere2D[13] = {};

	tColliderSphere2D[0] = Vector3(1.f, 0.f, 0.f);
	tColliderSphere2D[12] = Vector3(1.f, 0.f, 0.f);
	for (int i = 1; i <= 11; ++i)
	{
		tColliderSphere2D[i].x = cosf(30.f * i * PI / 180.f);
		tColliderSphere2D[i].y = sinf(30.f * i * PI / 180.f);
	}

	if (!CreateMesh(STATIC_INSTANCING_LAYOUT, "ColliderSphere2D", tColliderSphere2D, sizeof(Vector3), 13,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP))
		return false;

	m_DefaultMeshList.push_back("ColliderSphere2D");

	Vector3	tColliderOBB2D[5] =
	{
		Vector3(-1.f, 1.f, 0.f),
		Vector3(1.f, 1.f, 0.f),
		Vector3(1.f, -1.f, 0.f),
		Vector3(-1.f, -1.f, 0.f),
		Vector3(-1.f, 1.f, 0.f)
	};

	if (!CreateMesh(STATIC_INSTANCING_LAYOUT, "ColliderOBB2D", tColliderOBB2D, sizeof(Vector3), 5,
		D3D11_USAGE_IMMUTABLE, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP))
		return false;

	m_DefaultMeshList.push_back("ColliderOBB2D");

	CreateSampler("LinearSmp");

	ID3D11SamplerState*	pSampler = FindSampler("LinearSmp");

	CONTEXT->PSSetSamplers(0, 1, &pSampler);

	// AlphaBlend
	AddBlendDesc(RENDERSTATE_ALPHABLEND);
	CreateBlendState(RENDERSTATE_ALPHABLEND);
	CreateRasterizerState(RENDERSTATE_CULLNONE, D3D11_FILL_SOLID, D3D11_CULL_NONE);

	m_DefaultRenderStateList.push_back(RENDERSTATE_ALPHABLEND);
	m_DefaultRenderStateList.push_back(RENDERSTATE_CULLNONE);

	// None Depth
	CreateDepthStencil(RENDERSTATE_NONEDEPTH, FALSE);

	m_DefaultRenderStateList.push_back(RENDERSTATE_NONEDEPTH);

	// 충돌체용 재질
	CreateMaterial("ColliderRectMtrl");

	m_DefaultMaterialList.push_back("ColliderRectMtrl");

	CMaterial*	pMaterial = FindMaterial("ColliderRectMtrl");

	pMaterial->EnableInstancing();
	pMaterial->SetSubsetShader(STANDARD_COLLIDER_SHADER);
	pMaterial->SetInstancingShader(STANDARD_COLLIDER_SHADER);
	pMaterial->SetInstancingLayout(COLLIDER_LAYOUT);

	CMesh* pMesh = FindMesh("ColliderRect");
	pMesh->SetMaterial(pMaterial);
	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);


	CreateMaterial("ColliderSphere2DMtrl");

	m_DefaultMaterialList.push_back("ColliderSphere2DMtrl");

	pMaterial = FindMaterial("ColliderSphere2DMtrl");

	pMaterial->EnableInstancing();
	pMaterial->SetSubsetShader(STANDARD_COLLIDER_SHADER);
	pMaterial->SetInstancingShader(STANDARD_COLLIDER_SHADER);
	pMaterial->SetInstancingLayout(COLLIDER_LAYOUT);

	pMesh = FindMesh("ColliderSphere2D");

	pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMesh);

	SAFE_RELEASE(pMaterial);

	CreateMaterial("ColliderOBB2DMtrl");

	m_DefaultMaterialList.push_back("ColliderOBB2DMtrl");

	pMaterial = FindMaterial("ColliderOBB2DMtrl");

	pMaterial->EnableInstancing();
	pMaterial->SetSubsetShader(STANDARD_COLLIDER_SHADER);
	pMaterial->SetInstancingShader(STANDARD_COLLIDER_SHADER);
	pMaterial->SetInstancingLayout(COLLIDER_LAYOUT);

	pMesh = FindMesh("ColliderOBB2D");

	pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMesh);

	SAFE_RELEASE(pMaterial);

	return true;
}

void CResourceManager::ChangeScene()
{
	// 기본으로 설정된 리소스들은 모두 카운트를 1씩 증가해준다.
	list<string>::iterator	iter;
	list<string>::iterator	iterEnd = m_DefaultMeshList.end();

	for(iter = m_DefaultMeshList.begin(); iter != iterEnd; ++iter)
	{
		FindMesh(*iter);
	}

	iterEnd = m_DefaultTextureList.end();

	for (iter = m_DefaultTextureList.begin(); iter != iterEnd; ++iter)
	{
		FindTexture(*iter);
	}

	iterEnd = m_DefaultRenderStateList.end();

	for (iter = m_DefaultRenderStateList.begin(); iter != iterEnd; ++iter)
	{
		FindRenderState(*iter);
	}

	iterEnd = m_DefaultMaterialList.end();

	for (iter = m_DefaultMaterialList.begin(); iter != iterEnd; ++iter)
	{
		FindMaterial(*iter);
	}

	unordered_map<size_t, class CMesh*>::iterator	iterMesh = m_mapMesh.begin();
	unordered_map<size_t, class CMesh*>::iterator	iterMeshEnd = m_mapMesh.end();

	for (; iterMesh != iterMeshEnd;)
	{
		if (iterMesh->second->Release() == 0)
		{
			iterMesh = m_mapMesh.erase(iterMesh);
		}

		else
		{
			++iterMesh;
		}
	}

	unordered_map<size_t, class CTexture*>::iterator	iterT = m_mapTexture.begin();
	unordered_map<size_t, class CTexture*>::iterator	iterTEnd = m_mapTexture.end();

	for (; iterT != iterTEnd;)
	{
		if (iterT->second->Release() == 0)
		{
			iterT = m_mapTexture.erase(iterT);
		}

		else
		{
			++iterT;
		}
	}

	unordered_map<size_t, class CMaterial*>::iterator	iterMtrl = m_mapMaterial.begin();
	unordered_map<size_t, class CMaterial*>::iterator	iterMtrlEnd = m_mapMaterial.end();

	for (; iterMtrl != iterMtrlEnd;)
	{
		if (iterMtrl->second->Release() == 0)
		{
			iterMtrl = m_mapMaterial.erase(iterMtrl);
		}

		else
		{
			++iterMtrl;
		}
	}

	unordered_map<size_t, class CRenderState*>::iterator	iterRS = m_mapRenderState.begin();
	unordered_map<size_t, class CRenderState*>::iterator	iterRSEnd = m_mapRenderState.end();

	for (; iterRS != iterRSEnd;)
	{
		if (iterRS->second->Release() == 0)
		{
			iterRS = m_mapRenderState.erase(iterRS);
		}

		else
		{
			++iterRS;
		}
	}

	unordered_map<size_t, class CAnimation2DSequence*>::iterator	iterAnim = m_mapAnim2DSequence.begin();
	unordered_map<size_t, class CAnimation2DSequence*>::iterator	iterAnimEnd = m_mapAnim2DSequence.end();

	for (; iterAnim != iterAnimEnd;)
	{
		if (iterAnim->second->Release() == 0)
		{
			iterAnim = m_mapAnim2DSequence.erase(iterAnim);
		}

		else
		{
			++iterAnim;
		}
	}
}

bool CResourceManager::CreateMesh(const string& strInputLayoutName, const string & strName,
	const void * pVertices, int iVtxSize, int iVtxCount, 
	D3D11_USAGE eVtxUsage, D3D11_PRIMITIVE_TOPOLOGY ePrimitive, 
	const void * pIndices, int iIdxSize, int iIdxCount, 
	D3D11_USAGE eIdxUsage, DXGI_FORMAT eFmt)
{
	CMesh*	pMesh = FindMesh(strName);

	if (pMesh)
	{
		SAFE_RELEASE(pMesh);
		return false;
	}

	ID3D11InputLayout*	pLayout = GET_SINGLE(CShaderManager)->FindInputLayout(strInputLayoutName);

	if (!pLayout)
		return false;

	pMesh = new CStaticMesh;
	
	if (!pMesh->CreateMesh(pLayout, strName, pVertices, iVtxSize, iVtxCount,
		eVtxUsage, ePrimitive, pIndices, iIdxSize, iIdxCount,
		eIdxUsage, eFmt))
	{
		SAFE_RELEASE(pMesh);
		return false;
	}

	hash<string>	hs;
	size_t	iKey = hs(strName);

	m_mapMesh.insert(make_pair(iKey, pMesh));

	return true;
}

CMesh * CResourceManager::FindMesh(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapMesh.find(iKey);
	
	if (iter == m_mapMesh.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

bool CResourceManager::LoadTexture(const string & strName, const TCHAR * pFileName,
	const string & strPathName)
{
	CTexture*	pTexture = FindTexture(strName);

	if (pTexture)
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(strName, pFileName, strPathName))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapTexture.insert(make_pair(iKey, pTexture));

	return true;
}

bool CResourceManager::LoadTextureFullPath(const string & strName, 
	const TCHAR * pFullPath)
{
	CTexture*	pTexture = FindTexture(strName);

	if (pTexture)
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	pTexture = new CTexture;

	if (!pTexture->LoadTextureFullPath(strName, pFullPath))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapTexture.insert(make_pair(iKey, pTexture));

	return true;
}

bool CResourceManager::LoadTexture(const string & strName, const vector<const TCHAR*>& vecFileName,
	const string & strPathName)
{
	CTexture*	pTexture = FindTexture(strName);

	if (pTexture)
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(strName, vecFileName, strPathName))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapTexture.insert(make_pair(iKey, pTexture));

	return true;
}

bool CResourceManager::LoadTextureFullPath(const string & strName, 
	const vector<const TCHAR*>& vecFullPath)
{
	CTexture*	pTexture = FindTexture(strName);

	if (pTexture)
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	pTexture = new CTexture;

	if (!pTexture->LoadTextureFullPath(strName, vecFullPath))
	{
		SAFE_RELEASE(pTexture);
		return false;
	}

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapTexture.insert(make_pair(iKey, pTexture));

	return true;
}

CTexture * CResourceManager::FindTexture(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapTexture.find(iKey);

	if (iter == m_mapTexture.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

bool CResourceManager::CreateMaterial(const string & strName)
{
	CMaterial*	pMaterial = FindMaterial(strName);

	if (pMaterial)
	{
		SAFE_RELEASE(pMaterial);
		return false;
	}

	pMaterial = new CMaterial;

	if (!pMaterial->Init())
	{
		SAFE_RELEASE(pMaterial);
		return false;
	}

	pMaterial->SetName(strName);
	pMaterial->SetSerialNumber(strName);

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapMaterial.insert(make_pair(iKey, pMaterial));

	return true;
}

CMaterial * CResourceManager::FindMaterial(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapMaterial.find(iKey);

	if (iter == m_mapMaterial.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

bool CResourceManager::CreateSampler(const string & strName, D3D11_FILTER eFilter, 
	D3D11_TEXTURE_ADDRESS_MODE eAddrU, D3D11_TEXTURE_ADDRESS_MODE eAddrV,
	D3D11_TEXTURE_ADDRESS_MODE eAddrW, UINT iMaxAnisotropy)
{
	ID3D11SamplerState*	pSampler = FindSampler(strName);

	if (pSampler)
		return false;

	D3D11_SAMPLER_DESC	tDesc = {};

	tDesc.Filter = eFilter;
	tDesc.AddressU = eAddrU;
	tDesc.AddressV = eAddrV;
	tDesc.AddressW = eAddrW;
	tDesc.MaxAnisotropy = iMaxAnisotropy;
	tDesc.MinLOD = -FLT_MAX;
	tDesc.MaxLOD = FLT_MAX;
	tDesc.MipLODBias = 0.f;
	tDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	tDesc.BorderColor[0] = 1.f;
	tDesc.BorderColor[1] = 1.f;
	tDesc.BorderColor[2] = 1.f;
	tDesc.BorderColor[3] = 1.f;

	if (FAILED(DEVICE->CreateSamplerState(&tDesc, &pSampler)))
		return false;

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapSampler.insert(make_pair(iKey, pSampler));

	return true;
}

ID3D11SamplerState * CResourceManager::FindSampler(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapSampler.find(iKey);

	if (iter == m_mapSampler.end())
		return nullptr;

	return iter->second;
}

bool CResourceManager::CreateBlendState(const string & strName, BOOL bAlphaCoverage, 
	BOOL bIndependent)
{
	CBlendState*	pState = (CBlendState*)FindRenderState(strName);
	
	if (!pState)
		return false;

	pState->SetName(strName);

	if (!pState->CreateBlend(bAlphaCoverage, bIndependent))
	{
		SAFE_RELEASE(pState);
		return false;
	}

	SAFE_RELEASE(pState);

	return true;
}

bool CResourceManager::AddBlendDesc(const string & strName, BOOL bBlendEnable, D3D11_BLEND eSrc,
	D3D11_BLEND eDest, D3D11_BLEND_OP eOp, D3D11_BLEND eSrcAlpha, D3D11_BLEND eDestAlpha,
	D3D11_BLEND_OP eOpAlpha, UINT8 iWriteMask)
{
	CBlendState*	pState = (CBlendState*)FindRenderState(strName);

	if (!pState)
	{
		pState = new CBlendState;

		hash<string>	hs;

		size_t	iKey = hs(strName);

		m_mapRenderState.insert(make_pair(iKey, pState));

		pState->AddRef();
	}

	pState->SetName(strName);

	if (!pState->AddBlendDesc(bBlendEnable, eSrc, eDest, eOp, eSrcAlpha, eDestAlpha, eOpAlpha,
		iWriteMask))
	{
		SAFE_RELEASE(pState);
		return false;
	}

	SAFE_RELEASE(pState);

	return true;
}

bool CResourceManager::CreateDepthStencil(const string & strName, BOOL bDepthEnable, 
	D3D11_DEPTH_WRITE_MASK eDepthWriteMask, D3D11_COMPARISON_FUNC eDepthFunc, BOOL bStencilEnable,
	UINT8 iStencilReadMask, UINT8 iStencilWriteMask, D3D11_DEPTH_STENCILOP_DESC tFrontFace, 
	D3D11_DEPTH_STENCILOP_DESC tBackFace)
{
	CDepthStencilState*	pState = (CDepthStencilState*)FindRenderState(strName);

	if (pState)
	{
		SAFE_RELEASE(pState);
		return false;
	}

	pState	= new CDepthStencilState;

	pState->SetName(strName);

	if (!pState->CreateDepthStencil(bDepthEnable, eDepthWriteMask, eDepthFunc, bStencilEnable,
		iStencilReadMask, iStencilWriteMask, tFrontFace, tBackFace))
	{
		SAFE_RELEASE(pState);
		return false;
	}

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapRenderState.insert(make_pair(iKey, pState));

	return true;
}

bool CResourceManager::CreateRasterizerState(const string & strName, D3D11_FILL_MODE eFillMode, 
	D3D11_CULL_MODE eCullMode, BOOL bFrontCounterClockwise, INT iDepthBias, FLOAT fDepthBiasClamp,
	FLOAT fSlopeScaledDepthBias, BOOL bDepthClipEnable, BOOL bScissorEnable, BOOL bMultisampleEnable,
	BOOL bAntialiasedLineEnable)
{
	CRasterizerState*	pState = (CRasterizerState*)FindRenderState(strName);

	if (pState)
	{
		SAFE_RELEASE(pState);
		return false;
	}

	pState = new CRasterizerState;

	pState->SetName(strName);

	if (!pState->CreateRasterizerState(eFillMode, eCullMode, bFrontCounterClockwise, iDepthBias,
		fDepthBiasClamp, fSlopeScaledDepthBias, bDepthClipEnable, bScissorEnable,
		bMultisampleEnable, bAntialiasedLineEnable))
	{
		SAFE_RELEASE(pState);
		return false;
	}

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapRenderState.insert(make_pair(iKey, pState));

	return true;
}

CRenderState * CResourceManager::FindRenderState(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapRenderState.find(iKey);

	if (iter == m_mapRenderState.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

bool CResourceManager::CreateAnimation2DSequence(const string & strName, bool bLoop, float fPlayTime, int iFrameCount)
{
	CAnimation2DSequence* pSequence = FindAnimation2DSequence(strName);

	if (pSequence)
	{
		SAFE_RELEASE(pSequence);
		return false;
	}

	pSequence = new CAnimation2DSequence;

	pSequence->CreateSequence(strName, bLoop, fPlayTime, iFrameCount);

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapAnim2DSequence.insert(make_pair(iKey, pSequence));

	return true;
}

bool CResourceManager::AddAnimation2DSequenceTexture(const string & strSequenceName, const string & strName, const TCHAR * pFileName, const string & strPathName)
{
	CAnimation2DSequence* pSequence = FindAnimation2DSequence(strSequenceName);

	if (!pSequence)
		return false;

	bool bResult = pSequence->AddTexture(strName, pFileName, strPathName);

	SAFE_RELEASE(pSequence);

	return bResult;
}

bool CResourceManager::AddAnimation2DSequenceFrameInfo(const string & strName, const Vector2 & vStart, const Vector2 & vEnd)
{
	CAnimation2DSequence* pSequence = FindAnimation2DSequence(strName);

	if (!pSequence)
		return false;

	pSequence->AddFrameInfo(vStart, vEnd);

	SAFE_RELEASE(pSequence);

	return true;
}

bool CResourceManager::SetAnimation2DSequenceFrameInfoAll(const string & strName, const Vector2 & vStart, const Vector2 & vEnd)
{
	CAnimation2DSequence* pSequence = FindAnimation2DSequence(strName);

	if (!pSequence)
		return false;

	pSequence->SetFrameInfoAll(vStart, vEnd);

	SAFE_RELEASE(pSequence);

	return true;
}

CAnimation2DSequence * CResourceManager::FindAnimation2DSequence(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapAnim2DSequence.find(iKey);

	if (iter == m_mapAnim2DSequence.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

bool CResourceManager::LoadSound(const string & strName, bool bLoop, const char * pFileName, const string & strPathName)
{
	CSound*	pSound = FindSound(strName);

	if (pSound)
	{
		SAFE_RELEASE(pSound);
		return false;
	}

	pSound = new CSound;

	const char*	pPath = GET_SINGLE(CPathManager)->FindPathMultibyte(strPathName);

	string	strFullPath;

	if (pPath)
		strFullPath = pPath;

	strFullPath += pFileName;

	// FMOD_DEFAULT = 사운드를 한번만 출력한다.
	FMOD_MODE	eMode = FMOD_DEFAULT;

	if (bLoop)
		eMode = FMOD_LOOP_NORMAL;

	// FMOD_RESULT createSound(1, 2, 3, 4);
	// 1. const char *name_or_data		 - 사운드 파일 의 경로
	// 2. FMOD_MODE mode				 - FMOD_DEFAULT: 사운드 한번 출력, FMOD_LOOP_NORMAL: 사운드 무한 반복
	// 3. FMOD_CREATESOUNDEXINFO *exinfo - 사운드에 대한 확장 정보를 추가적으로 받을 것인가를 선택, nullptr
	// 4. Sound **sound					 - 새로 만들 Sound 객체를 받을 Sound 객체의 주소
	if (m_pSystem->createSound(strFullPath.c_str(), eMode, nullptr, &pSound->m_pSound) != FMOD_OK)
	{
		SAFE_RELEASE(pSound);
		return false;
	}

	hash<string>	h;

	m_mapSound.insert(make_pair(h(strName), pSound));

	return true;
}

bool CResourceManager::CreateSoundChannelGroup(const string & strName)
{
	ChannelGroup*	pGroup = FindSoundChannelGroup(strName);

	if (pGroup)
		return false;

	m_pSystem->createChannelGroup(strName.c_str(), &pGroup);
	m_pMasterGroup->addGroup(pGroup);

	hash<string>	h;
	m_mapChannelGroup.insert(make_pair(h(strName), pGroup));

	return true;
}

CSound * CResourceManager::FindSound(const string & strName)
{
	hash<string>	hs;
	size_t	iKey = hs(strName);

	auto	iter = m_mapSound.find(iKey);

	if (iter == m_mapSound.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

ChannelGroup * CResourceManager::FindSoundChannelGroup(const string & strName)
{
	hash<string>	hs;
	size_t	iKey = hs(strName);

	auto	iter = m_mapChannelGroup.find(iKey);

	if (iter == m_mapChannelGroup.end())
		return nullptr;

	return iter->second;
}

void CResourceManager::UpdateSound()
{
	m_pSystem->update();
}

void CResourceManager::Play(CSound * pSound, const string & strGroup)
{
	ChannelGroup*	pGroup = FindSoundChannelGroup(strGroup);

	if (!pGroup)
		return;

	m_pSystem->playSound(pSound->m_pSound, pGroup, false, &pSound->m_pChannel);
}

void CResourceManager::Pause(CSound * pSound, const string & strGroup)
{
	ChannelGroup*	pGroup = FindSoundChannelGroup(strGroup);

	if (!pGroup)
	{
		BOOM;
		return;
	}


	FMOD_RESULT rs = m_pSystem->playSound(pSound->m_pSound, pGroup, true, &pSound->m_pChannel);
	int a = 0;
}

void CResourceManager::Stop(const string & strGroup)
{
	ChannelGroup*	pGroup = FindSoundChannelGroup(strGroup);

	if (!pGroup)
		return;

	pGroup->stop();
}

void CResourceManager::SetVolume(int iVolume, const string & strGroup)
{
	ChannelGroup*	pGroup = FindSoundChannelGroup(strGroup);

	if (!pGroup)
		return;

	pGroup->setVolume(iVolume / 100.f);
}

void CResourceManager::Mute(const string & strGroup)
{
	ChannelGroup*	pGroup = FindSoundChannelGroup(strGroup);

	if (!pGroup)
		return;

	pGroup->setMute(true);
}

void CResourceManager::UnMute(const string & strGroup)
{
	ChannelGroup*	pGroup = FindSoundChannelGroup(strGroup);

	if (!pGroup)
		return;

	pGroup->setMute(false);
}

void CResourceManager::Mute()
{
	m_pMasterGroup->setMute(true);
}

void CResourceManager::UnMute()
{
	m_pMasterGroup->setMute(false);
}