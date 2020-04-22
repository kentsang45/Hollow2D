
#include "Animation2D.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation2DSequence.h"
#include "../Resource/Material.h"
#include "StaticMeshComponent.h"
#include "../Resource/Texture.h"

CAnimation2D::CAnimation2D()
{
	SetTypeID<CAnimation2D>();
	m_pSequence = nullptr;
	m_pMaterial = nullptr;
}

CAnimation2D::CAnimation2D(const CAnimation2D & com)
{
	m_iRef = 1;
	m_pMaterial = nullptr;
}

CAnimation2D::~CAnimation2D()
{
	SAFE_RELEASE(m_pSequence);
	SAFE_RELEASE(m_pMaterial);
	SAFE_RELEASE_MAP(m_mapAnimSequence);
}

bool CAnimation2D::IsSequenceEnd() const
{
	return  m_pSequence->IsSequenceEnd();
}

CAnimation2DSequence * CAnimation2D::GetSequence() const
{
	return m_pSequence;
}

CTexture * CAnimation2D::GetAnimTexture() const
{
	return m_pSequence->GetTexture();
}

Animation2DFrameInfo CAnimation2D::GetAnimFrame() const
{
	return m_pSequence->GetFrame();
}

unsigned int CAnimation2D::GetTextureWidth() const
{
	return m_pSequence->GetTexture()->GetWidth();
}

unsigned int CAnimation2D::GetTextureHeight() const
{
	return m_pSequence->GetTexture()->GetHeight();
}

bool CAnimation2D::AddAnimation2DSequence(const string & strName)
{
	CAnimation2DSequence* pSequence = FindAnimSequence(strName);

	if (pSequence)
	{
		SAFE_RELEASE(pSequence);
		return false;
	}

	pSequence = GET_SINGLE(CResourceManager)->FindAnimation2DSequence(strName);

	if (!pSequence)
		return false;

	CAnimation2DSequence*	pNewSequence = pSequence->Clone();

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapAnimSequence.insert(make_pair(iKey, pNewSequence));

	if (!m_pSequence)
	{
		m_pSequence = pNewSequence;
		m_pSequence->AddRef();
	}

	pNewSequence->SetMaterial(m_pMaterial);

	SAFE_RELEASE(pSequence);

	return true;
}

CAnimation2DSequence * CAnimation2D::FindAnimSequence(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapAnimSequence.find(iKey);

	if (iter == m_mapAnimSequence.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

void CAnimation2D::SetMaterial(CMaterial * pMaterial)
{
	SAFE_RELEASE(m_pMaterial);
	m_pMaterial = pMaterial;

	if (m_pMaterial)
		m_pMaterial->AddRef();

	auto	iter = m_mapAnimSequence.begin();
	auto	iterEnd = m_mapAnimSequence.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->second->SetMaterial(pMaterial);
	}
}

void CAnimation2D::SetReturnSequenceName(const string & strSequence, const string & strReturnName)
{
	CAnimation2DSequence*	pSequence = FindAnimSequence(strSequence);

	if (pSequence)
		pSequence->SetReturnSequence(strReturnName);

	SAFE_RELEASE(pSequence);
}

void CAnimation2D::ChangeAnimation(const string & strName)
{
	CAnimation2DSequence*	pSequence = FindAnimSequence(strName);

	if (m_pSequence == pSequence || !pSequence)
	{
		SAFE_RELEASE(pSequence);
		return;
	}

	m_pSequence->Clear();

	SAFE_RELEASE(m_pSequence);
	m_pSequence = pSequence;

	CMaterial*	pMaterial = m_pOwner->GetMaterial();

	m_pSequence->SetMaterialTexture(pMaterial);

	SAFE_RELEASE(pMaterial);
}

void CAnimation2D::ChangeUIAnimation(const string & strName)
{
	CAnimation2DSequence*	pSequence = FindAnimSequence(strName);

	if (m_pSequence == pSequence || !pSequence)
	{
		SAFE_RELEASE(pSequence);
		return;
	}

	m_pSequence->Clear();

	SAFE_RELEASE(m_pSequence);
	m_pSequence = pSequence;



	/*CMaterial*	pMaterial = m_pOwner->GetMaterial();

	m_pSequence->SetMaterialTexture(pMaterial);

	SAFE_RELEASE(pMaterial);
*/

}

bool CAnimation2D::Init()
{
	return true;
}

void CAnimation2D::Update(float fTime)
{
	if (m_pSequence->Update(fTime))
	{
		if (m_pSequence->GetReturnSequence().length() > 0)
		{
			ChangeAnimation(m_pSequence->GetReturnSequence());
		}
	}
}

void CAnimation2D::SetShader()
{
	if (!m_pSequence)
		return;

	m_pSequence->SetShader();
}

bool CAnimation2D::CreateNotify(const string & strSequenceName, const string & strNotifyName,
	int iFrame)
{
	CAnimation2DSequence*	pSequence = FindAnimSequence(strSequenceName);

	if (!pSequence)
		return false;

	bool bResult = pSequence->CreateNotify(strNotifyName, iFrame);

	SAFE_RELEASE(pSequence);

	return bResult;
}

bool CAnimation2D::CreateNotify(const string & strSequenceName, const string & strNotifyName, 
	float fTime)
{
	CAnimation2DSequence*	pSequence = FindAnimSequence(strSequenceName);

	if (!pSequence)
		return false;

	bool bResult = pSequence->CreateNotify(strNotifyName, fTime);

	SAFE_RELEASE(pSequence);

	return bResult;
}

bool CAnimation2D::AddNotifyFunction(const string & strSequenceName, const string& strNotifyName, void(*pFunc)(float))
{
	CAnimation2DSequence*	pSequence = FindAnimSequence(strSequenceName);

	if (!pSequence)
		return false;

	bool bResult = pSequence->AddNotifyFunction(strNotifyName, pFunc);

	SAFE_RELEASE(pSequence);

	return bResult;
}
