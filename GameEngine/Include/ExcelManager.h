#pragma once

#include "GameEngine.h"
#include "libxl.h"

using namespace libxl;

class ENGINE_DLL CExcelManager
{
public:


	bool CreateBook();
	bool LoadMonster(const TCHAR* filename);

	void Test();
	int ReadingTest();




	DECLARE_SINGLE(CExcelManager);
};

