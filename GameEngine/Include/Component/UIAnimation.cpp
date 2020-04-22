#include "UIAnimation.h"


#include "ColliderRect.h"


#include "../Resource/StaticMesh.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/ShaderManager.h"
#include "../Resource/Shader.h"
#include "../Resource/BlendState.h"
#include "../Resource/Texture.h"

#include "../Component/Animation2D.h"







CUIAnimation::CUIAnimation()
{
	m_bTickUpdate = true;

	SetTypeID<CUIAnimation>();

	m_pTexture = nullptr;
	m_pAnim = nullptr;
}

CUIAnimation::CUIAnimation(const CUIAnimation & com)
{
}

CUIAnimation::~CUIAnimation()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pAnim);
}

bool CUIAnimation::Init()
{
	if (!CUI::Init())
		return false;


	// m_pShader = GET_SINGLE(CShaderManager)->FindShader(UI_SHADER);
	// SAFE_RELEASE(m_pShader);


	return true;
}

void CUIAnimation::Begin()
{
	CUI::Begin();
}

void CUIAnimation::Update(float fTime)
{
	CUI::Update(fTime);

	m_pAnim->Update(fTime);
}

void CUIAnimation::Render(float fTime)
{



	MaterialCBuffer tCBuffer = {};
	tCBuffer.vDif = Vector4::White;

	GET_SINGLE(CShaderManager)->UpdateCBuffer(MATERIAL_CBUFFER, &tCBuffer);



	if (nullptr != m_pAnim)
	{
		m_pAnim->SetShader();
		CTexture* pTex = m_pAnim->GetAnimTexture();
		pTex->SetTexture(0, CST_PIXEL);

		SAFE_RELEASE(pTex);
	}
	else
	{
		m_pTexture->SetTexture(0, CST_PIXEL);
	}

	CUI::Render(fTime);

}







void CUIAnimation::CreateAnim2D()
{
	if (nullptr != m_pAnim)
	{
		return;
	}

	m_pAnim = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	SAFE_RELEASE(m_pShader);
	m_pShader = GET_SINGLE(CShaderManager)->FindShader(UI_ANIM2D_SHADER);

}

void CUIAnimation::AddAnim2DSequence(const std::string & strName)
{
	m_pAnim->AddAnimation2DSequence(strName);
}

void CUIAnimation::ChangeAnimation(const std::string & strName)
{
	m_pAnim->ChangeUIAnimation(strName);
}

void CUIAnimation::SetReturnSequenceName(const std::string & strName, const std::string & strReturnName)
{
	m_pAnim->SetReturnSequenceName(strName, strReturnName);
}

CStaticMesh * CUIAnimation::GetMesh()
{
	return nullptr;
}

bool CUIAnimation::IsAnimationOver() const
{
	return m_pAnim->IsSequenceEnd();
}


void CUIAnimation::SetTexture(const string & strName, const TCHAR * pFileName, const string & strPathName)
{
	SAFE_RELEASE(m_pTexture);
	if (pFileName)
		GET_SINGLE(CResourceManager)->LoadTexture(strName, pFileName, strPathName);
	m_pTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);


}