#pragma once

#include "EngineGlobals.h"

#include "Object/GameObject.h"



class MightyEffect : public CGameObject
{
public:
	MightyEffect();
	~MightyEffect();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void Start(float fTime, const Vector3& vPos);

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

private:
	class CStaticMeshComponent* m_pMesh;
	class CAnimation2D* m_pAnimation;
	class CColliderRect* m_pBody;

	// class HitEffect* m_pHitEffect;

	bool m_bIsOn;
	Vector3 m_vPlayerPos;
};

