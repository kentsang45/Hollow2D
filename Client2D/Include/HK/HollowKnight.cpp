#include "HollowKnight.h"



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

#include "EffectSound.h"
#include "SoundObject.h"

#include "../HKStage.h"
#include "CoinUI.h"
#include "HPHead.h"

#include "../GameMode/MainGameMode.h"
#include "HKMode.h"

#include "CollisionManager.h"
#include "Engine.h"

#include "Darkness.h"
#include "LightEffect.h"
#include "SoulParticle.h"
#include "BugParticle.h"

#include "Component/Audio.h"

HollowKnight::HollowKnight()
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
	, m_pDarkMesh(nullptr)
	, m_pDarkAnimation(nullptr)

{
	const int m_iStateCount = PS_END;

	m_vecStateName.reserve(m_iStateCount);

	m_fJumpTotalTime = 0.38;
	m_fJumpTime = 0.f;


	m_fDamagedTime = 0.f;
	m_fDamagedTotalTime = 0.15f;

	m_iHP = 5;
	m_iHPCount = 5;
}

HollowKnight::~HollowKnight()
{
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pDarkMesh);
	SAFE_RELEASE(m_pDarkAnimation);

	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pMaterial);

	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);

	SAFE_RELEASE(m_pDark);

	SAFE_RELEASE(m_pAttackEffect);

	SAFE_RELEASE(m_pFootsteps);

	for (int i = 0; i < 5; ++i)
	{
		SAFE_RELEASE(m_stackHP[i]);
	}

	m_stackHP.clear();

	if (false == m_stackHP.empty())
	{
		BOOM;
	}
}

void HollowKnight::PlaceAt(int stageNumber, bool bStart)
{
	float X = 0.f;
	float Y = 0.f;
	int sizeX = 0;
	int sizeY = 0;

	int HKSixeX = 4;
	int HKSizeY = 4;

	m_iStageNumber = stageNumber;

	m_bAir = true;
	SetPhysics(false);
	switch (stageNumber)
	{
	case 1:
		// 중앙
		m_fStageSizeX = 6700;
		m_fStageSizeY = 1800;

		X = (stageNumber - 1) * 10000.f + m_fStageSizeX * 0.5f;
		Y = m_fStageSizeY * 0.5f;

		// 시작점
		if (true == bStart)
		{
			// leftTopX = 69
			// leftTopY = 0
			// float xX = (2 * 50.f) * 0.5f + 76 * 50.f;
			// float yY = (2 * 50.f) * 0.5f + 18 * 50.f;

			// float xX = (2 * 50.f) * 0.5f + 23 * 50.f;
			// float yY = (2 * 50.f) * 0.5f + 18 * 50.f;

			// float xX = (2 * 50.f) * 0.5f + 95 * 50.f;
			// float yY = (2 * 50.f) * 0.5f + 23 * 50.f;


			// REAL
			 float xX = (2 * 50.f) * 0.5f + 69 * 50.f;
			float yY = (2 * 50.f) * 0.5f + 0 * 50.f;

			SetRelativePos(xX, -yY, 0.f);
		}
		else
		{
			// SetRelativePos(x, 0.f);

			float xX = (2 * 50.f) * 0.5f + 132 * 50.f;
			float yY = (2 * 50.f) * 0.5f + 16 * 50.f;

			SetRelativePos(xX, -yY, 0.f);
		}

		break;

	case 2:
		m_fStageSizeX = 5200;
		m_fStageSizeY = 1750;
		X = (stageNumber - 1) * 10000.f + m_fStageSizeX * 0.5f;
		Y = m_fStageSizeY * 0.5f;

		// 시작점
		if (true == bStart)
		{
			// leftTopX = 69
			// leftTopY = 0
			// float xX = (2 * 50.f) * 0.5f + 76 * 50.f;
			// float yY = (2 * 50.f) * 0.5f + 18 * 50.f;

			// float xX = (2 * 50.f) * 0.5f + 23 * 50.f;
			// float yY = (2 * 50.f) * 0.5f + 18 * 50.f;

			float xX = (stageNumber - 1) * 10000.f + (2 * 50.f) * 0.5f + 0 * 50.f;
			float yY = (2 * 50.f) * 0.5f + 21 * 50.f;

			SetRelativePos(xX, -yY, 0.f);

	
		}
		else
		{
			float xX = (stageNumber - 1) * 10000.f + (2 * 50.f) * 0.5f + 78 * 50.f;
			float yY = (2 * 50.f) * 0.5f + 32 * 50.f;

			m_fForce = 1200.f;
			SetCurrentState(PS_JUMP);

			SetRelativePos(xX, -yY, 0.f);
		}

		break;

	case 3:
		m_fStageSizeX = 1950;
		m_fStageSizeY = 4800;
		X = (stageNumber - 1) * 10000.f + m_fStageSizeX * 0.5f;
		Y = m_fStageSizeY * 0.5f;

		// 시작점
		if (true == bStart)
		{
			// leftTopX = 69
			// leftTopY = 0
			// float xX = (2 * 50.f) * 0.5f + 76 * 50.f;
			// float yY = (2 * 50.f) * 0.5f + 18 * 50.f;

			// float xX = (2 * 50.f) * 0.5f + 23 * 50.f;
			// float yY = (2 * 50.f) * 0.5f + 18 * 50.f;



			// test
			//float xX = (stageNumber - 1) * 10000.f + (2 * 50.f) * 0.5f + 28 * 50.f;
			// float yY = (2 * 50.f) * 0.5f + 63 * 50.f;

			// REAL
			float xX = X - 50.f;
			float yY = 51.f;

			SetRelativePos(xX, -yY, 0.f);
		}
		else
		{
			float xX = (stageNumber - 1) * 10000.f + (2 * 50.f) * 0.5f + 0 * 50.f;
			float yY = (2 * 50.f) * 0.5f + 85 * 50.f;

			SetRelativePos(xX, -yY, 0.f);

			// SetRelativePos(x, 0.f);
		}

		break;

	case 4:
		m_fStageSizeX = 6900;
		m_fStageSizeY = 1800;
		X = (stageNumber - 1) * 10000.f + m_fStageSizeX * 0.5f;
		Y = m_fStageSizeX * 0.5f;

		// 시작점
		if (true == bStart)
		{
			// leftTopX = 69
			// leftTopY = 0
			// float xX = (2 * 50.f) * 0.5f + 76 * 50.f;
			// float yY = (2 * 50.f) * 0.5f + 18 * 50.f;

			float xX = (stageNumber - 1) * 10000.f + (2 * 50.f) * 0.5f + 135 * 50.f;
			float yY = (2 * 50.f) * 0.5f + 14 * 50.f;

			

			SetRelativePos(xX, -yY, 0.f);
		}
		else
		{
			float xX = (stageNumber - 1) * 10000.f + (2 * 50.f) * 0.5f + 0 * 50.f;
			float yY = (2 * 50.f) * 0.5f + 28 * 50.f;




			SetRelativePos(xX, -yY, 0.f);
			// SetRelativePos(x, 0.f);
		}
		break;

	case 5:
		m_fStageSizeX = 5000;
		m_fStageSizeY = 1950;
		X = (stageNumber - 1) * 10000.f + m_fStageSizeX * 0.5f;
		Y = m_fStageSizeY * 0.5f;
		// 시작점
		if (true == bStart)
		{
			// leftTopX = 69
			// leftTopY = 0
			// float xX = (stageNumber - 1) * 10000.f + (2 * 50.f) * 0.5f + 46 * 50.f;
			// float yY = (2 * 50.f) * 0.5f + 31 * 50.f;

			 float xX = (stageNumber - 1) * 10000.f + (2 * 50.f) * 0.5f + 98 * 50.f;
			 float yY = (2 * 50.f) * 0.5f + 32 * 50.f;



			SetRelativePos(xX, -yY, 0.f);
		}
		else
		{
			// SetRelativePos(x, 0.f);
		}

		break;

	default:
		BOOM;
		break;
	}

}

bool HollowKnight::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}



	m_pFootsteps = m_pScene->SpawnObject<SoundObject>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		Vector3(0.f, 0.f, GetRelativeRot().z));

	m_pFootsteps->SetSound("Footsteps", "Footsteps.wav");


	//////////////////////////////////////////////////////////////////////////////

	m_pCamera = CreateComponent<CCameraComponent>("Camera");

	///////////////////////////////////////////////////////////// COLLIDER SETTING
	m_pBody = CreateComponent<CColliderRect>("PlayerBody");
	m_pBody->SetExtent(80.f, 100.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);
	m_pBody->AddBlockCallback<HollowKnight>(this, &HollowKnight::OnBlock);
	m_pBody->AddBeginOverlapCallback<HollowKnight>(this, &HollowKnight::BeginOverlap);
	m_pBody->AddEndOverlapCallback<HollowKnight>(this, &HollowKnight::EndOverlap);
	
	// m_pBody->AddBeginOverlapCallback<HollowKnight>(this, &HollowKnight::HitStay);
	m_pBody->SetCollisionProfile("Player");
	m_pBody->SetPlayer(true);

	m_pBody->EnableOverlap(true);


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

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMaterial");
	// pMaterial->SetSubsetDiffuse(Vector4(555.f, 555.f, 555.f, 1.f));
	m_pMesh->SetMaterial(pMaterial);
	
	SAFE_RELEASE(pMaterial);

	SetRoot(m_pMesh);

	//////////////////////////////////////////////////////////////////////////////
	m_pMesh->AddChild(m_pCamera, TR_POS);
	m_pCamera->SetCameraType(CT_ORTHOGONAL);
	m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f, _RESOLUTION.iHeight / -2.f + 100.f, -10.f);


	///////////////////////////////////////////////////////////////////////////////
	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetRelativePos(0.f, 1000.f, 0.f);
	// m_pMesh->SetRelativeScale(400.f * 0.8f, 400.f * 0.8f, 1.f);
	m_pMesh->SetRelativeScale(400.f, 400.f, 1.f);
	// m_pMesh->SetPivot(0.5f, 0.565f, 0.f);
	m_pMesh->SetPivot(0.5f, 0.46f, 0.f);

	SetAnimation();
	SetKey();

	SetCurrentState(PS_FALL);

	// 중력 적용
	CGameObject::SetPhysics(true);

	// 점프 힘
	// SetForce(1.f);
	
	// 마우스와 충돌
	// m_pBody->CollisionMouse(true);

	// HP UI 설정
	SetHP();

	m_fGravitySpeed = 10.f;
	






	// 안개
	/*m_pDarkMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pDarkMesh->SetStaticMesh(pMesh);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("DarknessMaterial");
	m_pDarkMesh->SetMaterial(pMaterial);
	m_pDarkMesh->SetPivot(0.5f, 0.5f, 0.f);

	pMaterial->SetSubsetDiffuse(Vector4(0.5f, 0.5f, 0.5f, 0.5f));

	SAFE_RELEASE(pMaterial);

	m_pDarkMesh->SetRelativePos(0.f, 0.f, 1.f);
	m_pDarkMesh->SetRelativeScale(3840.f, 2160.f, 1.f);

	m_pMesh->AddChild(m_pDarkMesh, TR_POS);

	m_pDarkAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pDarkMesh->SetAnimation2D(m_pDarkAnimation);
	m_pDarkAnimation->AddAnimation2DSequence("DARKNESS");
	m_pDarkAnimation->ChangeAnimation("DARKNESS");*/

	m_pDark = m_pScene->SpawnObject<Darkness>();

	/*LightEffect* le = m_pScene->SpawnObject<LightEffect>();
	SAFE_RELEASE(le);
*/
	return true;
}

void HollowKnight::Begin()
{
	CGameObject::Begin();


}

void HollowKnight::Update(float fTime)
{
	CGameObject::Update(fTime);

	SetBugEffect(fTime);
	SetSoulEffect(fTime);

	if (true == m_bReset)
	{
		m_fResetTime += fTime;

		if (m_fResetTime >= m_fResetTotalTime)
		{
			m_fResetTime = 0;
			m_bReset = false;
			PlaceStart();
		}

	}


	// 공중부양 ( 씬전환 중 낙하를 막기 위해
	if (true == m_bAir)
	{
		SetPhysics(false);

		m_fAirTime += fTime;

		if (m_fAirTime >= m_fAirTotalTime)
		{
			m_bAir = false;
			m_fAirTime = 0.f;
			SetPhysics(true);
		}
	}




	// 무적 판정
	if (true == m_bInvincible)
	{
		m_fInvincibleTime += fTime;

		if (m_fInvincibleTime >= m_fInvincibleTotalTime)
		{
			m_fInvincibleTime = 0.f;
			m_bInvincible = false;
		}
	}

	// 충돌중이 아니라면
	if (true == m_bAttacking)
	{
		m_fAttackTime += fTime;

		if (m_fAttackTime >= m_fAttackTotalTime)
		{
			m_bAttacking = false;
			m_fAttackTime = 0.f;
		}
	}
	

	// 중력, 충돌
	if (true == m_bOnLand && 0 == m_fDamagedTime)
	{
		ClearGravity();

		JumpEnd(fTime);

		m_bFalling = false;
		m_fJumpTime = 0.f;
		m_fForce = 0.f;
	}
	else
	{
		if (true == m_bFalling)
		{
			// 떨어지기
			// m_fForce -= 100.f;
		}

	}

	if (false == m_bColliding && false == m_bOnLand && false == m_bJumping)
	{
		if (true == m_pAnimation->IsSequenceEnd())
		{
			SetCurrentState(PS_FALLING);
		}		

		m_bFalling = true;
		m_bOnLand = false;
		m_bHitStage = false;

		m_bNoRight = false;
		m_bNoLeft = false;
	}



	// 땅 박힌거 복구
	



	/*if (false == m_pBody->IsColliding() && false == m_bJumping)
	{
		SetCurrentStzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzate(PS_FALL);
		m_bFalling = true;
		m_fForce = 0.f;
	}*/

	// 떨어지기 반복
	if (PS_FALL == m_eState && true == m_pAnimation->IsSequenceEnd())
	{
		SetCurrentState(PS_FALLING);
	}
	if (false == m_pBody->IsColliding())
	{
		m_bNoRight = false;
		m_bNoLeft = false;
	}


	// GET DAMAGED
	if ((PS_DAMAGED == m_eState))
	{
		m_fDamagedTime += fTime;

		// 아직 맞아서 날아가는 중
		if (m_fDamagedTotalTime >= m_fDamagedTime)
		{
			m_pMovement->SetMoveSpeed(3000.f);

			if (true == m_bNoLeft && DIR_LEFT == m_eMonsterDir)
			{	
				// m_eDirType = DIR_RIGHT;
				m_eMonsterDir = DIR_RIGHT;
			}
			else if (true == m_bNoRight && DIR_RIGHT == m_eMonsterDir)
			{
				// m_eDirType = DIR_LEFT;
				m_eMonsterDir = DIR_LEFT;

			}

			m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * m_eMonsterDir * 2.f);


			if (false == m_bCeiling)
			{
				m_pMovement->AddMovement(GetWorldAxis(AXIS_Y));
				Jump(fTime);
			}
			else
			{
				m_bFalling = true;
				JumpOver(fTime);
			}
			

			m_bOnLand = false;
			m_bHitStage = false;
			m_bColliding = false;
		
			return;
		}
		else
		{

			JumpOver(fTime); 

			m_pMovement->SetMoveSpeed(500.f);
			m_fNormalSpeed = 500.f;
			m_bOnLand = false;
			m_bHitStage = false;
	
			SetCurrentState(PS_FALL);
			m_bFalling = true;
			m_fForce = 0.f;
			m_fDamagedTime = 0.f;
		}	



		if (true == m_bDamaged)
		{
			m_fBlackTime += fTime;

			if (m_fBlackTime <= 1.5f)
			{
				int black = RandomNumber::GetRandomNumber(1, 10);

				if (black <= 5)
				{
					int y = RandomNumber::GetRandomNumber(0, 100) - 50;
					int x = RandomNumber::GetRandomNumber(0, 100) - 50;

					BlackSoftEffect* bs = m_pScene->SpawnObject<BlackSoftEffect>(
						GetWorldPos() + Vector3((float)x, (float)y, 0.f)
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

		return;
	}
	else
	{
		m_pMovement->SetMoveSpeed(m_fNormalSpeed);
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

		m_pHealing = m_pScene->SpawnObject<Healing>(GetWorldPos() + Vector3(0.f, 0.f, 0.f));
	}

	// FIREBALL
	if (PS_FIRE == m_eState)
	{
		m_fFireTime += fTime;
	
		if (0.2f <= m_fFireTime && false == m_bFireOn)
		{
			FireBall* fire = m_pScene->SpawnObject<FireBall>(
				GetWorldPos() + GetWorldAxis(AXIS_X) * 100.f * (int)m_eDirType + Vector3(0.f, 0.f, 0.f) 
				);

			fire->Flip(m_eDirType);

			CProjectileMovementComponent* pMovement = fire->FindObjectComponent<CProjectileMovementComponent>();
			// pMovement->SetDistance(500.f);

			SAFE_RELEASE(pMovement);

			CColliderRect* pBody = fire->GetBody();
			pBody->SetCollisionProfile("PlayerProjectile");

			SAFE_RELEASE(fire);

			if (false == m_bFireOn)
			{
				SetEffectSound("Fireball", "Fireball.wav");
			}

			m_bFireOn = true;

			m_fFireTime = 0.f;

			FireBallStart* start = m_pScene->SpawnObject<FireBallStart>(
				GetWorldPos() + GetWorldAxis(AXIS_X) * 100.f * (int)m_eDirType + Vector3(0.f, 0.f, 0.f)
				);

			start->Flip(m_eDirType);

			SAFE_RELEASE(start);

		}
	}



}

void HollowKnight::Render(float fTime)
{
	CameraControl(fTime);
	CameraShake(fTime);

	CGameObject::Render(fTime);


	// DEBUG
	/*{
		char	strText[256] = {};
		sprintf_s(strText, m_vecStateName[m_eState].c_str());
		OutputDebugStringA(strText);
	}

	{
		char	strText[256] = {};
		sprintf_s(strText, "%d", m_iDir);
		OutputDebugStringA(strText);
	}*/

	if (true == m_bNext)
	{
		SetStage(++m_iStageNumber, true);
		m_bNext = false;
	}
	if (true == m_bPrev)
	{
		SetStage(--m_iStageNumber, false);
		m_bPrev = false;
	}
}


DIR_TYPE HollowKnight::GetDirection() const
{
	return m_eDirType;
}

void HollowKnight::MoveX(float fScale, float fTime)
{
	if (0.f == fScale)
	{
		m_pFootsteps->StopSO();
		m_bWalkSound = false;
	}
	else
	{
		if (true == m_bOnLand)
		{
			if (false == m_pFootsteps->IsPlaying() && false == m_bWalkSound)
			{
				m_pFootsteps->PlaySO();
				m_bWalkSound = true;
			}
		
		}
		else
		{
			m_pFootsteps->StopSO();
			m_bWalkSound = false;
		}
	}


	bool bAnimState = m_pAnimation->IsSequenceEnd();

	if (PS_DAMAGED == m_eState)
	{
		m_pMovement->SetMoveSpeed(500.f);
		m_fNormalSpeed = 500.f;
		return;
	}

	//char	strText[256] = {};
	//sprintf_s(strText, "NoRight : %d, NoLeft : %d\n", m_bNoRight, m_bNoLeft);
	//OutputDebugStringA(strText);



	/*if (-1.f == fScale)
	{
		m_bNoRight = true;
	}
	else if (1.f == fScale)
	{
		m_bNoLeft = true;
	}*/

	// 충돌
	// 오른쪽 막힌 상황에서 오른쪽 가기
	if (1.f == fScale && true == m_bNoRight)
	{
		m_pMovement->SetMoveSpeed(0.f);
		m_fNormalSpeed = 0.f;
		// SetWorldPos(m_vNoRight);

		return;
	}
	// 오른쪽 막힌 상황에서 왼쪽 가기
	else if (-1.f == fScale && true == m_bNoRight)
	{
		int a = 0;
		m_pMovement->SetMoveSpeed(500.f);
		m_fNormalSpeed = 500.f;
		m_bEscape = true;

		m_bNoRight = false;
	}
	else if (-1 == fScale && true == m_bNoLeft)
	{
		m_pMovement->SetMoveSpeed(0.f);
		m_fNormalSpeed = 0.f;
		// SetWorldPos(m_vNoLeft);
		return;
	}
	else if (1.f == fScale && true == m_bNoLeft)
	{
		m_pMovement->SetMoveSpeed(500.f);
		m_fNormalSpeed = 500.f;
		m_bEscape = true;
		m_bNoLeft = false;
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
	else
	{
		if (-1.f == fScale && DIR_RIGHT == m_eDirType)
		{
			m_eDirType = DIR_LEFT;
			Reverse(fTime);
		}
		else if (1.f == fScale && DIR_LEFT == m_eDirType)
		{
			m_eDirType = DIR_RIGHT;
			Reverse(fTime);
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
			// 걸으면 먼지

			m_fDustTime = 0.f;
 			DustEffect* dust = m_pScene->SpawnObject<DustEffect>(
				GetWorldPos() - Vector3(0.f, 400.f * 0.12f, 0.f) );
			SAFE_RELEASE(dust);
		}
	}
}




void HollowKnight::Fire(float fTime)
{
	if (PS_DAMAGED == m_eState)
	{
		m_bHealOver = true;
		return;
	}
	// RELEASE

	if (true == m_bFire && false == m_bHealStart)
	{
		SetCurrentState(PS_FIRE);
		m_fHealTime = 0.f;
	}




	m_bHealOver = true;
}

void HollowKnight::Attack(float fTime)
{
	if (PS_DAMAGED == m_eState)
	{
		return;
	}

	HKAttackEffect* attack;

	if (false == m_bAttacking)
	{
		//// TEST
		// CameraShakeOn();



		m_bAttacking = true;

		attack = m_pScene->SpawnObject<HKAttackEffect>(
			GetWorldPos() + GetWorldAxis(AXIS_X) * 100.f * (int)m_eDirType + Vector3(0.f, 10.f, 0.f)
			);

		attack->Flip(m_eDirType);

		CColliderRect* pBody = attack->GetBody();
		pBody->SetCollisionProfile("PlayerProjectile");
		m_fAttackTime += fTime;
		SAFE_RELEASE(attack);

		// SOUND
		EffectSound*	pFireSound = m_pScene->SpawnObject<EffectSound>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
			Vector3(0.f, 0.f, GetRelativeRot().z));

		pFireSound->SetSound("HeroAttack", "HeroAttack.wav");

		SAFE_RELEASE(pFireSound);
	}
	
	SetCurrentState(PS_ATTACK);
}

void HollowKnight::Jump(float fTime)
{
	if (true == m_bFalling)
	{
		return;
	}

	// 점프 시간 제한 
	if (m_fJumpTime >= m_fJumpTotalTime || true == m_bCeiling)
	{
		// SlowGravity();
		JumpOver(fTime);
		m_bCeiling = false;
		m_fGravitySpeed = 20.f;
		return;
	}





	m_fForce = 1000.f;
	m_fGravitySpeed = 20.f;

	if (PS_DAMAGED == m_eState)
	{
		m_fForce = 500.f;
		m_bJumping = true;
		return;
	}


	// 첫 점프
	if (false == m_bJumping)
	{
		m_bColliding = false;

		SetCurrentState(PS_JUMP);

		m_pMovement->SetMoveSpeed(500.f);
		m_fNormalSpeed = 500.f;

		// 큰 먼지 생성
		DustEffect* dust = m_pScene->SpawnObject<DustEffect>(
			GetWorldPos() - Vector3(0.f, 400.f * 0.2f, 0.f));

		dust->SetStaticSize(200.f);
		dust->SetStop();
		SAFE_RELEASE(dust);



		EffectSound*	pFireSound = m_pScene->SpawnObject<EffectSound>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
			Vector3(0.f, 0.f, GetRelativeRot().z));
		pFireSound->SetSound("Jump", "Jump.wav");
		SAFE_RELEASE(pFireSound);
	}
	else if( true == m_bFalling)
	{
		return;
	}

	m_fJumpTime += fTime;

	m_bFalling = false;
	m_bJumping = true;

	m_bOnLand = false;
	m_bHitStage = false;

	if (m_fDustTime <= m_fDustTotalTime * 0.7f)
	{
		m_fDustTime += fTime;
	}
	else
	{
		m_fDustTime = 0.f;
		DustEffect* dust = m_pScene->SpawnObject<DustEffect>(
			GetWorldPos() - Vector3(0.f, 400.f * 0.2f, 0.f));

		dust->SetMaxSize(40.f);

		SAFE_RELEASE(dust);
	}

	// 충돌 관련 점프
	if(false == m_pBody->IsColliding())
	{
		m_bNoRight = false;
		m_bNoLeft = false;
	}

}

// 다 내려옴
void HollowKnight::JumpEnd(float fTime)
{
	m_pMovement->SetMoveSpeed(500.f);
	m_fNormalSpeed = 500.f;

	m_fJumpTime = 0.f;
	m_bFalling = false;
	m_fGravitySpeed = 20.f;

	if (false == m_bHitStage)
	{
		SetCurrentState(PS_LAND);
		m_bHitStage = true;

		EffectSound*	pFireSound = m_pScene->SpawnObject<EffectSound>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
			Vector3(0.f, 0.f, GetRelativeRot().z));
		pFireSound->SetSound("Land_Soft", "Land_Soft.wav");
		SAFE_RELEASE(pFireSound);
	}
}

// RELEASE
// 이제 내려오기 시작
void HollowKnight::JumpOver(float fTime)
{
	m_pMovement->SetMoveSpeed(500.f);
	m_fNormalSpeed = 500.f;
	m_fGravitySpeed = 20.f;

	if (true == m_bCeiling)
	{
		m_bFalling = true;
		m_bJumping = false;
		m_fForce = -300.f;
	}


	else if (false == m_bFalling)
	{
		SetCurrentState(PS_FALL);
		m_bFalling = true;
		m_fForce = 200.f;
		m_bJumping = false;
	}

}



void HollowKnight::Heal(float fTime)
{
	m_fHealTime += fTime;
	m_bHealOver = false;

	if (true == m_bHealStart && false == m_bFire)
	{
		if (PS_BHEAL == m_eState && true == m_pAnimation->IsSequenceEnd())
		{
			SetCurrentState(PS_HEAL);
			m_bIsHealing = true;
		}
		else if (true == m_bHealStart)
		{
			SetCurrentState(PS_BHEAL);

			HealStart* healStart = m_pScene->SpawnObject<HealStart>(
				GetWorldPos() + Vector3(0.f, 0.1f, 0.f)
				);

			SAFE_RELEASE(healStart);
		}

	}


	if (false == m_bIsHealing)
	{
		m_bHealStart = true;
	}
}

















void HollowKnight::SetEffect(HKAttackEffect * attackEffect)
{
 	m_pAttackEffect = attackEffect;
}







void HollowKnight::SetCurrentState(PLAYER_STATE state)
{
	if (state == m_eState)
	{
		return;
	}

	m_eState = state;

	std::string stateName = m_vecStateName[state];
	stateName.append("_HK");

	m_pAnimation->ChangeAnimation(stateName);

	if (PS_WALK == m_eState)
	{
		if (true == m_bOnLand)
		{
			//m_pFootsteps->Play();
		}	
	}
	else
	{
		// m_pFootsteps->StopSO();
	}

	
}

void HollowKnight::ReturnSequence(float fTime)
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
			GetWorldPos() + Vector3(0.f, 0.1f, 0.f)
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

void HollowKnight::UpdateHeal(float fTime)
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

void HollowKnight::Reverse(float fTime)
{
	Flip(m_eDirType);
}


void HollowKnight::SetAnimation()
{
	m_vecStateName.push_back("IDLE");

	m_vecStateName.push_back("BWALK");
	m_vecStateName.push_back("WALK");
	m_vecStateName.push_back("AWALK");

	m_vecStateName.push_back("TURN");

	m_vecStateName.push_back("ATTACK");

	 m_vecStateName.push_back("JUMP");
	 m_vecStateName.push_back("FALL");
	 m_vecStateName.push_back("FALLING");
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
	m_pAnimation->AddAnimation2DSequence("FALLING_HK");
	m_pAnimation->AddAnimation2DSequence("LAND_HK");


	m_pAnimation->AddAnimation2DSequence("BHEAL_HK");
	m_pAnimation->AddAnimation2DSequence("HEAL_HK");
	m_pAnimation->AddAnimation2DSequence("AHEAL_HK");

	m_pAnimation->AddAnimation2DSequence("FIRE_HK");

	m_pAnimation->AddAnimation2DSequence("DAMAGED_HK");
}

void HollowKnight::SetKey()
{
	GET_SINGLE(CInput)->AddAxisKey("MoveX", DIK_RIGHT, 1.f);
	GET_SINGLE(CInput)->AddAxisKey("MoveX", DIK_LEFT, -1.f);
	GET_SINGLE(CInput)->BindAxis<HollowKnight>("MoveX", this, &HollowKnight::MoveX);
			   
	GET_SINGLE(CInput)->AddActionKey("Attack", DIK_X);
	GET_SINGLE(CInput)->BindAction<HollowKnight>("Attack", AKS_PRESS, this, &HollowKnight::Attack);
			   
	GET_SINGLE(CInput)->AddActionKey("Fire", DIK_A);
	GET_SINGLE(CInput)->BindAction<HollowKnight>("Fire", AKS_RELEASE, this, &HollowKnight::Fire);
			   
	GET_SINGLE(CInput)->AddActionKey("Heal", DIK_A);
	GET_SINGLE(CInput)->BindAction<HollowKnight>("Heal", AKS_PUSH, this, &HollowKnight::Heal);
			   



	GET_SINGLE(CInput)->AddActionKey("Jump", DIK_Z);
	GET_SINGLE(CInput)->BindAction<HollowKnight>("Jump", AKS_PUSH, this, &HollowKnight::Jump);

	GET_SINGLE(CInput)->AddActionKey("JumpOver", DIK_Z);
	GET_SINGLE(CInput)->BindAction<HollowKnight>("JumpOver", AKS_RELEASE, this, &HollowKnight::JumpOver);

	GET_SINGLE(CInput)->AddActionKey("NextStage", DIK_P);
	GET_SINGLE(CInput)->BindAction<HollowKnight>("NextStage", AKS_PRESS, this, &HollowKnight::NextStage);

	GET_SINGLE(CInput)->AddActionKey("PrevStage", DIK_O);
	GET_SINGLE(CInput)->BindAction<HollowKnight>("PrevStage", AKS_PRESS, this, &HollowKnight::PrevStage);

	GET_SINGLE(CInput)->AddActionKey("SoundTest", DIK_I);
	GET_SINGLE(CInput)->BindAction<HollowKnight>("SoundTest", AKS_PRESS, this, &HollowKnight::SoundTestOn);

	GET_SINGLE(CInput)->AddActionKey("SoundTest2", DIK_U);
	GET_SINGLE(CInput)->BindAction<HollowKnight>("SoundTest2", AKS_PRESS, this, &HollowKnight::SoundTestOff);
	

	// GET_SINGLE(CInput)->Set(true);

	//GET_SINGLE(CInput)->AddActionKey("Reverse", DIK_R);
	//GET_SINGLE(CInput)->BindAction<HollowKnight>("Reverse", AKS_PUSH, this, &HollowKnight::Reverse);
}

void HollowKnight::SetHP()
{

	for (int i = 0; i < 5; ++i)
	{
		UIHP* hp = m_pScene->SpawnObject<UIHP>(Vector3(330.f + i * 70, 930.f, 2.f));

		m_stackHP.push_back(hp);


	}

	CoinUI* ch = m_pScene->SpawnObject<CoinUI>();
	SAFE_RELEASE(ch);

	HPHead* hh = m_pScene->SpawnObject<HPHead>();
	SAFE_RELEASE(hh);
}

void HollowKnight::UpdateCamera()
{

}




void HollowKnight::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (nullptr == pDest)
	{
		return;
	}

	float y = 0.f;
	float x = 0.f;
	float margin = 0.f;

	if (true == m_bEscape)
	{
		m_fEscapeTime += fTime;

		if (m_fEscapeTime >= m_fEscapeTotalTime)
		{
			m_bEscape = false;
			m_fEscapeTime = 0.f;
		}

		return;
	}



	if (true == pDest->IsStage())
	{
		int playerPos = (int)pSrc->GetIntersect().z;

		if (false == m_bColliding)
		{

			switch (playerPos)
			{
			case 1: // LEFT
				x = pDest->GetColliderSectionMin().x - pSrc->GetRelativeScale().x * 0.5f - margin;
				
				m_vNoRight = Vector3(x, GetWorldPos().y, GetWorldPos().z);
				
				SetWorldPos(m_vNoRight);



				m_bNoRight = true;
				break;
			case 2: // TOP
				// m_pMovement->AddMovement(Vector3(0.f, /*pSrc->GetColliderSectionMin().y - pDest->GetColliderSectionMax().y*/1000.f, 0.f));
				if(false == m_bJumping)
				{ 
					m_bLandUp = true;
					m_fUp = pSrc->GetIntersect().y - pSrc->GetColliderSectionMin().y;
					ClearGravity();
					JumpEnd(fTime);
					m_bOnLand = true;
					m_bCeiling = false;

					y = pDest->GetColliderSectionMax().y + pSrc->GetRelativeScale().y * 0.5f;

					SetWorldPos(Vector3(GetWorldPos().x, y, GetWorldPos().z));
				}
				else
				{

					m_bColliding = false;
				}
				

				break;
			case 3: // RIGHT
				x = pDest->GetColliderSectionMax().x + pSrc->GetRelativeScale().x * 0.5f + margin;

				m_vNoLeft = Vector3(x, GetWorldPos().y, GetWorldPos().z);

				SetWorldPos(m_vNoLeft);
				m_bNoLeft = true;
				break;
			case 4: // BOTTOM
				m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * -2.f, 0.f));
				m_bFalling = true;
				JumpOver(fTime);
				m_bCeiling = true;
				m_bOnLand = false;
				break;
			default:
				BOOM
					break;
			}

			m_bColliding = true;
		}
		else
		{
			switch (playerPos)
			{
			case 1: // LEFT
				x = pDest->GetColliderSectionMin().x - pSrc->GetRelativeScale().x * 0.5f - margin;
				m_vNoRight = Vector3(x, GetWorldPos().y, GetWorldPos().z);

				SetWorldPos(m_vNoRight);
				m_bNoRight = true;
				break;
			case 2: // TOP
				// m_pMovement->AddMovement(Vector3(0.f, /*pSrc->GetColliderSectionMin().y - pDest->GetColliderSectionMax().y*/1000.f, 0.f));
				if (false == m_bJumping)
				{
					m_bLandUp = true;
					m_fUp = pSrc->GetIntersect().y - pSrc->GetColliderSectionMin().y;
					ClearGravity();
					JumpEnd(fTime);
					m_bOnLand = true;
					m_bCeiling = false;

					y = pDest->GetColliderSectionMax().y + pSrc->GetRelativeScale().y * 0.5f - 5.f;

					SetWorldPos(Vector3(GetWorldPos().x, y, GetWorldPos().z));
				}
				else
				{
					m_bColliding = false;
				}
				break;
			case 3: // RIGHT
				x = pDest->GetColliderSectionMax().x + pSrc->GetRelativeScale().x * 0.5f + margin;
				m_vNoLeft = Vector3(x, GetWorldPos().y, GetWorldPos().z);

				SetWorldPos(m_vNoLeft);
				m_bNoLeft = true;
				break;
			case 4: // BOTTOM
				m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * -2.f, 0.f));
				m_bFalling = true;
				JumpOver(fTime);
				m_bCeiling = true;
				m_bOnLand = false;
				break;
			default:
				// BOOM
					break;
			}

			m_bColliding = true;
		}

		return;
	}

	int playerPos = (int)pSrc->GetIntersect().z;

	// 공중에 떠 있는 상태
	if (false == m_bColliding)
	{
		if (true == pDest->IsStage())
		{
			
			switch (playerPos)
			{
			case 1: // LEFT
				x = pDest->GetColliderSectionMin().x - pSrc->GetRelativeScale().x * 0.5f - margin;
				m_vNoRight = Vector3(x, GetWorldPos().y, GetWorldPos().z);

				SetWorldPos(m_vNoRight);
				m_bNoRight = true;
				break;
			case 2: // TOP
				// m_pMovement->AddMovement(Vector3(0.f, /*pSrc->GetColliderSectionMin().y - pDest->GetColliderSectionMax().y*/1000.f, 0.f));
				m_bLandUp = true;
				m_fUp = pSrc->GetIntersect().y - pSrc->GetColliderSectionMin().y;
				ClearGravity();
				JumpEnd(fTime);
				m_bOnLand = true;
				m_bCeiling = false;

				y = pDest->GetColliderSectionMax().y + pSrc->GetRelativeScale().y * 0.5f - 5.f;

				SetWorldPos(Vector3(GetWorldPos().x, y, GetWorldPos().z));

				break;
			case 3: // RIGHT
				x = pDest->GetColliderSectionMax().x + pSrc->GetRelativeScale().x * 0.5f + margin;
				m_vNoLeft = Vector3(x, GetWorldPos().y, GetWorldPos().z);

				SetWorldPos(m_vNoLeft);
				m_bNoLeft = true;
				break;
			case 4: // BOTTOM
				m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * -2.f, 0.f));
				m_bFalling = true;
				JumpOver(fTime);
				m_bCeiling = true;
				m_bOnLand = false;
				break;
			default:
				BOOM
					break;
			}

			m_bColliding = true;
		}
	}
	// 이미 땅바닥 또는 벽에 부딛힌 상태
	else
	{
		if (true == pDest->IsStage())
		{
			switch (playerPos)
			{
			case 1: // LEFT
				m_bNoRight = true;

				x = pDest->GetColliderSectionMin().x - pSrc->GetRelativeScale().x * 0.5f - margin;
				m_vNoRight= Vector3(x, GetWorldPos().y, GetWorldPos().z);

				SetWorldPos(m_vNoRight);

				break;
			case 2: // TOP		
				m_bLandUp = true;
				m_fUp = pSrc->GetIntersect().y - pSrc->GetColliderSectionMin().y;
				ClearGravity();
				JumpEnd(fTime);
				m_bOnLand = true;
				m_bCeiling = false;

				y = pDest->GetColliderSectionMax().y + pSrc->GetRelativeScale().y * 0.5f - 5.f;

				SetWorldPos(Vector3(GetWorldPos().x, y, GetWorldPos().z));
				break;
			case 3: // RIGHT
				x = pDest->GetColliderSectionMax().x + pSrc->GetRelativeScale().x * 0.5f + margin;
				m_vNoLeft = Vector3(x, GetWorldPos().y, GetWorldPos().z);

				SetWorldPos(m_vNoLeft);

				

				m_bNoLeft = true;
				break;
			case 4: // BOTTOM
				m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * -2.f, 0.f));
				m_bFalling = true;
				JumpOver(fTime);
				m_bCeiling = true;
				m_bOnLand = false;
				break;
			default:
				BOOM
					break;
			}
		}
	}







	if (true == pDest->IsMonster() || "MonsterProjectile" == pDest->GetCollisionProfile()->strName)
	{
		if ((PS_DAMAGED == m_eState))
		{
			return;
		}

		GET_SINGLE(CTimerManager)->CreateSlowMotion(5.f);

		m_bDamaged = true;
		
		if (false == m_bInvincible)
		{
			m_bInvincible = true;
		}
		else if (true == m_bInvincible)
		{
			return;
		}


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
				GetWorldPos() + Vector3((float)x, (float)y, 0.f)
				);

			SAFE_RELEASE(bs);
		}

		for (int i = 0; i < 30; ++i)
		{
			int y = RandomNumber::GetRandomNumber(0, 100);
			int x = RandomNumber::GetRandomNumber(0, 100);

			BlackSoftEffect* bs = m_pScene->SpawnObject<BlackSoftEffect>(
				GetWorldPos() + Vector3((float)-x, (float)y, 0.f)
				);

			bs->SetLeft();
			SAFE_RELEASE(bs);
		}




		GetHit* hit = m_pScene->SpawnObject<GetHit>(
			GetWorldPos() + Vector3(0.f, 0.1f, 0.f)
			);

		SAFE_RELEASE(hit);

		BurstEffect* burst = m_pScene->SpawnObject<BurstEffect>(
			GetWorldPos() + Vector3(0.f, 0.1f, 0.f)
			);

		SAFE_RELEASE(burst);

		CrackEffect* crack = m_pScene->SpawnObject<CrackEffect>(
			GetWorldPos() + Vector3(0.f, 0.1f, 0.f)
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

void HollowKnight::BeginOverlap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	/*OutLineCBuffer	tBuffer = {};
	tBuffer.iPixelSize = 5;

	Animation2DFrameInfo	tFrameInfo = m_pAnimation->GetAnimFrame();

	tBuffer.vScale = Vector2(m_pMesh->GetWorldScale().x, m_pMesh->GetWorldScale().y);
	tBuffer.vImageSize = tFrameInfo.vEnd - tFrameInfo.vStart;*/

	// m_pMesh->UpdateMaterialCBufferNode(OUTLINE_CBUFFER, &tBuffer);

}

void HollowKnight::EndOverlap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	// OutLineCBuffer	tBuffer = {};


	// m_pMesh->UpdateMaterialCBufferNode(OUTLINE_CBUFFER, &tBuffer);

	if (nullptr == pDest)
	{
		return;
	}

	if (true == pDest->IsStage())
	{
		m_bColliding = false;
		m_bNoLeft = false;
		m_bNoRight = false;
		m_bCeiling = false;
		m_bOnLand = false;

		m_fNormalSpeed = 500.f;
		m_pMovement->SetMoveSpeed(m_fNormalSpeed);
	}
}




///////////////////////////////////////////////////////////////////////////




void HollowKnight::CameraControl(float fTime)
{


	float maxX = (m_iStageNumber-1) * 10000.f + m_fStageSizeX - _RESOLUTION.iWidth * 0.5f; // 우
	float maxY = 0.f - _RESOLUTION.iHeight * 0.5f - 100.f; // 상
	float minX = (m_iStageNumber - 1) * 10000.f + _RESOLUTION.iWidth * 0.5f; // 좌
	float minY = -m_fStageSizeY + _RESOLUTION.iHeight * 0.5f - 100.f; // 하

	bool check = false;

	Vector3 pos = GetWorldPos();

	float newX = pos.x;
	float newY = pos.y;
	float newZ = pos.z;

	// 우 보다 크면 고정
	if (pos.x >= maxX)
	{
		//newX = maxX;
		check = true;

		// m_pCamera->SetRelativePos(maxX + maxX - newX, _RESOLUTION.iHeight / -2.f + 100.f, -10.f);
		m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f + maxX - newX, _RESOLUTION.iHeight / -2.f + 100.f, -10.f);

		// 상 보다 크면 고정
		if (pos.y >= maxY)
		{
			check = true;

			m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f + maxX - newX, _RESOLUTION.iHeight / -2.f + 100.f + maxY - newY, -10.f);
		}
		else if (pos.y <= minY)
		{
			m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f + maxX - newX, _RESOLUTION.iHeight / -2.f + 100.f + minY - newY, -10.f);

			check = true;
		}
	}
	// 좌 보다 작으면 고정
	else if (pos.x <= minX)
	{
		//newX = minX;
		check = true;

		m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f + minX - newX, _RESOLUTION.iHeight / -2.f + 100.f, -10.f);

		// 상 보다 크면 고정
		if (pos.y >= maxY)
		{
			check = true;

			m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f + minX - newX, _RESOLUTION.iHeight / -2.f + 100.f + maxY - newY, -10.f);
		}
		else if (pos.y <= minY)
		{
			m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f + minX - newX, _RESOLUTION.iHeight / -2.f + 100.f + minY - newY, -10.f);

			check = true;
		}
	}
	else
	{
		if (pos.y >= maxY)
		{
			check = true;

			m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f , _RESOLUTION.iHeight / -2.f + 100.f + maxY - newY, -10.f);
		}
		else if (pos.y <= minY)
		{
			m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f , _RESOLUTION.iHeight / -2.f + 100.f + minY - newY, -10.f);

			check = true;
		}
	}

	


	// 바꾸기
	if (true == check)
	{
		// m_pCamera->SetWorldPos(newX, newY, newZ);
		// m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f + minX - newX, _RESOLUTION.iHeight / -2.f + 100.f, -10.f);
	}
	else
	{
		m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f, _RESOLUTION.iHeight / -2.f + 100.f, -10.f);
	}




	

}

void HollowKnight::CameraShake(float fTime)
{
	if (true == m_bShake)
	{
		//// 처음 들어옴
		if (0.f == m_fShakeTime)
		{
			
		}

		m_vPrevPos = m_pCamera->GetRelativePos();

		float start = 0.1f;
		float gap = 0.05f;

		m_fShakeTime += fTime;

		// 90도를 30분의 1로 나눈다.
		float x = RandomNumber::GetRandomNumber(1, m_iIntensity) - 1;
		float y = RandomNumber::GetRandomNumber(1, m_iIntensity) - 1;

		// x *= 30.f;
		// y *= 30.f;

		int dirX = RandomNumber::GetRandomNumber(1, 2);
		int dirY = RandomNumber::GetRandomNumber(1, 2);

		if (2 == dirX)
		{
			dirX = -1;
		}
		if (2 == dirY)
		{
			dirY = -1;
		}

		m_pCamera->SetRelativePos(m_vPrevPos + Vector3(GetWorldAxis(AXIS_X) * dirX * x + GetWorldAxis(AXIS_Y) * dirY * y));

		if (m_fShakeTime >= m_fShakeTotalTime)
		{
			m_fShakeTime = 0.f;
			m_bShake = false;
		}
		//else if (m_fShakeTime <= start) // 0.1
		//{
		//	m_pCamera->
		//}
		//else if (m_fShakeTime >= start + gap) // 0.2
		//{

		//}
		//else if (m_fShakeTime >= start + gap * 2) // 3
		//{

		//}
		//else if (m_fShakeTime >= start + gap * 3) // 4
		//{

		//}
		//else if (m_fShakeTime >= start) // 5
		//{

		//}
	}



}

void HollowKnight::CameraShakeOn(float fSetTime, int iIntensity)
{
	if (m_iStageNumber == 5 && iIntensity == 10)
	{
		return;
	}

	m_bShake = true;
	m_fShakeTotalTime = fSetTime;
	m_iIntensity = iIntensity;
}




void HollowKnight::SetStage(int iStage, bool bStart)
{
	/*DESTROY_SINGLE(CInput);
	DESTROY_SINGLE(CCollisionManager);*/

	// GET_SINGLE(CCollisionManager)->SetSkip(true);

	/*CScene*	pNextScene = GET_SINGLE(CSceneManager)->CreateNextScene();

	pNextScene->SetGameMode<HKMode>();
	HKMode* mode = (HKMode*)pNextScene->GetGameMode();


	mode->SetMode(iStage, bStart, iHP, iCoin);*/

	PlaceAt(iStage, bStart);

	m_iStageNumber = iStage;
}

void HollowKnight::GoToNext()
{
	m_bNext = true;
}

void HollowKnight::GoToPrev()
{
	m_bPrev = true;
}

void HollowKnight::NextStage(float fTime)
{
	SetStage(++m_iStageNumber, true);
	m_bNext = false;
}

void HollowKnight::PrevStage(float fTime)
{
	SetStage(--m_iStageNumber, false);
	m_bNext = false;
}


void HollowKnight::PlaceStart()
{
	SetStage(m_iStageNumber, true);
}

void HollowKnight::SetSoulEffect(float fTime)
{

		int randomX =  RandomNumber::GetRandomNumberTime(1, 3840) - 1920;
		int randomY = RandomNumber::GetRandomNumberTime(1, 2160) - 1080;

		SoulParticle* soul = m_pScene->SpawnObject<SoulParticle>(
			GetWorldPos() + Vector3(randomX, randomY, 0.f)
			);

		SAFE_RELEASE(soul);
}

void HollowKnight::SetBugEffect(float fTime)
{
	int prob = RandomNumber::GetRandomNumberTime(1, 30);

	// 200분의 1
	if (1 == prob)
	{
		float randomX = (float)RandomNumber::GetRandomNumberTime(1, 1920) - 960;
		float randomY = (float)RandomNumber::GetRandomNumberTime(1, 1080) - 540;

		// -960~960
		// 음수라면
		if (randomX <= 0)
		{
			randomX -= 960.f;
		}
		else
		{
			randomX += 960.f;
		}

		if (randomY <= 0)
		{
			randomY -= 540.f;
		}
		else
		{
			randomY += 540.f;
		}

		BugParticle* soul = m_pScene->SpawnObject<BugParticle>(
			GetWorldPos() + Vector3(randomX, randomY, 0.f)
			);

		SAFE_RELEASE(soul);

	}

	
}

//void HollowKnight::SetBright(float fTime)
//{
//	if (true == m_bBright)
//	{
//		m_fBrightTime += fTime;
//
//		if (m_fBrightTime >= m_fBrightTotalTime)
//		{
//			m_fBrightTime = 0.f;
//			m_bBright = false;
//		}
//
//		// 어두워지기
//		if (m_fBrightTime >= m_fBrightTotalTime * 0.5f)
//		{
//
//		}
//		// 밝아지기
//	}
//}



void HollowKnight::SoundTestOn(float fTime)
{
	
}

void HollowKnight::SoundTestOff(float fTime)
{
	m_pFootsteps->StopSO();
}

void HollowKnight::SetEffectSound(const string& strKey, const char* pFileName)
{
	EffectSound*	pFireSound = m_pScene->SpawnObject<EffectSound>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		Vector3(0.f, 0.f, GetRelativeRot().z));

	pFireSound->SetSound(strKey, pFileName);

	SAFE_RELEASE(pFireSound);
}

