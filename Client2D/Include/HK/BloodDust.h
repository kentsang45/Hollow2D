#pragma once

#include "EngineGlobals.h"

#include "Object/GameObject.h"



class BloodDust : public CGameObject
{
public:
	BloodDust();
	~BloodDust();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void Start(float fTime, const Vector3& vPos);

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void SetDir(int dir);

	void SetNormalMonster();
private:
	class CStaticMeshComponent* m_pMesh;
	class CAnimation2D* m_pAnimation;
	class CProjectileMovementComponent* m_pMovement;

	// class CColliderRect* m_pBody;

	// class HitEffect* m_pHitEffect;

	bool m_bIsOn;
	Vector3 m_vPlayerPos;

	int m_iDir = 0;
	Vector3 m_vVelo;
};

