#pragma once

#include "Object/GameObject.h"

class CMainMap :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CMainMap();
	~CMainMap();

private:
	class CTileMap*	m_pTileMap;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

