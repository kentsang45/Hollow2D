#include "Animation2DSequence.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Material.h"
#include "ShaderManager.h"

CAnimation2DSequence::CAnimation2DSequence()	:
	m_fTime(0.f),
	m_fFrameTime(0.f),
	m_fSequenceTime(0.f),
	m_fPlayTime(1.f),
	m_bLoop(true),
	m_iFrame(0),
	m_iFrameMax(1),
	m_pAnim2D(nullptr),
	m_pMaterial(nullptr),
	m_bFrameEnd(false),
	m_fPlayScale(1.f)
{
}

CAnimation2DSequence::CAnimation2DSequence(const CAnimation2DSequence & anim)
{
	*this = anim;
	m_iRef = 1;

	m_NotifyList.clear();

	for (size_t i = 0; i < m_vecTexture.size(); ++i)
	{
		m_vecTexture[i]->AddRef();
	}

	m_pMaterial = nullptr;
}

CAnimation2DSequence::~CAnimation2DSequence()
{
	SAFE_RELEASE(m_pMaterial);
	SAFE_DELETE_NORMAL_VECLIST(m_NotifyList);
	SAFE_RELEASE_VECLIST(m_vecTexture);
}

const string & CAnimation2DSequence::GetReturnSequence() const
{
	return m_strReturnSequence;
}

CTexture * CAnimation2DSequence::GetTexture() const
{
	if (m_eAnimType == A2T_ATLAS)
	{
		m_vecTexture[0]->AddRef();
		return m_vecTexture[0];
	}

	m_vecTexture[m_iFrame]->AddRef();
	return m_vecTexture[m_iFrame];
}

Animation2DFrameInfo CAnimation2DSequence::GetFrame() const
{
	return m_vecFrameInfo[m_iFrame];
}

bool CAnimation2DSequence::Update(float fTime)
{
	m_fTime += fTime * m_fPlayScale;
	m_fSequenceTime += fTime * m_fPlayScale;

	m_bFrameEnd = false;
	bool	bLoopEnd = false;

	if (m_fTime >= m_fFrameTime)
	{
		m_fTime -= m_fFrameTime;
		++m_iFrame;		

		if (m_iFrame >= m_iFrameMax)
		{
			m_fSequenceTime -= m_fPlayTime;

			auto	iter = m_NotifyList.begin();
			auto	iterEnd = m_NotifyList.end();

			for (; iter != iterEnd; ++iter)
			{
				(*iter)->bCall = false;
			}

			m_bFrameEnd = true;
			if (m_bLoop)
			{
				m_iFrame = 0;
			}

			else
			{
				bLoopEnd = true;
				m_iFrame = m_iFrameMax - 1;
			}
		}
		if (m_eAnimType == A2T_FRAME)
		{
			if(m_pMaterial)
			{
				m_pMaterial->ClearTexture();
				m_pMaterial->SetTexture(0, m_vecTexture[m_iFrame]);
			}
		}
	}

	auto	iter = m_NotifyList.begin();
	auto	iterEnd = m_NotifyList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->fTime <= m_fSequenceTime && !(*iter)->bCall)
		{
			(*iter)->bCall = true;

			size_t	iSize = (*iter)->vecFunction.size();

			for (size_t i = 0; i < iSize; ++i)
			{
				(*iter)->vecFunction[i](fTime);
			}
		}
	}

	return bLoopEnd;
}

CAnimation2DSequence * CAnimation2DSequence::Clone()
{
	return new CAnimation2DSequence(*this);
}

void CAnimation2DSequence::SetMaterial(CMaterial * pMaterial)
{
	SAFE_RELEASE(m_pMaterial);
	m_pMaterial = pMaterial;

	if (m_pMaterial)
		m_pMaterial->AddRef();
}

bool CAnimation2DSequence::IsSequenceEnd() const
{
	return m_bFrameEnd;
}

void CAnimation2DSequence::SetPlayScale(float fScale)
{
	m_fPlayScale = fScale;
}

void CAnimation2DSequence::SetPlayTime(float fTime)
{
	m_fPlayTime = fTime;
}

bool CAnimation2DSequence::CreateSequence(const string& strName, bool bLoop, float fPlayTime, int iFrameCount)
{
	SetName(strName);
	m_bLoop = bLoop;
	m_fPlayTime = fPlayTime;
	m_iFrameMax = iFrameCount;
	m_fFrameTime = m_fPlayTime / m_iFrameMax;

	return true;
}

bool CAnimation2DSequence::AddTexture(const string & strName, const TCHAR * pFileName,
	const string & strPathName)
{
	GET_SINGLE(CResourceManager)->LoadTexture(strName, pFileName, strPathName);
	CTexture*	pTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);

	if (!pTexture)
		return false;

	m_vecTexture.push_back(pTexture);

	if(m_vecTexture.size() == 1)
		m_eAnimType = A2T_ATLAS;

	else
		m_eAnimType = A2T_FRAME;

	return true;
}

bool CAnimation2DSequence::CreateNotify(const string & strName, int iFrame)
{
	if (m_fFrameTime == 0.f)
		return false;

	PAnim2DNotify	pNotify = new Anim2DNotify;
	pNotify->strName = strName;
	pNotify->iFrame = iFrame;
	pNotify->fTime = iFrame * m_fFrameTime;

	m_NotifyList.push_back(pNotify);

	return true;
}

bool CAnimation2DSequence::CreateNotify(const string & strName, float fTime)
{
	if (m_fFrameTime == 0.f)
		return false;

	PAnim2DNotify	pNotify = new Anim2DNotify;
	pNotify->strName = strName;
	pNotify->iFrame = fTime / m_fFrameTime;
	pNotify->fTime = fTime;

	m_NotifyList.push_back(pNotify);

	return true;
}

bool CAnimation2DSequence::AddNotifyFunction(const string & strName, void(*pFunc)(float))
{
	auto	iter = m_NotifyList.begin();
	auto	iterEnd = m_NotifyList.end();

	PAnim2DNotify	pNotify = nullptr;

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->strName == strName)
		{
			pNotify = *iter;
			break;
		}
	}

	if (!pNotify)
		return false;

	pNotify->vecFunction.push_back(bind(pFunc, placeholders::_1));

	return true;
}

void CAnimation2DSequence::AddFrameInfo(const Vector2 & vStart, const Vector2 & vEnd)
{
	Animation2DFrameInfo	tInfo = {};
	tInfo.vStart = vStart;
	tInfo.vEnd = vEnd;
	tInfo.iFrame = m_vecFrameInfo.size();

	m_vecFrameInfo.push_back(tInfo);
}

void CAnimation2DSequence::SetFrameInfoAll(const Vector2 & vStart, const Vector2 & vEnd)
{
	Animation2DFrameInfo	tInfo = {};
	tInfo.vStart = vStart;
	tInfo.vEnd = vEnd;

	for (int i = 0; i < m_iFrameMax; ++i)
	{
		tInfo.iFrame = i;

		m_vecFrameInfo.push_back(tInfo);
	}
}

void CAnimation2DSequence::SetMaterialTexture(CMaterial * pMaterial)
{
	if (!pMaterial)
		return;

	pMaterial->ClearTexture();

	CTexture*	pTexture = m_vecTexture[0];

	if (m_eAnimType == A2T_FRAME)
		pTexture = m_vecTexture[m_iFrame];

	pMaterial->SetTexture(0, pTexture);
}

void CAnimation2DSequence::SetShader()
{
	m_tCBuffer.vStart = m_vecFrameInfo[m_iFrame].vStart;
	m_tCBuffer.vEnd = m_vecFrameInfo[m_iFrame].vEnd;
	CTexture*	pTexture = m_vecTexture[0];

	if (m_eAnimType == A2T_FRAME)
		pTexture = m_vecTexture[m_iFrame];
	m_tCBuffer.fImageWidth = pTexture->GetWidth();
	m_tCBuffer.fImageHeight = pTexture->GetHeight();
	m_tCBuffer.iAnimType = m_eAnimType;

	GET_SINGLE(CShaderManager)->UpdateCBuffer(ANIM2D_CBUFFER, &m_tCBuffer);
}

void CAnimation2DSequence::Clear()
{
	m_fTime = 0.f;
	m_fSequenceTime = 0.f;
	m_iFrame = 0;

	auto	iter = m_NotifyList.begin();
	auto	iterEnd = m_NotifyList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->bCall = false;
	}
}

void CAnimation2DSequence::SetReturnSequence(const string & strName)
{
	m_strReturnSequence = strName;
}
