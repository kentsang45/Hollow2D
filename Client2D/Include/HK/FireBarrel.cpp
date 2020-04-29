#include "FireBarrel.h"


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

#include "GetHit.h"

FireBarrel::FireBarrel()
	: m_iStyle(0)
	, m_pMesh(nullptr)
	, m_pMovement(nullptr)
	, m_pRotPivot(nullptr)
	, m_pChildMesh(nullptr)
	, m_pBody(nullptr)
{


	m_fRot = (float)RandomNumber::GetRandomNumber(0, 360);
}

FireBarrel::~FireBarrel()
{
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pRotPivot);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pChildMesh);
	SAFE_RELEASE(m_pBody);
}

bool FireBarrel::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}



	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
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
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("FireBarrel");
	m_pChildMesh->SetMaterial(pMaterial);
	

	SAFE_RELEASE(pMaterial);



	// ROT PIVOT
	m_pRotPivot = CreateComponent<CSceneComponent>("RotPivot");


	m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);
	m_pRotPivot->AddChild(m_pChildMesh, TR_POS | TR_ROT);

	m_fScale = (float)RandomNumber::GetRandomNumber(80, 90);


	// 100~200
	m_pChildMesh->SetRelativeScale(m_fScale, m_fScale, 0.f);
	m_pChildMesh->SetRelativePos(0.f, 0.f, 0.f);
	m_pChildMesh->SetPivot(0.5f, 0.5f, 0.f);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Empty");

	m_pMesh->SetMaterial(pMaterial);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(1.f, 1.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);


	m_fMoveSpeed = RandomNumber::GetRandomNumber(100, 200);
	m_iDir = RandomNumber::GetRandomNumber(1, 2) - 2;
	m_fRotSpeed = RandomNumber::GetRandomNumber(2, 4);


	if (0 == m_iDir)
	{
		m_iDir = 1;
	}

	Flip(m_iDir);



	// COLLIDER
	m_pBody = CGameObject::CreateComponent<CColliderRect>("ParticleBody");


	m_pBody->SetExtent(100.f, 100.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	m_pBody->SetCollisionProfile("MonsterProjectile");

	m_pBody->AddBlockCallback<FireBarrel>(this, &FireBarrel::OnBlock);

	m_pMesh->AddChild(m_pBody, TR_POS);


	// Áß·Â Àû¿ë
	CGameObject::SetPhysics(true);
	// SetForce(m_fCurrentForce * 1.2f);

	m_fGravitySpeed = 20.f;

	m_pMovement->SetRotationSpeed(10000.f);



	return true;
}

void FireBarrel::Begin()
{
	CGameObject::Begin();
}

void FireBarrel::Update(float fTime)
{
	CGameObject::Update(fTime);

	// ½Ã°£
	m_fLifeTime += fTime;

	m_fGravitySpeed = .1f;

	if (m_fLifeTime >= m_fDeathTime)
	{
		

		return;
	}

	m_pRotPivot->AddRelativeRotationZ(-180.f * fTime * m_fRotSpeed * m_iDir);	
}

void FireBarrel::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void FireBarrel::MoveX()
{

}

void FireBarrel::JumpEnd(float fTime)
{
	m_fForce = 0.f;
}

void FireBarrel::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	//if (nullptr == pDest)
	//{
	//	return;
	//}

	GetHit* gh = m_pScene->SpawnObject<GetHit>(GetWorldPos() + Vector3(0.f, 50.f, 0.f));
	gh->SetAnimation(1);
	SAFE_RELEASE(gh);


	Kill();


	//// if ("Stage" == pDest->GetCollisionProfile()->strName)
	//if (true == pDest->IsStage())
	//{
	//	int playerPos = (int)pSrc->GetIntersect().z;

	//	switch (playerPos)
	//	{
	//	case 1: // LEFT
	//		m_pMovement->AddMovement(Vector3(pSrc->GetIntersect().x * -2.f, 0.f, 0.f));
	//		m_bNoRight = true;

	//		break;
	//	case 2: // TOP
	//		m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * 2.f, 0.f));
	//		ClearGravity();
	//		JumpEnd(fTime);
	//		m_bOnLand = true;
	//		m_bNoRight = false;
	//		m_bNoLeft = false;


	//		break;
	//	case 3: // RIGHT
	//		m_pMovement->AddMovement(Vector3(pSrc->GetIntersect().x * 2.f, 0.f, 0.f));
	//		m_bNoLeft = true;

	//		break;
	//	case 4: // BOTTOM
	//		m_pMovement->AddMovement(Vector3(0.f, pSrc->GetIntersect().y * -2.f, 0.f));

	//		// m_bCeiling = true;
	//		break;
	//	default:
	//		BOOM
	//			break;
	//	}

	//	// ¹Ù¿î½º
	//	if (true == m_bJump && true == m_bOnLand)
	//	{
	//		m_fCurrentForce = m_fCurrentForce * 0.33f;
	//		m_fMoveSpeed = m_fMoveSpeed * 0.33f;
	//		ClearGravity();

	//		if (m_fCurrentForce <= 10.f)
	//		{
	//			// ¸ØÃã, ³¡
	//			m_bJump = false;
	//			m_bStop = true;
	//		}
	//		// ´Ù½Ã ÇÑ¹ø Æ¨±è
	//		else
	//		{
	//			float y = pDest->GetColliderSectionMax().y + pSrc->GetRelativeScale().y * 0.5f + 5.f;

	//			SetWorldPos(Vector3(GetWorldPos().x, y, GetWorldPos().z));

	//			SetForce(m_fCurrentForce);
	//			m_pMovement->SetMoveSpeed(m_fMoveSpeed);
	//			m_bJump = true;
	//			m_bOnLand = false;

	//			return;
	//		}
	//	}

	//	if (false == m_bNoLeft && false == m_bNoRight)
	//	{
	//		ClearGravity();
	//		JumpEnd(fTime);
	//	}


	//}
}

void FireBarrel::SetDirection(int dir)
{
	m_iDir = dir;
}

