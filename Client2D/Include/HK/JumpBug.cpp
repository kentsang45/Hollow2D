#include "JumpBug.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Component/ColliderRect.h"
#include "Component/ColliderOBB2D.h"

#include "TimerManager.h"

#include "Sencer.h"

JumpBug::JumpBug()
{
}


JumpBug::~JumpBug()
{
	SAFE_RELEASE(m_pPlayerLeftSencer);
	SAFE_RELEASE(m_pPlayerRightSencer);

}

bool JumpBug::Init()
{
	if (false == Bug::Init())
	{
		BOOM
			return false;
	}

	Bug::SetAnimation("JB");
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

	// m_pPlayerLeftSencer->SetRelativePos(-300.f, 0.f, 0.f);
	// m_pPlayerRightSencer->SetRelativePos(300.f, 0.f, 0.f);

	m_fGravitySpeed = 16.f;

	m_bDieLand = true;

	m_pBody->AddBlockCallback<JumpBug>(this, &JumpBug::OnBlock);

	return true;
}

void JumpBug::Begin()
{
	Bug::Begin();

	m_pMovement->SetMoveSpeed(m_fMoveSpeed);

	Bug::TurnOff();
}

void JumpBug::Update(float fTime)
{
	Bug::Update(fTime);

	if (true == m_bWillJump)
	{
		int a = 0;
	}

	// DEBUG
	// char	strText[256] = {};
	// sprintf_s(strText, (m_vecStateName[m_eState] + "\n").c_str());
	// OutputDebugStringA(strText);

	// 슬로우모션 적용
	m_bSlowAdjust = GET_SINGLE(CTimerManager)->IsSlowMotion();
	if (true == m_bSlowAdjust)
	{
		if (false == m_bSlowDone)
		{
			m_fMoveSpeed *= 2.f;
			m_bSlowDone = true;
		}		
	}
	else
	{
		if (true == m_bSlowDone)
		{
			m_fMoveSpeed *= 0.5f;
			m_bSlowDone = false;
		}
	}
	

	// 죽음
	if (true == m_bDead || 0 >= m_iHP)
	{
		m_pMesh->SetPivot(0.5f, 0.54f, 0.f);
		return;
	}


	if (BS_STAND == m_eState)
	{
		if (true == m_pAnimation->IsSequenceEnd())
		{
			SetCurrentState(BS_WALK);
			return;
		}
		else
		{
			return;
		}

	}

	// 돌기가 끝나면
	if (BS_TURN == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		// 점프하기 위한 턴이 아닌 경우만
		if (false == m_bWillJump)
		{
			SetCurrentState(BS_WALK);
			m_bWillJump = false;
			return;
		}
		else
		{
			SetCurrentState(BS_BJUMP);
			RealJump(fTime);
			m_bWillJump = false;
			return;
		}

	}


	//////////////////////////////////////////////////////////////////////////////////////////

	// 점프
	if (BS_BJUMP == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_JUMP);
		return;
	}	

	// 공격후 걷기
	if (BS_ATTACK == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_STAND);
		return;
	}

	//// 날아가고 있을때는 아무것도 못한다.
	if (false == m_bOnLand || BS_ATTACK == m_eState)
	{
		return;
	}

	// 착지
	if (true == m_bIsJumping)
	{
		if (true == m_bOnLand)
		{
			m_bIsJumping = false;
			SetCurrentState(BS_ATTACK);
			m_fMoveSpeed = 100.f;
			m_pMovement->SetMoveSpeed(m_fMoveSpeed);
			m_bWillJump = false;

			return;
		}

		Bug::CheckCollision();

		m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * m_eDir);
		m_fForce -= m_fOriginForce * m_fOriginForce;
		return;
	}

	

	// 플레이어 찾기
	if (false == m_bWillJump)
	{
		Vector3 playerVec = m_pScene->GetGameMode()->GetPlayer()->GetWorldPos();
		Vector3 monsterVec = GetWorldPos();

		m_fDisX = playerVec.x - monsterVec.x;
		float disY = playerVec.y - monsterVec.y;

		// 플레이어와 몬스터의 거리가 위아래 250 사이
		if (disY <= 250.f && disY >= -250.f)
		{
			if (m_fDisX <= 400.f && m_fDisX >= -400.f)
			{
				if (m_fDisX <= 400.f && m_fDisX >= 0.f)
				{
					// 플레이어가 오른쪽
					// 근데 나는 왼쪽
					if (DIR_LEFT == m_eDir)
					{
						SetCurrentState(BS_TURN);
						Reverse();
						m_eDir = DIR_RIGHT;
						m_bWillJump = true;
						return;
					}
					// 나도 오른쪽
					else
					{
						SetCurrentState(BS_BJUMP);
						RealJump(fTime);
						return;
					}
				}
				else
				{
					// 플레이어가 왼쪽
					// 나도 왼쪽
					if (DIR_LEFT == m_eDir)
					{
						SetCurrentState(BS_BJUMP);
						RealJump(fTime);
						return;
					}
					else
					{
						SetCurrentState(BS_TURN);
						Reverse();
						m_eDir = DIR_LEFT;
						m_bWillJump = true;
						return;
					}
				}

		
			}
		}
	}
	
	

	
	








}

void JumpBug::Render(float fTime)
{
	Bug::Render(fTime);
}

void JumpBug::MoveX(float fTime)
{
	Bug::MoveX(fTime);
}

void JumpBug::Reverse()
{
	Bug::Reverse();
}

void JumpBug::CheckFront()
{
	Bug::CheckFront();
}

void JumpBug::MoveBack(float fTime)
{
	Bug::MoveBack(fTime);
}

void JumpBug::JumpBack(float fTime)
{
	Bug::JumpBack(fTime);
}

void JumpBug::JumpEnd(float fTime)
{
	Bug::JumpEnd(fTime);
}



void JumpBug::RealJump(float fTime)
{
	// parent
	m_bJumping = true;
	m_bOnLand = false;


	// JB
	m_bIsJumping = true;

	m_fForce = m_fOriginForce * 60;

	m_fMoveSpeed = m_fDisX;

	if (m_fMoveSpeed <= 0)
	{
		m_fMoveSpeed *= -1.f;
	}

	m_pMovement->SetMoveSpeed(m_fMoveSpeed);

}

void JumpBug::SetCurrentState(BUG_STATE eState)
{
	Bug::SetCurrentState(eState);
}


void JumpBug::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	Bug::OnBlock(pSrc, pDest, fTime);
}

void JumpBug::ClearState()
{

}






//// 걷다가 또는 서있다가 플레이어를 보면

//if (BS_WALK == m_eState)
//{
//	// 왼쪽 보고 있는데 왼쪽에 있는 경우
//	if (true == m_pPlayerLeftSencer->IsPlayer() && DIR_LEFT == m_eDir)
//	{
//		SetCurrentState(BS_BDASH);
//		m_fWalkTime = 0.f;
//		m_fDashTime = 0.f;
//		m_pMovement->SetMoveSpeed(0.f);
//		return;
//	}
//	// 왼쪽 보고 있는데 오른쪽에 있는 경우
//	else if (true == m_pPlayerRightSencer->IsPlayer() && DIR_LEFT == m_eDir)
//	{
//		SetCurrentState(BS_TURN);
//		// 다음 행동 예약
//		m_fWalkTime = 0.f;
//		m_fDashTime = 0.f;
//		m_bWillDash = true;
//		Reverse();
//		m_eDir = DIR_RIGHT;
//		return;
//	}
//	// 오른쪽 보고 있는데 왼쪽에 있는 경우
//	else if (true == m_pPlayerLeftSencer->IsPlayer() && DIR_RIGHT == m_eDir)
//	{
//		SetCurrentState(BS_TURN);
//		m_fWalkTime = 0.f;
//		m_fDashTime = 0.f;
//		// 다음 행동 예약
//		m_bWillDash = true;
//		Reverse();
//		m_eDir = DIR_LEFT;
//		return;
//	}
//	// 오른쪽 보고 있는데 오른쪽에 있는 경우
//	else if (true == m_pPlayerRightSencer->IsPlayer() && DIR_RIGHT == m_eDir)
//	{
//		SetCurrentState(BS_BDASH);
//		m_fWalkTime = 0.f;
//		m_fDashTime = 0.f;
//		m_pMovement->SetMoveSpeed(0.f);

//		return;
//	}
//}




//// 준비동작 끝나고 달리기
//if (BS_BWALK == m_eState && m_pAnimation->IsSequenceEnd())
//{
//	SetCurrentState(BS_DASH);
//	m_pMovement->SetMoveSpeed(500.f);
//	return;
//}

//// 대쉬하고 있다가 돌아가기
//if (BS_DASH == m_eState)
//{
//	m_fDashTime += fTime;

//	SetCurrentState(BS_DASH);

//	if (m_fDashTime >= m_fDashTotalTime)
//	{
//		m_fDashTime = 0.f;
//		SetCurrentState(BS_WALK);
//		m_fWalkTime = 0.f;
//		return;
//	}
//}

//// 걷기 돌아가기
//if (BS_WALK == m_eState)
//{
//	m_fWalkTime += fTime;
//	SetCurrentState(BS_WALK);
//	m_pMovement->SetMoveSpeed(m_fMoveSpeed);

//	// 안움직이기
//	if (m_fWalkTime >= m_fWalkTotalTime)
//	{
//		SetCurrentState(BS_WALK);
//		m_pMovement->SetMoveSpeed(0.f);
//		m_fWalkTime = 0.f;
//		return;
//	}

//	return;
//}

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