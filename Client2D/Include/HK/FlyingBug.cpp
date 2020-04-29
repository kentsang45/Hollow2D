#include "FlyingBug.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Component/ColliderRect.h"
#include "Component/ColliderOBB2D.h"

#include "Sencer.h"

#include "MonsterHitEffect.h"
#include "HollowKnight.h"

#include "../RandomNumber.h"

FlyingBug::FlyingBug()
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


	m_fMoveSpeed = 300.f;
	m_fCurrentForce = 300.f;

	m_bJumping = false;
}

FlyingBug::~FlyingBug()
{
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pAnimation);

	SAFE_RELEASE(m_pRightSencer);
	SAFE_RELEASE(m_pLeftSencer);
}

bool FlyingBug::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pBody = CGameObject::CreateComponent<CColliderRect>("FlyingBugBody");
	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pBody, TR_POS | TR_ROT);







	m_pMesh->SetAnimation2D(m_pAnimation);



	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);


	m_pMovement->SetMoveSpeed(m_fMoveSpeed);


	/////////////////////////////

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BugMaterial");
	m_pMesh->SetMaterial(pMaterial);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(400.f, 400.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	m_pBody->SetExtent(100.f, 100.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);



	m_pBody->SetCollisionProfile("Monster");

	
	// 센서 장착
	// RIGHT
	m_pRightSencer = m_pScene->SpawnObject<Sencer>();
	m_pRightSencer->SetCheck(2);
	CColliderRect* pSencerBody = m_pRightSencer->GetBody();
	m_pMesh->AddChild(pSencerBody, TR_POS);

	pSencerBody->SetRelativePos((m_pBody->GetExtent().x * 0.5f + 1), -(m_pBody->GetExtent().y * 0.5f + 1), 0.f);

	// LEFT
	m_pLeftSencer = m_pScene->SpawnObject<Sencer>();
	m_pLeftSencer->SetCheck(1);
	pSencerBody = m_pLeftSencer->GetBody();
	m_pMesh->AddChild(pSencerBody, TR_POS);

	pSencerBody->SetRelativePos(-(m_pBody->GetExtent().x * 0.5f + 1), -(m_pBody->GetExtent().y * 0.5f + 1), 0.f);

	m_pBody->SetMonster(true);



	m_pHK = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();


	SetAnimation("FB");
	m_bFlying = true;

	// 


	m_pBody->AddBlockCallback<FlyingBug>(this, &FlyingBug::OnBlock);

	return true;
}

void FlyingBug::Begin()
{
	CGameObject::Begin();
}

void FlyingBug::Update(float fTime)
{
	CGameObject::Update(fTime);

	// char	strText[256] = {};
	// sprintf_s(strText, "LEFT = %d, RIGHT = %d\n", m_pLeftSencer->IsOverlap(), m_pRightSencer->IsOverlap());
	// OutputDeFlyingBugStringA(strText);

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
	////////////////////////////////////////////////////
	////////////////////////////////////////////////////

	



	




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
			}
		}

		JumpBack(fTime);
	}
	else if (BS_DEAD != m_eState)
	{
		// 돌기
		if (BS_TURN == m_eState && true == m_pAnimation->IsSequenceEnd())
		{
			SetCurrentState(BS_STAND);

			return;
		}


		// 플레이어 찾음!!!
		if (true == CheckPlayer())
		{
			if (false == m_bFollowing)
			{
				m_bFollowing = true;
				SetCurrentState(BS_BWALK);
			}

			if (BS_BWALK == m_eState && true == m_pAnimation->IsSequenceEnd())
			{
				SetCurrentState(BS_WALK);
			}


			MoveBack(fTime);


			return;
		}
		// 못찾음!
		else
		{
			SetCurrentState(BS_STAND);
			m_bFollowing = false;
		}


	}


	// m_pMovement->AddRotationZ(180.f * fTime * rotationNumber);

}

void FlyingBug::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void FlyingBug::MoveX(float fTime)
{
	Flip(m_eDir);

	if (true == m_bFlyUp)
	{
		// 위로
		m_eVertical = (DIR_TYPE)1;
		
		m_fUpTime += fTime;
		
		if (m_fUpTime >= m_fUpTotalTime)
		{
			m_eVertical = (DIR_TYPE)1;
			m_fUpTime = 0.f;
			m_bFlyUp = false;
		}
	}

	else if (true == m_bFlyDown)
	{
		// 아래로
		m_eVertical = (DIR_TYPE)-1;

		m_fDownTime += fTime;

		if (m_fDownTime >= m_fDownTotalTime)
		{
			m_eVertical = (DIR_TYPE)1;
			m_fDownTime = 0.f;
			m_bFlyDown = false;
		}
	}


	if (DIR_LEFT == m_eDir)
	{
		if (true == m_bNoLeft)
		{
			if (false == m_bBounceRight)
			{
				m_bBounceRight = true;

				int temp = (RandomNumber::GetRandomNumber(1, 3));
			
				if (1 == temp)
				{
					m_bFlyDown = true;
					m_bFlyUp = false;
				}
				else if (3 == temp)
				{
					m_bFlyUp = true;
					m_bFlyDown = false;
				}				
			}
		}
	}
	else if (DIR_RIGHT == m_eDir)
	{
		if (true == m_bNoRight)
		{
			if (false == m_bBounceLeft)
			{
				m_bBounceLeft= true;

				int temp = (RandomNumber::GetRandomNumber(1, 3));

				if (1 == temp)
				{
					m_bFlyDown = true;
					m_bFlyUp = false;
				}
				else if (3 == temp)
				{
					m_bFlyUp = true;
					m_bFlyDown = false;
				}

			}
		}
	}

	if (true == m_bBounceRight)
	{
		m_fBounceTime += fTime;
		m_eDir = DIR_RIGHT;


		if (m_fBounceTime >= .5f)
		{
			m_fBounceTime = 0.f;
			m_bBounceRight = false;
			m_bNoLeft = false;
		}
	}

	else if (true == m_bBounceLeft)
	{
		m_fBounceTime += fTime;
		m_eDir = DIR_LEFT;


		if (m_fBounceTime >= .5f)
		{
			m_fBounceTime = 0.f;
			m_bBounceLeft = false;
			m_bNoRight = false;
		}
	}




	Vector3 newDir = GetWorldAxis(AXIS_X) * m_eDir + GetWorldAxis(AXIS_Y) * m_eVertical;


	m_pMovement->AddMovement(newDir);
}

void FlyingBug::Reverse()
{

	Flip(m_eDir);

}

// false면 REVERSE해야한다.
void FlyingBug::CheckFront()
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
void FlyingBug::CheckCollision()
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

void FlyingBug::MoveBack(float fTime)
{
	if (true == m_bNoMoveBack)
	{
		return;
	}

	if (true == m_bMoveBack)
	{
		m_fMoveBackTime += fTime;

		m_pMovement->SetMoveSpeed(2000.f);
		m_fMoveSpeed = 2000.f;

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
		}
	}
	else
	{
		MoveX(fTime);
	}
}

void FlyingBug::JumpBack(float fTime)
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


	if (DIR_LEFT == m_eMoveBackDir)
	{
		if (true == m_bNoLeft)
		{
			m_eMoveBackDir = DIR_RIGHT;
		}
	}
	else if (DIR_RIGHT == m_eMoveBackDir)
	{
		if (true == m_bNoRight)
		{
			m_eMoveBackDir = DIR_LEFT;
		}
	}

	m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * m_eMoveBackDir);
}

void FlyingBug::JumpEnd(float fTime)
{
	m_fForce = 0.f;
}







void FlyingBug::SetCurrentState(BUG_STATE eState)
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

void FlyingBug::SetAnimation(const string& strAniName)
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
	m_vecStateName.push_back("DIELAND");
	m_vecStateName.push_back("ATTACK");


	m_vecStateName.push_back("ATTACKA");
	m_vecStateName.push_back("ATTACKB");
	m_vecStateName.push_back("ATTACKC");

	m_vecStateName.push_back("WAIT");

	m_vecStateName.push_back("AATTACK"); // After Attack
	m_vecStateName.push_back("BTTACK"); // Before Attack
	m_vecStateName.push_back("BLOCK");
	m_vecStateName.push_back("BLOCKHIT");


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




void FlyingBug::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	int a = 0;

	if (nullptr == pDest)
	{
		return;
	}

	if ("PlayerProjectile" == pDest->GetCollisionProfile()->strName)
	{
		MonsterHitEffect* attack = m_pScene->SpawnObject<MonsterHitEffect>(GetWorldPos());

		SAFE_RELEASE(attack);

		HollowKnight* player = (HollowKnight*)(m_pScene->GetGameMode()->GetPlayer());

		m_eMoveBackDir = player->GetDirection();


		m_iHP -= 1;

		if (true == m_bDead)
		{
			return;
		}

		if (0 >= m_iHP)
		{
			SetPhysics(true);

			m_bJump = true;
			m_fMoveBackTimeMax = 0.2f;
			m_fMoveSpeed = 300.f;
			m_pMovement->SetMoveSpeed(m_fMoveSpeed);
			m_bLandPhysics = true;
			m_bJumping = false;
			SetCurrentState(BS_DIE);

			m_bFlying = false;


			m_bOnLand = false;

			m_pBody->SetMonster(false);
			return;
		}
		else
		{
			m_bMoveBack = true;
		}
	}


	if (true == pDest->IsStage())
	{
		int playerPos = (int)pSrc->GetIntersect().z;
		float y = 0.f;

		if (true == m_bFlying)
		{
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
				m_bOnLand = false;
				m_bNoRight = false;
				m_bNoLeft = false;
				m_pLeftSencer->ClearOverlap();
				m_pRightSencer->ClearOverlap();

				y = pDest->GetColliderSectionMax().y + pSrc->GetRelativeScale().y * 0.5f + 5.f;
				SetWorldPos(Vector3(GetWorldPos().x, y, GetWorldPos().z));

				m_bFlyUp = true;
				

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

				m_bFlyDown = true;
				break;
			default:
				BOOM
					break;
			}


			return;
		}

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

			y = pDest->GetColliderSectionMax().y + pSrc->GetRelativeScale().y * 0.5f + 5.f;
			SetWorldPos(Vector3(GetWorldPos().x, y, GetWorldPos().z));

			// return;

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

			ClearGravity();
			m_fForce = -300.f;

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

void FlyingBug::PlaceAt(int leftTopX, int leftTopY)
{
	// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
	float X = (2 * 50.f) * 0.5f + leftTopX * 50.f;
	float Y = (2 * 50.f) * 0.5f + leftTopY * 50.f;

	// m_pMesh->SetRelativePos(X, -Y + 10.f, 0.f);
	SetRelativePos(X, -Y + 10.f, 0.f);

}

bool FlyingBug::CheckPlayer()
{
	m_vHK = m_pHK->GetWorldPos();
	m_vSrc = GetWorldPos();
	float dis = Vector3::Distance(m_vHK, m_vSrc);

	m_eVertical;

	// 플레이어가 왼쪽에
	if (m_vHK.x - m_vSrc.x < 0)
	{
		m_eDir = DIR_LEFT;
		Flip(-1);
	}
	else if(m_vHK.x - m_vSrc.x > 0)
	{
		m_eDir = DIR_RIGHT;
		Flip(1);
	}

	// 플레이어가 밑에있으면 방향은 위로
	if (m_vHK.y - m_vSrc.y < 0)
	{
		m_eVertical = (DIR_TYPE)-1;
		// Flip(-1);
	}
	else if (m_vHK.y - m_vSrc.y > 0)
	{
		m_eVertical = (DIR_TYPE)1;
		// Flip(1);
	}




	if (500.f >= dis)
	{
		return true;
	}
	else
	{
		return false; 
	}
}

void FlyingBug::RandomIdle(float fTime)
{
	// float idleTime = RandomNumber::GetRandomNumber



}



