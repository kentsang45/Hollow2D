#pragma once

#include "Object/GameObject.h"


class WaterDrop : public CGameObject
{


public:
	WaterDrop();
	~WaterDrop();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void Start(float fTime, const Vector3& vPos);
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	class CColliderRect* GetBody() const;
	void PlaceAt(int sizeX, int sizeY, int leftTopX, int leftTopY, int iStyle);

	void SetStageNumber(int stage) { m_iStageNumber = stage; }
private:
	class CStaticMeshComponent* m_pMesh;
	class CAnimation2D* m_pAnimation;
	class CProjectileMovementComponent* m_pMovement;
	class CColliderRect* m_pBody;

	// class HitEffect* m_pHitEffect;

	bool m_bStart = true;
	bool m_bFalling = false;
	bool m_bEnd = false;

	int m_iStageNumber = 0;

	Vector3 m_vStartPos = Vector3::Zero;

	float m_fWaitTime = 0.f;
	float m_fWaitTotalTime = 0.f;

	int m_iStyle = 0;

	string m_strSoundName;
	string m_strSoundFileName;

	class HollowKnight* m_pHK;
};


