#pragma once

#include "Bug.h"

class ShieldBug : public Bug
{
public:
	ShieldBug();
	~ShieldBug();

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

	void AttackA(float fTime);
	void AttackB(float fTime);

	void SetCurrentState(BUG_STATE  eState);

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void ClearState();

private:
	class Sencer* m_pPlayerLeftSencer;
	class Sencer* m_pPlayerRightSencer;


	class CColliderRect* m_pSencerBody;

	// WALK
	float m_fWalkTime = 0.f;
	float m_fWalkTotalTime = 3.0f;

	// WAITING
	bool m_bWaiting = false;
	float m_fWaitingTime = 0.f;
	float m_fWaitingTotalTime = .5f;

	// BLOCK
	bool m_bWillBlock = false;
};

