#pragma once

#include "Object/GameObject.h"

class CTestPixelCollision :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CTestPixelCollision();
	~CTestPixelCollision();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CColliderPixel*		m_pBody;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

