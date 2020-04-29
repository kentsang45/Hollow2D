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
#include "SmallBug.h"
#include "FlyingBug.h"

#include "FalseKing.h"

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


void HKMode::PlaceMonster(int stageNumber)
{
	bool setMonster = true;

	if (true == setMonster)
	{
		DashingBug* db1 = nullptr;
		DashingBug* db2 = nullptr;
		
		JustBug* jb1 = nullptr;

		SmallBug* smb1 = nullptr;
		SmallBug* smb2 = nullptr;

		HornBug* hb1 = nullptr;

		FlyingBug* fb1 = nullptr;
		FlyingBug* fb2 = nullptr;
		FlyingBug* fb3 = nullptr;
		FlyingBug* fb4 = nullptr;



		JumpBug* jump1 = nullptr;

		ShieldBug* shield1 = nullptr;
		ShieldBug* shield2 = nullptr;

		FalseKing* fk = nullptr;

		switch (stageNumber)
		{
		case 1:
			jb1 = m_pScene->SpawnObject<JustBug>();
			jb1->PlaceAt(13, 27);

			smb1 = m_pScene->SpawnObject<SmallBug>();
			smb1->PlaceAt(10, 18);

			smb2 = m_pScene->SpawnObject<SmallBug>();
			smb2->PlaceAt(100, 17);

			db1 = m_pScene->SpawnObject<DashingBug>();
			db1->PlaceAt(55, 29);

			db2 = m_pScene->SpawnObject<DashingBug>();
			db2->PlaceAt(102, 26);
			break;

		case 2:
			hb1 = m_pScene->SpawnObject<HornBug>();
			hb1->PlaceAt(19, 21);

			fb1 = m_pScene->SpawnObject<FlyingBug>();
			fb1->PlaceAt(42, 20);

			fb2 = m_pScene->SpawnObject<FlyingBug>();
			fb2->PlaceAt(73, 11);

			fb3 = m_pScene->SpawnObject<FlyingBug>();
			fb3->PlaceAt(82, 10);

			fb4 = m_pScene->SpawnObject<FlyingBug>();
			fb4->PlaceAt(68, 23);


			break;

		case 3:
			jb1 = m_pScene->SpawnObject<JustBug>();
			jb1->PlaceAt(13, 31);

			smb1 = m_pScene->SpawnObject<SmallBug>();
			smb1->PlaceAt(16, 51);

			smb2 = m_pScene->SpawnObject<SmallBug>();
			smb2->PlaceAt(14, 79);

			fb1 = m_pScene->SpawnObject<FlyingBug>();
			fb1->PlaceAt(14, 19);

			fb2 = m_pScene->SpawnObject<FlyingBug>();
			fb2->PlaceAt(14, 71);



			break;

		case 4:


		/*	db1 = m_pScene->SpawnObject<DashingBug>();
			db1->PlaceAt(37, 14);

			db2 = m_pScene->SpawnObject<DashingBug>();
			db2->PlaceAt(39, 30);

*/

			jump1 = m_pScene->SpawnObject<JumpBug>();
			jump1->PlaceAt(28, 30);

			/*shield1 = m_pScene->SpawnObject<ShieldBug>();
			shield1->PlaceAt(16, 30);

			shield2 = m_pScene->SpawnObject<ShieldBug>();
			shield2->PlaceAt(90, 30);*/

			break;

		case 5:

			fk = m_pScene->SpawnObject<FalseKing>();
			// fk->PlaceAt(29, 24);
			fk->PlaceAt(40, 24);

			break;

		default:
			BOOM;
			break;
		}


		/*DashingBug* db1 = nullptr;
		DashingBug* db2 = nullptr;

		JustBug* jb1 = nullptr;

		SmallBug* smb1 = nullptr;
		SmallBug* smb2 = nullptr;

		HornBug* hb1 = nullptr;

		FlyingBug* fb1 = nullptr;
		FlyingBug* fb2 = nullptr;
		FlyingBug* fb3 = nullptr;
		FlyingBug* fb4 = nullptr;



		JumpBug* jump1 = nullptr;
		ShieldBug* shield1 = nullptr;
		ShieldBug* shield2 = nullptr;*/

		SAFE_RELEASE(db1);
		SAFE_RELEASE(db2);

		SAFE_RELEASE(jb1);



		SAFE_RELEASE(smb1);
		SAFE_RELEASE(smb2);

		SAFE_RELEASE(hb1);

		SAFE_RELEASE(fb1);
		SAFE_RELEASE(fb2);
		SAFE_RELEASE(fb3);
		SAFE_RELEASE(fb4);

		SAFE_RELEASE(jump1);
		SAFE_RELEASE(shield1);
		SAFE_RELEASE(shield2);

		SAFE_RELEASE(fk);
	}

	return;
}