#pragma once

#include "Object/GameObject.h"


class Grass : public CGameObject
{


public:
	Grass();
	~Grass();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);


	void PlaceAt(int sizeX, int sizeY, int leftTopX, int leftTopY);

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
};


