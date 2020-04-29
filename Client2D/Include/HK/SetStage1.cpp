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

#include <sstream>


void HKMode::SetStage(int stageNumber)
{
	// HKTileMap* map = m_pScene->SpawnObject<HKTileMap>();

	PlaceMonster(stageNumber);

	



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

		SetObject(stageNumber);

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
		switch (stageNumber)
		{
		case 1:
			excel->LoadStage(TEXT("Stage1.xls"), m_pScene);
			break;
		case 2:
			excel->LoadStage(TEXT("Stage2.xls"), m_pScene);
			break;
		case 3:
			excel->LoadStage(TEXT("Stage3.xls"), m_pScene);
			break;
		case 4:
			excel->LoadStage(TEXT("Stage4.xls"), m_pScene);
			break;
		case 5:
			excel->LoadStage(TEXT("Stage5.xls"), m_pScene);
			break;
		default:
			BOOM;
			break;
		}
	
		// SetObject(3);
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




	bool setObject= true;

	if (true == setObject)
	{
		switch (stageNumber)
		{
		case 1:
		{
			grass1 = m_pScene->SpawnObject<Grass>();
			grass1->PlaceAt(4, 4, 79, 18, 2);

			grass2 = m_pScene->SpawnObject<Grass>();
			grass2->PlaceAt(4, 4, 74, 18, 4);

			grass3 = m_pScene->SpawnObject<Grass>();
			grass3->PlaceAt(4, 4, 59, 18, 5);

			grass4 = m_pScene->SpawnObject<Grass>();
			grass4->PlaceAt(4, 4, 54, 18, 4);

			grass5 = m_pScene->SpawnObject<Grass>();
			grass5->PlaceAt(4, 4, 90, 18, 5);

			grass6 = m_pScene->SpawnObject<Grass>();
			grass6->PlaceAt(4, 4, 86, 23, 2);

			grass7 = m_pScene->SpawnObject<Grass>();
			grass7->PlaceAt(4, 4, 107, 26, 2);

			grass8 = m_pScene->SpawnObject<Grass>();
			grass8->PlaceAt(4, 4, 112, 26, 5);

			grass9 = m_pScene->SpawnObject<Grass>();
			grass9->PlaceAt(4, 4, 117, 26, 1);

			grass10 = m_pScene->SpawnObject<Grass>();
			grass10->PlaceAt(4, 4, 124, 15, 1);

			grass11 = m_pScene->SpawnObject<Grass>();
			grass11->PlaceAt(4, 4, 50, 30, 1);

			//
			grass12 = m_pScene->SpawnObject<Grass>();
			grass12->PlaceAt(4, 4, 43, 19.5f, 1);
			grass12->Reverse();

			grass13 = m_pScene->SpawnObject<Grass>();
			grass13->PlaceAt(4, 4, 34, 19.5f, 2);

			grass14 = m_pScene->SpawnObject<Grass>();
			grass14->PlaceAt(4, 4, 25, 19.5f, 4);
			//
			grass15 = m_pScene->SpawnObject<Grass>();
			grass15->PlaceAt(4, 4, 17, 27, 2);

			grass16 = m_pScene->SpawnObject<Grass>();
			grass16->PlaceAt(4, 4, 12, 18, 4);
			grass16->Reverse();

			grass17 = m_pScene->SpawnObject<Grass>();
			grass17->PlaceAt(4, 4, 4, 27, 1);

			//////////////////////////////////

			cart1 = m_pScene->SpawnObject<Cart>();
			cart1->PlaceAt(4, 4, 38, 19.5f, 3);

			////////////////////////////////// 93, 24
			statue1 = m_pScene->SpawnObject<Statue>();
			statue1->PlaceAt(4, 4, 93, 24, 4);

			statue2 = m_pScene->SpawnObject<Statue>();
			statue2->PlaceAt(4, 4, 102, 26, 7);

			statue3 = m_pScene->SpawnObject<Statue>();
			statue3->PlaceAt(4, 4, 9, 27, 4);

			break;
		}
		case 2:
		{
			grass1 = m_pScene->SpawnObject<Grass>();
			grass1->PlaceAt(4, 4, 0, 21, 2);

			grass2 = m_pScene->SpawnObject<Grass>();
			grass2->PlaceAt(4, 4, 11, 21, 5);

			grass3 = m_pScene->SpawnObject<Grass>();
			grass3->PlaceAt(4, 4, 16, 21, 5);

			grass4 = m_pScene->SpawnObject<Grass>();
			grass4->PlaceAt(4, 4, 23, 21, 1);

			grass5 = m_pScene->SpawnObject<Grass>();
			grass5->PlaceAt(4, 4, 22, 32, 3);

			grass6 = m_pScene->SpawnObject<Grass>();
			grass6->PlaceAt(4, 4, 90, 29, 3);
			grass6->Reverse();

			grass7 = m_pScene->SpawnObject<Grass>();
			grass7->PlaceAt(4, 4, 93, 29, 4);
			grass7->Reverse();

			grass8 = m_pScene->SpawnObject<Grass>();
			grass8->PlaceAt(4, 4, 99, 14, 2);
			grass8->Reverse();




			statue1 = m_pScene->SpawnObject<Statue>();
			statue1->PlaceAt(4, 4, 65, 29, 7);



			break;
		}
		case 3:
		{
			grass1 = m_pScene->SpawnObject<Grass>();
			grass1->PlaceAt(4, 4, 3, 14, 4);

			grass2 = m_pScene->SpawnObject<Grass>();
			grass2->PlaceAt(4, 4, 29, 16, 4);

			grass3 = m_pScene->SpawnObject<Grass>();
			grass3->PlaceAt(4, 4, 33, 16, 4);

			grass4 = m_pScene->SpawnObject<Grass>();
			grass4->PlaceAt(4, 4, 7, 25, 2);

			grass5 = m_pScene->SpawnObject<Grass>();
			grass5->PlaceAt(4, 4, 13, 25, 2);
			grass5->Reverse();



			grass6 = m_pScene->SpawnObject<Grass>();
			grass6->PlaceAt(4, 4, 10, 32, 4);

			grass7 = m_pScene->SpawnObject<Grass>();
			grass7->PlaceAt(4, 4, 15, 32, 5);

			grass8 = m_pScene->SpawnObject<Grass>();
			grass8->PlaceAt(4, 4, 19, 32, 1);


			grass9 = m_pScene->SpawnObject<Grass>();
			grass9->PlaceAt(4, 4, 32, 39, 1);
			grass9->Reverse();




			grass10 = m_pScene->SpawnObject<Grass>();
			grass10->PlaceAt(4, 4, 36, 51, 2);

			grass11 = m_pScene->SpawnObject<Grass>();
			grass11->PlaceAt(4, 4, 22, 53, 1);

			grass12 = m_pScene->SpawnObject<Grass>();
			grass12->PlaceAt(4, 4, 13, 58, 4);


			grass13 = m_pScene->SpawnObject<Grass>();
			grass13->PlaceAt(4, 4, 28, 63, 4);
			

			grass14 = m_pScene->SpawnObject<Grass>();
			grass14->PlaceAt(4, 4, 22, 75, 3);




			grass15 = m_pScene->SpawnObject<Grass>();
			grass15->PlaceAt(4, 4, 7, 84, 1);

			grass16 = m_pScene->SpawnObject<Grass>();
			grass16->PlaceAt(4, 4, 5, 84, 1);
			grass16->Reverse();

			grass17 = m_pScene->SpawnObject<Grass>();
			grass17->PlaceAt(4, 4, 1, 84, 5);

			grass18 = m_pScene->SpawnObject<Grass>();
			grass18->PlaceAt(4, 4, 28, 86, 4);

			grass19 = m_pScene->SpawnObject<Grass>();
			grass19->PlaceAt(4, 4, 10, 88, 3);






			statue1 = m_pScene->SpawnObject<Statue>();
			statue1->PlaceAt(4, 4, 30, 50, 6);
		
			statue2 = m_pScene->SpawnObject<Statue>();
			statue2->PlaceAt(4, 4, 17, 53, 8);

			statue3 = m_pScene->SpawnObject<Statue>();
			statue3->PlaceAt(4, 4, 16, 69, 7);

		
		



		
			break; 
		}	
		case 4:
		{
			cart1 = m_pScene->SpawnObject<Cart>();
			cart1->PlaceAt(4, 4, 48, 30, 3);

			cart2 = m_pScene->SpawnObject<Cart>();
			cart2->PlaceAt(4, 4, 60, 32, 3, false);
			cart3 = m_pScene->SpawnObject<Cart>();
			cart3->PlaceAt(4, 4, 58, 32, 4, false);
			cart4 = m_pScene->SpawnObject<Cart>();
			cart4->PlaceAt(4, 4, 55, 32, 2, false);

			cart5 = m_pScene->SpawnObject<Cart>();
			cart5->PlaceAt(4, 4, 38, 31, 4, false);

			cart6 = m_pScene->SpawnObject<Cart>();
			cart6->PlaceAt(4, 4, 71, 31, 4, false);

			cart7 = m_pScene->SpawnObject<Cart>();
			cart7->PlaceAt(4, 4, 74, 31, 4, false);


			statue1 = m_pScene->SpawnObject<Statue>();
			statue1->PlaceAt(4, 4, 126, 24, 4);

			statue2 = m_pScene->SpawnObject<Statue>();
			statue2->PlaceAt(4, 4, 116, 28, 2);

			statue3 = m_pScene->SpawnObject<Statue>();
			statue3->PlaceAt(4, 4, 79, 28, 2);

			statue4 = m_pScene->SpawnObject<Statue>();
			statue4->PlaceAt(4, 4, 43, 29, 3);


			break;
		}

		case 5:
		{
			cart1 = m_pScene->SpawnObject<Cart>();
			cart1->PlaceAt(4, 4, 81, 33, 4, false);

			cart2 = m_pScene->SpawnObject<Cart>();
			cart2->PlaceAt(4, 4, 72, 33, 2, false);

			cart3 = m_pScene->SpawnObject<Cart>();
			cart3->PlaceAt(4, 4, 13, 33, 3, false);

			grass1 = m_pScene->SpawnObject<Grass>();
			grass1->PlaceAt(4, 4, 18, 32.5f, 4);

			grass2 = m_pScene->SpawnObject<Grass>();
			grass2->PlaceAt(4, 4, 16, 32.5f, 2);

			grass3 = m_pScene->SpawnObject<Grass>();
			grass3->PlaceAt(4, 4, 7, 32.5f, 1);

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
}