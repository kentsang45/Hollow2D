#pragma once



#include "Scene/GameMode.h"

class HKMode : public CGameMode
{
public:
	HKMode();
	~HKMode();

	virtual bool Init();
	// 스테이지 번호, 스타트지점? 끝지점?, 현재 HP, 현재 돈

	void SetMode(int iStage, bool bStart, int iHP, int iCoin);

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
	void SetStage(int stage = 6);

	// 몬스터들을 위치 시킨다.
	void PlaceMonster();

	void SetObject();

	bool IsDebug() const { return m_bDebug; }
private:
	class HollowKnight* m_pHK = nullptr;
	bool m_bSet = false;

	int m_iCount = 0;
	int m_iStart = 0;

	bool m_bDebug = false;
};

