
#include "MainMap.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/TileMap.h"

CMainMap::CMainMap()
{
}

CMainMap::~CMainMap()
{
	SAFE_RELEASE(m_pTileMap);
}

bool CMainMap::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pTileMap = CGameObject::CreateComponent<CTileMap>("TileMap");

	// m_pTileMap->CreateTile(TT_RECT, 100, 100, Vector3(100.f, 100.f, 1.f));

	// m_pTileMap->LoadPath("TileMap/Tile.tmp");
	// m_pTileMap->SetTileMaterial("MainMapTileMaterial");

	m_pTileMap->LoadPath("TileMap/IsoTile.tmp");
	m_pTileMap->SetTileMaterial("MainMapIsoTileMaterial");

	/*for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			m_pTileMap->AddFrame(Vector2(j * 100.f, i * 100.f),
				Vector2((j + 1) * 100.f, (i + 1) * 100.f), Vector2(900.f, 500.f),
				IT_ATLAS);
		}
	}*/

	SetRoot(m_pTileMap);

	return true;
}

void CMainMap::Begin()
{
	CGameObject::Begin();
}

void CMainMap::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CMainMap::Render(float fTime)
{
	CGameObject::Render(fTime);
}
