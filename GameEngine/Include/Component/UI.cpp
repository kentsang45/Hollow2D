
#include "UI.h"
#include "../Resource/StaticMesh.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/ShaderManager.h"
#include "../Resource/Shader.h"
#include "ColliderRect.h"
#include "../Object/GameObject.h"
#include "../Resource/BlendState.h"

CUI::CUI()
{
	m_bTickUpdate = true;

	SetTypeID<CUI>();

	m_pMesh	= (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pLayout	= GET_SINGLE(CShaderManager)->FindInputLayout(POS_UV_LAYOUT);
	m_pShader	= GET_SINGLE(CShaderManager)->FindShader(UI_SHADER);

	m_bUI	= true;

	m_pAlphaBlend	= nullptr;

	m_pBody = nullptr;

	m_iZOrder = 0;
}

CUI::CUI(const CUI & com)	:
	CSceneComponent(com)
{
	m_pMesh	= com.m_pMesh;

	if(m_pMesh)
		m_pMesh->AddRef();

	m_pLayout	= com.m_pLayout;

	m_pShader	= com.m_pShader;

	if(m_pShader)
		m_pShader->AddRef();

	m_pAlphaBlend	= nullptr;

	m_iZOrder = com.m_iZOrder;

	m_pBody = nullptr;
}

CUI::~CUI()
{
	SAFE_RELEASE(m_pAlphaBlend);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pShader);
	SAFE_RELEASE(m_pMesh);
}

CMaterial * CUI::GetMaterial() const
{
	return nullptr;
}

int CUI::GetZOrder() const
{
	return m_iZOrder;
}

void CUI::SetZOrder(int iZOrder)
{
	m_iZOrder = iZOrder;


	if (m_pBody)
		m_pBody->SetZOrder(m_iZOrder);
}

void CUI::SetShader(const string & strName)
{
	SAFE_RELEASE(m_pShader);
	m_pShader	= GET_SINGLE(CShaderManager)->FindShader(strName);
}

void CUI::SetShader(const string & strName, const TCHAR * pFileName[ST_END], 
	const char * pEntry[ST_END], const string & strPathName)
{
	SAFE_RELEASE(m_pShader);
	GET_SINGLE(CShaderManager)->LoadShader(strName, pFileName, pEntry, strPathName);
	m_pShader = GET_SINGLE(CShaderManager)->FindShader(strName);
}

void CUI::SetMesh(const string & strName)
{
	SAFE_RELEASE(m_pMesh);
	m_pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh(strName);
}

void CUI::SetInputLayout(const string & strName)
{
	m_pLayout	= GET_SINGLE(CShaderManager)->FindInputLayout(strName);
}

void CUI::Unable()
{
	SAFE_RELEASE(m_pBody);
	m_pBody = nullptr;
}

bool CUI::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CUI::Begin()
{
	CSceneComponent::Begin();

	m_pBody	= m_pOwner->CreateComponent<CColliderRect>("UIBody");

	m_pBody->EnableUI();

	m_pBody->SetZOrder(m_iZOrder);

	AddChild(m_pBody, TR_POS);

	m_pBody->AddBeginOverlapCallback(this, &CUI::BodyCollision);
	m_pBody->AddEndOverlapCallback(this, &CUI::BodyCollisionExit);

	m_pAlphaBlend	= GET_SINGLE(CResourceManager)->FindRenderState(RENDERSTATE_ALPHABLEND);


}

void CUI::Update(float fTime)
{
	CSceneComponent::Update(fTime);

	if (nullptr != m_pBody)
	{
		m_pBody->SetRelativeScale(GetRelativeScale());
		m_pBody->SetExtent(GetRelativeScale().x, GetRelativeScale().y);
	}
	
}

void CUI::Render(float fTime)
{
	CSceneComponent::Render(fTime);

	size_t	iContainer = m_pMesh->GetContainerCount();

	m_pShader->SetShader();

	m_pAlphaBlend->SetState();

	for (size_t i = 0; i < iContainer; ++i)
	{
		size_t	iSubset = m_pMesh->GetSubsetCount(i);

		for (size_t j = 0; j < iSubset; ++j)
		{
			m_pMesh->Render(i, j);
		}
	}

	m_pAlphaBlend->ResetState();
}

void CUI::CollisionBody(CColliderBase * pDest, float fTime)
{
}

void CUI::ExitBody(CColliderBase * pDest, float fTime)
{
}

void CUI::BodyCollision(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	CollisionBody(pDest, fTime);
}

void CUI::BodyCollisionExit(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	ExitBody(pDest, fTime);
}
