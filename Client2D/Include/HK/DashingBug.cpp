#include "DashingBug.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Component/ColliderRect.h"
#include "Component/ColliderOBB2D.h"

#include "Sencer.h"

DashingBug::DashingBug()
{
}


DashingBug::~DashingBug()
{
	SAFE_RELEASE(m_pPlayerSencer);
	// SAFE_RELEASE(m_pSencerBody);
}

bool DashingBug::Init()
{
	if (false == Bug::Init())
	{
		BOOM
		return false;
	}

	Bug::SetAnimation("DB");
	m_pMesh->SetPivot(0.5f, 0.528f, 0.f);

	// 플레이어 찾기위한 센서
	m_pPlayerSencer = m_pScene->SpawnObject<Sencer>();
	m_pSencerBody = m_pPlayerSencer->GetBody();
	m_pMesh->AddChild(m_pSencerBody, TR_POS);

	m_fMoveSpeed = 100.f;
	m_fWalkSpeed = 100.f;

	m_pBody->AddBlockCallback<DashingBug>(this, &DashingBug::OnBlock);

	return true;
}

void DashingBug::Begin()
{
	Bug::Begin();

	m_pMovement->SetMoveSpeed(m_fMoveSpeed);
}

void DashingBug::Update(float fTime)
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
		m_pMesh->SetPivot(0.5f, 0.58f, 0.f);
		return;
	}

	m_pPlayerSencer->SetRelativePos(300.f * m_eDir, 0.f, 0.f);




	// 걷다가 또는 서있다가 플레이어를 보면
	if (true == m_pPlayerSencer->IsPlayer()
		&& (BS_WALK == m_eState || BS_STAND == m_eState))
	{
		Dash(fTime);
		m_fWalkTime = 0.f;
		m_fDashTime = 0.f;
		return;
	}


	// 준비동작 끝나고 달리기
	if (BS_BWALK == m_eState && m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_DASH);
		m_pMovement->SetMoveSpeed(500.f);
		m_fMoveSpeed = 500.f;
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
			SetCurrentState(BS_STAND);
			m_fMoveSpeed = 100.f;
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
			SetCurrentState(BS_STAND);

			m_pMovement->SetMoveSpeed(0.f);
			m_fMoveSpeed = 0.f;

			m_fWalkTime = 0.f;
			return;
		}

		return;
	}

	// 서있다가 돌아가기
	if (BS_STAND == m_eState)
	{
		m_fStandTime += fTime;

		SetCurrentState(BS_STAND);
		// 안움직이기
		m_pMovement->SetMoveSpeed(0.f);

		if (m_fStandTime >= m_fStandTotalTime)
		{
			// 다시 움직이기
			m_fStandTime = 0.f;
			SetCurrentState(BS_WALK);

			m_pMovement->SetMoveSpeed(m_fWalkSpeed);
			m_fMoveSpeed = m_fWalkSpeed;

			return;
		}
	}





}

void DashingBug::Render(float fTime)
{
	Bug::Render(fTime);
}

void DashingBug::MoveX(float fTime)
{
	Bug::MoveX(fTime);
}

void DashingBug::Reverse()
{
}

void DashingBug::CheckFront()
{
	Bug::CheckFront();
}

void DashingBug::MoveBack(float fTime)
{
	Bug::MoveBack(fTime);
}

void DashingBug::JumpBack(float fTime)
{
	Bug::JumpBack(fTime);
}

void DashingBug::JumpEnd(float fTime)
{
	Bug::JumpEnd(fTime);
}


void DashingBug::Dash(float fTime)
{
	SetCurrentState(BS_BWALK);
	
	m_pMovement->SetMoveSpeed(0.f);



}

void DashingBug::SetCurrentState(BUG_STATE eState)
{
	Bug::SetCurrentState(eState);
}


void DashingBug::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	Bug::OnBlock(pSrc, pDest, fTime);
}

void DashingBug::ClearState()
{

}
