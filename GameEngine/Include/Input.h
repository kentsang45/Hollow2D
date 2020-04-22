#pragma once

#include "GameEngine.h"

enum KEY_STATE
{
	KS_PRESS,
	KS_PUSH,
	KS_RELEASE,
	KS_END
};

enum KEY_UNION
{
	KU_CTRL,
	KU_ALT,
	KU_SHIFT,
	KU_END
};

enum MOUSE_INFO_TYPE
{
	MIT_LBUTTON,
	MIT_RBUTTON,
	MIT_END
};

typedef struct _tagKeyInfo
{
	unsigned char	cKey;
	bool		bOnEvent[KS_END];

	_tagKeyInfo() :
		cKey(0)
	{
		memset(bOnEvent, 0, sizeof(bool) * KS_END);
	}
}KeyInfo, *PKeyInfo;

typedef struct _tagKeyAxisInfo
{
	unsigned char	cKey;
	float			fScale;

	_tagKeyAxisInfo() :
		cKey(0),
		fScale(0.f)
	{
	}
}KeyAxisInfo, *PKeyAxisInfo;

typedef struct _tagKeyAxis
{
	string	strName;
	list<KeyAxisInfo>	KeyList;
	function<void(float, float)>	func;

	_tagKeyAxis()
	{
	}

}KeyAxis, *PKeyAxis;

enum ACTION_KEY_STATE
{
	AKS_PRESS,
	AKS_PUSH,
	AKS_RELEASE,
	AKS_DOUBLE,
	AKS_END
};

typedef struct _tagKeyActionInfo
{
	unsigned char	cKey;
	bool			bSKey[KU_END];
	float			fKeyTime;

	_tagKeyActionInfo() :
		cKey(0),
		fKeyTime(0.f)
	{
		memset(bSKey, 0, sizeof(bool) * KU_END);
	}
}KeyActionInfo, *PKeyActionInfo;

typedef struct _tagKeyAction
{
	string	strName;
	list<KeyActionInfo>	KeyList;
	function<void(float)>	func[AKS_END];
	bool		bKeyState[AKS_END];

	_tagKeyAction()
	{
		memset(bKeyState, 0, sizeof(bool) * AKS_END);
	}
}KeyAction, *PKeyAction;

enum INPUT_TYPE
{
	IT_DX,
	IT_WINDOW
};

enum MOUSE_TYPE
{
	MT_LBUTTON,
	MT_RBUTTON,
	MT_END
};

class ENGINE_DLL CInput
{
private:
	IDirectInput8*			m_pInput;
	IDirectInputDevice8*	m_pKeyboard;
	IDirectInputDevice8*	m_pMouse;
	unsigned char			m_KeyState[256];
	KeyInfo					m_tKeyInfo[256];
	DIMOUSESTATE			m_tMouseState;
	unordered_map<size_t, PKeyAxis>	m_mapAxis;
	unordered_map<size_t, PKeyAction>	m_mapAction;
	list<unsigned char>		m_UseKeyList;
	float					m_fDoubleKeyTime;
	INPUT_TYPE				m_eInputType;
	Vector2					m_vMousePos;
	Vector2					m_vMouseWorldPos;
	Vector2					m_vMouseMove;
	class CTransform*		m_pMouseTr;
	class CMesh*			m_pMouseMesh;
	class CShader*			m_pMouseShader;
	class CAnimation2D*		m_pMouseAnim;
	class CTexture*			m_pMouseTexture;
	class CRenderState*		m_pAlphaBlend;
	bool					m_bShowCursor;
	KeyInfo					m_tMouseInfo[MT_END];

public:
	Vector2 GetMousePos()	const;
	Vector2 GetMouseWorldPos()	const;
	Vector2 GetMouseMove()	const;
	bool LButtonDown()	const;
	bool RButtonDown()	const;
	bool LButtonPush()	const;
	bool RButtonPush()	const;
	bool LButtonRelease()	const;
	bool RButtonRelease()	const;

public:
	void SetDoubleKeyTime(float fTime);
	void CreateAnim2D();
	void AddAnim2DSequence(const string& strName);
	void ChangeAnimation(const string& strName);
	void SetReturnSequenceName(const string& strName, const string& strReturnName);
	void SetMouseTexture(const string& strName, const TCHAR* pFileName = nullptr, const string& strPathName = TEXTURE_PATH);
	void MouseSize(const Vector2& vSize);
	void AlphaBlendEnable();

private:
	bool InitDX();
	bool InitWindow();

public:
	bool Init();
	void Update(float fTime);
	void Render(float fTime);

private:
	void UpdateMouse(float fTime);
	void UpdateKeyInfo(float fTime);
	void UpdateKeyInfoDX(float fTime);
	void UpdateKeyInfoWindow(float fTime);
	void UpdateAxis(float fTime);
	void UpdateAction(float fTime);

private:
	void ReadKeyboard();
	void ReadMouse();

public:
	void AddAxisKey(const string& strName, unsigned char cKey, float fScale = 0.f);
	void BindAxis(const string& strName, void(*pFunc)(float, float));
	template <typename T>
	void BindAxis(const string& strName, T* pObj, void (T::*pFunc)(float, float))
	{
		PKeyAxis	pAxis = FindAxis(strName);

		if (!pAxis)
		{
			pAxis = new KeyAxis;
			pAxis->strName = strName;

			hash<string>	hs;

			size_t	iKey = hs(strName);

			m_mapAxis.insert(make_pair(iKey, pAxis));
		}

		pAxis->func = bind(pFunc, pObj, placeholders::_1, placeholders::_2);
	}

public:
	void AddActionKey(const string& strName, unsigned char cKey);
	void AddActionKeyUnion(const string& strName, unsigned char cKey, KEY_UNION eType,
		bool bCheck);
	void BindAction(const string& strName, ACTION_KEY_STATE eType, void(*pFunc)(float));
	template <typename T>
	void BindAction(const string& strName, ACTION_KEY_STATE eType, T* pObj, void (T::*pFunc)(float))
	{
		PKeyAction	pAction = FindAction(strName);

		if (!pAction)
		{
			pAction = new KeyAction;
			pAction->strName = strName;

			hash<string>	hs;

			size_t	iKey = hs(strName);

			m_mapAction.insert(make_pair(iKey, pAction));
		}

		pAction->func[eType] = bind(pFunc, pObj, placeholders::_1);
	}


private:
	PKeyAxis FindAxis(const string& strName);
	PKeyAction FindAction(const string& strName);
	unsigned char ConvertKey(unsigned char cKey);

	DECLARE_SINGLE(CInput)
};

