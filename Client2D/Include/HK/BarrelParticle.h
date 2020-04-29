#pragma once

#include "Object/GameObject.h"


class BarrelParticle : public CGameObject
{


public:

	BarrelParticle();
	~BarrelParticle();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void MoveX();
	void JumpEnd(float fTime);

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void SetDirection(int dir);

	static void ResetStyle();
private:
	class CStaticMeshComponent* m_pMesh;
	class CStaticMeshComponent* m_pChildMesh;

	class CCharacterMovementComponent*	m_pMovement;
	class CSceneComponent*		m_pRotPivot;

	class CColliderRect* m_pBody;



	// class HitEffect* m_pHitEffect;

	// COLLIDER

	bool m_bIsOn = false;


	float m_fLifeTime = 0.f;
	float m_fDeathTime = 4.f;

	bool m_bJump = false;

	float m_fRot;

	int m_iDir = 0;
	int m_iRotDir = 0;

	// 중력
	float m_fCurrentForce = 0.f;
	float m_fMoveSpeed = 200.f;

	// 충돌
	bool m_bNoRight = false;
	bool m_bNoLeft = false;
	bool m_bNoUp = false;

	bool m_bStop = false;

	static int m_iStyle;
};


