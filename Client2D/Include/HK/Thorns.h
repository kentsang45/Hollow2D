#pragma once

#include "Object/GameObject.h"


class Thorns : public CGameObject
{


public:
	Thorns();
	~Thorns();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);


	void PlaceAt(int sizeX, int sizeY, float leftTopX, float leftTopY, int iStyle);

	void BeginOverlap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void Reverse();

private:
	class CStaticMeshComponent* m_pMesh;
	class CAnimation2D* m_pAnimation;

	// class HitEffect* m_pHitEffect;

	// COLLIDER
	class CColliderRect* m_pBody;

	bool m_bIsOn = false;
	bool m_bDead = false;

	int m_iStyle = 0;

	string m_strIdleName;
	string m_strMoveName;
	string m_strDeathName;


	bool m_bShiny = false;

	float m_fWaitTime = 0.f;
	float m_fWaitTotalTime = 0.f;

	/////////////////////////////////////////////////////////////////////////
public:
	void SetStageNumber(int stage) { m_iStageNumber = stage; }
	int m_iStageNumber = 0;


};


