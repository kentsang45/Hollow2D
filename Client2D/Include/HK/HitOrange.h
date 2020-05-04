#pragma once

#include "Object/GameObject.h"


class HitOrange : public CGameObject
{


public:
	HitOrange();
	~HitOrange();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void Start(float fTime, const Vector3& vPos);

	void SetAnimation(int style);

	void SetBinding();

private:
	class CStaticMeshComponent* m_pMesh;
	class CAnimation2D* m_pAnimation;
	class CMaterial* m_pMaterial;

	// class HitEffect* m_pHitEffect;

	float m_fLifeTime = 0.f;
	float m_fLifeTotalTime = 1.3f;

	bool m_bBind = false;
	float m_fCurScale = 50.f;
};


