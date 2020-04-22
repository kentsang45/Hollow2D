#pragma once

#include "GameEngine.h"
#include "libxl.h"
#include <sstream>


using namespace libxl;


class HKExcelManager
{
public:
	HKExcelManager();
	~HKExcelManager();

	// 콜라이더 하나하나
	bool LoadStage(const TCHAR* path, class HKTileMap* tileMap);

	// 큰 콜라이더
	bool LoadStage(const TCHAR* path, class CScene* pScene);




	
};

