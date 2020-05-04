#pragma once

#include "Object/GameObject.h"


class BugParticle : public CGameObject
{


public:

	BugParticle();
	~BugParticle();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void MoveX();

	void SetStyle(int i) { m_iStyle = i; }

private:
	class CStaticMeshComponent* m_pMesh;
	class CStaticMeshComponent* m_pChildMesh;

	class CCharacterMovementComponent*	m_pMovement;
	class CSceneComponent*		m_pRotPivot;

	class CAnimation2D* m_pAnimation;

	// class HitEffect* m_pHitEffect;

	// COLLIDER

	int m_iStyle = 0;

	float m_fLifeTime = 0.f;

	Vector3 m_vVelo = Vector3::Zero;
};


