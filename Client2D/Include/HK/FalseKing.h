#pragma once

#include "Bug.h"

class FalseKing : public Bug
{
public:
	FalseKing();
	~FalseKing();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void MoveX(float fTime);
	void Reverse();
	void CheckFront();
	void MoveBack(float fTime);
	void JumpBack(float fTime);

	void JumpEnd(float fTime);


	void RealJump(float fTime);



	void SetCurrentState(BUG_STATE  eState);
	void SetAnim(BUG_STATE eState);

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void ClearState();

	void PatternA(); // 기모으기 -> 때리기
	void PatternB(); // 그냥 점프
	void PatternC(); // 점프 공격

	void PatternD(); // 기모으기 -> 쿵쾅쿵쾅

	void FindPlayer(float fTime);

	void Stand(float fTime);
	void Jump(float fTime);
	void JumpB(float fTime);
	void GetHit(float fTIme);
	void Attack(float fTime);
	void AttackB(float fTime);
	void AttackC(float fTime);

	void Land(float fTime);
	void GetUp(float fTime);

	void Die(float fTime);
	void Dead(float fTime);

	void CheckDir();
	void CheckHP();

	void SetBarrel();
	void ResetState();

private:
	class HollowKnight* m_pHK = nullptr;
	Vector3 m_vHK;

	class Sencer* m_pPlayerLeftSencer;
	class Sencer* m_pPlayerRightSencer;
	class CColliderRect* m_pSencerBody;

	float m_fTimer = 0.f;
	float m_fTimer2 = 0.f;
	float m_fTimer3 = 0.f;


	float m_fStandTime = 1.5f;
	int m_iPrep = 0; // 때리기 전에 준비 과정을 몇번 할 것이냐 // -1 이면 준비를 건너 뛴다.

	BUG_STATE m_eAnimState = (BUG_STATE)-1;

	// 플레이어와의 거리
	float m_fDis = 0.f;
	
	bool m_bFKJump = false;
	bool m_bGetHit = false;

	bool m_bEffect = false;

	bool m_iStage1 = false;
	bool m_iStage2 = false;

	bool m_bOpen = false;
	float m_fOpenTime = 0.f;
	float m_fOpenTotalTime = 7.f;

	// 누워있을때 OPEN, 그리고 맞는다.

	// 중간으로 가야할 상황이 생긴다.
	float m_fCenter = 46 * 50.f + 25.f;

	bool m_bDead = false;

	// int m_iHP = 30;

	bool m_bLowHP = false;
	bool m_bOneChange = true;

	bool m_bNoGetHit = false;
};

