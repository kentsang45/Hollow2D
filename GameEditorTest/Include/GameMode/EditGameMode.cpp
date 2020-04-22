
#include "../pch.h"
#include "EditGameMode.h"
#include "../Object/EditMapObject.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "Resource/Animation2DSequence.h"
#include "Resource/Material.h"
#include "../Object/FreeCamera.h"


CEditGameMode::CEditGameMode()	:
	m_pCamera(nullptr),
	m_pTileMapObj(nullptr),
	m_eUpdateType(TUT_FRAME)
{
}

CEditGameMode::~CEditGameMode()
{
	SAFE_RELEASE(m_pTileMapObj);
	SAFE_RELEASE(m_pCamera);
}

void CEditGameMode::SetTileMapObj(CEditMapObject * pTileMap)
{
	SAFE_RELEASE(m_pTileMapObj);
	m_pTileMapObj	= pTileMap;

	if(m_pTileMapObj)
		m_pTileMapObj->AddRef();
}

CEditMapObject * CEditGameMode::GetTileMapObj() const
{
	return m_pTileMapObj;
}

bool CEditGameMode::Init()
{
	CGameMode::Init();

	CreateMaterial();


	/*CEditMapObject*	pEditMap = m_pScene->SpawnObject<CEditMapObject>();

	SAFE_RELEASE(pEditMap);*/

	m_pCamera = m_pScene->SpawnObject<CFreeCamera>();

	SetPlayer(m_pCamera);

	/*GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MouseDefault", true, 1.f, 13);

	for (int i = 0; i <= 12; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Mouse\\Default\\%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "MouseDefault%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MouseDefault", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MouseDefault", Vector2(0.f, 0.f),
		Vector2(32.f, 31.f));

	GET_SINGLE(CInput)->CreateAnim2D();
	GET_SINGLE(CInput)->AddAnim2DSequence("MouseDefault");
	GET_SINGLE(CInput)->AlphaBlendEnable();*/

	return true;
}

bool CEditGameMode::CreateMaterial()
{
	GET_SINGLE(CResourceManager)->CreateMaterial("MainMapTileMaterial");

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("MainMapTileMaterial");

	pMaterial->SetSubsetShader(TILEMAP_SHADER);
	pMaterial->SetTexture(0, "MainMapTile", TEXT("Tile.bmp"));

	SAFE_RELEASE(pMaterial);

	return true;
}

bool CEditGameMode::CreateAnimation2DSequence()
{
	return true;
}
