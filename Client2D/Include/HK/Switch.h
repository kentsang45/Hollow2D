#pragma once

#include "Object/GameObject.h"


class Switch : public CGameObject
{


public:
	Switch();
	~Switch();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);


	void PlaceAt(int sizeX, int sizeY, float leftTopX, float leftTopY, int iStyle, bool bCart = true);


	void BeginOverlap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void SetStart(bool start) { m_bStart = start; }
	bool GetStart() const { return m_bStart; }



private:
	class CStaticMeshComponent* m_pMesh;
	// COLLIDER
	class CColliderRect* m_pBody;

	bool m_bIsOn = false;
	bool m_bDead = false;

	string m_strAniName;

	int m_iSizeX = 0;
	int m_iSizeY = 0;

	bool m_bStart = true;

	/////////////////////////////////////////////////////////////////////////
public:
	void SetStageNumber(int stage) { m_iStageNumber = stage; }
	int m_iStageNumber = 0;
};


