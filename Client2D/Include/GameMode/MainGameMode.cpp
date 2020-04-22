#include "MainGameMode.h"
#include "../Object/TestObject.h"
#include "../Object/Minion.h"
#include "../Object/ChildObj.h"
#include "Scene/Scene.h"
#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Resource/Animation2DSequence.h"
#include "CollisionManager.h"
#include "../Object/TestPixelCollision.h"
#include "../Object/TestButton.h"
#include "../Object/TestBar.h"
#include "../Object/MainMap.h"
#include "Input.h"

CMainGameMode::CMainGameMode()
{
}

CMainGameMode::~CMainGameMode()
{
}

bool CMainGameMode::Init()
{
	CGameMode::Init();

	GET_SINGLE(CCollisionManager)->CreateChannel("Player", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("Monster", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("PlayerProjectile", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("MonsterProjectile", CT_BLOCK);

	GET_SINGLE(CCollisionManager)->CreateProfile("Player", "Player");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Player", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "PlayerProjectile", CT_IGNORE);

	GET_SINGLE(CCollisionManager)->CreateProfile("Monster", "Monster");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Monster", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "MonsterProjectile", CT_IGNORE);

	GET_SINGLE(CCollisionManager)->CreateProfile("PlayerProjectile", "PlayerProjectile");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "MonsterProjectile", CT_IGNORE);

	GET_SINGLE(CCollisionManager)->CreateProfile("MonsterProjectile", "MonsterProjectile");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "MonsterProjectile", CT_IGNORE);

	CreateMaterial();

	CreateAnimation2DSequence();

	CTestObject*	pObj = m_pScene->SpawnObject<CTestObject>();

	SetPlayer(pObj);

	CChildObj*	pChildObj = m_pScene->SpawnObject<CChildObj>("Child");

	pObj->AddChild(pChildObj, TR_ROT | TR_POS);

	SAFE_RELEASE(pChildObj);

	SAFE_RELEASE(pObj);

	CMinion*	pMinion = m_pScene->SpawnObject<CMinion>(Vector3(1300.f, 400.f, 0.f));

	SAFE_RELEASE(pMinion);

	CTestPixelCollision*	pTestPixel = m_pScene->SpawnObject<CTestPixelCollision>();

	SAFE_RELEASE(pTestPixel);

	CTestButton*	pTestButton = m_pScene->SpawnObject<CTestButton>();

	SAFE_RELEASE(pTestButton);

	CTestBar*	pTestBar = m_pScene->SpawnObject<CTestBar>();

	SAFE_RELEASE(pTestBar);

	CMainMap*	pMap = m_pScene->SpawnObject<CMainMap>();

	SAFE_RELEASE(pMap);

	return true;
}

bool CMainGameMode::CreateMaterial()
{
	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerMtrl");

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerMtrl");

	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);

	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerAnimMtrl");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMtrl");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	//pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);

	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerAnimOutLineMtrl");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimOutLineMtrl");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_OUTLINE_SHADER);
	//pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	pMaterial->CreateCBufferNode(OUTLINE_CBUFFER, 11, sizeof(OutLineCBuffer));

	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("TestPixelMtrl");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("TestPixelMtrl");

	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "TestPixel", TEXT("PixelCollision.png"));

	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("MainMapTileMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("MainMapTileMaterial");

	pMaterial->SetSubsetShader(TILEMAP_SHADER);
	pMaterial->SetTexture(0, "MainMapTile", TEXT("Tile.bmp"));

	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("BulletMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BulletMaterial");

	pMaterial->SetSubsetShader(TILEMAP_SHADER);
	pMaterial->SetTexture(0, "Bullet", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	pMaterial->EnableInstancing();
	pMaterial->AddRef();

	SAFE_RELEASE(pMaterial);

	return true;
}

bool CMainGameMode::CreateAnimation2DSequence()
{
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MinionIdle", true, 1.f, 7);
	GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MinionIdle", "MinionAtlas",
		TEXT("Monster/MinionAtlas.png"));

	for (int i = 0; i < 7; ++i)
	{
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceFrameInfo("MinionIdle", Vector2(50.f * i, 0.f),
			Vector2(50.f * (i + 1), 37.f));
	}

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MinionWalk", true, 1.f, 6);

	for (int i = 0; i <= 5; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Monster/MinionFrame/adventurer-run2-0%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "MinionWalk%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MinionWalk", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MinionWalk", Vector2(0.f, 0.f),
		Vector2(50.f, 37.f));

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MinionKick", false, 1.f, 8);

	for (int i = 0; i <= 7; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Monster/MinionFrame/adventurer-kick-0%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "MinionKick%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MinionKick", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MinionKick", Vector2(0.f, 0.f),
		Vector2(50.f, 37.f));

	return true;
}
