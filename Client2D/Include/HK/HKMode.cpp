#include "HKMode.h"

#include "Scene/Scene.h"
#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Resource/Animation2DSequence.h"

#include "CollisionManager.h"

#include "HollowKnight.h"
#include "NewHK.h"
#include "JustBug.h"
#include "DashingBug.h"
#include "HornBug.h"
#include "JumpBug.h"
#include "ShieldBug.h"



#include "TestStage.h"
#include "HKButton.h"

#include "HKAttackEffect.h"

#include "HKMouse.h"

#include "UIHP.h"

#include "../RandomNumber.h"

#include "HKExcelManager.h"
#include "HKTileMap.h"

#include "../Object/TestObject.h"
#include "CoinCount.h"

#include "BGMObject.h"

#include <sstream>

#include "Input.h"
#include "CollisionManager.h"

HKMode::HKMode()
{
}

HKMode::~HKMode()
{
	SAFE_RELEASE(m_pHK);
}

bool HKMode::Init()
{
	//if (!GET_SINGLE(CInput)->Init())
	//	return false;

	CGameMode::Init();

	RandomNumber::Init();
	


	SetCollision();
	CreateMaterial();
	SetHK();
	SetBug();
	SetUI();

	
	
	// SetTileMap();

	////////////////////////////////////////// 엑셀 로딩

	// GET_SINGLE(CExcelManager)->Test();
	// DESTROY_SINGLE(CExcelManager);



	/*CTestObject*	pObj = m_pScene->SpawnObject<CTestObject>();

	SetPlayer(pObj);
	SAFE_RELEASE(pObj);*/

	if (nullptr == m_pHK)
	{
		m_pHK = m_pScene->SpawnObject<HollowKnight>();
		SetPlayer(m_pHK);		
	}

	/////////////////////////////////////////////////////////////////////////////
	// SOUND
	

	BGMObject*	pBGMObj = m_pScene->SpawnObject<BGMObject>("BGMObj");
	m_pHK->AddChild(pBGMObj, TR_ROT | TR_POS);
	SAFE_RELEASE(pBGMObj);



	// ShieldBug* bug = m_pScene->SpawnObject<ShieldBug>(Vector3(500.f, 500.f, 0.f));
	// SAFE_RELEASE(bug);

	

	// 폰트 짜응~
	CoinCount*	pCoinCount = m_pScene->SpawnObject<CoinCount>();
	SAFE_RELEASE(pCoinCount);


	//HKButton*	pTestButton = m_pScene->SpawnObject<HKButton>();
	//SAFE_RELEASE(pTestButton);

	// HKMouse*	pMouse = m_pScene->SpawnObject<HKMouse>();
	// SAFE_RELEASE(pMouse);





	//SetStage(3);
	SetStage(2);


	return true;
}

void HKMode::SetMode(int iStage, bool bStart, int iHP, int iCoin)
{
	if (nullptr == m_pHK)
	{
		m_pHK = m_pScene->SpawnObject<HollowKnight>();
		SetPlayer(m_pHK);
	}

	// SetStage(iStage);
	m_pHK->PlaceAt(iStage, bStart);

}

bool HKMode::CreateMaterial()
{
	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerMaterial");
	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerMaterial");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("StageMaterial");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("StageMaterial");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "TestStage", TEXT("TestCollision.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerAnimMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMaterial");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	// pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);



	GET_SINGLE(CResourceManager)->CreateMaterial("ReversePlayerAnimMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("ReversePlayerAnimMaterial");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	// pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);
	//////////////////////////////////////////////////////

	GET_SINGLE(CResourceManager)->CreateMaterial("AttackEffectMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	// pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	//////////////////////////////////////////////////////


	GET_SINGLE(CResourceManager)->CreateMaterial("SideEffectMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("SideEffectMaterial");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	// pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	////////////////////////////////////////////////////////

	GET_SINGLE(CResourceManager)->CreateMaterial("HitEffectMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("HitEffectMaterial");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	// pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	////////////////////////////////////////////////////////

	GET_SINGLE(CResourceManager)->CreateMaterial("MonsterHitEffectMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("MonsterHitEffectMaterial");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	// pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);





	GET_SINGLE(CResourceManager)->CreateMaterial("BugMaterial");

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BugMaterial");

	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	// pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);



	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerAnimOutlineMtrl");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimOutlineMtrl");
	pMaterial->SetSubsetShader(STANDARD_ANIM2D_OUTLINE_SHADER);
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	pMaterial->CreateCBufferNode(OUTLINE_CBUFFER, 11, sizeof(OutLineCBuffer));
	SAFE_RELEASE(pMaterial);


	//// SOFT
	GET_SINGLE(CResourceManager)->CreateMaterial("SoftMaterial");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("SoftMaterial");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	if (false == pMaterial->SetTexture(0, "Soft", TEXT("HOLLOW/Effect/Soft.png"))) {} //BOOM; }
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);



	//// BLACK SOFT
	GET_SINGLE(CResourceManager)->CreateMaterial("BlackSoftMaterial");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BlackSoftMaterial");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	if (false == pMaterial->SetTexture(0, "BlackSoft", TEXT("HOLLOW/Effect/BlackSoft.png"))) {} //BOOM; }
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// STAGE
	GET_SINGLE(CResourceManager)->CreateMaterial("Stage1");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage1", TEXT("HOLLOW/Stage/Stage1/Stage1.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage1M_BACK");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1M_BACK");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage1M_BACK", TEXT("HOLLOW/Stage/Stage1/Stage1M_BACK.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage1M_BACK2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1M_BACK2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage1M_BACK2", TEXT("HOLLOW/Stage/Stage1/Stage1M_BACK2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage1M_BACK3");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1M_BACK3");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage1M_BACK3", TEXT("HOLLOW/Stage/Stage1/Stage1M_BACK3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage1M_BACK4");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1M_BACK4");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage1M_BACK4", TEXT("HOLLOW/Stage/Stage1/Stage1M_BACK4.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage1M_FRONT");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1M_FRONT");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage1M_FRONT", TEXT("HOLLOW/Stage/Stage1/Stage1M_FRONT.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// STAGE
	GET_SINGLE(CResourceManager)->CreateMaterial("Stage2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage2", TEXT("HOLLOW/Stage/Stage2/Stage2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage2M_BACK");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2M_BACK");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage2M_BACK", TEXT("HOLLOW/Stage/Stage2/Stage2M_BACK.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage2M_BACK2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2M_BACK2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage2M_BACK2", TEXT("HOLLOW/Stage/Stage2/Stage2M_BACK2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage2M_BACK3");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2M_BACK3");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage2M_BACK3", TEXT("HOLLOW/Stage/Stage2/Stage2M_BACK3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage2M_BACK4");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2M_BACK4");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage2M_BACK4", TEXT("HOLLOW/Stage/Stage2/Stage2M_BACK4.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage2M_FRONT");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2M_FRONT");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage2M_FRONT", TEXT("HOLLOW/Stage/Stage2/Stage2M_FRONT.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// STAGE
	GET_SINGLE(CResourceManager)->CreateMaterial("Stage3");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage3", TEXT("HOLLOW/Stage/Stage3/Stage3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage3M_BACK");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3M_BACK");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage3M_BACK", TEXT("HOLLOW/Stage/Stage3/Stage3M_BACK.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage3M_BACK2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3M_BACK2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage3M_BACK2", TEXT("HOLLOW/Stage/Stage3/Stage3M_BACK2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage3M_BACK3");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3M_BACK3");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage3M_BACK3", TEXT("HOLLOW/Stage/Stage3/Stage3M_BACK3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage3M_BACK4");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3M_BACK4");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage3M_BACK4", TEXT("HOLLOW/Stage/Stage3/Stage3M_BACK4.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage3M_FRONT");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3M_FRONT");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage3M_FRONT", TEXT("HOLLOW/Stage/Stage3/Stage3M_FRONT.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// STAGE
	GET_SINGLE(CResourceManager)->CreateMaterial("Stage4");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage4", TEXT("HOLLOW/Stage/Stage4/Stage4.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage4M_BACK");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4M_BACK");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage4M_BACK", TEXT("HOLLOW/Stage/Stage4/Stage4M_BACK.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage4M_BACK2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4M_BACK2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage4M_BACK2", TEXT("HOLLOW/Stage/Stage4/Stage4M_BACK2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage4M_BACK3");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4M_BACK3");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage4M_BACK3", TEXT("HOLLOW/Stage/Stage4/Stage4M_BACK3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage4M_BACK4");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4M_BACK4");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage4M_BACK4", TEXT("HOLLOW/Stage/Stage4/Stage4M_BACK4.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage4M_FRONT");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4M_FRONT");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage4M_FRONT", TEXT("HOLLOW/Stage/Stage4/Stage4M_FRONT.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// STAGE
	GET_SINGLE(CResourceManager)->CreateMaterial("Stage5");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage5", TEXT("HOLLOW/Stage/Stage5/Stage5.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage5M_BACK");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5M_BACK");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage5M_BACK", TEXT("HOLLOW/Stage/Stage5/Stage5M_BACK.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage5M_BACK2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5M_BACK2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage5M_BACK2", TEXT("HOLLOW/Stage/Stage5/Stage5M_BACK2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage5M_BACK3");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5M_BACK3");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage5M_BACK3", TEXT("HOLLOW/Stage/Stage5/Stage5M_BACK3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage5M_BACK4");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5M_BACK4");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage5M_BACK4", TEXT("HOLLOW/Stage/Stage5/Stage5M_BACK4.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);


	GET_SINGLE(CResourceManager)->CreateMaterial("Stage5M_FRONT");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5M_FRONT");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage5M_FRONT", TEXT("HOLLOW/Stage/Stage5/Stage5M_FRONT.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	////////////////////////////////////////////////////////////////////////// PARTICLE
	////////////////////////////////////////////////////////////////////////// PARTICLE
	////////////////////////////////////////////////////////////////////////// PARTICLE GRASS
	GET_SINGLE(CResourceManager)->CreateMaterial("GrassParticle0");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticle0");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "GrassParticle0", TEXT("HOLLOW/Particle/GrassParticle/GrassParticle0.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("GrassParticle1");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticle1");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "GrassParticle1", TEXT("HOLLOW/Particle/GrassParticle/GrassParticle1.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("GrassParticle2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticle2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "GrassParticle2", TEXT("HOLLOW/Particle/GrassParticle/GrassParticle2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Empty");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Empty");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Empty", TEXT("HOLLOW/Empty.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	////////////////////////////////////////////////////////////////////////// PARTICLE
	////////////////////////////////////////////////////////////////////////// PARTICLE
	////////////////////////////////////////////////////////////////////////// PARTICLE ROCK
	GET_SINGLE(CResourceManager)->CreateMaterial("RockParticle0");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("RockParticle0");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "RockParticle0", TEXT("HOLLOW/Particle/RockParticle/RockParticle0.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("RockParticle1");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("RockParticle1");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "RockParticle1", TEXT("HOLLOW/Particle/RockParticle/RockParticle1.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("RockParticle2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("RockParticle2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "RockParticle2", TEXT("HOLLOW/Particle/RockParticle/RockParticle2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("RockParticle3");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("RockParticle3");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "RockParticle3", TEXT("HOLLOW/Particle/RockParticle/RockParticle3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	GET_SINGLE(CResourceManager)->CreateMaterial("BarrelParticle0");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BarrelParticle0");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "BarrelParticle0", TEXT("HOLLOW/Particle/BarrelParticle/BarrelParticle0.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("BarrelParticle1");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BarrelParticle1");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "BarrelParticle1", TEXT("HOLLOW/Particle/BarrelParticle/BarrelParticle1.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("BarrelParticle2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BarrelParticle2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "BarrelParticle2", TEXT("HOLLOW/Particle/BarrelParticle/BarrelParticle2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("BarrelParticle3");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BarrelParticle3");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "BarrelParticle3", TEXT("HOLLOW/Particle/BarrelParticle/BarrelParticle3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("BarrelParticle4");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BarrelParticle4");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "BarrelParticle4", TEXT("HOLLOW/Particle/BarrelParticle/BarrelParticle4.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("BarrelParticle5");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BarrelParticle5");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "BarrelParticle5", TEXT("HOLLOW/Particle/BarrelParticle/BarrelParticle5.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("FireBarrel");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("FireBarrel");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "FireBarrel", TEXT("HOLLOW/Particle/FireBarrel.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);



	GET_SINGLE(CResourceManager)->CreateMaterial("Blob0");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Blob0");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Blob0", TEXT("HOLLOW/Effect/Blob/NEW/Blob0.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Blob1");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Blob1");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Blob1", TEXT("HOLLOW/Effect/Blob/NEW/Blob1.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Blob2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Blob2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Blob2", TEXT("HOLLOW/Effect/Blob/NEW/Blob2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Blob3");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Blob3");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Blob3", TEXT("HOLLOW/Effect/Blob/NEW/Blob3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);



	GET_SINGLE(CResourceManager)->CreateMaterial("DarknessMaterial");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("DarknessMaterial");
	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	// pMaterial->SetTexture(0, "DarknessMaterial", TEXT("HOLLOW/Darkness.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);




	//GET_SINGLE(CResourceManager)->CreateMaterial("PlayerAnimMaterial");

	//pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMaterial");

	//pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	//// pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	//pMaterial->SetRenderState("AlphaBlend");
	//pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	//SAFE_RELEASE(pMaterial);




	//for (size_t i = 0; i < 13; ++i)
	//{
	//	TCHAR	strFileName[MAX_PATH] = {};
	//	wsprintf(strFileName, TEXT("HOLLOW/Monster/EFFECT/FK_WAVE%d.png"), i);

	//	char	strKey[256] = {};
	//	sprintf_s(strKey, "FK_WAVE%d", i);


	//	GET_SINGLE(CResourceManager)->CreateMaterial(strKey);
	//	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial(strKey);
	//	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	//	pMaterial->SetTexture(0, strKey, strFileName);
	//	pMaterial->SetRenderState("AlphaBlend");
	//	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	//	SAFE_RELEASE(pMaterial);
	//}









	/*GET_SINGLE(CResourceManager)->CreateMaterial("Stage2");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage2", TEXT("HOLLOW/Stage/Stage1/Stage2.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);



	GET_SINGLE(CResourceManager)->CreateMaterial("Stage3");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage3", TEXT("HOLLOW/Stage/Stage1/Stage3.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage4");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage4", TEXT("HOLLOW/Stage/Stage1/Stage4.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);

	GET_SINGLE(CResourceManager)->CreateMaterial("Stage5");
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5");
	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	pMaterial->SetTexture(0, "Stage5", TEXT("HOLLOW/Stage/Stage1/Stage5.png"));
	pMaterial->SetRenderState("AlphaBlend");
	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	SAFE_RELEASE(pMaterial);*/

	return true;
}






void HKMode::SetCollision()
{
	GET_SINGLE(CCollisionManager)->CreateChannel("Player", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("Monster", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("PlayerProjectile", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateChannel("MonsterProjectile", CT_BLOCK);

	GET_SINGLE(CCollisionManager)->CreateChannel("Object", CT_OVERLAP);
	GET_SINGLE(CCollisionManager)->CreateProfile("Object", "Object");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Object", "Object", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Object", "Sencer", CT_IGNORE);

	// GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Object", "Player", CT_OVERLAP);

	GET_SINGLE(CCollisionManager)->CreateChannel("Stage", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateProfile("Stage", "Stage");

	GET_SINGLE(CCollisionManager)->CreateChannel("Sencer", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateProfile("Sencer", "Sencer");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Sencer", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Sencer", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Sencer", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Sencer", "Sencer", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Sencer", "Object", CT_IGNORE);



	GET_SINGLE(CCollisionManager)->CreateChannel("Particle", CT_BLOCK);
	GET_SINGLE(CCollisionManager)->CreateProfile("Particle", "Particle");

	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Particle", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Particle", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Particle", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Particle", "Sencer", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Particle", "Object", CT_IGNORE);


	GET_SINGLE(CCollisionManager)->CreateProfile("Player", "Player");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Player", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Player", "PlayerProjectile", CT_IGNORE);

	GET_SINGLE(CCollisionManager)->CreateProfile("Monster", "Monster");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Monster", CT_IGNORE);
	//GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "MonsterProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("Monster", "Object", CT_IGNORE);

	GET_SINGLE(CCollisionManager)->CreateProfile("PlayerProjectile", "PlayerProjectile");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "Player", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("PlayerProjectile", "MonsterProjectile", CT_IGNORE);

	GET_SINGLE(CCollisionManager)->CreateProfile("MonsterProjectile", "MonsterProjectile");
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "Monster", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "PlayerProjectile", CT_IGNORE);
	GET_SINGLE(CCollisionManager)->UpdateProfileChannel("MonsterProjectile", "MonsterProjectile", CT_IGNORE);



	//{
	//	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerMtrl");

	//	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerMtrl");

	//	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	//	pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	//	pMaterial->SetRenderState("AlphaBlend");
	//	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);

	//	SAFE_RELEASE(pMaterial);

	//	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerAnimMtrl");

	//	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMtrl");

	//	pMaterial->SetSubsetShader(STANDARD_ANIM2D_SHADER);
	//	//pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	//	pMaterial->SetRenderState("AlphaBlend");
	//	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);

	//	SAFE_RELEASE(pMaterial);

	//	GET_SINGLE(CResourceManager)->CreateMaterial("PlayerAnimOutLineMtrl");

	//	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimOutLineMtrl");

	//	pMaterial->SetSubsetShader(STANDARD_ANIM2D_OUTLINE_SHADER);
	//	//pMaterial->SetTexture(0, "Player", TEXT("teemo.png"));
	//	pMaterial->SetRenderState("AlphaBlend");
	//	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	//	pMaterial->CreateCBufferNode(OUTLINE_CBUFFER, 11, sizeof(OutLineCBuffer));

	//	SAFE_RELEASE(pMaterial);

	//	GET_SINGLE(CResourceManager)->CreateMaterial("TestPixelMtrl");

	//	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("TestPixelMtrl");

	//	pMaterial->SetSubsetShader(STANDARD_TEX_SHADER);
	//	pMaterial->SetTexture(0, "TestPixel", TEXT("PixelCollision.png"));

	//	SAFE_RELEASE(pMaterial);

	//	GET_SINGLE(CResourceManager)->CreateMaterial("MainMapTileMaterial");

	//	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("MainMapTileMaterial");

	//	pMaterial->SetSubsetShader(TILEMAP_SHADER);
	//	pMaterial->SetTexture(0, "MainMapTile", TEXT("Tile.bmp"));

	//	SAFE_RELEASE(pMaterial);

	//	GET_SINGLE(CResourceManager)->CreateMaterial("BulletMaterial");

	//	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BulletMaterial");

	//	pMaterial->SetSubsetShader(TILEMAP_SHADER);
	//	pMaterial->SetTexture(0, "Bullet", TEXT("teemo.png"));
	//	pMaterial->SetRenderState("AlphaBlend");
	//	pMaterial->SetMaterialShaderStyle(MSS_ALPHA);
	//	pMaterial->EnableInstancing();
	//	pMaterial->AddRef();

	//	SAFE_RELEASE(pMaterial);
	//}


	//{
	//	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MinionIdle", true, 1.f, 7);
	//	GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MinionIdle", "MinionAtlas",
	//		TEXT("Monster/MinionAtlas.png"));

	//	for (int i = 0; i < 7; ++i)
	//	{
	//		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceFrameInfo("MinionIdle", Vector2(50.f * i, 0.f),
	//			Vector2(50.f * (i + 1), 37.f));
	//	}

	//	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MinionWalk", true, 1.f, 6);

	//	for (int i = 0; i <= 5; ++i)
	//	{
	//		TCHAR	strFileName[MAX_PATH] = {};

	//		wsprintf(strFileName, TEXT("Monster/MinionFrame/adventurer-run2-0%d.png"), i);

	//		char	strKey[256] = {};
	//		sprintf_s(strKey, "MinionWalk%d", i);

	//		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MinionWalk", strKey, strFileName);
	//	}

	//	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MinionWalk", Vector2(0.f, 0.f),
	//		Vector2(50.f, 37.f));

	//	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MinionKick", false, 1.f, 8);

	//	for (int i = 0; i <= 7; ++i)
	//	{
	//		TCHAR	strFileName[MAX_PATH] = {};

	//		wsprintf(strFileName, TEXT("Monster/MinionFrame/adventurer-kick-0%d.png"), i);

	//		char	strKey[256] = {};
	//		sprintf_s(strKey, "MinionKick%d", i);

	//		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MinionKick", strKey, strFileName);
	//	}

	//	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MinionKick", Vector2(0.f, 0.f),
	//		Vector2(50.f, 37.f));
	//}

}


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/*
할것들



*/



void HKMode::SetTileMap()
{
	HKTileMap* map = m_pScene->SpawnObject<HKTileMap>();

	HKExcelManager* excel = new HKExcelManager;
	
	excel->LoadStage(TEXT("Stage01.xls"), map);

	// HKExcelManager::LoadStage(TEXT("Stage01.xls"), map);
	
	SAFE_RELEASE(map);

	delete excel;
}
