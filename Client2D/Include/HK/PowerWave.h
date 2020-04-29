#pragma once

#include "Object/GameObject.h"


class PowerWave : public CGameObject
{


public:
	PowerWave();
	~PowerWave();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void SetDir(int dir);
	void Start(float fTime, const Vector3& vPos);
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	class CColliderRect* GetBody() const;

	void ResetStyle() { m_iStyle = 0; }

private:
	class CStaticMeshComponent* m_pMesh;
	class CProjectileMovementComponent* m_pMovement;
	class CColliderRect* m_pBody;
	class CAnimation2D* m_pAnimation;

	// class HitEffect* m_pHitEffect;

	bool m_bIsOn;
	Vector3 m_vPlayerPos;

	static int m_iStyle;
	float m_fMoveSpeed = 100.f;

	float m_fScaleX = 30.f;
	float m_fCScaleX = 25.f; 

	int m_iSpeedStyle = 0;
};


