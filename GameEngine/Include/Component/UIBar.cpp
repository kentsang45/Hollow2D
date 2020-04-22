
#include "UIBar.h"
#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/ShaderManager.h"

CUIBar::CUIBar()
{
	m_fPercent	= 1.f;
	m_pTexture	= nullptr;
	m_eBarDir	= BD_LEFTFROMRIGHT;
	m_bNext	= false;
	m_fTime = 0.f;
	m_fTimeLimit = 0.5f;
	m_fNextPercent	= 1.f;
}

CUIBar::CUIBar(const CUIBar & com)	:
	CUI(com)
{
	m_fPercent = com.m_fPercent;
	m_fNextPercent = com.m_fNextPercent;
	m_pTexture	= com.m_pTexture;
	m_eBarDir = com.m_eBarDir;
	m_fTimeLimit = com.m_fTimeLimit;
	m_bNext = false;
	m_fTime = 0.f;

	if(m_pTexture)
		m_pTexture->AddRef();
}

CUIBar::~CUIBar()
{
	SAFE_RELEASE(m_pTexture);
}

void CUIBar::SetPercent(float fPercent)
{
	if(m_fPercent < fPercent)
	{
		m_fPercent = fPercent;
		if(m_bNext)
		{
			m_bNext = false;
			m_fTime = 0.f;
		}
	}

	else
	{
		m_fNextPercent = fPercent;
		m_bNext = true;
		m_fTime = 0.f;
	}
}

void CUIBar::SetTexture(const string & strName, const TCHAR * pFileName, const string & strPathName)
{
	SAFE_RELEASE(m_pTexture);
	if(pFileName)
		GET_SINGLE(CResourceManager)->LoadTexture(strName, pFileName, strPathName);
	m_pTexture	= GET_SINGLE(CResourceManager)->FindTexture(strName);
}

void CUIBar::SetNextTimeLimit(float fTime)
{
	m_fTimeLimit	= fTime;
}

bool CUIBar::Init()
{
	if (!CUI::Init())
		return false;

	return true;
}

void CUIBar::Begin()
{
	CUI::Begin();

	SetShader(UI_BAR_SHADER);
}

void CUIBar::Update(float fTime)
{
	CUI::Update(fTime);

	if (m_bNext)
	{
		m_fTime += fTime;

		if (m_fTime >= m_fTimeLimit)
		{
			m_fPercent	= m_fNextPercent;
			m_fTime = 0.f;
			m_bNext = false;
		}
	}
}

void CUIBar::Render(float fTime)
{
	m_pTexture->SetTexture(0, CST_PIXEL);

	BarCBuffer	tBuffer	= {};
	tBuffer.fPercent	= m_fPercent;
	tBuffer.iBarDir = m_eBarDir;
	tBuffer.fNextPercent = m_fNextPercent;
	if(m_bNext)
		tBuffer.iNext	= 1;

	else
		tBuffer.iNext	= 0;

	GET_SINGLE(CShaderManager)->UpdateCBuffer(BAR_CBUFFER, &tBuffer);

	CUI::Render(fTime);
}
