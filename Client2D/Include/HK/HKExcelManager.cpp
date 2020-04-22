#include "HKExcelManager.h"

#include "HKTileMap.h"

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


#include "Scene/Scene.h"

#include "TestStage.h"




HKExcelManager::HKExcelManager()
{
}

HKExcelManager::~HKExcelManager()
{
}

bool HKExcelManager::LoadStage(const TCHAR * path, class HKTileMap* tileMap)
{
	Book* book = xlCreateBook();

	if (book->load(path))
	{
		Sheet* sheet = book->getSheet(0);

		int totalY = sheet->lastRow();
		int totalX = sheet->lastCol();

		tileMap->SetInit(totalX, totalY);

		if (nullptr != sheet)
		{
			for (int row = 0; row < totalY; ++row)
			{
				for (int col = 0; col < totalX; ++col)
				{
					CellType cellType = sheet->cellType(row, col);

					int index = row * totalX + col;

					switch (cellType)
					{
					case CELLTYPE_EMPTY:
						break;
					case CELLTYPE_NUMBER:
					{
						int num = sheet->readNum(row, col);

						if (1 == num)
						{
							tileMap->CreateOneTile(col, row, 50.f, 50.f, index);
						}
						else
						{
							int a = 0;
						}

						break;
					}
					case CELLTYPE_STRING:
					{
						BOOM;
						break;
					}
					case CELLTYPE_BOOLEAN:
					{
						BOOM;
						break;
					}
					case CELLTYPE_BLANK:

					case CELLTYPE_ERROR:
					{
						BOOM;
						break;
					}
					}
				}			
			}
		}
	}
	else
	{
		BOOM
	}

	book->release();

	return true;
}

bool HKExcelManager::LoadStage(const TCHAR * path, class CScene* pScene)
{
	Book* book = xlCreateBook();

	if (book->load(path))
	{
		Sheet* sheet = book->getSheet(0);

		int totalY = sheet->lastRow();
		int totalX = sheet->lastCol();

		if (nullptr != sheet)
		{
			for (int row = 0; row < totalY; ++row) // Y
			{
				int num1 = sheet->readNum(row, 0); // sizeX
				int num2 = sheet->readNum(row, 1); // sizeY
				int num3 = sheet->readNum(row, 2); // LTX
				int num4 = sheet->readNum(row, 3); // LTY

				TestStage* stage = pScene->SpawnObject<TestStage>();
				stage->PlaceAt(num1, num2, num3, num4);
				SAFE_RELEASE(stage);			
			}
		}
	}
	else
	{
		BOOM
	}

	book->release();

	return true;
}
