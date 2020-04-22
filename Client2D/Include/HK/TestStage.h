#pragma once

#include "Object/GameObject.h"


class TestStage : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	TestStage();
	~TestStage();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void SetScale(const Vector3& vScale);

	void PlaceAt(int sizeX, int sizeY, int leftTopX, int leftTopY);

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

private:
	class CStaticMeshComponent*	m_pMesh;
	class CMaterial* m_pMaterial;
	class CColliderRect* m_pBody;
	class CCharacterMovementComponent* m_pMovement;
};

