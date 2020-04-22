#pragma once

#include "Object/GameObject.h"

class BlackSoftEffect : public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	BlackSoftEffect();
	~BlackSoftEffect();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CProjectileMovementComponent*	m_pMovement;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	class CColliderRect* GetBody() const;

	void SetLeft();
	void SetVertical() { m_bVertical = true; }
private:
	float m_fLifeTime;
	float m_fLifeTotalTime;

	int m_iXDecider = 1;
	int m_iYDecider = 1;

	float m_fYTime = 0.f;

	float m_fXTime = 0.f;

	bool m_bVertical = false;
};

