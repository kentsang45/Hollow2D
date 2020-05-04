#pragma once

#include "Object/GameObject.h"


class SoulParticle : public CGameObject
{


public:
	SoulParticle();
	~SoulParticle();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void Start(float fTime, const Vector3& vPos);

	void SetAnimation(int style);

private:
	class CStaticMeshComponent* m_pMesh;
	class CAnimation2D* m_pAnimation;
	class CCharacterMovementComponent* m_pMovement;
	class CMaterial* m_pMaterial;
	// class HitEffect* m_pHitEffect;

	bool m_bIsOn;
	Vector3 m_vVelo;

	float m_fSize = 0.f;
	float m_fTotalSize = 0.f;

	float m_fLifeTime = 0.f;
	float m_fTime = 0.f;
	float m_fTime2 = 1.f;

};

