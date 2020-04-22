#include "Text.h"
#include "../FontManager.h"
#include "../Device.h"
#include "Transform.h"
#include "../Scene/Scene.h"
#include "CameraComponent.h"
#include "../CameraManager.h"
#include "../Render/RenderManager.h"

CText::CText()
{
	m_bTickUpdate = true;

	SetTypeID<CText>();

	m_iZOrder = 0;

	m_p2DTarget = _RENDERTARGET2DUI;
	m_bShadow = false;

	m_pFontName = new TCHAR[64];
	memset(m_pFontName, 0, sizeof(TCHAR) * 64);
	lstrcpy(m_pFontName, TEXT("Noto Sans CJK KR Black"));
	m_fSize = 20.f;
	m_eAlignH = TAH_LEFT;
	m_eAlignV = TAV_CENTER;
	m_eRenderType = TRT_UI;

	m_bAlpha = false;
	m_bShadowAlpha = false;
	m_fOpacity = 1.f;
	m_fShadowOpacity = 1.f;
	m_vColor = Vector4::White;
	m_vShadowColor = Vector4::Black;

	m_iMaxCount = 256;
	m_pText = new TCHAR[m_iMaxCount];
	memset(m_pText, 0, sizeof(TCHAR) * m_iMaxCount);

	lstrcpy(m_pText, TEXT("Text"));

	m_pTextFormat = GET_SINGLE(CFontManager)->FindFont("NormalText1");
	m_pTextLayout = GET_SINGLE(CFontManager)->CreateTextLayout(m_pText, m_pTextFormat, 100.f, 100.f);
	m_pColor = GET_SINGLE(CFontManager)->CreateColor(m_vColor);
	m_pShadowColor = GET_SINGLE(CFontManager)->CreateColor(m_vShadowColor);
}

CText::CText(const CText & com) :
	CSceneComponent(com)
{
	*this = com;

	m_pText = new TCHAR[m_iMaxCount];
	lstrcpy(m_pText, com.m_pText);

	m_pFontName = new TCHAR[64];
	lstrcpy(m_pFontName, com.m_pFontName);

	CreateTextLayout();
}

CText::~CText()
{
	SAFE_RELEASE(m_pTextLayout);
	SAFE_DELETE_ARRAY(m_pText);
	SAFE_DELETE_ARRAY(m_pFontName);
}

TEXT_RENDER_TYPE CText::GetTextRenderType() const
{
	return m_eRenderType;
}

int CText::GetZOrder() const
{
	return m_iZOrder;
}

void CText::SetZOrder(int iZOrder)
{
	m_iZOrder = iZOrder;
}

void CText::SetRenderType(TEXT_RENDER_TYPE eType)
{
	m_eRenderType = eType;

	switch (eType)
	{
	case TRT_2D:
	case TRT_3D:
		m_p2DTarget = _RENDERTARGET2DMAIN;
		break;
	case TRT_UI:
		m_p2DTarget = _RENDERTARGET2DUI;
		break;
	}
}

void CText::SetTextCount(int iMaxCount)
{
	if (m_iMaxCount >= iMaxCount)
		return;

	TCHAR*	pText = new TCHAR[iMaxCount];
	memset(pText, 0, sizeof(TCHAR) * iMaxCount);

	memcpy(pText, m_pText, sizeof(TCHAR) * m_iMaxCount);

	m_iMaxCount = iMaxCount;

	SAFE_DELETE_ARRAY(m_pText);
	m_pText = pText;
}

void CText::SetText(const TCHAR * pText)
{
	int	iCount = lstrlen(pText);

	if (m_iMaxCount < iCount)
	{
		m_iMaxCount = iCount + 1;
		SAFE_DELETE_ARRAY(m_pText);
		m_pText = new TCHAR[m_iMaxCount];
	}

	memset(m_pText, 0, sizeof(TCHAR) * m_iMaxCount);
	lstrcpy(m_pText, pText);

	CreateTextLayout();
}

void CText::AddText(const TCHAR * pText)
{
	int	iCount = lstrlen(pText);
	int	iCurCount = lstrlen(m_pText);

	if (m_iMaxCount < iCount + iCurCount)
	{
		m_iMaxCount = (iCount + iCurCount) * 2;

		TCHAR*	pNewText = new TCHAR[m_iMaxCount];
		memset(pNewText, 0, sizeof(TCHAR) * m_iMaxCount);

		lstrcpy(pNewText, m_pText);

		SAFE_DELETE_ARRAY(m_pText);

		m_pText = pNewText;
	}

	lstrcat(m_pText, pText);

	CreateTextLayout();
}

void CText::SetFont(const string & strName, const TCHAR * pFontName, int iWeight, int iStyle, int iStretch, float fSize, const TCHAR * pLocalName)
{
	lstrcpy(m_pFontName, pFontName);
	m_fSize = fSize;

	GET_SINGLE(CFontManager)->CreateTextFormat(strName, pFontName, iWeight, iStyle, iStretch, fSize, pLocalName);

	m_pTextFormat = GET_SINGLE(CFontManager)->FindFont(strName);

	CreateTextLayout();
}

void CText::SetFont(const string & strName)
{
	m_pTextFormat = GET_SINGLE(CFontManager)->FindFont(strName);

	CreateTextLayout();
}

void CText::SetSize(float fSize)
{
	m_fSize = fSize;

	CreateTextLayout();
}

void CText::SetAlignH(TEXT_ALIGH_H eAlign)
{
	m_eAlignH = eAlign;

	if (!m_pTextLayout)
		CreateTextLayout();

	switch (eAlign)
	{
	case TAH_LEFT:
		m_pTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		break;
	case TAH_RIGHT:
		m_pTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		break;
	case TAH_CENTER:
		m_pTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		break;
	}
}

void CText::SetAlignV(TEXT_ALIGH_V eAlign)
{
	m_eAlignV = eAlign;

	if (!m_pTextLayout)
		CreateTextLayout();

	switch (eAlign)
	{
	case TAV_TOP:
		m_pTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		break;
	case TAV_BOTTOM:
		m_pTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		break;
	case TAV_CENTER:
		m_pTextLayout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		break;
	}
}

void CText::SetShadow(bool bShadow)
{
	m_bShadow = bShadow;
}

void CText::SetShadowOffset(const Vector3 & vShadowOffset)
{
	m_vShadowOffset = vShadowOffset;
}

void CText::SetShadowColor(float r, float g, float b, float a)
{
	m_vShadowColor = Vector4(r, g, b, a);

	m_pShadowColor = GET_SINGLE(CFontManager)->CreateColor(r, g, b, a);
}

void CText::SetShadowColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_vShadowColor = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);

	m_pShadowColor = GET_SINGLE(CFontManager)->CreateColor(r, g, b, a);
}

void CText::SetShadowColor(const Vector4 & vColor)
{
	m_vShadowColor = vColor;

	m_pShadowColor = GET_SINGLE(CFontManager)->CreateColor(vColor);
}

void CText::SetShadowColor(unsigned int iColor)
{
	m_vShadowColor.z = (iColor & 0x000000ff) / 255.f;
	m_vShadowColor.y = ((iColor >> 8) & 0x000000ff) / 255.f;
	m_vShadowColor.x = ((iColor >> 16) & 0x000000ff) / 255.f;
	m_vShadowColor.w = ((iColor >> 24) & 0x000000ff) / 255.f;

	m_pShadowColor = GET_SINGLE(CFontManager)->CreateColor(iColor);
}

void CText::AlphaBlend(bool bAlphaBlend)
{
	m_bAlpha = bAlphaBlend;
}

void CText::ShadowAlphaBlend(bool bAlphaBlend)
{
	m_bShadowAlpha = bAlphaBlend;
}

void CText::SetOpacity(float fOpacity)
{
	m_fOpacity = fOpacity;
}

void CText::SetShadowOpacity(float fOpacity)
{
	m_fShadowOpacity = fOpacity;
}

void CText::SetColor(float r, float g, float b, float a)
{
	m_vColor = Vector4(r, g, b, a);

	m_pColor = GET_SINGLE(CFontManager)->CreateColor(r, g, b, a);
}

void CText::SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_vColor = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);

	m_pColor = GET_SINGLE(CFontManager)->CreateColor(r, g, b, a);
}

void CText::SetColor(const Vector4 & vColor)
{
	m_vColor = vColor;

	m_pColor = GET_SINGLE(CFontManager)->CreateColor(vColor);
}

void CText::SetColor(unsigned int iColor)
{
	m_vColor.z = (iColor & 0x000000ff) / 255.f;
	m_vColor.y = ((iColor >> 8) & 0x000000ff) / 255.f;
	m_vColor.x = ((iColor >> 16) & 0x000000ff) / 255.f;
	m_vColor.w = ((iColor >> 24) & 0x000000ff) / 255.f;

	m_pColor = GET_SINGLE(CFontManager)->CreateColor(iColor);
}

void CText::SetRenderArea(float l, float t, float r, float b)
{
	m_tRenderArea = D2D1::RectF(l, _RESOLUTION.iHeight - t, r, _RESOLUTION.iHeight - b);

	CreateTextLayout();
}

void CText::CreateTextLayout()
{
	if (!m_pTextFormat)
		return;

	SAFE_RELEASE(m_pTextLayout);

	m_pTextLayout = GET_SINGLE(CFontManager)->CreateTextLayout(m_pText, m_pTextFormat,
		m_tRenderArea.right - m_tRenderArea.left, m_tRenderArea.bottom - m_tRenderArea.top);

	DWRITE_TEXT_RANGE	tRange;
	tRange.startPosition = 0;
	tRange.length = lstrlen(m_pText);

	m_pTextLayout->SetFontSize(m_fSize, tRange);
}

bool CText::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CText::Begin()
{
	CSceneComponent::Begin();
}

void CText::Update(float fTime)
{
	CSceneComponent::Update(fTime);
}

void CText::Render(float fTime)
{
	CComponent::Render(fTime);

	m_p2DTarget->BeginDraw();

	Vector3	vPos = m_pTransform->GetWorldPos();
	float	fHeight = m_tRenderArea.bottom - m_tRenderArea.top;

	if (m_eRenderType != TRT_UI)
	{
		// 카메라의  위치를 빼서  화면상의  위치를  구한다.
		CCameraComponent*	pCamera = m_pScene->GetCameraManager()->GetMainCamera();

		vPos -= pCamera->GetWorldPos();
	}

	// 그림자를  출력해야  할  경우  그림자를  먼저  출력한다.
	if (m_bShadow)
	{
		Vector3	vShadowPos = vPos + m_vShadowOffset;

		if (m_bShadowAlpha)
			m_pShadowColor->SetOpacity(m_fShadowOpacity);

		else
			m_pShadowColor->SetOpacity(1.f);

		vShadowPos.y = _RESOLUTION.iHeight - vShadowPos.y - fHeight;

		m_p2DTarget->DrawTextLayout(D2D1::Point2F(vShadowPos.x, vShadowPos.y), m_pTextLayout, m_pShadowColor, D2D1_DRAW_TEXT_OPTIONS_NONE);
	}

	if (m_bAlpha)
		m_pColor->SetOpacity(m_fOpacity);

	else
		m_pColor->SetOpacity(1.f);

	vPos.y = _RESOLUTION.iHeight - vPos.y - fHeight;

	m_p2DTarget->DrawTextLayout(D2D1::Point2F(vPos.x, vPos.y), m_pTextLayout, m_pColor, D2D1_DRAW_TEXT_OPTIONS_NONE);

	m_p2DTarget->EndDraw();
}
