#pragma once

#include "Object/GameObject.h"


class Cart : public CGameObject
{


public:
	Cart();
	~Cart();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);


	void PlaceAt(int sizeX, int sizeY, float leftTopX, float leftTopY, int iStyle, bool bCart = true);
	void ChangeAnimation(int iAnim);


	void BeginOverlap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

private:
	class CStaticMeshComponent* m_pMesh;
	class CAnimation2D* m_pAnimation;

	// class HitEffect* m_pHitEffect;

	// COLLIDER
	class CColliderRect* m_pBody;

	bool m_bIsOn = false;
	bool m_bDead = false;

	string m_strAniName;

	int m_iSizeX = 0;
	int m_iSizeY = 0;

	int m_iStyle = 0;

	bool m_bCart = true;
};


