#pragma once

#include "Object/GameObject.h"

class CMinion :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CMinion();
	~CMinion();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CCharacterMovementComponent*	m_pMovement;
	class CColliderRect*		m_pBody;
	class CColliderSphere2D*	m_pBodySphere;
	class CColliderOBB2D*		m_pBodyOBB2D;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

public:
	void Fire();
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
};

