#pragma once

#include "UI.h"

struct ENGINE_DLL _tagButtonStyle
{
	class CTexture*	pTexture;
	Vector4			vColor;
	// »óÅÂº° Sound
	_tagButtonStyle()
	{
		pTexture	= nullptr;
		vColor	= Vector4::White;
	}
};

class ENGINE_DLL CUIButton :
	public CUI
{
	friend class CGameObject;

protected:
	CUIButton();
	CUIButton(const CUIButton& com);
	virtual ~CUIButton();

protected:
	BUTTON_STATE	m_eButtonState;
	BUTTON_EVENT	m_eButtonEvent;
	_tagButtonStyle	m_tStyle[BS_END];
	function<void(float)>	m_Event[BE_END];

public:
	void SetButtonStyleTexture(BUTTON_STATE eState, const string& strName, const TCHAR* pFileName = nullptr,
		const string& strPathName = TEXTURE_PATH);
	void SetButtonStyleColor(BUTTON_STATE eState, const Vector4& vColor);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

protected:
	virtual void CollisionBody(class CColliderBase* pDest, float fTime);
	virtual void ExitBody(class CColliderBase* pDest, float fTime);

public:
	void SetButtonEvent(BUTTON_EVENT eEvent, void(*pFunc)(float));
	template <typename T>
	void SetButtonEvent(BUTTON_EVENT eEvent, T* pObj, void(T::*pFunc)(float))
	{
		m_Event[eEvent] = bind(pFunc, pObj, placeholders::_1);
	}
};

