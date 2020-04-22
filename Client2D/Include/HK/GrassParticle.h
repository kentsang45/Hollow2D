#pragma once

#include "Object/GameObject.h"


class GrassParticle : public CGameObject
{


public:

	GrassParticle();
	~GrassParticle();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void MoveX();
	void SetDirection(int dir) { m_iDir = dir; m_iRotDir = dir; }


private:
	class CStaticMeshComponent* m_pMesh;
	class CStaticMeshComponent* m_pChildMesh;

	class CCharacterMovementComponent*	m_pMovement;
	class CSceneComponent*		m_pRotPivot;
	// class HitEffect* m_pHitEffect;

	// COLLIDER

	bool m_bIsOn = false;

	int m_iStyle = 0;

	float m_fJumpTime;

	bool m_bJumping = false;

	float m_fRot;

	int m_iDir = 1;
	int m_iRotDir = 1;
};


