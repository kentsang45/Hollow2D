#pragma once

#include "Object/GameObject.h"


class CoinEffect : public CGameObject
{


public:
	CoinEffect();
	~CoinEffect();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void Start(float fTime, const Vector3& vPos);

private:
	class CStaticMeshComponent* m_pMesh;
	class CStaticMeshComponent* m_pChildMesh;

	class CSceneComponent*		m_pRotPivot;

	class CAnimation2D* m_pAnimation;

	// class HitEffect* m_pHitEffect;

	bool m_bIsOn;
	Vector3 m_vPlayerPos;

	float m_fTime = 0.f;

	float m_fRandom = 0.f;

	class HollowKnight* m_pHK = nullptr;
};


