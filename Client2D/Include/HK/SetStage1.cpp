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
#include "Cart.h"

#include "Portal.h"
#include "Switch.h"
#include "Thorns.h"
#include "WaterDrop.h"

#include <sstream>


void HKMode::SetStage(int stage)
{
	// HKTileMap* map = m_pScene->SpawnObject<HKTileMap>();




	bool bShow = false;



	m_iCount = stage;	

	if (6 == stage)
	{
		m_iStart = 1;
		m_iCount = 6;


	}	
	else
	{
		m_iStart = stage;
		m_iCount = stage + 1;
	}
	
	m_pHK->PlaceAt(m_iStart, true);

	SetObject();
	PlaceMonster();

	

	for (m_iStart; m_iStart < m_iCount; ++m_iStart)
	{
		HKExcelManager* excel = new HKExcelManager;

		

		if (true == bShow)
		{

			HKStage* stage = m_pScene->SpawnObject<HKStage>();
			HKStage* stage1 = m_pScene->SpawnObject<HKStage>();
			HKStage* stage2 = m_pScene->SpawnObject<HKStage>();
			HKStage* stage3 = m_pScene->SpawnObject<HKStage>();
			HKStage* stage4 = m_pScene->SpawnObject<HKStage>();
			HKStage* stageF = m_pScene->SpawnObject<HKStage>();

			switch (m_iStart)
			{
			case 1:
				excel->LoadStage(TEXT("Stage1.xls"), m_pScene, m_iStart);
				stage->PlaceAt(1, 0);
				stage1->PlaceAt(1, 1);
				stage2->PlaceAt(1, 2);
				stage3->PlaceAt(1, 3);
				stage4->PlaceAt(1, 4);
				stageF->PlaceAt(1, 5);

				break;

			case 2:
				excel->LoadStage(TEXT("Stage2.xls"), m_pScene, m_iStart);
				stage->PlaceAt(2, 0);
				stage1->PlaceAt(2, 1);
				stage2->PlaceAt(2, 2);
				stage3->PlaceAt(2, 3);
				stage4->PlaceAt(2, 4);
				stageF->PlaceAt(2, 5);
				break;

			case 3:
				excel->LoadStage(TEXT("Stage3.xls"), m_pScene, m_iStart);
				stage->PlaceAt(3, 0);
				stage1->PlaceAt(3, 1);
				stage2->PlaceAt(3, 2);
				stage3->PlaceAt(3, 3);
				stage4->PlaceAt(3, 4);
				stageF->PlaceAt(3, 5);
				break;

			case 4:
				excel->LoadStage(TEXT("Stage4.xls"), m_pScene, m_iStart);
				stage->PlaceAt(4, 0);
				stage1->PlaceAt(4, 1);
				stage2->PlaceAt(4, 2);
				stage3->PlaceAt(4, 3);
				stage4->PlaceAt(4, 4);
				stageF->PlaceAt(4, 5);
				break;

			case 5:
				excel->LoadStage(TEXT("Stage5.xls"), m_pScene, m_iStart);
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


			switch (m_iStart)
			{
			case 1:
				excel->LoadStage(TEXT("Stage1.xls"), m_pScene, m_iStart);
				break;
			case 2:
				excel->LoadStage(TEXT("Stage2.xls"), m_pScene, m_iStart);
				break;
			case 3:
				excel->LoadStage(TEXT("Stage3.xls"), m_pScene, m_iStart);
				break;
			case 4:
				excel->LoadStage(TEXT("Stage4.xls"), m_pScene, m_iStart);
				break;
			case 5:
				excel->LoadStage(TEXT("Stage5.xls"), m_pScene, m_iStart);
				break;
			default:
				BOOM;
				break;
			}

			// SetObject(3);
		}

		delete excel;

	}

	






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


void HKMode::SetObject()
{
	Grass* grass1 = nullptr;
	Grass* grass2 = nullptr;
	Grass* grass3 = nullptr;
	Grass* grass4 = nullptr;	
	Grass* grass5 = nullptr;
	Grass* grass6 = nullptr;
	Grass* grass7 = nullptr;
	Grass* grass8 = nullptr;
	Grass* grass9 = nullptr;
	Grass* grass10 = nullptr;
	Grass* grass11 = nullptr;
	Grass* grass12 = nullptr;
	Grass* grass13 = nullptr;
	Grass* grass14 = nullptr;
	Grass* grass15 = nullptr;
	Grass* grass16 = nullptr;
	Grass* grass17 = nullptr;
	Grass* grass18 = nullptr;
	Grass* grass19 = nullptr;

	Cart* cart1 = nullptr;
	Cart* cart2 = nullptr;
	Cart* cart3 = nullptr;
	Cart* cart4 = nullptr;
	Cart* cart5 = nullptr;
	Cart* cart6 = nullptr;	
	Cart* cart7 = nullptr;
	Cart* cart8 = nullptr;
	
	
	
	Statue* statue1 = nullptr;
	Statue* statue2 = nullptr;
	Statue* statue3 = nullptr;
	Statue* statue4 = nullptr;

	Portal* pt1 = nullptr;
	Portal* pt2 = nullptr;
	Switch* sw1 = nullptr;

	Thorns* th1 = nullptr;
	Thorns* th2 = nullptr;
	Thorns* th3 = nullptr;
	Thorns* th4 = nullptr;
	Thorns* th5 = nullptr;
	Thorns* th6 = nullptr;
	Thorns* th7 = nullptr;
	Thorns* th8 = nullptr;
	Thorns* th9 = nullptr;
	Thorns* th10 = nullptr;

	WaterDrop* wd1 = nullptr;
	WaterDrop* wd2 = nullptr;
	WaterDrop* wd3 = nullptr;
	WaterDrop* wd4 = nullptr;
	WaterDrop* wd5 = nullptr;
	WaterDrop* wd6 = nullptr;
	WaterDrop* wd7 = nullptr;
	WaterDrop* wd8 = nullptr;
	WaterDrop* wd9 = nullptr;
	WaterDrop* wd10 = nullptr;



	bool setObject= true;

	for (size_t stageNumber = m_iStart; stageNumber < m_iCount; ++stageNumber)
	{
		if (true == setObject)
		{
			switch (stageNumber)
			{
			case 1:
			{
				pt2 = m_pScene->SpawnObject<Portal>();
				pt2->SetStageNumber(stageNumber);

				pt2->PlaceAt(1,11, 133 + 2, 8, 2);
				pt2->SetStart(false);

				grass1 = m_pScene->SpawnObject<Grass>();
				grass1->SetStageNumber(stageNumber);
				grass1->PlaceAt(4, 4, 79, 18, 2);

				grass2 = m_pScene->SpawnObject<Grass>();
				grass2->SetStageNumber(stageNumber);
				grass2->PlaceAt(4, 4, 74, 18, 4);

				grass3 = m_pScene->SpawnObject<Grass>();
				grass3->SetStageNumber(stageNumber);
				grass3->PlaceAt(4, 4, 59, 18, 5);

				grass4 = m_pScene->SpawnObject<Grass>();
				grass4->SetStageNumber(stageNumber);
				grass4->PlaceAt(4, 4, 54, 18, 4);

				grass5 = m_pScene->SpawnObject<Grass>();
				grass5->SetStageNumber(stageNumber);
				grass5->PlaceAt(4, 4, 90, 18, 5);

				grass6 = m_pScene->SpawnObject<Grass>();
				grass6->SetStageNumber(stageNumber);
				grass6->PlaceAt(4, 4, 86, 23, 2);

				grass7 = m_pScene->SpawnObject<Grass>();
				grass7->SetStageNumber(stageNumber);
				grass7->PlaceAt(4, 4, 107, 26, 2);

				grass8 = m_pScene->SpawnObject<Grass>();
				grass8->SetStageNumber(stageNumber);
				grass8->PlaceAt(4, 4, 112, 26, 5);

				grass9 = m_pScene->SpawnObject<Grass>();
				grass9->SetStageNumber(stageNumber);
				grass9->PlaceAt(4, 4, 117, 26, 1);

				grass10 = m_pScene->SpawnObject<Grass>();
				grass10->SetStageNumber(stageNumber);
				grass10->PlaceAt(4, 4, 124, 15, 1);

				grass11 = m_pScene->SpawnObject<Grass>();
				grass11->SetStageNumber(stageNumber);
				grass11->PlaceAt(4, 4, 50, 30, 1);

				//
				grass12 = m_pScene->SpawnObject<Grass>();
				grass12->SetStageNumber(stageNumber);
				grass12->PlaceAt(4, 4, 43, 19.5f, 1);
				grass12->Reverse();

				grass13 = m_pScene->SpawnObject<Grass>();
				grass13->SetStageNumber(stageNumber);
				grass13->PlaceAt(4, 4, 34, 19.5f, 2);

				grass14 = m_pScene->SpawnObject<Grass>();
				grass14->SetStageNumber(stageNumber);
				grass14->PlaceAt(4, 4, 25, 19.5f, 4);
				//
				grass15 = m_pScene->SpawnObject<Grass>();
				grass15->SetStageNumber(stageNumber);
				grass15->PlaceAt(4, 4, 17, 27, 2);

				grass16 = m_pScene->SpawnObject<Grass>();
				grass16->SetStageNumber(stageNumber);
				grass16->PlaceAt(4, 4, 12, 18, 4);
				grass16->Reverse();

				grass17 = m_pScene->SpawnObject<Grass>();
				grass17->SetStageNumber(stageNumber);
				grass17->PlaceAt(4, 4, 4, 27, 1);

				//////////////////////////////////

				cart1 = m_pScene->SpawnObject<Cart>();
				cart1->SetStageNumber(stageNumber);
				cart1->PlaceAt(4, 4, 38, 19.5f, 3);

				////////////////////////////////// 93, 24
				statue1 = m_pScene->SpawnObject<Statue>();
				statue1->SetStageNumber(stageNumber);
				statue1->PlaceAt(4, 4, 93, 24, 4);

				statue2 = m_pScene->SpawnObject<Statue>();
				statue2->SetStageNumber(stageNumber);
				statue2->PlaceAt(4, 4, 102, 26, 7);

				statue3 = m_pScene->SpawnObject<Statue>();
				statue3->SetStageNumber(stageNumber);
				statue3->PlaceAt(4, 4, 9, 27, 4);


				///////////////////////////////////////
				wd1 = m_pScene->SpawnObject<WaterDrop>();
				wd1->SetStageNumber(stageNumber);
				wd1->PlaceAt(4, 4, 62, 13, 2);

				wd2 = m_pScene->SpawnObject<WaterDrop>();
				wd2->SetStageNumber(stageNumber);
				wd2->PlaceAt(4, 4, 79, 15, 4);

				wd3 = m_pScene->SpawnObject<WaterDrop>();
				wd3->SetStageNumber(stageNumber);
				wd3->PlaceAt(4, 4, 45, 11, 5);

				wd4 = m_pScene->SpawnObject<WaterDrop>();
				wd4->SetStageNumber(stageNumber);
				wd4->PlaceAt(4, 4, 11, 24, 4);

				wd5 = m_pScene->SpawnObject<WaterDrop>();
				wd5->SetStageNumber(stageNumber);
				wd5->PlaceAt(4, 4, 94, 7, 5);

				wd6 = m_pScene->SpawnObject<WaterDrop>();
				wd6->SetStageNumber(stageNumber);
				wd6->PlaceAt(4, 4, 114, 20, 2);

				break;
			}
			case 2:
			{
				pt1 = m_pScene->SpawnObject<Portal>();
				pt1->SetStageNumber(stageNumber);
				pt1->PlaceAt(1, 7, -1, 17, 2);

				pt2 = m_pScene->SpawnObject<Portal>();
				pt2->SetStageNumber(stageNumber);
				pt2->PlaceAt(6, 2, 76, 35, 2);
				pt2->SetStart(false);

				grass1 = m_pScene->SpawnObject<Grass>();
				grass1->SetStageNumber(stageNumber);
				grass1->PlaceAt(4, 4, 0, 21, 2);

				grass2 = m_pScene->SpawnObject<Grass>();
				grass2->SetStageNumber(stageNumber);
				grass2->PlaceAt(4, 4, 11, 21, 5);

				grass3 = m_pScene->SpawnObject<Grass>();
				grass3->SetStageNumber(stageNumber);
				grass3->PlaceAt(4, 4, 16, 21, 5);

				grass4 = m_pScene->SpawnObject<Grass>();
				grass4->SetStageNumber(stageNumber);
				grass4->PlaceAt(4, 4, 23, 21, 1);

				grass5 = m_pScene->SpawnObject<Grass>();
				grass5->SetStageNumber(stageNumber);
				grass5->PlaceAt(4, 4, 22, 32, 3);

				grass6 = m_pScene->SpawnObject<Grass>();
				grass6->SetStageNumber(stageNumber);
				grass6->PlaceAt(4, 4, 90, 29, 3);
				grass6->Reverse();

				grass7 = m_pScene->SpawnObject<Grass>();
				grass7->SetStageNumber(stageNumber);
				grass7->PlaceAt(4, 4, 93, 29, 4);
				grass7->Reverse();

				grass8 = m_pScene->SpawnObject<Grass>();
				grass8->SetStageNumber(stageNumber);
				grass8->PlaceAt(4, 4, 99, 14, 2);
				grass8->Reverse();




				statue1 = m_pScene->SpawnObject<Statue>();
				statue1->SetStageNumber(stageNumber);
				statue1->PlaceAt(4, 4, 65, 29, 7);

				th1 = m_pScene->SpawnObject<Thorns>();
				th1->SetStageNumber(stageNumber);
				th1->PlaceAt(2, 2, 26, 25, 7);

				th2 = m_pScene->SpawnObject<Thorns>();
				th2->SetStageNumber(stageNumber);
				th2->PlaceAt(2, 2, 28, 25, 7);

				th3 = m_pScene->SpawnObject<Thorns>();
				th3->SetStageNumber(stageNumber);
				th3->PlaceAt(2, 2, 30, 25, 7);


				th4 = m_pScene->SpawnObject<Thorns>();
				th4->SetStageNumber(stageNumber);
				th4->PlaceAt(2, 2, 35, 25, 7);

				th5 = m_pScene->SpawnObject<Thorns>();
				th5->SetStageNumber(stageNumber);
				th5->PlaceAt(2, 2, 37, 25, 7);

				th6 = m_pScene->SpawnObject<Thorns>();
				th6->SetStageNumber(stageNumber);
				th6->PlaceAt(2, 2, 39, 25, 7);


				th7 = m_pScene->SpawnObject<Thorns>();
				th7->SetStageNumber(stageNumber);
				th7->PlaceAt(2, 2, 47, 25, 7);

				th8 = m_pScene->SpawnObject<Thorns>();
				th8->SetStageNumber(stageNumber);
				th8->PlaceAt(2, 2, 49, 25, 7);






				wd1 = m_pScene->SpawnObject<WaterDrop>();
				wd1->SetStageNumber(stageNumber);
				wd1->PlaceAt(4, 4, 20, 14, 2);

				wd2 = m_pScene->SpawnObject<WaterDrop>();
				wd2->SetStageNumber(stageNumber);
				wd2->PlaceAt(4, 4, 59, 14, 4);

				wd3 = m_pScene->SpawnObject<WaterDrop>();
				wd3->SetStageNumber(stageNumber);
				wd3->PlaceAt(4, 4, 91, 21, 5);

				break;
			}
			case 3:
			{
				pt2 = m_pScene->SpawnObject<Portal>();
				pt2->SetStageNumber(stageNumber);
				pt2->PlaceAt(2, 8, -2, 79, 2);
				pt2->SetStart(false);

				pt1 = m_pScene->SpawnObject<Portal>();
				pt1->SetStageNumber(stageNumber);
				pt1->PlaceAt(5, 1, 16, -1.1, 2);


				/////////////////////////////////////////
				grass1 = m_pScene->SpawnObject<Grass>();
				grass1->SetStageNumber(stageNumber);
				grass1->PlaceAt(4, 4, 3, 14, 4);

				grass2 = m_pScene->SpawnObject<Grass>();
				grass2->SetStageNumber(stageNumber);
				grass2->PlaceAt(4, 4, 29, 16, 4);

				grass3 = m_pScene->SpawnObject<Grass>();
				grass3->SetStageNumber(stageNumber);
				grass3->PlaceAt(4, 4, 33, 16, 4);

				grass4 = m_pScene->SpawnObject<Grass>();
				grass4->SetStageNumber(stageNumber);
				grass4->PlaceAt(4, 4, 7, 25, 2);

				grass5 = m_pScene->SpawnObject<Grass>();
				grass5->SetStageNumber(stageNumber);
				grass5->PlaceAt(4, 4, 13, 25, 2);
				grass5->Reverse();



				grass6 = m_pScene->SpawnObject<Grass>();
				grass6->SetStageNumber(stageNumber);
				grass6->PlaceAt(4, 4, 10, 32, 4);

				grass7 = m_pScene->SpawnObject<Grass>();
				grass7->SetStageNumber(stageNumber);
				grass7->PlaceAt(4, 4, 15, 32, 5);

				grass8 = m_pScene->SpawnObject<Grass>();		
				grass8->SetStageNumber(stageNumber);
				grass8->PlaceAt(4, 4, 19, 32, 1);


				grass9 = m_pScene->SpawnObject<Grass>();
				grass9->SetStageNumber(stageNumber);
				grass9->PlaceAt(4, 4, 32, 39, 1);
				grass9->Reverse();




				grass10 = m_pScene->SpawnObject<Grass>();
				grass10->SetStageNumber(stageNumber);
				grass10->PlaceAt(4, 4, 36, 51, 2);

				grass11 = m_pScene->SpawnObject<Grass>();
				grass11->SetStageNumber(stageNumber);
				grass11->PlaceAt(4, 4, 22, 53, 1);

				grass12 = m_pScene->SpawnObject<Grass>();
				grass12->SetStageNumber(stageNumber);
				grass12->PlaceAt(4, 4, 13, 58, 4);


				grass13 = m_pScene->SpawnObject<Grass>();
				grass13->SetStageNumber(stageNumber);
				grass13->PlaceAt(4, 4, 28, 63, 4);


				grass14 = m_pScene->SpawnObject<Grass>();
				grass14->SetStageNumber(stageNumber);
				grass14->PlaceAt(4, 4, 22, 75, 3);




				grass15 = m_pScene->SpawnObject<Grass>();
				grass15->SetStageNumber(stageNumber);
				grass15->PlaceAt(4, 4, 7, 84, 1);

				grass16 = m_pScene->SpawnObject<Grass>();
				grass16->SetStageNumber(stageNumber);
				grass16->PlaceAt(4, 4, 5, 84, 1);
				grass16->Reverse();

				grass17 = m_pScene->SpawnObject<Grass>();
				grass17->SetStageNumber(stageNumber);
				grass17->PlaceAt(4, 4, 1, 84, 5);

				grass18 = m_pScene->SpawnObject<Grass>();
				grass18->SetStageNumber(stageNumber);
				grass18->PlaceAt(4, 4, 28, 86, 4);

				grass19 = m_pScene->SpawnObject<Grass>();
				grass19->SetStageNumber(stageNumber);
				grass19->PlaceAt(4, 4, 10, 88, 3);






				statue1 = m_pScene->SpawnObject<Statue>();
				statue1->SetStageNumber(stageNumber);
				statue1->PlaceAt(4, 4, 30, 50, 6);

				statue2 = m_pScene->SpawnObject<Statue>();
				statue2->SetStageNumber(stageNumber);
				statue2->PlaceAt(4, 4, 17, 53, 8);

				statue3 = m_pScene->SpawnObject<Statue>();
				statue3->SetStageNumber(stageNumber);
				statue3->PlaceAt(4, 4, 16, 69, 7);


				wd1 = m_pScene->SpawnObject<WaterDrop>();
				wd1->SetStageNumber(stageNumber);
				wd1->PlaceAt(4, 4, 4, 6, 2);

				wd2 = m_pScene->SpawnObject<WaterDrop>();
				wd2->SetStageNumber(stageNumber);
				wd2->PlaceAt(4, 4, 22, 23, 4);

				wd3 = m_pScene->SpawnObject<WaterDrop>();
				wd3->SetStageNumber(stageNumber);
				wd3->PlaceAt(4, 4, 32, 31, 5);

				wd4 = m_pScene->SpawnObject<WaterDrop>();
				wd4->SetStageNumber(stageNumber);
				wd4->PlaceAt(4, 4, 3, 46, 4);

				wd5 = m_pScene->SpawnObject<WaterDrop>();
				wd5->SetStageNumber(stageNumber);
				wd5->PlaceAt(4, 4, 21, 64, 5);

				wd6 = m_pScene->SpawnObject<WaterDrop>();
				wd6->SetStageNumber(stageNumber);
				wd6->PlaceAt(4, 4, 15, 84, 2);




				break;
			}
			case 4:
			{
				pt1 = m_pScene->SpawnObject<Portal>();
				pt1->SetStageNumber(stageNumber);
				pt1->PlaceAt(1, 6, 138, 13, 2);

				pt2 = m_pScene->SpawnObject<Portal>();
				pt2->SetStageNumber(stageNumber);
				pt2->PlaceAt(1, 6, -1, 24, 2);
				pt2->SetStart(false);

				/////////////////////////////////////////////
				cart1 = m_pScene->SpawnObject<Cart>();
				cart1->SetStageNumber(stageNumber);
				cart1->PlaceAt(4, 4, 48, 30, 3);

				cart2 = m_pScene->SpawnObject<Cart>();
				cart2->SetStageNumber(stageNumber);
				cart2->PlaceAt(4, 4, 60, 32 - 1, 3, false);
				cart3 = m_pScene->SpawnObject<Cart>();
				cart3->SetStageNumber(stageNumber);
				cart3->PlaceAt(4, 4, 58, 32 - 1, 4, false);
				cart4 = m_pScene->SpawnObject<Cart>();
				cart4->SetStageNumber(stageNumber);
				cart4->PlaceAt(4, 4, 55, 32 - 1, 2, false);

				cart5 = m_pScene->SpawnObject<Cart>();
				cart5->SetStageNumber(stageNumber);
				cart5->PlaceAt(4, 4, 38, 31 - 1, 4, false);

				cart6 = m_pScene->SpawnObject<Cart>();
				cart6->SetStageNumber(stageNumber);
				cart6->PlaceAt(4, 4, 71, 31 - 1, 4, false);

				cart7 = m_pScene->SpawnObject<Cart>();
				cart7->SetStageNumber(stageNumber);
				cart7->PlaceAt(4, 4, 74, 31 - 1, 4, false);


				statue1 = m_pScene->SpawnObject<Statue>();
				statue1->SetStageNumber(stageNumber);
				statue1->PlaceAt(4, 4, 126, 24, 4);

				statue2 = m_pScene->SpawnObject<Statue>();
				statue2->SetStageNumber(stageNumber);
				statue2->PlaceAt(4, 4, 116, 28, 2);

				statue3 = m_pScene->SpawnObject<Statue>();
				statue3->SetStageNumber(stageNumber);
				statue3->PlaceAt(4, 4, 79, 28, 2);

				statue4 = m_pScene->SpawnObject<Statue>();
				statue4->SetStageNumber(stageNumber);
				statue4->PlaceAt(4, 4, 43, 29, 3);

				th1 = m_pScene->SpawnObject<Thorns>();
				th1->SetStageNumber(stageNumber);
				th1->PlaceAt(2, 2, 14, 14, 7);

				th2 = m_pScene->SpawnObject<Thorns>();
				th2->SetStageNumber(stageNumber);
				th2->PlaceAt(2, 2, 16, 14, 7);

				th3 = m_pScene->SpawnObject<Thorns>();
				th3->SetStageNumber(stageNumber);
				th3->PlaceAt(2, 2, 18, 14, 7);


				th4 = m_pScene->SpawnObject<Thorns>();
				th4->SetStageNumber(stageNumber);
				th4->PlaceAt(2, 2, 20, 14, 7);

				th5 = m_pScene->SpawnObject<Thorns>();
				th5->SetStageNumber(stageNumber);
				th5->PlaceAt(2, 2, 22, 14, 7);

				th6 = m_pScene->SpawnObject<Thorns>();
				th6->SetStageNumber(stageNumber);
				th6->PlaceAt(2, 2, 24, 14, 7);


				th7 = m_pScene->SpawnObject<Thorns>();
				th7->SetStageNumber(stageNumber);
				th7->PlaceAt(2, 2, 26, 14, 7);

				th8 = m_pScene->SpawnObject<Thorns>();
				th8->SetStageNumber(stageNumber);
				th8->PlaceAt(2, 2, 28, 14, 7);

				th9 = m_pScene->SpawnObject<Thorns>();
				th9->SetStageNumber(stageNumber);
				th9->PlaceAt(2, 2, 30, 14, 7);

				th10 = m_pScene->SpawnObject<Thorns>();
				th10->SetStageNumber(stageNumber);
				th10->PlaceAt(2, 2, 32, 14, 7);


				wd1 = m_pScene->SpawnObject<WaterDrop>();
				wd1->SetStageNumber(stageNumber);
				wd1->PlaceAt(4, 4, 112, 12, 2);

				wd2 = m_pScene->SpawnObject<WaterDrop>();
				wd2->SetStageNumber(stageNumber);
				wd2->PlaceAt(4, 4, 92, 20, 4);

				wd3 = m_pScene->SpawnObject<WaterDrop>();
				wd3->SetStageNumber(stageNumber);
				wd3->PlaceAt(4, 4, 64, 4, 5);

				wd4 = m_pScene->SpawnObject<WaterDrop>();
				wd4->SetStageNumber(stageNumber);
				wd4->PlaceAt(4, 4, 51, 24, 4);

				wd5 = m_pScene->SpawnObject<WaterDrop>();
				wd5->SetStageNumber(stageNumber);
				wd5->PlaceAt(4, 4, 33, 24, 5);

				wd6 = m_pScene->SpawnObject<WaterDrop>();
				wd6->SetStageNumber(stageNumber);
				wd6->PlaceAt(4, 4, 42, 10, 2);

				wd7 = m_pScene->SpawnObject<WaterDrop>();
				wd7->SetStageNumber(stageNumber);
				wd7->PlaceAt(4, 4, 3, 24, 2);

				break;
			}

			case 5:
			{
				pt1 = m_pScene->SpawnObject<Portal>();
				pt1->SetStageNumber(stageNumber);
				pt1->PlaceAt(1, 5, 100, 31, 2);

				pt2 = m_pScene->SpawnObject<Portal>();
				pt2->SetStageNumber(stageNumber);
				pt2->PlaceAt(1, 5, -1, 34, 2);
				pt2->SetStart(false);

				sw1 = m_pScene->SpawnObject<Switch>();
				sw1->SetStageNumber(stageNumber);
				sw1->PlaceAt(1, 5, 34, 31, 2);


				//////////////////////////////////////////////////
				cart1 = m_pScene->SpawnObject<Cart>();
				cart1->SetStageNumber(stageNumber);
				cart1->PlaceAt(4, 4, 81, 33, 4, false);

				cart2 = m_pScene->SpawnObject<Cart>();
				cart2->SetStageNumber(stageNumber);
				cart2->PlaceAt(4, 4, 72, 33, 2, false);

				cart3 = m_pScene->SpawnObject<Cart>();
				cart3->SetStageNumber(stageNumber);
				cart3->PlaceAt(4, 4, 13, 33, 3, false);

				grass1 = m_pScene->SpawnObject<Grass>();
				grass1->SetStageNumber(stageNumber);
				grass1->PlaceAt(4, 4, 18, 32.5f, 4);
			
				grass2 = m_pScene->SpawnObject<Grass>();
				grass2->SetStageNumber(stageNumber);
				grass2->PlaceAt(4, 4, 16, 32.5f, 2);
			
				grass3 = m_pScene->SpawnObject<Grass>();
				grass3->SetStageNumber(stageNumber);
				grass3->PlaceAt(4, 4, 7, 32.5f, 1);




				wd1 = m_pScene->SpawnObject<WaterDrop>();
				wd1->SetStageNumber(stageNumber);
				wd1->PlaceAt(4, 4, 80, 31, 2);

				wd2 = m_pScene->SpawnObject<WaterDrop>();
				wd2->SetStageNumber(stageNumber);
				wd2->PlaceAt(4, 4, 17, 29, 4);

				wd3 = m_pScene->SpawnObject<WaterDrop>();
				wd3->SetStageNumber(stageNumber);
				wd3->PlaceAt(4, 4, 4, 13, 5);

				break;
			}
			default:
				BOOM;
				break;
			}
		}



		SAFE_RELEASE(grass1);
		SAFE_RELEASE(grass2);
		SAFE_RELEASE(grass3);
		SAFE_RELEASE(grass4);
		SAFE_RELEASE(grass5);
		SAFE_RELEASE(grass6);
		SAFE_RELEASE(grass7);
		SAFE_RELEASE(grass8);
		SAFE_RELEASE(grass9);
		SAFE_RELEASE(grass10);
		SAFE_RELEASE(grass11);
		SAFE_RELEASE(grass12);
		SAFE_RELEASE(grass13);
		SAFE_RELEASE(grass14);
		SAFE_RELEASE(grass15);
		SAFE_RELEASE(grass16);
		SAFE_RELEASE(grass17);
		SAFE_RELEASE(grass18);
		SAFE_RELEASE(grass19);

		SAFE_RELEASE(cart1);
		SAFE_RELEASE(cart2);
		SAFE_RELEASE(cart3);
		SAFE_RELEASE(cart4);
		SAFE_RELEASE(cart5);
		SAFE_RELEASE(cart6);
		SAFE_RELEASE(cart7);
		SAFE_RELEASE(cart8);

		SAFE_RELEASE(statue1);
		SAFE_RELEASE(statue2);
		SAFE_RELEASE(statue3);
		SAFE_RELEASE(statue4);



		SAFE_RELEASE(pt1);
		SAFE_RELEASE(pt2);
		SAFE_RELEASE(sw1);

		SAFE_RELEASE(th1);
		SAFE_RELEASE(th2);
		SAFE_RELEASE(th3);
		SAFE_RELEASE(th4);
		SAFE_RELEASE(th5);
		SAFE_RELEASE(th6);
		SAFE_RELEASE(th7);
		SAFE_RELEASE(th8);
		SAFE_RELEASE(th9);
		SAFE_RELEASE(th10);

		SAFE_RELEASE(wd1);
		SAFE_RELEASE(wd2);
		SAFE_RELEASE(wd3);
		SAFE_RELEASE(wd4);
		SAFE_RELEASE(wd5);
		SAFE_RELEASE(wd6);
		SAFE_RELEASE(wd7);
		SAFE_RELEASE(wd8);
		SAFE_RELEASE(wd9);
		SAFE_RELEASE(wd10);
	}
}