#include "NewHK.h"



#include "EngineGlobals.h"

#include "TimerManager.h"
#include "Input.h"

#include "Scene/Scene.h"

#include "Device.h"

#include "Component/CameraComponent.h"
#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"



#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderRect.h"

#include "Sencer.h"

#include "HKAttackEffect.h"
#include "FireBall.h"
#include "FireBallStart.h"

#include "HealStart.h"
#include "Healing.h"
#include "HealOver.h"

#include "GetHit.h"
#include "BurstEffect.h"
#include "DustEffect.h"
#include "SoftEffect.h"
#include "HPEffect.h"
#include "CrackEffect.h"
#include "BlackSoftEffect.h"

#include "UIHP.h"

#include "../RandomNumber.h"

NewHK::NewHK()
	: m_eState(PS_IDLE)
	, m_pMaterial(nullptr)
	, m_fHealTime(0.f)
	, m_bFire(false)
	, m_bIsHealing(false)
	, m_bHealOver(false)
	, m_bHealStart(false)
	, m_bTurnStart(false)
	, m_bTurnOver(false)
	, m_eDirType(DIR_RIGHT)
	, m_pAttackEffect(nullptr)
	, m_fFireTime(0.f)
	, m_bFireOn(false)
	, m_pHealing(nullptr)
	, m_bHitStage(false)
	, m_fTurningTime(0.f)

{
	const int m_iStateCount = PS_END;

	m_vecStateName.reserve(m_iStateCount);

	m_fJumpTotalTime = 0.225;
	m_fJumpTime = 0.f;


	m_fDamagedTime = 0.f;
	m_fDamagedTotalTime = 0.2f;

	m_iHP = 5;
	m_iHPCount = 5;
}

NewHK::~NewHK()
{
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pAnimation);

	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pMaterial);

	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);

	SAFE_RELEASE(m_pAttackEffect);

	/*for (int i = 0; i < 5; ++i)
	{
		SAFE_RELEASE(m_stackHP[i]);
	}
*/

	SAFE_RELEASE_VECLIST(m_stackHP);

	if (false == m_stackHP.empty())
	{
		BOOM;
	}
}

bool NewHK::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////





	m_pCamera = CreateComponent<CCameraComponent>("Camera");

	///////////////////////////////////////////////////////////// COLLIDER SETTING
	m_pBody = CreateComponent<CColliderRect>("PlayerBody");
	m_pBody->SetExtent(150.f, 150.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);
	m_pBody->AddBlockCallback<NewHK>(this, &NewHK::OnBlock);
	m_pBody->AddBeginOverlapCallback<NewHK>(this, &NewHK::BeginOverlap);
	m_pBody->AddEndOverlapCallback<NewHK>(this, &NewHK::EndOverlap);
	// m_pBody->AddBeginOverlapCallback<NewHK>(this, &NewHK::HitStay);
	m_pBody->SetCollisionProfile("Player");




	//////////////////////////////////////////////////////////// MESH
	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);

	//////////////////////////////////////////////////////////// ANIMATION
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	m_pMesh->SetAnimation2D(m_pAnimation);
	m_pMesh->AddChild(m_pBody, TR_POS);


	///////////////////////////////////////////////////////////// MATERIAL
	// m_pMaterial	= GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMaterial");
	// m_pMesh->SetMaterial(m_pMaterial);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimOutlineMtrl");
	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_pMesh);

	//////////////////////////////////////////////////////////////////////////////
	m_pMesh->AddChild(m_pCamera, TR_POS);
	m_pCamera->SetCameraType(CT_ORTHOGONAL);
	m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f, _RESOLUTION.iHeight / -2.f, -10.f);
	///////////////////////////////////////////////////////////////////////////////
	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetRelativePos(-500.f, 500.f, 0.f);
	m_pMesh->SetRelativeScale(400.f * 0.8f, 400.f * 0.8f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.565f, 0.f);

	SetAnimation();
	SetKey();

	SetCurrentState(PS_IDLE);

	// 중력 적용
	CGameObject::SetPhysics(true);

	// 점프 힘
	SetForce(3.f);

	// 마우스와 충돌
	// m_pBody->CollisionMouse(true);

	// HP UI 설정
	// SetHP();



	return true;
}

void NewHK::Begin()
{
	CGameObject::Begin();
}

void NewHK::Update(float fTime)
{
	CGameObject::Update(fTime);

	// 중력
	if (true == m_bOnLand)
	{
		ClearGravity();

		JumpEnd(fTime);
	}


	// GET DAMAGED
	if ((PS_DAMAGED == m_eState))
	{
		m_fDamagedTime += fTime;

		// 아직 맞아서 날아가는 중
		if (m_fDamagedTotalTime >= m_fDamagedTime)
		{
			m_pMovement->SetMoveSpeed(2500.f);
			m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * m_eMonsterDir * 2.f);
			m_pMovement->AddMovement(GetWorldAxis(AXIS_Y));

			m_bOnLand = false;
			m_bHitStage = false;

			return;
		}
		else
		{
			m_pMovement->SetMoveSpeed(500.f);
			m_bOnLand = false;
			m_bHitStage = false;

			SetCurrentState(PS_FALL);
			m_bFalling = true;
			m_fForce = 0.f;
			m_fDamagedTime = 0.f;
		}
	}

	if (true == m_bDamaged)
	{
		m_fBlackTime += fTime;

		if (m_fBlackTime <= 1.5f)
		{
			int black = RandomNumber::GetRandomNumber(1, 10);

			if (black <= 3)
			{
				int y = RandomNumber::GetRandomNumber(0, 100) - 50;
				int x = RandomNumber::GetRandomNumber(0, 100) - 50;

				BlackSoftEffect* bs = m_pScene->SpawnObject<BlackSoftEffect>(
					GetWorldPos() + Vector3((float)x, (float)y, -0.5f)
					);

				bs->SetVertical();

				SAFE_RELEASE(bs);
			}
		}
		else
		{
			m_bDamaged = false;
			m_fBlackTime = 0.f;
		}
	}





	//글자

	UpdateHeal(fTime);
	ReturnSequence(fTime);

	// BHEAL 끝나면
	if ((PS_BHEAL == m_eState) && (true == m_pAnimation->IsSequenceEnd()) && (true == m_bHealStart))
	{
		SetCurrentState(PS_HEAL);
		m_bHealStart = false;
		m_bIsHealing = true;

		m_pHealing = m_pScene->SpawnObject<Healing>(GetWorldPos() + Vector3(0.f, -0.1f, -0.5f));
	}

	// FIREBALL
	if (PS_FIRE == m_eState)
	{
		m_fFireTime += fTime;

		if (0.2f <= m_fFireTime && false == m_bFireOn)
		{
			FireBall* fire = m_pScene->SpawnObject<FireBall>(
				GetWorldPos() + GetWorldAxis(AXIS_X) * 100.f * (int)m_eDirType + Vector3(0.f, 0.f, -0.53f)
				);

			fire->Flip(m_eDirType);

			CProjectileMovementComponent* pMovement = fire->FindObjectComponent<CProjectileMovementComponent>();
			// pMovement->SetDistance(500.f);

			SAFE_RELEASE(pMovement);

			CColliderRect* pBody = fire->GetBody();
			pBody->SetCollisionProfile("PlayerProjectile");

			SAFE_RELEASE(fire);

			m_bFireOn = true;

			m_fFireTime = 0.f;

			FireBallStart* start = m_pScene->SpawnObject<FireBallStart>(
				GetWorldPos() + GetWorldAxis(AXIS_X) * 100.f * (int)m_eDirType + Vector3(0.f, 0.f, -0.53f)
				);

			start->Flip(m_eDirType);

			SAFE_RELEASE(start);

		}
	}




}

void NewHK::Render(float fTime)
{
	CGameObject::Render(fTime);

	// DEBUG
	{
		char	strText[256] = {};
		sprintf_s(strText, m_vecStateName[m_eState].c_str());
		// OutputDebugStringA(strText);
	}

	{
		// char	strText[256] = {};
		// sprintf_s(strText, "%d", m_iDir);
		// OutputDebugStringA(strText);
	}
}


DIR_TYPE NewHK::GetDirection() const
{
	return m_eDirType;
}

void NewHK::MoveX(float fScale, float fTime)
{
	bool bAnimState = m_pAnimation->IsSequenceEnd();

	if (PS_DAMAGED == m_eState)
	{
		m_pMovement->SetMoveSpeed(500.f);
		return;
	}




	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////  방향전환

	if (PS_FALL != m_eState && PS_JUMP != m_eState)
	{
		if (-1.f == fScale && DIR_RIGHT == m_eDirType)
		{
			if (PS_TURN == m_eState && true == m_pAnimation->IsSequenceEnd())
			{
				m_bTurnOver = true;
				m_bTurnStart = false;
				m_eDirType = DIR_LEFT;
				Reverse(fTime);
				SetCurrentState(PS_IDLE);
			}
			// 방금 돈다.
			else if (PS_TURN != m_eState && false == m_bTurnStart)
			{
				SetCurrentState(PS_TURN);
				m_bTurnStart = true;
				return;
			}
		}
		else if (1.f == fScale && DIR_LEFT == m_eDirType)
		{
			if (PS_TURN == m_eState && true == m_pAnimation->IsSequenceEnd())
			{
				m_bTurnOver = true;
				m_bTurnStart = false;
				m_eDirType = DIR_RIGHT;
				Reverse(fTime);
				SetCurrentState(PS_IDLE);
			}
			// 방금 돈다
			else if (PS_TURN != m_eState && false == m_bTurnStart)
			{
				SetCurrentState(PS_TURN);
				m_bTurnStart = true;
				return;
			}
		}

		// 도는 중
		if (true == m_bTurnStart)
		{
			m_fTurningTime += fTime;

			if (0.5f <= m_fTurningTime)
			{
				m_bTurnStart = false;
				m_fTurningTime = 0.f;
			}

			return;
		}
	}


	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////// 


	if (0.f == fScale && PS_TURN != m_eState)
	{
		if (PS_BWALK == m_eState || PS_WALK == m_eState)
		{
			SetCurrentState(PS_AWALK);
		}
		else if (true == bAnimState && PS_AWALK == m_eState)
		{
			SetCurrentState(PS_IDLE);
		}
		else if (PS_LAND == m_eState)
		{
			// SetCurrentState(PS_IDLE);
		}


		return;
	}

	// 이동 불가 상태
	if (PS_FIRE == m_eState)
	{
		return;
	}

	m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * fScale);

	m_bMove = true;


	if (PS_IDLE == m_eState || PS_AWALK == m_eState)
	{
		SetCurrentState(PS_BWALK);
	}
	else if (PS_BWALK == m_eState && true == bAnimState)
	{
		SetCurrentState(PS_WALK);


	}

	if (0 != fScale && true == m_bOnLand)
	{
		if (m_fDustTime <= m_fDustTotalTime)
		{
			m_fDustTime += fTime;
		}
		else
		{
			/*m_fDustTime = 0.f;
			DustEffect* dust = m_pScene->SpawnObject<DustEffect>(
				GetWorldPos() - Vector3(0.f, 400.f * 0.2f, 0.f));

			SAFE_RELEASE(dust);*/
		}
	}
}




void NewHK::Fire(float fTime)
{
	// RELEASE

	if (true == m_bFire && false == m_bHealStart)
	{
		SetCurrentState(PS_FIRE);
		m_fHealTime = 0.f;
	}




	m_bHealOver = true;
}

void NewHK::Attack(float fTime)
{
	SetCurrentState(PS_ATTACK);

	HKAttackEffect* attack = m_pScene->SpawnObject<HKAttackEffect>(
		GetWorldPos() + GetWorldAxis(AXIS_X) * 100.f * (int)m_eDirType + Vector3(0.f, 10.f, -0.5f)
		);

	attack->Flip(m_eDirType);

	CColliderRect* pBody = attack->GetBody();
	pBody->SetCollisionProfile("PlayerProjectile");

	SAFE_RELEASE(attack);
}

void NewHK::Jump(float fTime)
{

	if (m_fJumpTime >= m_fJumpTotalTime)
	{
		JumpOver(fTime);
		return;
	}

	if (false == m_bJumping)
	{
		m_fForce = m_fOriginForce * 700;
		SetCurrentState(PS_JUMP);

		/*DustEffect* dust = m_pScene->SpawnObject<DustEffect>(
			GetWorldPos() - Vector3(0.f, 400.f * 0.2f, 0.f));

		dust->SetStaticSize(200.f);

		SAFE_RELEASE(dust);*/
	}


	m_fJumpTime += fTime;

	m_bFalling = false;
	m_bJumping = true;

	m_fForce -= m_fOriginForce * m_fOriginForce;

	m_bOnLand = false;
	m_bHitStage = false;

	if (m_fDustTime <= m_fDustTotalTime * 0.7f)
	{
		m_fDustTime += fTime;
	}
	else
	{
		/*m_fDustTime = 0.f;
		DustEffect* dust = m_pScene->SpawnObject<DustEffect>(
			GetWorldPos() - Vector3(0.f, 400.f * 0.2f, 0.f));

		dust->SetMaxSize(40.f);

		SAFE_RELEASE(dust);*/
	}
}

void NewHK::JumpEnd(float fTime)
{
	m_bJumping = false;
	m_fForce = 0.f;
	m_fJumpTime = 0.f;

	if (false == m_bHitStage)
	{
		SetCurrentState(PS_LAND);
		m_bHitStage = true;
	}
}

// RELEASE
void NewHK::JumpOver(float fTime)
{
	m_bJumping = false;
	m_fForce = 0.f;

	if (false == m_bFalling)
	{
		SetCurrentState(PS_FALL);
		m_bFalling = true;
	}

}



void NewHK::Heal(float fTime)
{
	m_fHealTime += fTime;
	m_bHealOver = false;

	if (true == m_bHealStart && false == m_bFire)
	{
		if (PS_BHEAL == m_eState && true == m_pAnimation->IsSequenceEnd())
		{
			// SetCurrentState(PS_HEAL);
			m_bIsHealing = true;
		}
		else if (true == m_bHealStart)
		{
			SetCurrentState(PS_BHEAL);

			HealStart* healStart = m_pScene->SpawnObject<HealStart>(
				GetWorldPos() + Vector3(0.f, 0.1f, -0.5f)
				);

			SAFE_RELEASE(healStart);
		}

	}


	if (false == m_bIsHealing)
	{
		m_bHealStart = true;
	}
}






void NewHK::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (nullptr == pDest)
	{
		return;
	}

	if (true == pDest->IsStage())
	{
		ClearGravity();
		JumpEnd(fTime);
		m_bOnLand = true;

		m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * 2.f, 0.f));
	}

	if (true == pDest->IsMonster())
	{
		GET_SINGLE(CTimerManager)->CreateSlowMotion(10.f);

		m_bDamaged = true;

		// 힐 중이었으면 리셋
		if (nullptr != m_pHealing)
		{
			m_pHealing->Start(0.f, Vector3::Zero);

			SAFE_RELEASE(m_pHealing);

			m_pHealing = nullptr;

			m_bHealOver = true;
			m_fHealTime = 0.f;
			m_bHealStart = false;
			m_bIsHealing = false;
			m_bFireOn = false;
			m_bFire = false;
		}



		SetCurrentState(PS_DAMAGED);

		if (0 < m_iHPCount)
		{
			--m_iHPCount;
			UIHP* hp = m_stackHP[m_iHPCount];

			hp->BreakHP();
		}

		// 검은 공 이펙트
		for (int i = 0; i < 30; ++i)
		{
			int y = RandomNumber::GetRandomNumber(0, 100);
			int x = RandomNumber::GetRandomNumber(0, 100);

			BlackSoftEffect* bs = m_pScene->SpawnObject<BlackSoftEffect>(
				GetWorldPos() + Vector3((float)x, (float)y, -0.5f)
				);

			SAFE_RELEASE(bs);
		}

		for (int i = 0; i < 30; ++i)
		{
			int y = RandomNumber::GetRandomNumber(0, 100);
			int x = RandomNumber::GetRandomNumber(0, 100);

			BlackSoftEffect* bs = m_pScene->SpawnObject<BlackSoftEffect>(
				GetWorldPos() + Vector3((float)-x, (float)y, -0.5f)
				);

			bs->SetLeft();
			SAFE_RELEASE(bs);
		}




		GetHit* hit = m_pScene->SpawnObject<GetHit>(
			GetWorldPos() + Vector3(0.f, 0.1f, -0.5f)
			);

		SAFE_RELEASE(hit);

		BurstEffect* burst = m_pScene->SpawnObject<BurstEffect>(
			GetWorldPos() + Vector3(0.f, 0.1f, -0.5f)
			);

		SAFE_RELEASE(burst);

		CrackEffect* crack = m_pScene->SpawnObject<CrackEffect>(
			GetWorldPos() + Vector3(0.f, 0.1f, -0.5f)
			);

		SAFE_RELEASE(crack);

		float srcX = pSrc->GetWorldPos().x;
		float destX = pDest->GetWorldPos().x;


		if (srcX < destX)
		{
			// 적은 오른쪽
			// 따라서 날아가야할 곳은 반대
			m_eMonsterDir = DIR_LEFT;
		}
		else
		{
			m_eMonsterDir = DIR_RIGHT;
		}
	}

}

void NewHK::BeginOverlap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	OutLineCBuffer	tBuffer = {};
	tBuffer.iPixelSize = 5;

	Animation2DFrameInfo	tFrameInfo = m_pAnimation->GetAnimFrame();

	tBuffer.vScale = Vector2(m_pMesh->GetWorldScale().x, m_pMesh->GetWorldScale().y);
	tBuffer.vImageSize = tFrameInfo.vEnd - tFrameInfo.vStart;

	m_pMesh->UpdateMaterialCBufferNode(OUTLINE_CBUFFER, &tBuffer);
}

void NewHK::EndOverlap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	OutLineCBuffer	tBuffer = {};


	m_pMesh->UpdateMaterialCBufferNode(OUTLINE_CBUFFER, &tBuffer);

}














void NewHK::SetEffect(HKAttackEffect * attackEffect)
{
	m_pAttackEffect = attackEffect;
}

void NewHK::SetCurrentState(PLAYER_STATE state)
{
	if (state == m_eState)
	{
		return;
	}

	m_eState = state;

	std::string stateName = m_vecStateName[state];
	stateName.append("_HK");

	m_pAnimation->ChangeAnimation(stateName);




	if (PS_IDLE == m_eState)
	{
		int a = 0;
	}
}

void NewHK::ReturnSequence(float fTime)
{
	if (PS_ATTACK == m_eState && m_pAnimation->IsSequenceEnd())
	{

		SetCurrentState(PS_IDLE);
	}
	else if (PS_LAND == m_eState && m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(PS_IDLE);
	}
	else if (PS_FIRE == m_eState && m_pAnimation->IsSequenceEnd() && "FIRE_HK" == m_pAnimation->GetSequence()->GetName())
	{
		SetCurrentState(PS_IDLE);
		m_bFireOn = false;
		m_fFireTime = 0.f;
	}
	else if (PS_HEAL == m_eState && m_pAnimation->IsSequenceEnd() && true == m_bHealOver)
	{
		SetCurrentState(PS_AHEAL);
		m_fHealTime = 0.f;
		m_bFire = false;
		m_bHealStart = false;
		m_bIsHealing = false;

		m_pHealing->Start(0.f, Vector3::Zero);

		SAFE_RELEASE(m_pHealing);

		m_pHealing = nullptr;

		HealOver* healOver = m_pScene->SpawnObject<HealOver>(
			GetWorldPos() + Vector3(0.f, 0.1f, -0.5f)
			);

		SAFE_RELEASE(healOver);

		// UI HP
		if (5 > m_iHPCount)
		{
			m_stackHP[m_iHPCount]->Normal();

			for (int i = 0; i < 30; ++i)
			{
				int pos = RandomNumber::GetRandomNumber(0, 40) + 20;

				Vector3 temp = m_stackHP[m_iHPCount]->GetWorldPos();

				HPEffect* soft = m_pScene->SpawnObject<HPEffect>(
					m_stackHP[m_iHPCount]->GetRelativePos() + Vector3((float)pos, 25.f, 0.f));

				SAFE_RELEASE(soft);
			}
			for (int i = 0; i < 30; ++i)
			{
				int pos = RandomNumber::GetRandomNumber(0, 40) + 20;

				Vector3 temp = m_stackHP[m_iHPCount]->GetWorldPos();

				HPEffect* soft = m_pScene->SpawnObject<HPEffect>(
					m_stackHP[m_iHPCount]->GetRelativePos() + Vector3((float)pos, 25.f, 0.f));

				soft->SetDown();

				SAFE_RELEASE(soft);
			}

			++m_iHPCount;
		}

	}
	else if (PS_AHEAL == m_eState && m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(PS_IDLE);
	}
	else if (PS_TURN == m_eState && m_pAnimation->IsSequenceEnd())
	{
		// SetCurrentState(PS_IDLE);
	}
}

void NewHK::UpdateHeal(float fTime)
{
	if (PS_FIRE == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		m_fHealTime = 0.f;
	}

	// 힐 중, 시간 짧으면
	if (m_fHealTime <= 1.f && true == m_bHealStart)
	{
		m_bFire = true;
		m_bHealStart = false;
	}
	else
	{
		m_bFire = false;
	}

	// 힐 끝나면 기공파 못씀
	if (PS_HEAL == m_eState && true == m_pAnimation->IsSequenceEnd() && false == m_bFire)
	{
		// m_fHealTime = 0.f;
		m_bFire = false;
		m_bHealStart = false;
	}
}

void NewHK::Reverse(float fTime)
{
	Flip(m_eDirType);
}


void NewHK::SetAnimation()
{
	m_vecStateName.push_back("IDLE");

	m_vecStateName.push_back("BWALK");
	m_vecStateName.push_back("WALK");
	m_vecStateName.push_back("AWALK");

	m_vecStateName.push_back("TURN");

	m_vecStateName.push_back("ATTACK");

	m_vecStateName.push_back("JUMP");
	m_vecStateName.push_back("FALL");
	m_vecStateName.push_back("LAND");

	m_vecStateName.push_back("BHEAL");
	m_vecStateName.push_back("HEAL");
	m_vecStateName.push_back("AHEAL");

	m_vecStateName.push_back("FIRE");

	m_vecStateName.push_back("DAMAGED");





	m_pAnimation->AddAnimation2DSequence("IDLE_HK");

	m_pAnimation->AddAnimation2DSequence("BWALK_HK");
	m_pAnimation->AddAnimation2DSequence("WALK_HK");
	m_pAnimation->AddAnimation2DSequence("AWALK_HK");


	m_pAnimation->AddAnimation2DSequence("TURN_HK");

	m_pAnimation->AddAnimation2DSequence("ATTACK_HK");

	m_pAnimation->AddAnimation2DSequence("JUMP_HK");
	m_pAnimation->AddAnimation2DSequence("FALL_HK");
	m_pAnimation->AddAnimation2DSequence("LAND_HK");


	m_pAnimation->AddAnimation2DSequence("BHEAL_HK");
	m_pAnimation->AddAnimation2DSequence("HEAL_HK");
	m_pAnimation->AddAnimation2DSequence("AHEAL_HK");

	m_pAnimation->AddAnimation2DSequence("FIRE_HK");

	m_pAnimation->AddAnimation2DSequence("DAMAGED_HK");
}

void NewHK::SetKey()
{
	GET_SINGLE(CInput)->AddAxisKey("MoveX", DIK_RIGHT, 1.f);
	GET_SINGLE(CInput)->AddAxisKey("MoveX", DIK_LEFT, -1.f);
	GET_SINGLE(CInput)->BindAxis<NewHK>("MoveX", this, &NewHK::MoveX);

	GET_SINGLE(CInput)->AddActionKey("Attack", DIK_X);
	GET_SINGLE(CInput)->BindAction<NewHK>("Attack", AKS_PRESS, this, &NewHK::Attack);

	GET_SINGLE(CInput)->AddActionKey("Fire", DIK_A);
	GET_SINGLE(CInput)->BindAction<NewHK>("Fire", AKS_RELEASE, this, &NewHK::Fire);

	GET_SINGLE(CInput)->AddActionKey("Heal", DIK_A);
	GET_SINGLE(CInput)->BindAction<NewHK>("Heal", AKS_PUSH, this, &NewHK::Heal);




	GET_SINGLE(CInput)->AddActionKey("Jump", DIK_Z);
	GET_SINGLE(CInput)->BindAction<NewHK>("Jump", AKS_PUSH, this, &NewHK::Jump);

	GET_SINGLE(CInput)->AddActionKey("JumpOver", DIK_Z);
	GET_SINGLE(CInput)->BindAction<NewHK>("JumpOver", AKS_RELEASE, this, &NewHK::JumpOver);

	//GET_SINGLE(CInput)->AddActionKey("Reverse", DIK_R);
	//GET_SINGLE(CInput)->BindAction<NewHK>("Reverse", AKS_PUSH, this, &NewHK::Reverse);
}

void NewHK::SetHP()
{

	/*for (int i = 0; i < 5; ++i)
	{
		UIHP* hp = m_pScene->SpawnObject<UIHP>(Vector3(330.f + i * 70, 930.f, 0.f));

		m_stackHP.push_back(hp);


	}*/

}
