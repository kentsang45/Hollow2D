#pragma once

#include "Object/GameObject.h"

class HKAttackEffect : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	HKAttackEffect();
	~HKAttackEffect();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void Start(float fTime, const Vector3& vPos );

	// void SetHitEffect(class HitEffect* pHE);

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	class CColliderRect* GetBody() const;

	void Flip(int iFlip);

private:
	class CStaticMeshComponent* m_pMesh;
	class CCharacterMovementComponent* m_pMovement;
	class CAnimation2D* m_pAnimation;
	class CColliderRect* m_pBody;
	// class HitEffect* m_pHitEffect;

	bool m_bIsOn;
	Vector3 m_vPlayerPos;


};

