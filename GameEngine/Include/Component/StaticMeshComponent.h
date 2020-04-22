#pragma once

#include "SceneComponent.h"

class ENGINE_DLL CStaticMeshComponent :
	public CSceneComponent
{
	friend class CGameObject;

protected:
	CStaticMeshComponent();
	CStaticMeshComponent(const CStaticMeshComponent& com);
	~CStaticMeshComponent();

private:
	class CStaticMesh*	m_pMesh;
	class CMaterial*	m_pMaterial;
	class CAnimation2D*	m_pAnimation2D;

public:
	bool IsAnimation2D()	const;

public:
	virtual class CMaterial* GetMaterial()	const;

public:
	void SetStaticMesh(class CStaticMesh* pMesh);
	void SetMaterial(class CMaterial* pMaterial);
	void SetAnimation2D(class CAnimation2D* pAnimation);
	bool UpdateMaterialCBufferNode(const string& strName, void* pData);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
	virtual void RenderInstancing(float fTime, PInstancingBuffer pBuffer);
};

