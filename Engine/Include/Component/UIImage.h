#pragma once

#include "UI.h"

class ENGINE_DLL CUIImage :
	public CUI
{
	friend class CGameObject;

protected:
	CUIImage();
	CUIImage(const CUIImage& com);
	virtual ~CUIImage();

protected:
	class CTexture*	m_pTexture;
	Vector4			m_vColor;

public:
	void SetTexture(const string& strName, const TCHAR* pFileName = nullptr,
		const string& strPathName = TEXTURE_PATH);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

