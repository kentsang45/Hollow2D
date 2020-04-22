#pragma once

#include "SceneComponent.h"

enum TEXT_ALIGH_H
{
	TAH_LEFT,
	TAH_CENTER,
	TAH_RIGHT
};

enum TEXT_ALIGH_V
{
	TAV_TOP,
	TAV_CENTER,
	TAV_BOTTOM
};

enum TEXT_RENDER_TYPE
{
	TRT_UI,
	TRT_2D,
	TRT_3D
};

class ENGINE_DLL CText :
	public CSceneComponent
{
public:
	CText();
	CText(const CText& text);
	~CText();

private:
	IDWriteTextFormat*		m_pTextFormat;
	IDWriteTextLayout*		m_pTextLayout;
	ID2D1SolidColorBrush*	m_pColor;
	ID2D1RenderTarget*		m_p2DTarget;
	TCHAR*					m_pText;
	int						m_iMaxCount;
	string					m_strFontKey;
	TCHAR*					m_pFontName;
	float					m_fSize;
	bool					m_bAlpha;
	float					m_fOpacity;
	Vector4					m_vColor;
	D2D1_RECT_F				m_tRenderArea;

	// Shadow
	bool					m_bShadow;
	ID2D1SolidColorBrush*	m_pShadowColor;
	bool					m_bShadowAlpha;
	float					m_fShadowOpacity;
	Vector4					m_vShadowColor;
	Vector3					m_vShadowOffset;

	TEXT_ALIGH_H			m_eAlignH;
	TEXT_ALIGH_V			m_eAlignV;
	TEXT_RENDER_TYPE		m_eRenderType;
	int						m_iZOrder;

public:
	TEXT_RENDER_TYPE GetTextRenderType()	const;
	int GetZOrder()	const;
	void SetZOrder(int iZOrder);

public:
	void SetRenderType(TEXT_RENDER_TYPE eType);
	void SetTextCount(int iMaxCount);
	void SetText(const TCHAR* pText);
	void AddText(const TCHAR* pText);
	void SetFont(const string& strName, const TCHAR* pFontName, int iWeight, int iStyle, int iStretch, float fSize,
		const TCHAR* pLocalName);
	void SetFont(const string& strName);
	void SetSize(float fSize);
	void SetAlignH(TEXT_ALIGH_H eAlign);
	void SetAlignV(TEXT_ALIGH_V eAlign);
	void SetShadow(bool bShadow);
	void SetShadowOffset(const Vector3& vShadowOffset);
	void SetShadowColor(float r, float g, float b, float a);
	void SetShadowColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void SetShadowColor(const Vector4& vColor);
	void SetShadowColor(unsigned int iColor);
	void AlphaBlend(bool bAlphaBlend);
	void ShadowAlphaBlend(bool bAlphaBlend);
	void SetOpacity(float fOpacity);
	void SetShadowOpacity(float fOpacity);
	void SetColor(float r, float g, float b, float a);
	void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void SetColor(const Vector4& vColor);
	void SetColor(unsigned int iColor);
	void SetRenderArea(float l, float t, float r, float b);

	void CreateTextLayout();

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};
