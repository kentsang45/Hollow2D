#pragma once

#include "Bug.h"

class DashingBug : public Bug
{
public:
	DashingBug();
	~DashingBug();

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

	void Dash(float fTime);

	void SetCurrentState(BUG_STATE  eState);

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void ClearState();

private:
	class Sencer* m_pPlayerSencer;
	class CColliderRect* m_pSencerBody;

	// DASH
	float m_fDashTime = 0.f;
	float m_fDashTotalTime = 1.f;
	bool m_bDash = false;

	// STAND
	float m_fStandTime = 0.f;
	float m_fStandTotalTime = 1.5f;
	bool m_bStand = false;

	// WALK
	float m_fWalkTime = 0.f;
	float m_fWalkTotalTime = 3.0f;
};

