
#include "UIImage.h"
#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/ShaderManager.h"

CUIImage::CUIImage()
{
	m_pTexture = nullptr;
	m_vColor	= Vector4::White;
}

CUIImage::CUIImage(const CUIImage & com) :
	CUI(com)
{
	m_pTexture = com.m_pTexture;
	m_vColor	= com.m_vColor;

	if (m_pTexture)
		m_pTexture->AddRef();
}

CUIImage::~CUIImage()
{
	SAFE_RELEASE(m_pTexture);
}

void CUIImage::SetTexture(const string & strName, const TCHAR * pFileName, const string & strPathName)
{
	SAFE_RELEASE(m_pTexture);
	if (pFileName)
		GET_SINGLE(CResourceManager)->LoadTexture(strName, pFileName, strPathName);
	m_pTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);
}

bool CUIImage::Init()
{
	if (!CUI::Init())
		return false;

	return true;
}

void CUIImage::Begin()
{
	CUI::Begin();
}

void CUIImage::Update(float fTime)
{
	CUI::Update(fTime);
}

void CUIImage::Render(float fTime)
{
	MaterialCBuffer	tCBuffer = {};
	tCBuffer.vDif = m_vColor;

	GET_SINGLE(CShaderManager)->UpdateCBuffer(MATERIAL_CBUFFER, &tCBuffer);

	m_pTexture->SetTexture(0, CST_PIXEL);

	CUI::Render(fTime);
}
