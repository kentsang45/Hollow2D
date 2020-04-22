#pragma once

#include "Object/GameObject.h"


class MonsterHitEffect : public CGameObject
{


public:
	MonsterHitEffect();
	~MonsterHitEffect();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void Start(float fTime, const Vector3& vPos);

private:
	class CStaticMeshComponent* m_pMesh;
	class CAnimation2D* m_pAnimation;

	// class HitEffect* m_pHitEffect;

	bool m_bIsOn;
	Vector3 m_vPlayerPos;
};


