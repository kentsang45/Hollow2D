#pragma once

#include "ObjectComponent.h"

class ENGINE_DLL CPaperBurn :
	public CObjectComponent
{
	friend class CGameObject;

protected:
	CPaperBurn();
	CPaperBurn(const CPaperBurn& com);
	virtual ~CPaperBurn();

private:
	float	m_fTime;
	float	m_fBurnTime;
	class CSceneComponent*	m_pUpdateComponent;
	function<void()>	m_CompleteFunction;
	bool	m_bComplete;
	class CTexture*	m_pBurnTexture;
	bool	m_bInverse;
	PaperBurnCBuffer	m_tCBuffer;
	class CMaterial*	m_pMaterial;

public:
	bool IsInverse()	const;

public:
	void SetUpdateComponent(class CSceneComponent* pComponent);
	void SetBurnTime(float fTime);
	void Clear();
	void SetBurnTexture(const string& strName, const TCHAR* pFileName, const string& strPathName = TEXTURE_PATH);
	void Inverse();
	void SetColorOutLine(const Vector3& vColor);
	void SetColorOutLine(float r, float g, float b);
	void SetColorCenter(const Vector3& vColor);
	void SetColorCenter(float r, float g, float b);
	void SetColorInLine(const Vector3& vColor);
	void SetColorInLine(float r, float g, float b);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);

public:
	void SetCompleteFunction(void(*pFunc)());

	template <typename T>
	void SetCompleteFunction(T* pObj, void (T::*pFunc)())
	{
		m_CompleteFunction = bind(pFunc, pObj);
	}
};

