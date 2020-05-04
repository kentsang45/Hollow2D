#pragma once

#include "Object/GameObject.h"

class HKStage : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	HKStage();
	~HKStage();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void SetScale(const Vector3& vScale);

	void PlaceAt(int level, int layerLevel);
	void SetPlayer(class HollowKnight* player) { m_pHK = player; }

private:
	class CStaticMeshComponent*	m_pMesh;
	class CMaterial* m_pMaterial;
	class HollowKnight* m_pHK = nullptr;
	class CCharacterMovementComponent* m_pMovement;

	int m_iSizeX = 0;
	int m_iSizeY = 0;
	int m_iDepth = 0;

	int m_iStage = 0;
};

