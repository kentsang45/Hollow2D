#pragma once

#include "Scene/GameMode.h"

class CEditGameMode :
	public CGameMode
{
public:
	CEditGameMode();
	~CEditGameMode();

private:
	class CFreeCamera*	m_pCamera;
	class CEditMapObject*	m_pTileMapObj;

public:
	void SetTileMapObj(class CEditMapObject* pTileMap);
	class CEditMapObject* GetTileMapObj()	const;

public:
	virtual bool Init();

private:
	bool CreateMaterial();
	bool CreateAnimation2DSequence();
};

