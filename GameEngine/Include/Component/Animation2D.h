#pragma once

#include "../Ref.h"
#include "../Resource/Animation2DSequence.h"

class ENGINE_DLL CAnimation2D :
	public CRef
{
	friend class CStaticMeshComponent;
	friend class CInput;

protected:
	CAnimation2D();
	CAnimation2D(const CAnimation2D& com);
	virtual ~CAnimation2D();

public:
	template <typename T>
	static T* CreateAnimation2D(const string& strName = "Animation2D")
	{
		T*	pAnim = new T;

		pAnim->SetName(strName);

		if (!pAnim->Init())
		{
			SAFE_RELEASE(pAnim);
			return pAnim;
		}

		return pAnim;
	}

private:
	unordered_map<size_t, class CAnimation2DSequence*>	m_mapAnimSequence;
	class CAnimation2DSequence*			m_pSequence;
	class CStaticMeshComponent*			m_pOwner;
	class CMaterial*					m_pMaterial;

public:
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	bool IsSequenceEnd() const;
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////


	class CAnimation2DSequence* GetSequence()	const;
	class CTexture* GetAnimTexture()	const;
	Animation2DFrameInfo GetAnimFrame()	const;
	unsigned int GetTextureWidth()	const;
	unsigned int GetTextureHeight()	const;

public:
	bool AddAnimation2DSequence(const string& strName);
	class CAnimation2DSequence* FindAnimSequence(const string& strName);
	void SetMaterial(class CMaterial* pMaterial);
	void SetReturnSequenceName(const string& strSequence, const string& strReturnName);

public:
	void ChangeAnimation(const string& strName);
	void ChangeUIAnimation(const string& strName);

public:
	virtual bool Init();
	virtual void Update(float fTime);

public:
	void SetShader();

	bool CreateNotify(const string& strSequenceName, const string& strNotifyName, int iFrame);
	bool CreateNotify(const string& strSequenceName, const string& strNotifyName, float fTime);
	bool AddNotifyFunction(const string& strSequenceName, const string& strNotifyName, void(*pFunc)(float));
	template <typename T>
	bool AddNotifyFunction(const string& strSequenceName, const string& strNotifyName, T* pObj, void(T::*pFunc)(float))
	{
		CAnimation2DSequence*	pSequence = FindAnimSequence(strSequenceName);

		if (!pSequence)
			return false;

		bool bResult = pSequence->AddNotifyFunction<T>(strNotifyName, pObj, pFunc);

		SAFE_RELEASE(pSequence);

		return bResult;
	}
};

