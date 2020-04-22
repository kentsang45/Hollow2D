#pragma once



#include "Scene/GameMode.h"

class HKMode : public CGameMode
{
public:
	HKMode();
	~HKMode();

	virtual bool Init();

private:
	bool CreateMaterial();
	bool CreateAnimation2DSequence();
	void MakePlayerAnimation(const std::string& strName, int iFrameCount, int iFrameSecond, const std::string& strFileName);


	void SetCollision();



	// HOLLOW KNIGHT
	void SetHK();
	void SetBug();
	void SetUI();
	void SetTileMap();
	
	// 배경을 위치 시킨다.
	void SetStage(int stageNumber);

	// 몬스터들을 위치 시킨다.
	void PlaceMonster(int stageNumber);

	void SetObject(int stageNumber);
};

