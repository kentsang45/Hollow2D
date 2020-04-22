
#include "UIButton.h"
#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/ShaderManager.h"
#include "ColliderRect.h"
#include "../Input.h"

CUIButton::CUIButton()
{
	m_bTickUpdate = true;

	SetTypeID<CUIButton>();

	m_eButtonState	= BS_NORMAL;
	m_eButtonEvent	= BE_NONE;
}

CUIButton::CUIButton(const CUIButton & com) :
	CUI(com)
{
}

CUIButton::~CUIButton()
{
	for (int i = 0; i < BS_END; ++i)
	{
		SAFE_RELEASE(m_tStyle[i].pTexture);
	}
}

void CUIButton::SetButtonStyleTexture(BUTTON_STATE eState, const string & strName, 
	const TCHAR * pFileName, const string & strPathName)
{
	if(pFileName)
		GET_SINGLE(CResourceManager)->LoadTexture(strName, pFileName, strPathName);

	SAFE_RELEASE(m_tStyle[eState].pTexture);
	m_tStyle[eState].pTexture	= GET_SINGLE(CResourceManager)->FindTexture(strName);
}

void CUIButton::SetButtonStyleColor(BUTTON_STATE eState, const Vector4 & vColor)
{
	m_tStyle[eState].vColor	= vColor;
}

bool CUIButton::Init()
{
	if (!CUI::Init())
		return false;

	return true;
}

void CUIButton::Begin()
{
	CUI::Begin();
}

void CUIButton::Update(float fTime)
{
	CUI::Update(fTime);

	if (m_eButtonState == BS_MOUSEON)
	{
		if (GET_SINGLE(CInput)->LButtonDown())
		{
			m_eButtonState	= BS_CLICK;
		}
	}

	else if (m_eButtonState == BS_CLICK)
	{
		if (GET_SINGLE(CInput)->LButtonRelease())
		{
			m_eButtonState = BS_MOUSEON;

			if (m_Event[BE_CLICK])
				m_Event[BE_CLICK](fTime);
		}
	}
}

void CUIButton::Render(float fTime)
{
	MaterialCBuffer	tCBuffer = {};
	tCBuffer.vDif = m_tStyle[m_eButtonState].vColor;

	GET_SINGLE(CShaderManager)->UpdateCBuffer(MATERIAL_CBUFFER, &tCBuffer);

	m_tStyle[m_eButtonState].pTexture->SetTexture(0, CST_PIXEL);
		
	CUI::Render(fTime);
}

void CUIButton::CollisionBody(CColliderBase * pDest, float fTime)
{
	m_eButtonState	= BS_MOUSEON;

	if(m_Event[BE_MOUSEON])
		m_Event[BE_MOUSEON](fTime);
}

void CUIButton::ExitBody(CColliderBase * pDest, float fTime)
{
	m_eButtonState = BS_NORMAL;

	if (m_Event[BE_MOUSEOFF])
		m_Event[BE_MOUSEOFF](fTime);
}

void CUIButton::SetButtonEvent(BUTTON_EVENT eEvent, void(*pFunc)(float))
{
	m_Event[eEvent]	= pFunc;
}
