#pragma once

#include "Object/GameObject.h"


class GrassParticleMesh : public CGameObject
{


public:

	GrassParticleMesh();
	~GrassParticleMesh();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);




private:
	class CStaticMeshComponent* m_pMesh;
	class CCharacterMovementComponent*	m_pMovement;
	class CSceneComponent*		m_pRotPivot;
	// class HitEffect* m_pHitEffect;

	// COLLIDER

	bool m_bIsOn = false;

	int m_iStyle = 0;

	float m_fJumpTime;

	bool m_bJumping = false;

	float m_fRot;

	int m_iDir = 0;
};


