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
	TILE_UPDATE_TYPE	m_eUpdateType;
	class CMainFrame*	m_pMainFrame;

public:
	void SetTileMapObj(class CEditMapObject* pTileMap);
	class CEditMapObject* GetTileMapObj()	const;
	void SetUpdateType(TILE_UPDATE_TYPE eType)
	{
		m_eUpdateType	= eType;
	}

	void SetMainFrame(class CMainFrame* pFrame)
	{
		m_pMainFrame	= pFrame;
	}

	class CMainFrame* GetMainFrame()	const
	{
		return m_pMainFrame;
	}

	TILE_UPDATE_TYPE GetTileUpdateType()	const
	{
		return m_eUpdateType;
	}

public:
	virtual bool Init();

private:
	bool CreateMaterial();
	bool CreateAnimation2DSequence();
};

