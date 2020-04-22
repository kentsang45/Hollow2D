#pragma once

#include "Object/GameObject.h"

class CChildObj :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CChildObj();
	~CChildObj();

private:
	class CStaticMeshComponent*	m_pMesh;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

