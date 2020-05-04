#include "Bug.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Component/ColliderRect.h"
#include "Component/ColliderOBB2D.h"

#include "Sencer.h"

#include "MonsterHitEffect.h"
#include "HollowKnight.h"

#include "../RandomNumber.h"

#include "Coin.h"
#include "HitOrange.h"
#include "BloodDust.h"
#include "Blob.h"

#include "EffectSound.h"

Bug::Bug()
	: m_eDir(DIR_LEFT)
	, m_eMoveBackDir(DIR_LEFT)
	, m_pRightSencer(nullptr)
	, m_pLeftSencer(nullptr)
	, m_bMoveBack(false)
	, m_fMoveBackTime(0.f)
	, m_fMoveBackTimeMax(0.1f)
	, m_iHP(3)
	, m_fWalkSpeed(300.f)
{
	m_eState = (BUG_STATE)4;
	m_fCurrentForce = 300.f;
	m_fMoveSpeed = 300.f;
	m_bJumping = false;
}

Bug::~Bug()
{
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pAnimation);

	SAFE_RELEASE(m_pRightSencer);
	SAFE_RELEASE(m_pLeftSencer);
}

bool Bug::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pBody = CGameObject::CreateComponent<CColliderRect>("BugBody");
	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pBody, TR_POS | TR_ROT);

	m_pHK = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();





	m_pMesh->SetAnimation2D(m_pAnimation);



	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);


	m_pMovement->SetMoveSpeed(m_fMoveSpeed);


	/////////////////////////////

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BugMaterial");
	m_pMesh->SetMaterial(pMaterial);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(400.f, 400.f, 1.f);


	m_pBody->SetExtent(150.f, 150.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);



	m_pBody->SetCollisionProfile("Monster");

	// 중력 적용
	CGameObject::SetPhysics(true);

	// 센서 장착
	// RIGHT
	m_pRightSencer = m_pScene->SpawnObject<Sencer>();
	m_pRightSencer->SetStyle(2);
	CColliderRect* pSencerBody = m_pRightSencer->GetBody();
	m_pMesh->AddChild(pSencerBody, TR_POS);

	pSencerBody->SetRelativePos((m_pBody->GetExtent().x * 0.5f + 1), -(m_pBody->GetExtent().y * 0.5f + 1), 0.f);

	// LEFT
	m_pLeftSencer = m_pScene->SpawnObject<Sencer>();
	m_pLeftSencer->SetStyle(1);
	pSencerBody = m_pLeftSencer->GetBody();
	m_pMesh->AddChild(pSencerBody, TR_POS);

	pSencerBody->SetRelativePos(-(m_pBody->GetExtent().x * 0.5f + 1), -(m_pBody->GetExtent().y * 0.5f + 1), 0.f);

	m_pBody->SetMonster(true);







	SetForce(m_fCurrentForce);

	return true;
}

void Bug::Begin()
{
	CGameObject::Begin();
}

void Bug::Update(float fTime)
{
	if (m_pHK->GetStageNumber() != m_iStageNumber)
	{
		return;
	}

	if (m_fWait <= 3.f)
	{
		m_fWait += fTime;
		return;
	}

	CGameObject::Update(fTime);



	// char	strText[256] = {};
	// sprintf_s(strText, "LEFT = %d, RIGHT = %d\n", m_pLeftSencer->IsOverlap(), m_pRightSencer->IsOverlap());
	// OutputDebugStringA(strText);

	if (false == m_bParentUpdate)
	{
		return;
	}

	if (true == m_bOnLand)
	{
		ClearGravity();
	}
	else
	{

	}

	bool anim = m_pAnimation->IsSequenceEnd();

	if (true == m_bDead)
	{
		return;
	}


	if (BS_DEAD == m_eState && true == anim)
	{
		m_bDead = true;

		return;
	}

	////////////////////////////////////////////////////


	if (BS_TURN == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		// Reverse();
		m_bChildUpdate = true;

		SetCurrentState(BS_WALK);

		return;
	}

	



	if (true == m_bJump)
	{
		if (false == m_bOnLand)
		{
			bool leftFree = m_pLeftSencer->IsOverlap();
			bool rightFree = m_pRightSencer->IsOverlap();

			// 점프중에 바닥에
			if (false == leftFree && false == rightFree)
			{
				if (DIR_LEFT == m_eDir)
				{
					// 왼쪽으로 가고 있는데 왼쪽 센서가...
					if (true == leftFree || true == m_bNoLeft)
					{
						// Reverse();
						m_eDir = DIR_RIGHT;
						m_eMoveBackDir = DIR_RIGHT;
						m_bNoLeft = false;
						m_pLeftSencer->ClearOverlap();
						m_pRightSencer->ClearOverlap();

						
					}
				}
				else if (DIR_RIGHT == m_eDir)
				{
					// 오른쪽으로 가고 있는데 왼쪽 센서가...
					if (true == rightFree || true == m_bNoRight)
					{
						// Reverse();
						m_eDir = DIR_LEFT;
						m_eMoveBackDir = DIR_LEFT;
						m_bNoRight = false;
						m_pLeftSencer->ClearOverlap();
						m_pRightSencer->ClearOverlap();

					}
				}
			}
			// 점프중인데 오른쪽이 걸렸다.
			else if (true == leftFree && false == rightFree)
			{
				if (true == m_bNoRight)
				{
					// Reverse();
					m_eDir = DIR_LEFT;
					m_eMoveBackDir = DIR_LEFT;
					m_bNoRight = false;
					m_pLeftSencer->ClearOverlap();
					m_pRightSencer->ClearOverlap();

				}
			}
			else if (false == leftFree && true == rightFree)
			{
				if (true == m_bNoLeft)
				{
					// Reverse();
					m_eDir = DIR_RIGHT;
					m_eMoveBackDir = DIR_RIGHT;
					m_bNoLeft = false;
					m_pLeftSencer->ClearOverlap();
					m_pRightSencer->ClearOverlap();
				}
				else if (true == m_bNoRight)
				{
					// Reverse();
					m_eDir = DIR_LEFT;
					m_eMoveBackDir = DIR_LEFT;
					m_bNoRight = false;
					m_pLeftSencer->ClearOverlap();
					m_pRightSencer->ClearOverlap();
				}

			}			
		}

		JumpBack(fTime);
	}
	else if (BS_DEAD != m_eState)
	{
		if (true == m_bOnLand && false == m_bLandPhysics)
		{
			CheckFront();
		}
		else
		{
			// CheckCollision();
		}

		MoveBack(fTime);
	}


		// m_pMovement->AddRotationZ(180.f * fTime * rotationNumber);
	
}

void Bug::Render(float fTime)
{
	if (m_pHK->GetStageNumber() == m_iStageNumber)
	{
		CGameObject::Render(fTime);
	}

}

void Bug::MoveX(float fTime)
{
	/*switch (m_eDir)
	{
	case DIR_LEFT:
		Flip(1);
		break;
	case DIR_RIGHT:
		Flip(0);
		break;
	default:
		break;
	}*/


	Flip(m_eDir);

	if (true == m_bNoLeft && DIR_LEFT == m_eDir)
	{
		return;
	}
	else if (true == m_bNoRight && DIR_RIGHT == m_eDir)
	{
		return;
	}

	m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * m_eDir);
}

void Bug::Reverse()
{

	Flip(m_eDir);

}

// false면 REVERSE해야한다.
void Bug::CheckFront()
{
	if (DIR_LEFT == m_eDir)
	{
		// 왼쪽으로 가고 있는데 왼쪽 센서가...
		if (true == m_pLeftSencer->IsOverlap())
		{
			SetCurrentState(BS_TURN);
			m_eDir = DIR_RIGHT;
			m_bNoLeft = false;
			m_pLeftSencer->ClearOverlap();
			m_pRightSencer->ClearOverlap();
			m_bChildUpdate = false;
			return;
		}
	}

	if (DIR_RIGHT == m_eDir)
	{
		// 오른쪽으로 가고 있는데 왼쪽 센서가...
		if (true == m_pRightSencer->IsOverlap())
		{
			SetCurrentState(BS_TURN);
			m_eDir = DIR_LEFT;
			m_bNoRight = false;
			m_pLeftSencer->ClearOverlap();
			m_pRightSencer->ClearOverlap();
			m_bChildUpdate = false;
			return;
		}
	}

	CheckCollision();

	return;
}

// false면 REVERSE해야한다.
void Bug::CheckCollision()
{
	if (DIR_LEFT == m_eDir)
	{
		// 왼쪽으로 가고 있는데 왼쪽 센서가...
		if (true == m_bNoLeft)
		{
			SetCurrentState(BS_TURN);
			m_eDir = DIR_RIGHT;
			m_bNoLeft = false;
			m_pLeftSencer->ClearOverlap();
			m_pRightSencer->ClearOverlap();
			m_pMovement->SetMoveSpeed(0.f);
			m_bChildUpdate = false;
			return;
		}
	}

	if (DIR_RIGHT == m_eDir)
	{
		// 오른쪽으로 가고 있는데 왼쪽 센서가...
		if (true == m_bNoRight)
		{
			SetCurrentState(BS_TURN);
			m_eDir = DIR_LEFT;
			m_bNoRight = false;
			m_pLeftSencer->ClearOverlap();
			m_pRightSencer->ClearOverlap();
			m_pMovement->SetMoveSpeed(0.f);
			m_bChildUpdate = false;
			return;
		}
	}

	m_pMovement->SetMoveSpeed(m_fMoveSpeed);

	return;
}

void Bug::MoveBack(float fTime)
{
	if (true == m_bNoMoveBack)
	{
		return;
	}

	if (true == m_bMoveBack)
	{
		m_fMoveBackTime += fTime;

		m_pMovement->SetMoveSpeed(1500.f);
		m_fMoveSpeed = 1500.f;

		if (true == m_bNoRight && DIR_RIGHT == m_eMoveBackDir)
		{

		}
		else if (true == m_bNoLeft && DIR_LEFT == m_eMoveBackDir)
		{

		}
		else
		{
			m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * m_eMoveBackDir);
		}

		

		if (m_fMoveBackTime >= m_fMoveBackTimeMax)
		{
			m_pMovement->SetMoveSpeed(m_fWalkSpeed);
			m_fMoveSpeed = m_fWalkSpeed;

			m_bMoveBack = false;
			m_fMoveBackTime = 0.f;
			m_bMoveBackOver = true;
		}
	}
	else
	{
		MoveX(fTime);
	}
}

void Bug::JumpBack(float fTime)
{
	if (false == m_bJumping)
	{
		m_pMovement->SetMoveSpeed(m_fMoveSpeed);

		// 죽을때 항상 일정하게 날아간다.
		ClearGravity();
		m_fGravitySpeed = 10.f;


		m_fForce = m_fCurrentForce;
		
	

		// 큰 먼지 생성
		// DustEffect* dust = m_pScene->SpawnObject<DustEffect>(
		//	GetWorldPos() - Vector3(0.f, 400.f * 0.2f, 0.f));
		// dust->SetStaticSize(200.f);
		// SAFE_RELEASE(dust);
		m_bJumping = true;

		m_bOnLand = false;
	}

	m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * m_eMoveBackDir);
}

void Bug::JumpEnd(float fTime)
{
	m_fForce = 0.f;
}







void Bug::SetCurrentState(BUG_STATE eState)
{
	if (eState == m_eState)
	{
		return;
	}

	m_eState = eState;



	std::string stateName = m_strAniName;
	stateName.append("_");
	stateName.append(m_vecStateName[eState]);

	m_pAnimation->ChangeAnimation(stateName);
}

void Bug::SetAnimation(const string& strAniName)
{
	//m_strAniName = strAniName;
	//m_strAniName.append("_WALK");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_TURN");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_DIE");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_DEAD");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_DASH");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_BWALK");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_STAND");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_BDASH");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_BDIE");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_BJUMP");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_JUMP");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_DIELAND");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);
	//m_strAniName.clear();
	//m_strAniName = strAniName;
	//m_strAniName.append("_ATTACK");
	//m_pAnimation->AddAnimation2DSequence(m_strAniName);



	m_vecStateName.push_back("WALK");
	m_vecStateName.push_back("TURN");
	m_vecStateName.push_back("DIE");
	m_vecStateName.push_back("DEAD");
	m_vecStateName.push_back("DASH");
	m_vecStateName.push_back("BWALK");
	m_vecStateName.push_back("STAND");

	m_vecStateName.push_back("BDASH");
	m_vecStateName.push_back("BDIE");

	m_vecStateName.push_back("BJUMP");
	m_vecStateName.push_back("JUMP");

	m_vecStateName.push_back("JUMPB");
	m_vecStateName.push_back("LAND");

	m_vecStateName.push_back("DIELAND");
	m_vecStateName.push_back("ATTACK");


	m_vecStateName.push_back("ATTACKA");
	m_vecStateName.push_back("ATTACKB");
	m_vecStateName.push_back("ATTACKC");

	m_vecStateName.push_back("WAIT");

	m_vecStateName.push_back("AATTACK"); // After Attack
	m_vecStateName.push_back("BATTACK"); // Before Attack
	m_vecStateName.push_back("BLOCK");
	m_vecStateName.push_back("BLOCKHIT");
	m_vecStateName.push_back("GETHIT");
	m_vecStateName.push_back("GETHIT_LAND");
	m_vecStateName.push_back("GETHIT_IDLE");
	m_vecStateName.push_back("GETUP");

	m_vecStateName.push_back("DAMAGED");
	m_vecStateName.push_back("OPEN");
	m_vecStateName.push_back("LAID");

	for (int i = 0; i < (int)BS_OVER; ++i)
	{
		m_strAniName.clear();
		m_strAniName = strAniName;
		m_strAniName.append("_");
		m_strAniName.append(m_vecStateName[i]);
		m_pAnimation->AddAnimation2DSequence(m_strAniName);
	}

	m_strAniName.clear();
	m_strAniName = strAniName;

	SetCurrentState(BS_WALK);
}




void Bug::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	int a = 0;

	if (nullptr == pDest)
	{
		return;
	}

	if ("PlayerProjectile" == pDest->GetCollisionProfile()->strName)
	{
		if (true == m_bDead)
		{
			return;
		}
		
		GetHitSound();

		MonsterHitEffect* attack = m_pScene->SpawnObject<MonsterHitEffect>(GetWorldPos());
		SAFE_RELEASE(attack);

		

		HollowKnight* player = (HollowKnight*)(m_pScene->GetGameMode()->GetPlayer());
		m_eMoveBackDir = player->GetDirection();

		for (size_t i = 0; i < 6; ++i)
		{
			int x = RandomNumber::GetRandomNumber(1, 200) - 100;
			int y = RandomNumber::GetRandomNumber(1, 200) - 100;

			BloodDust* bd = m_pScene->SpawnObject<BloodDust>(GetWorldPos() + Vector3((float)x, (float)y, 0.f));
			bd->SetNormalMonster();
			bd->SetDir(m_eMoveBackDir);
			SAFE_RELEASE(bd);
		}

		for (size_t i = 0; i < 6; ++i)
		{
			int x = RandomNumber::GetRandomNumber(1, 200) - 100;
			int y = RandomNumber::GetRandomNumber(1, 200) - 100;

			Blob* bd = m_pScene->SpawnObject<Blob>(GetWorldPos() + Vector3((float)x, (float)y, 0.f));
			bd->SetNormalMonster();
			// 0보다 작으면 반대로 날아간다.

			bd->SetDir(m_eMoveBackDir);
			
			SAFE_RELEASE(bd);
		}


		m_iHP -= 1;

	

		if (0 >= m_iHP)
		{
			DeathSound();

			HitOrange* ho1 = m_pScene->SpawnObject<HitOrange>(pDest->GetIntersect());
			ho1->SetBinding();
			SAFE_RELEASE(ho1);

			m_bJump = true;
			m_fMoveBackTimeMax = 0.2f;
			m_fMoveSpeed = 300.f;
			m_pMovement->SetMoveSpeed(m_fMoveSpeed);
			m_bLandPhysics = true;
			m_bJumping = false;
			SetCurrentState(BS_DIE);

			m_pBody->SetMonster(false);

			// m_pRightSencer->Kill();
			// m_pLeftSencer->Kill();

			// 동전이 나온다.

			HitOrange* ho = m_pScene->SpawnObject<HitOrange>(pDest->GetIntersect());
			SAFE_RELEASE(ho);

			int count = RandomNumber::GetRandomNumber(1, 3);

			for (size_t i = 0; i < count; ++i)
			{
				Coin* coin = m_pScene->SpawnObject<Coin>(GetWorldPos());
				SAFE_RELEASE(coin);
			}		

			return;
		}
		else
		{
			m_bMoveBack = true;

			HitOrange* ho = m_pScene->SpawnObject<HitOrange>(pDest->GetIntersect());
			SAFE_RELEASE(ho);

			BloodDust* bd = m_pScene->SpawnObject<BloodDust>(GetWorldPos());
			bd->SetNormalMonster();
			SAFE_RELEASE(bd);
		}
	}


	if (true == pDest->IsStage())
	{
		int playerPos = (int)pSrc->GetIntersect().z;

		switch (playerPos)
		{
		case 1: // LEFT
			m_pMovement->AddMovement(Vector3(pSrc->GetIntersect().x * -2.f, 0.f, 0.f));
			m_bNoRight = true;
			// m_bOnLand = false;
			break;
		case 2: // TOP
			m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * 2.f, 0.f));
			ClearGravity();
			JumpEnd(fTime);
			m_bOnLand = true;
			m_bNoRight = false;
			m_bNoLeft = false;
			m_pLeftSencer->ClearOverlap();
			m_pRightSencer->ClearOverlap();

			break;
		case 3: // RIGHT
			m_pMovement->AddMovement(Vector3(pSrc->GetIntersect().x * 2.f, 0.f, 0.f));
			m_bNoLeft = true;
			// m_bOnLand = false;
			break;
		case 4: // BOTTOM
			m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * -2.f, 0.f));
			// m_bOnLand = false;
			// m_bCeiling = true;
			break;
		default:
			BOOM
				break;
		}

		// 바운스
		if (true == m_bJump && true == m_bOnLand)
		{
			m_fCurrentForce = m_fCurrentForce * 0.33;
			m_fMoveSpeed = m_fMoveSpeed * 0.33;

			if (m_fCurrentForce <= 10.f)
			{
				SetCurrentState(BS_DEAD);
				m_bJump = false;
				m_bMoveBack = false;
				m_pBody->SetCollisionProfile("Object");
			}
			// 다시 한번 튕김
			else
			{
				ClearGravity();
				// m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * 2.f, 0.f));

				float y = pDest->GetColliderSectionMax().y + pSrc->GetRelativeScale().y * 0.5f + 5.f;

				SetWorldPos(Vector3(GetWorldPos().x, y, GetWorldPos().z));

				SetForce(m_fCurrentForce);
				m_bJump = true;
				m_bJumping = false;

				if (true == m_bDieLand)
				{
					SetCurrentState(BS_DIELAND);
				}

				return;
			}


		}

		ClearGravity();
		JumpEnd(fTime);


		// m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * 2.f, 0.f));

		return;
	}
}

void Bug::PlaceAt(int leftTopX, int leftTopY)
{
	

	// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
	float X = (m_iStageNumber - 1) * 10000.f + (3 * 50.f) * 0.5f + leftTopX * 50.f;
	float Y = (3 * 50.f) * 0.5f + leftTopY * 50.f;
	
	// m_pMesh->SetRelativePos(X, -Y + 10.f, 0.f);
	SetRelativePos(X, -Y + 10.f, 0.f);

}

void Bug::GetHitSound()
{
	EffectSound*	pFireSound = m_pScene->SpawnObject<EffectSound>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		Vector3(0.f, 0.f, GetRelativeRot().z));

	
		m_strSoundName = "enemy_damage";
		m_strSoundFileName = m_strSoundName;
		m_strSoundFileName.append(".wav");
	

	pFireSound->SetSound(m_strSoundName, m_strSoundFileName.c_str());

	SAFE_RELEASE(pFireSound);
}

void Bug::DeathSound()
{
	EffectSound*	pFireSound = m_pScene->SpawnObject<EffectSound>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		Vector3(0.f, 0.f, GetRelativeRot().z));


	m_strSoundName = "enemy_death";
	m_strSoundFileName = m_strSoundName;
	m_strSoundFileName.append(".wav");


	pFireSound->SetSound(m_strSoundName, m_strSoundFileName.c_str());

	SAFE_RELEASE(pFireSound);
}



