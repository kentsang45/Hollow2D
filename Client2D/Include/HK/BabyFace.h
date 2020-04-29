#pragma once

#include "Object/GameObject.h"

#include "../Client.h"

class BabyFace : public CGameObject
{


public:
	BabyFace();
	~BabyFace();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void Start(float fTime, const Vector3& vPos);
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	class CColliderRect* GetBody() const;

	void Die(float fTime);

	void SetDir(int dir) { m_iDir = dir; }


private:
	class CStaticMeshComponent* m_pMesh;
	class CAnimation2D* m_pAnimation;
	class CProjectileMovementComponent* m_pMovement;
	class CColliderRect* m_pBody;

	// class HitEffect* m_pHitEffect;

	bool m_bIsOn = false;;
	Vector3 m_vPlayerPos;

	BUG_STATE m_eAnimState = (BUG_STATE)-1;

	bool m_bJump = false;
	bool m_bDead = false;

	// int m_iDir = 0;
};


