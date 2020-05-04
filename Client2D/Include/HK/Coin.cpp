#include "Coin.h"


#include "EngineGlobals.h"

#include "Scene/Scene.h"
#include "Component/CameraComponent.h"
#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"



#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderRect.h"


#include "../RandomNumber.h"

#include "HollowKnight.h"

#include "CoinEffect.h"

#include "EffectSound.h"

Coin::Coin()
	: m_iStyle(0)
	, m_pMesh(nullptr)
	, m_pMovement(nullptr)
	, m_pChildMesh(nullptr)
	, m_pBody(nullptr)
	, m_pAnimation(nullptr)
{


	m_fRot = (float)RandomNumber::GetRandomNumber(0, 360);
}

Coin::~Coin()
{
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pChildMesh);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pAnimation);
}

bool Coin::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}



	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);
	SetRoot(m_pMesh);



	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);
	SetPhysics(true);

	// CHILD MESH
	m_pChildMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pChildMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);

	// CHILD MATERIAL
	int style = RandomNumber::GetRandomNumber(1, 4);
	CMaterial* pMaterial = nullptr;


	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pChildMesh->SetMaterial(pMaterial);
		

	SAFE_RELEASE(pMaterial);



	// ROT PIVOT
	// m_pRotPivot = CreateComponent<CSceneComponent>("RotPivot");


	// m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);
	// m_pRotPivot->AddChild(m_pChildMesh, TR_POS | TR_ROT);

	m_pChildMesh->SetRelativeScale(60.f, 60.f, 0.f);
	m_pChildMesh->SetRelativePos(0.f, 0.f, 0.f);
	m_pChildMesh->SetPivot(0.5f, 0.5f, 0.f);

	/*if (0 == m_iStyle)
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Coin0");
	}
	else if (1 == m_iStyle)
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Coin1");
	}
	else
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Coin2");
	}*/
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Empty");

	m_pMesh->SetMaterial(pMaterial);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(50.f, 50.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);


	int speed = RandomNumber::GetRandomNumber(400, 600);

	m_pMovement->SetMoveSpeed((float)speed);

	m_fMoveSpeed = speed;


	// COLLIDER
	m_pBody = CGameObject::CreateComponent<CColliderRect>("ParticleBody");


	m_pBody->SetExtent(30.f, 30.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	m_pBody->SetCollisionProfile("Object");

	m_pBody->AddBlockCallback<Coin>(this, &Coin::OnBlock);

	m_pMesh->AddChild(m_pBody, TR_POS);


	// Áß·Â Àû¿ë
	CGameObject::SetPhysics(true);
	// SetForce(m_fCurrentForce * 1.2f);

	m_fGravitySpeed = 30.f;


	m_pAnimation->AddAnimation2DSequence("COIN");
	m_pMesh->SetAnimation2D(m_pAnimation);
	m_pAnimation->ChangeAnimation("COIN");

	m_iDir = RandomNumber::GetRandomNumber(1, 2);

	if (2 == m_iDir)
	{
		m_iDir = -1;
	}


	return true;
}

void Coin::Begin()
{
	CGameObject::Begin();
}

void Coin::Update(float fTime)
{
	CGameObject::Update(fTime);

	// ½Ã°£
	m_fLifeTime += fTime;

	if (m_fLifeTime >= m_fDeathTime)
	{
		Kill();

		return;
	}




	if (true == m_bStop)
	{
		ClearGravity();
		return;
	}














	// ¶¥¿¡ ´êÀ¸¸é
	if (true == m_bOnLand)
	{
		ClearGravity();
		return;
	}

	// Á¡ÇÁ
	if (false == m_bJump)
	{
		ClearGravity();

		m_fCurrentForce = RandomNumber::GetRandomNumber(10, 400);

		m_fForce = m_fCurrentForce;

		m_bJump = true;
		m_bOnLand = false;
	}

	// m_fForce -= (m_fOriginForce * m_fOriginForce);

	// ¿À¸¥ÂÊ
	if (1 == m_iDir)
	{
		if (true == m_bNoRight)
		{
			m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * -1.f);
			m_fMoveSpeed *= 0.6f;
			m_pMovement->SetMoveSpeed(m_fMoveSpeed);

			m_iDir = 2;
			m_bNoRight = false;
		}
		else
		{
			m_pMovement->AddMovement(GetWorldAxis(AXIS_X));
		}

	}
	// ¿ÞÂÊ
	else
	{
		if (true == m_bNoLeft)
		{
			m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * -1.f);
			m_fMoveSpeed *= 0.6f;
			m_pMovement->SetMoveSpeed(m_fMoveSpeed);

			m_iDir = 1;
			m_bNoLeft = false;
		}
		else
		{
			m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * -1.f);
		}
	}
}

void Coin::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void Coin::MoveX()
{

}

void Coin::JumpEnd(float fTime)
{
	m_fForce = 0.f;
}

void Coin::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (nullptr == pDest)
	{
		return;
	}


	if (true == pDest->IsPlayer())
	{
		HollowKnight* hk = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();

		if (false == m_bCoin)
		{
			hk->AddCoinCount();
			m_bCoin = true;

			CoinEffect* ce = m_pScene->SpawnObject<CoinEffect>(GetWorldPos() + Vector3(0.f, 0.f, -1.f));
			SAFE_RELEASE(ce);



			EffectSound*	pFireSound = m_pScene->SpawnObject<EffectSound>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
				Vector3(0.f, 0.f, GetRelativeRot().z));

			pFireSound->SetSound("Coin", "Coin.wav");

			SAFE_RELEASE(pFireSound);
		}

		Kill();

		return;
	}



	// if ("Stage" == pDest->GetCollisionProfile()->strName)
	if (true == pDest->IsStage())
	{
		int playerPos = (int)pSrc->GetIntersect().z;

		switch (playerPos)
		{
		case 1: // LEFT
			m_pMovement->AddMovement(Vector3(pSrc->GetIntersect().x * -2.f, 0.f, 0.f));
			m_bNoRight = true;

			break;
		case 2: // TOP
			m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * 2.f, 0.f));
			ClearGravity();
			JumpEnd(fTime);
			m_bOnLand = true;
			m_bNoRight = false;
			m_bNoLeft = false;


			break;
		case 3: // RIGHT
			m_pMovement->AddMovement(Vector3(pSrc->GetIntersect().x * 2.f, 0.f, 0.f));
			m_bNoLeft = true;

			break;
		case 4: // BOTTOM
			m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * -2.f, 0.f));

			// m_bCeiling = true;
			break;
		default:
			BOOM
				break;
		}

		// ¹Ù¿î½º
		if (true == m_bJump && true == m_bOnLand)
		{
			m_fCurrentForce = m_fCurrentForce * 0.33f;
			m_fMoveSpeed = m_fMoveSpeed * 0.33f;
			ClearGravity();

			if (m_fCurrentForce <= 10.f)
			{
				// ¸ØÃã, ³¡
				m_bJump = false;
				m_bStop = true;
			}
			// ´Ù½Ã ÇÑ¹ø Æ¨±è
			else
			{
				float y = pDest->GetColliderSectionMax().y + pSrc->GetRelativeScale().y * 0.5f + 5.f;

				SetWorldPos(Vector3(GetWorldPos().x, y, GetWorldPos().z));

				SetForce(m_fCurrentForce);
				m_pMovement->SetMoveSpeed(m_fMoveSpeed);
				m_bJump = true;
				m_bOnLand = false;

				return;
			}
		}

		if (false == m_bNoLeft && false == m_bNoRight)
		{
			ClearGravity();
			JumpEnd(fTime);
		}


	}
}

void Coin::SetDirection(int dir)
{
	m_iDir = dir;
}
