#pragma once

#include "UI.h"

struct ENGINE_DLL _tagBarStyle
{
	class CTexture*	pTexture;
	Vector4			vColor;
	// »óÅÂº° Sound
	_tagBarStyle()
	{
		pTexture = nullptr;
		vColor = Vector4::White;
	}
};

class ENGINE_DLL CUIBar :
	public CUI
{
	friend class CGameObject;

protected:
	CUIBar();
	CUIBar(const CUIBar& com);
	virtual ~CUIBar();

protected:
	class CTexture*	m_pTexture;
	float		m_fPercent;	// 0 ~ 1
	float		m_fNextPercent;	// 0 ~ 1
	BAR_DIR		m_eBarDir;
	bool		m_bNext;
	float		m_fTime;
	float		m_fTimeLimit;

public:
	void SetPercent(float fPercent);
	void SetTexture(const string& strName, const TCHAR* pFileName = nullptr,
		const string& strPathName = TEXTURE_PATH);
	void SetNextTimeLimit(float fTime);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

