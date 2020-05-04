#pragma once

#include "Object/GameObject.h"


class LightEffect : public CGameObject
{


public:
	LightEffect();
	~LightEffect();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void Start(float fTime, const Vector3& vPos);

	void SetAnimation(int style);

private:
	class CStaticMeshComponent* m_pMesh;
	class CAnimation2D* m_pAnimation;

	// class HitEffect* m_pHitEffect;

	bool m_bIsOn;
	Vector3 m_vPlayerPos;

	class HollowKnight* m_pHK = nullptr;
};


