#pragma once

#include "SceneComponent.h"

class ENGINE_DLL CAnimationMeshComponent :
	public CSceneComponent
{
	friend class CGameObject;

protected:
	CAnimationMeshComponent();
	CAnimationMeshComponent(const CAnimationMeshComponent& com);
	~CAnimationMeshComponent();

private:
	class CAnimationMesh*	m_pMesh;

public:
	void SetAnimationMesh(class CAnimationMesh* pMesh);
	virtual class CMaterial* GetMaterial()	const;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

