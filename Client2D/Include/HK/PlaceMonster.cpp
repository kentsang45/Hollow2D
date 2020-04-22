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
	DashingBug* db1 = nullptr;
	SmallBug* smb1 = nullptr;


	switch (stageNumber)
	{
	case 1:
		// db1 = m_pScene->SpawnObject<DashingBug>();
		// 원래 자리 db1->PlaceAt(109, 26);
		// db1->PlaceAt(69, 18);


		smb1 = m_pScene->SpawnObject<SmallBug>();
		smb1->PlaceAt(10, 18);


		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;

	case 5:
		break;

	default :
		BOOM;
		break;
	}

	SAFE_RELEASE(db1);
	SAFE_RELEASE(smb1);



	return;
}