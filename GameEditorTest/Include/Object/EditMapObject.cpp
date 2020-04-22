
#include "../pch.h"
#include "EditMapObject.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/TileMap.h"
#include "Input.h"
#include "Component/Tile.h"
#include "../GameMode/EditGameMode.h"
#include "../MainFrm.h"
#include "../TileMapEditorDlg.h"

CEditMapObject::CEditMapObject()	:
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
	if(!m_pTileMap)
	{
		m_pTileMap = CGameObject::CreateComponent<CTileMap>("TileMap");

		SetRoot(m_pTileMap);
	}
	for (int i = 0; i <= 379; ++i)
	{
		m_pTileMap->AddFrame(Vector2(0.f, 0.f),
			Vector2(160.f, 80.f), Vector2(160.f, 80.f),
			IT_ARRAY);
	}
	m_pTileMap->CreateTile(eType, iCountX, iCountY, Vector3(iSizeX, iSizeY, 1.f));

	//m_pTileMap->SetTileMaterial("MainMapTileMaterial");

	
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

	// 마우스를 눌렀는지 확인한다.
	if (GET_SINGLE(CInput)->LButtonPush() && m_pTileMap)
	{
		Vector2	vPos = GET_SINGLE(CInput)->GetMouseWorldPos();

		CTile*	pTile = m_pTileMap->GetTile(Vector3(vPos.x, vPos.y, 0.f));

		if (pTile)
		{
			CEditGameMode*	pMode = (CEditGameMode*)m_pScene->GetGameMode();

			if(pMode)
			{
				switch (pMode->GetTileUpdateType())
				{
					case TUT_FRAME:
					{
						ImageFrame	tFrame = {};

						CMaterial* pMaterial = pTile->GetMaterial();

						pMode->GetMainFrame()->GetTileMapDlg()->UpdateFrameData();

						tFrame.vStart = pMode->GetMainFrame()->GetTileMapDlg()->m_vFrameStart;
						tFrame.vEnd = pMode->GetMainFrame()->GetTileMapDlg()->m_vFrameEnd;
						//tFrame.vImageSize = pMode->GetMainFrame()->GetTileMapDlg()->m_vFrameSize;
						tFrame.vImageSize = Vector2(900.f, 500.f);
						tFrame.iFrame = 0;
						tFrame.iImageType = pMaterial->GetImageType();

						if (tFrame.iImageType == IT_ATLAS)
							tFrame.iFrame = 0;
						else
							tFrame.iFrame = tFrame.vStart.x;

						pTile->SetFrame(tFrame);
					}
					break;
					case TUT_OPTION:
					{
						int iSel = pMode->GetMainFrame()->GetTileMapDlg()->GetTileOption();

						if (iSel != -1)
						{
							pTile->SetTileOption((TILE_OPTION)iSel);
						}
					}
						break;
				}
			}
		}
	}
}

void CEditMapObject::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CEditMapObject::Save(const char * pFullPath)
{
	m_pTileMap->Save(pFullPath);
}

void CEditMapObject::Load(const char * pFullPath, const char* pMaterialName)
{
	SAFE_RELEASE(m_pTileMap);

	m_pTileMap = CGameObject::CreateComponent<CTileMap>("TileMap");

	SetRoot(m_pTileMap);

	m_pTileMap->Load(pFullPath);

	m_pTileMap->SetTileMaterial(pMaterialName);
}
