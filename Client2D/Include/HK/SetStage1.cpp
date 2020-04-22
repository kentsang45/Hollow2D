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

#include "../HKStage.h"

#include "Grass.h"
#include "Statue.h"

#include <sstream>


void HKMode::SetStage(int stageNumber)
{
	// HKTileMap* map = m_pScene->SpawnObject<HKTileMap>();

	HKExcelManager* excel = new HKExcelManager;

	bool bShow = true;

	if (true == bShow)
	{

		HKStage* stage = m_pScene->SpawnObject<HKStage>();
		HKStage* stage1 = m_pScene->SpawnObject<HKStage>();
		HKStage* stage2 = m_pScene->SpawnObject<HKStage>();
		HKStage* stage3 = m_pScene->SpawnObject<HKStage>();
		HKStage* stage4 = m_pScene->SpawnObject<HKStage>();
		HKStage* stageF = m_pScene->SpawnObject<HKStage>();


		switch (stageNumber)
		{
		case 1:
			excel->LoadStage(TEXT("Stage1.xls"), m_pScene);
			stage->PlaceAt(1, 0);
			stage1->PlaceAt(1, 1);
			stage2->PlaceAt(1, 2);
			stage3->PlaceAt(1, 3);
			stage4->PlaceAt(1, 4);
			stageF->PlaceAt(1, 5);
			SetObject(1);
			break;

		case 2:
			excel->LoadStage(TEXT("Stage2.xls"), m_pScene);
			stage->PlaceAt(2, 0);
			stage1->PlaceAt(2, 1);
			stage2->PlaceAt(2, 2);
			stage3->PlaceAt(2, 3);
			stage4->PlaceAt(2, 4);
			stageF->PlaceAt(2, 5);
			break;

		case 3:
			excel->LoadStage(TEXT("Stage3.xls"), m_pScene);
			stage->PlaceAt(3, 0);
			stage1->PlaceAt(3, 1);
			stage2->PlaceAt(3, 2);
			stage3->PlaceAt(3, 3);
			stage4->PlaceAt(3, 4);
			stageF->PlaceAt(3, 5);
			break;

		case 4:
			excel->LoadStage(TEXT("Stage4.xls"), m_pScene);
			stage->PlaceAt(4, 0);
			stage1->PlaceAt(4, 1);
			stage2->PlaceAt(4, 2);
			stage3->PlaceAt(4, 3);
			stage4->PlaceAt(4, 4);
			stageF->PlaceAt(4, 5);
			break;

		case 5:
			excel->LoadStage(TEXT("Stage5.xls"), m_pScene);
			stage->PlaceAt(5, 0);
			stage1->PlaceAt(5, 1);
			stage2->PlaceAt(5, 2);
			stage3->PlaceAt(5, 3);
			stage4->PlaceAt(5, 4);
			stageF->PlaceAt(5, 5);
			break;
		default:
			BOOM;
			break;
		}

		// HKExcelManager::LoadStage(TEXT("Stage01.xls"), map);

		HollowKnight* hk = (HollowKnight*)GetPlayer();

		stage->SetPlayer(hk);
		stage1->SetPlayer(hk);
		stage2->SetPlayer(hk);
		stage3->SetPlayer(hk);
		stage4->SetPlayer(hk);
		stageF->SetPlayer(hk);


		// SAFE_RELEASE(map);
		SAFE_RELEASE(stage);
		SAFE_RELEASE(stage1);
		SAFE_RELEASE(stage2);
		SAFE_RELEASE(stage3);
		SAFE_RELEASE(stage4);
		SAFE_RELEASE(stageF);

	}
	else
	{
		excel->LoadStage(TEXT("Stage1.xls"), m_pScene);
	}

	delete excel;







	//TestStage* stage2 = m_pScene->SpawnObject<TestStage>(Vector3(1500.f, 101.f, 0.f));
	//stage2->SetScale(Vector3(2000.f, 200.f, 0.f));
	//SAFE_RELEASE(stage2);

	//TestStage* stage3 = m_pScene->SpawnObject<TestStage>(Vector3(-2000.f, 301.f, 0.f));
	//stage3->SetScale(Vector3(2000.f, 200.f, 0.f));
	//SAFE_RELEASE(stage3);

	//TestStage* stage4 = m_pScene->SpawnObject<TestStage>(Vector3(2000.f, 301.f, 0.f));
	//stage4->SetScale(Vector3(300.f, 100.f, 0.f));
	//SAFE_RELEASE(stage4);

}


void HKMode::SetObject(int stageNumber)
{
	Grass* grass1 = nullptr;
	Statue* statue1 = nullptr;

	switch (stageNumber)
	{
	case 1:
		grass1 = m_pScene->SpawnObject<Grass>();
		grass1->PlaceAt(4, 4, 79, 18);

		// 93, 24
		statue1 = m_pScene->SpawnObject<Statue>();
		statue1->PlaceAt(4, 4, 93, 24);


		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		BOOM;
		break;
	}


	SAFE_RELEASE(grass1);
	SAFE_RELEASE(statue1);
}