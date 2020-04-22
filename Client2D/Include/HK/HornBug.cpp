#include "HornBug.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Component/ColliderRect.h"
#include "Component/ColliderOBB2D.h"

#include "Sencer.h"

HornBug::HornBug()
{
}


HornBug::~HornBug()
{
	SAFE_RELEASE(m_pPlayerLeftSencer);
	SAFE_RELEASE(m_pPlayerRightSencer);

}

bool HornBug::Init()
{
	if (false == Bug::Init())
	{
		BOOM
		return false;
	}

	Bug::SetAnimation("HB");
	m_pMesh->SetPivot(0.5f, 0.48f, 0.f);

	// 플레이어 찾기위한 센서
	m_pPlayerLeftSencer = m_pScene->SpawnObject<Sencer>();
	m_pSencerBody = m_pPlayerLeftSencer->GetBody();
	m_pMesh->AddChild(m_pSencerBody, TR_POS);
	SAFE_RELEASE(m_pSencerBody);


	m_pPlayerRightSencer = m_pScene->SpawnObject<Sencer>();
	m_pSencerBody = m_pPlayerRightSencer->GetBody();

	m_pMesh->AddChild(m_pSencerBody, TR_POS);
	SAFE_RELEASE(m_pSencerBody);

	m_fMoveSpeed = 100.f;

	m_pPlayerLeftSencer->SetRelativePos(-300.f, 0.f, 0.f);
	m_pPlayerRightSencer->SetRelativePos(300.f, 0.f, 0.f);


	m_pBody->AddBlockCallback<HornBug>(this, &HornBug::OnBlock);

	return true;
}

void HornBug::Begin()
{
	Bug::Begin();

	m_pMovement->SetMoveSpeed(m_fMoveSpeed);
}

void HornBug::Update(float fTime)
{
	Bug::Update(fTime);

	// 날아가고 있을때는 아무것도 못한다.
	if (false == m_bOnLand)
	{
		return;
	}

	// 죽음
	if (true == m_bDead)
	{
		// m_pMesh->SetPivot(0.5f, 0.54f, 0.f);
		return;
	}

	// 돌기가 끝나면
	if (BS_TURN == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_BDASH);
		m_pMovement->SetMoveSpeed(0.f);
		return;
	}

	// 대쉬!
	if (BS_BDASH == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_DASH);
		m_pMovement->SetMoveSpeed(500.f);
		return;
	}
	


	// 걷다가 또는 서있다가 플레이어를 보면
	
	if (BS_WALK == m_eState)
	{
		// 왼쪽 보고 있는데 왼쪽에 있는 경우
		if (true == m_pPlayerLeftSencer->IsPlayer() && DIR_LEFT == m_eDir)
		{
			SetCurrentState(BS_BDASH);
			m_fWalkTime = 0.f;
			m_fDashTime = 0.f;
			m_pMovement->SetMoveSpeed(0.f);
			return;
		}
		// 왼쪽 보고 있는데 오른쪽에 있는 경우
		else if (true == m_pPlayerRightSencer->IsPlayer() && DIR_LEFT == m_eDir)
		{
			SetCurrentState(BS_TURN);
			// 다음 행동 예약
			m_fWalkTime = 0.f;
			m_fDashTime = 0.f;
			m_bWillDash = true;
			Reverse();
			m_eDir = DIR_RIGHT;
			return;
		}
		// 오른쪽 보고 있는데 왼쪽에 있는 경우
		else if (true == m_pPlayerLeftSencer->IsPlayer() && DIR_RIGHT == m_eDir)
		{
			SetCurrentState(BS_TURN);
			m_fWalkTime = 0.f;
			m_fDashTime = 0.f;
			// 다음 행동 예약
			m_bWillDash = true;
			Reverse();
			m_eDir = DIR_LEFT;
			return;
		}
		// 오른쪽 보고 있는데 오른쪽에 있는 경우
		else if (true == m_pPlayerRightSencer->IsPlayer() && DIR_RIGHT == m_eDir)
		{
			SetCurrentState(BS_BDASH);
			m_fWalkTime = 0.f;
			m_fDashTime = 0.f;
			m_pMovement->SetMoveSpeed(0.f);

			return;
		}
	}
	



	// 준비동작 끝나고 달리기
	if (BS_BWALK == m_eState && m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_DASH);
		m_pMovement->SetMoveSpeed(500.f);
		return;
	}

	// 대쉬하고 있다가 돌아가기
	if (BS_DASH == m_eState)
	{
		m_fDashTime += fTime;

		SetCurrentState(BS_DASH);

		if (m_fDashTime >= m_fDashTotalTime)
		{
			m_fDashTime = 0.f;
			SetCurrentState(BS_WALK);
			m_fWalkTime = 0.f;
			return;
		}
	}

	// 걷기 돌아가기
	if (BS_WALK == m_eState)
	{
		m_fWalkTime += fTime;
		SetCurrentState(BS_WALK);
		m_pMovement->SetMoveSpeed(m_fMoveSpeed);

		// 안움직이기
		if (m_fWalkTime >= m_fWalkTotalTime)
		{
			SetCurrentState(BS_WALK);
			m_pMovement->SetMoveSpeed(0.f);
			m_fWalkTime = 0.f;
			return;
		}

		return;
	}

	// 서있다가 돌아가기
	//if (BS_STAND == m_eState)
	//{
	//	m_fStandTime += fTime;

	//	SetCurrentState(BS_STAND);
	//	// 안움직이기
	//	m_pMovement->SetMoveSpeed(0.f);

	//	if (m_fStandTime >= m_fStandTotalTime)
	//	{
	//		// 다시 움직이기
	//		m_fStandTime = 0.f;
	//		SetCurrentState(BS_WALK);
	//		m_pMovement->SetMoveSpeed(m_fMoveSpeed);
	//		return;
	//	}
	//}

	// 걷기가 끝난다면
	// if(BS_WALK == m_eSate)




}

void HornBug::Render(float fTime)
{
	Bug::Render(fTime);
}

void HornBug::MoveX(float fTime)
{
	Bug::MoveX(fTime);
}

void HornBug::Reverse()
{
	Bug::Reverse();
}

void HornBug::CheckFront()
{
	Bug::CheckFront();
}

void HornBug::MoveBack(float fTime)
{
	Bug::MoveBack(fTime);
}

void HornBug::JumpBack(float fTime)
{
	Bug::JumpBack(fTime);
}

void HornBug::JumpEnd(float fTime)
{
	Bug::JumpEnd(fTime);
}


void HornBug::Dash(float fTime)
{

}

void HornBug::SetCurrentState(BUG_STATE eState)
{
	Bug::SetCurrentState(eState);
}


void HornBug::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	Bug::OnBlock(pSrc, pDest, fTime);
}

void HornBug::ClearState()
{

}
