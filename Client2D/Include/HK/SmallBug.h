#pragma once

#include "Bug.h"
#include "../Client.h"

class SmallBug : public Bug
{
public:
	SmallBug();
	~SmallBug();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void MoveX(float fTime);
	void MoveY(float fTime);
	
	void Reverse();
	void CheckFront();
	void MoveBack(float fTime);
	void JumpBack(float fTime);

	void JumpEnd(float fTime);

	void Stop(float fTime);

	void Turn(float fTime);


	void SetCurrentState(BUG_STATE  eState);

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void FinishTurning();


private:
	float m_fStopTime = 0.f;
	float m_fStopMaxTime = 1.f;

	bool m_bStop = false;
	
	DIR_TYPE m_eDir;
	DIR_TYPE m_eNewDir;

	bool m_bLeftFree = false;
	bool m_bRightFree = false;

	class Sencer* m_pRTSencer;
	class Sencer* m_pLTSencer;

	bool m_bRot = false;

	bool m_bNoUp = false;
	bool m_bNoBot = false;


	bool m_bTurn = false;

	float m_fTurnTime = 0.f;
	float m_fTurnMaxTime = 1.f;

	// 역으로 도는 중
	bool m_bReverse = false;

	bool m_bTurnOver = false;
	float m_fTurnDelayTime = 0.f;
	float m_fDelayTotalTime = 0.1f;
};

