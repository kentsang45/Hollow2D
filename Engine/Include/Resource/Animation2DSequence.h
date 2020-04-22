#pragma once

#include "../Ref.h"

typedef struct _tagAnim2DNotify
{
	string		strName;
	vector<function<void(float)>>	vecFunction;
	int			iFrame;
	float		fTime;
	bool		bCall;

	_tagAnim2DNotify() :
		bCall(false),
		fTime(0.f),
		iFrame(0)
	{
	}
}Anim2DNotify, *PAnim2DNotify;

typedef struct _tagAnimation2DFrameInfo
{
	Vector2		vStart;
	Vector2		vEnd;
	int			iFrame;
}Animation2DFrameInfo, *PAnimation2DFrameInfo;

class ENGINE_DLL CAnimation2DSequence :
	public CRef
{
	friend class CAnimation2D;
	friend class CResourceManager;

private:
	CAnimation2DSequence();
	CAnimation2DSequence(const CAnimation2DSequence& anim);
	~CAnimation2DSequence();

private:
	class CAnimation2D*				m_pAnim2D;
	vector<class CTexture*>			m_vecTexture;
	ANIMATION_2D_TYPE				m_eAnimType;
	bool							m_bLoop;
	float							m_fPlayTime;
	float							m_fTime;
	float							m_fSequenceTime;
	float							m_fFrameTime;
	float							m_fPlayScale;
	int								m_iFrame;
	int								m_iFrameMax;
	list<PAnim2DNotify>				m_NotifyList;
	vector<Animation2DFrameInfo>	m_vecFrameInfo;
	Animation2DCBuffer				m_tCBuffer;
	class CMaterial*				m_pMaterial;
	string							m_strReturnSequence;
	bool							m_bFrameEnd;

public:
	const string& GetReturnSequence()	const;
	class CTexture* GetTexture()	const;
	Animation2DFrameInfo GetFrame()	const;

public:
	bool Update(float fTime);
	CAnimation2DSequence* Clone();
	void SetMaterial(class CMaterial* pMaterial);
	bool IsSequenceEnd()	const;

public:
	void SetPlayScale(float fScale);
	void SetPlayTime(float fTime);

public:
	bool CreateSequence(const string& strName, bool bLoop, float fPlayTime, int iFrameCount);
	bool AddTexture(const string& strName, const TCHAR* pFileName, const string& strPathName = TEXTURE_PATH);
	bool CreateNotify(const string& strName, int iFrame);
	bool CreateNotify(const string& strName, float fTime);
	bool AddNotifyFunction(const string& strName, void(*pFunc)(float));
	void AddFrameInfo(const Vector2& vStart, const Vector2& vEnd);
	void SetFrameInfoAll(const Vector2& vStart, const Vector2& vEnd);
	void SetMaterialTexture(class CMaterial* pMaterial);
	void SetShader();
	void Clear();
	void SetReturnSequence(const string& strName);

	template <typename T>
	bool AddNotifyFunction(const string& strName, T* pObj, void(T::*pFunc)(float))
	{
		auto	iter = m_NotifyList.begin();
		auto	iterEnd = m_NotifyList.end();

		PAnim2DNotify	pNotify = nullptr;

		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->strName == strName)
			{
				pNotify = *iter;
				break;
			}
		}

		if (!pNotify)
			return false;

		pNotify->vecFunction.push_back(bind(pFunc, pObj, placeholders::_1));

		return true;
	}
};

