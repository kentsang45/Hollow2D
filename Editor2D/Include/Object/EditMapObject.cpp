
#include "../stdafx.h"
#include "EditMapObject.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/TileMap.h"

CEditMapObject::CEditMapObject() :
	m_pTileMap(nullptr)
{
}

CEditMapObject::~CEditMapObject()
{
	SAFE_RELEASE(m_pTileMap);
}

void CEditMapObject::CreateTileMap(TILE_TYPE eType, int iCountX, int iCountY, int iSizeX, int iSizeY,
	const string & strTexName, const TCHAR * pFullPath)
{
	if (!m_pTileMap)
	{
		m_pTileMap = CGameObject::CreateComponent<CTileMap>("TileMap");

		SetRoot(m_pTileMap);
	}

	m_pTileMap->CreateTile(eType, iCountX, iCountY, Vector3(iSizeX, iSizeY, 1.f));

	// m_pTileMap->SetTileMaterial("MainMapTileMaterial");

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			m_pTileMap->AddFrame(Vector2(j * 100.f, i * 100.f),
				Vector2((j + 1) * 100.f, (i + 1) * 100.f), Vector2(900.f, 500.f),
				IT_ATLAS);
		}
	}
}

bool CEditMapObject::Init()
{
	if (!CGameObject::Init())
		return false;

	/*m_pTileMap = CGameObject::CreateComponent<CTileMap>("TileMap");

	m_pTileMap->CreateTile(TT_RECT, 100, 100, Vector3(100.f, 100.f, 1.f));

	m_pTileMap->SetTileMaterial("MainMapTileMaterial");

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			m_pTileMap->AddFrame(Vector2(j * 100.f, i * 100.f),
				Vector2((j + 1) * 100.f, (i + 1) * 100.f), Vector2(900.f, 500.f),
				IT_ATLAS);
		}
	}

	SetRoot(m_pTileMap);*/

	return true;
}

void CEditMapObject::Begin()
{
	CGameObject::Begin();
}

void CEditMapObject::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CEditMapObject::Render(float fTime)
{
	CGameObject::Render(fTime);
}
