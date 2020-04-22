#include "ShieldBug.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Component/ColliderRect.h"
#include "Component/ColliderOBB2D.h"

#include "BlockHitEffect.h"
#include "BlockHitB.h"


#include "Sencer.h"

#include "../RandomNumber.h"



ShieldBug::ShieldBug()
{
}


ShieldBug::~ShieldBug()
{
	SAFE_RELEASE(m_pPlayerLeftSencer);
	SAFE_RELEASE(m_pPlayerRightSencer);

}

bool ShieldBug::Init()
{
	if (false == Bug::Init())
	{
		BOOM
			return false;
	}

	Bug::SetAnimation("SB");
	m_pMesh->SetPivot(0.5f, 0.52f, 0.f);

	// 플레이어 찾기위한 센서
	m_pPlayerLeftSencer = m_pScene->SpawnObject<Sencer>();
	m_pSencerBody = m_pPlayerLeftSencer->GetBody();
	m_pMesh->AddChild(m_pSencerBody, TR_POS);
	SAFE_RELEASE(m_pSencerBody);


	m_pPlayerRightSencer = m_pScene->SpawnObject<Sencer>();
	m_pSencerBody = m_pPlayerRightSencer->GetBody();

	m_pMesh->AddChild(m_pSencerBody, TR_POS);
	SAFE_RELEASE(m_pSencerBody);

	m_fMoveSpeed = 150.f;

	m_pMesh->SetRelativeScale(600.f, 600.f, 1.f);

	m_pPlayerLeftSencer->SetRelativePos(-300.f, 0.f, 0.f);
	m_pPlayerRightSencer->SetRelativePos(300.f, 0.f, 0.f);

	m_bDieLand = true;

	m_pBody->AddBlockCallback<ShieldBug>(this, &ShieldBug::OnBlock);

	return true;
}

void ShieldBug::Begin()
{
	Bug::Begin();

	m_pMovement->SetMoveSpeed(m_fMoveSpeed);

	// Bug::TurnOff();
}

void ShieldBug::Update(float fTime)
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

	// DEBUG
	// char	strText[256] = {};
	// sprintf_s(strText, (m_vecStateName[m_eState] + "\n").c_str());
	// OutputDebugStringA(strText);


	if (false == m_bChildUpdate)
	{
		return;
	}



	// 돌기가 끝나면
	if (BS_TURN == m_eState && true == m_pAnimation->IsSequenceEnd())
	{

		// 점프하기 위한 턴이 아닌 경우만
		if (false == m_bWillBlock)
		{
			SetCurrentState(BS_WALK);
			m_bWillBlock = false;
			return;
		}
		else
		{
			SetCurrentState(BS_BLOCK);
			m_bBlocking = true;
			m_pBody->SetBlock(true);
			m_bWillBlock= false;
			return;
		}


		return;
	}


	///////////////////////////////////////////////////////////////
	// 기다려
	if (true == m_bWaiting)
	{
		m_fWaitingTime += fTime;

		if (m_fWaitingTime >= m_fWaitingTotalTime)
		{
			m_fWaitingTime = 0.f;
			m_bWaiting = false;
		}
		else
		{
			m_pMovement->SetMoveSpeed(0.f);
			m_fMoveSpeed = 0.f;
			return;
		}
	}


	// 준비동작 끝나고 달리기
	if (BS_BLOCK == m_eState && m_pAnimation->IsSequenceEnd())
	{
		m_bBlocking = false;
		m_pBody->SetBlock(false);
		int ran = RandomNumber::GetRandomNumber(0, 2);
		m_pMovement->SetMoveSpeed(600.f);
		m_fMoveSpeed = 600.f;
		if (0 == ran)
		{
			SetCurrentState(BS_ATTACKB);	
			return;
		}
		else
		{
			SetCurrentState(BS_ATTACKA);
			return;
		}
		/*SetCurrentState(BS_ATTACKB);
		m_pMovement->SetMoveSpeed(600.f);
		m_fMoveSpeed = 600.f;*/

		return;
	}

	// 공격하고 있다가 돌아가기
	if (BS_ATTACKA == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_AATTACK);
		return;
	}
	// 공격하고 있다가 돌아가기
	if (BS_ATTACKB == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_WAIT);
		m_pMovement->SetMoveSpeed(0.f);
		m_fMoveSpeed = 0.f;

		return;
	}
	// 공격하고 있다가 돌아가기
	if (BS_ATTACKC == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_AATTACK);

		return;
	}
	// 제자리
	if (BS_AATTACK == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_STAND);

		return;
	}
	// B -> C 어택
	if (BS_WAIT == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_ATTACKC);
		m_pMovement->SetMoveSpeed(600.f);
		m_fMoveSpeed = 600.f;
		return;
	}
	// 막기
	if (BS_WAIT == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_ATTACKC);
		m_pMovement->SetMoveSpeed(600.f);
		m_fMoveSpeed = 600.f;
		return;
	}

	// 막은 상태에서 맞았을때 
	if (BS_BLOCKHIT == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(BS_BATTACK);
		m_pMovement->SetMoveSpeed(0.f);
		m_fMoveSpeed = 0.f;
		return;
	}

	if (BS_BATTACK == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		m_bBlocking = false;
		m_pBody->SetBlock(false);
		int ran = RandomNumber::GetRandomNumber(0, 2);
		m_pMovement->SetMoveSpeed(600.f);
		m_fMoveSpeed = 600.f;
		if (0 == ran)
		{
			SetCurrentState(BS_ATTACKB);
			return;
		}
		else
		{
			SetCurrentState(BS_ATTACKA);
			return;
		}

		return;
	}



	// 걷다가 또는 서있다가 플레이어를 보면

	if (BS_WALK == m_eState)
	{
		// 왼쪽 보고 있는데 왼쪽에 있는 경우
		if (true == m_pPlayerLeftSencer->IsPlayer() && DIR_LEFT == m_eDir)
		{
			SetCurrentState(BS_BLOCK);
			m_fMoveSpeed = 0.f;
			m_pMovement->SetMoveSpeed(0.f);
			m_bBlocking = true;
			m_pBody->SetBlock(true);
			return;
		}
		// 왼쪽 보고 있는데 오른쪽에 있는 경우
		else if (true == m_pPlayerRightSencer->IsPlayer() && DIR_LEFT == m_eDir)
		{
			SetCurrentState(BS_TURN);
			m_bWillBlock = true;
			Reverse();
			m_eDir = DIR_RIGHT;
			return;
		}
		// 오른쪽 보고 있는데 왼쪽에 있는 경우
		else if (true == m_pPlayerLeftSencer->IsPlayer() && DIR_RIGHT == m_eDir)
		{
			SetCurrentState(BS_TURN);
			m_bWillBlock = true;
			Reverse();
			m_eDir = DIR_LEFT;
			return;
		}
		// 오른쪽 보고 있는데 오른쪽에 있는 경우
		else if (true == m_pPlayerRightSencer->IsPlayer() && DIR_RIGHT == m_eDir)
		{
			SetCurrentState(BS_BLOCK);
			m_fMoveSpeed = 0.f;
			m_pMovement->SetMoveSpeed(0.f);
			m_bBlocking = true;
			m_pBody->SetBlock(true);
			return;
		}
	}




	// 걷기 돌아가기
	if (BS_STAND == m_eState)
	{
		SetCurrentState(BS_WALK);
		m_fMoveSpeed = 150.f;
		m_pMovement->SetMoveSpeed(m_fMoveSpeed);

		return;
	}




}

void ShieldBug::Render(float fTime)
{
	Bug::Render(fTime);
}

void ShieldBug::MoveX(float fTime)
{
	Bug::MoveX(fTime);
}

void ShieldBug::Reverse()
{
	Bug::Reverse();
}

void ShieldBug::CheckFront()
{
	Bug::CheckFront();
}

void ShieldBug::MoveBack(float fTime)
{
	Bug::MoveBack(fTime);
}

void ShieldBug::JumpBack(float fTime)
{
	Bug::JumpBack(fTime);
}

void ShieldBug::JumpEnd(float fTime)
{
	Bug::JumpEnd(fTime);
}

void ShieldBug::AttackA(float fTime)
{

}

void ShieldBug::AttackB(float fTime)
{

}




void ShieldBug::SetCurrentState(BUG_STATE eState)
{
	Bug::SetCurrentState(eState);
}


void ShieldBug::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (true == m_bBlocking)
	{
		if (nullptr == pDest)
		{
			return;
		}

		if ("PlayerProjectile" == pDest->GetCollisionProfile()->strName)
		{
			BlockHitEffect* effect = m_pScene->SpawnObject<BlockHitEffect>(Vector3(pSrc->GetIntersect().x, pSrc->GetIntersect().y, 0.f));
			BlockHitB* effect2 = m_pScene->SpawnObject<BlockHitB>(Vector3(pSrc->GetIntersect().x, pSrc->GetIntersect().y, 0.f));

			effect->Flip(m_eDir);

			SAFE_RELEASE(effect); 
			SAFE_RELEASE(effect2);

			SetCurrentState(BS_BLOCKHIT);
		}
		
	}
	else
	{
		Bug::OnBlock(pSrc, pDest, fTime);
	}

}

void ShieldBug::ClearState()
{

}
