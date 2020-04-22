#pragma once

#include "Object/GameObject.h"

class SoftEffect : public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	SoftEffect();
	~SoftEffect();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CProjectileMovementComponent*	m_pMovement;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	class CColliderRect* GetBody() const;

private:
	float m_fLifeTime;
	int m_iDirDecider = 1;
};

