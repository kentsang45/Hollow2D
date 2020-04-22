#pragma once

#include "SceneComponent.h"

class ENGINE_DLL CUI :
	public CSceneComponent
{
	friend class CGameObject;

protected:
	CUI();
	CUI(const CUI& com);
	virtual ~CUI();

protected:
	class CStaticMesh*	m_pMesh;
	class CShader*		m_pShader;
	ID3D11InputLayout*	m_pLayout;
	class CColliderRect*	m_pBody;
	class CRenderState*		m_pAlphaBlend;
	int m_iZOrder;

public:
	virtual class CMaterial* GetMaterial()	const;
	int GetZOrder()	const;
	void SetZOrder(int iZOrder);

public:
	void SetShader(const string& strName);
	void SetShader(const string& strName, const TCHAR* pFileName[ST_END], 
		const char* pEntry[ST_END], const string& strPathName = SHADER_PATH);
	void SetMesh(const string& strName);
	void SetInputLayout(const string& strName);

	void Unable();
	
public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

protected:
	virtual void CollisionBody(class CColliderBase* pDest, float fTime);
	virtual void ExitBody(class CColliderBase* pDest, float fTime);

protected:
	void BodyCollision(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void BodyCollisionExit(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
};

