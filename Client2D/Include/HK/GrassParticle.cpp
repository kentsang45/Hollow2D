#include "GrassParticle.h"


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

#include "GrassParticleMesh.h"

GrassParticle::GrassParticle()
	: m_iStyle(0)
	, m_pMesh(nullptr)
	, m_pMovement(nullptr)
	, m_fJumpTime(0.f)
	, m_pRotPivot(nullptr)
	, m_pChildMesh(nullptr)
{


	m_fRot = (float)RandomNumber::GetRandomNumber(0, 360);
}

GrassParticle::~GrassParticle()
{
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pRotPivot);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pChildMesh);
}

bool GrassParticle::Init()
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
	int style = RandomNumber::GetRandomNumber(1, 3);
	CMaterial* pMaterial = nullptr;
	switch (style)
	{
	case 1:
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticle0");
		m_pChildMesh->SetMaterial(pMaterial);
		break;

	case 2:
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticle1");
		m_pChildMesh->SetMaterial(pMaterial);
		break;

	case 3:
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticle2");
		m_pChildMesh->SetMaterial(pMaterial);
		break;

	default:
		BOOM;
		break;
	}
	
	SAFE_RELEASE(pMaterial);



	// ROT PIVOT
	m_pRotPivot = CreateComponent<CSceneComponent>("RotPivot");


	m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);
	m_pRotPivot->AddChild(m_pChildMesh, TR_POS | TR_ROT);

	m_pChildMesh->SetRelativeScale(50.f, 50.f, 0.f);
	m_pChildMesh->SetRelativePos(0.f, 0.f, 0.f);
	m_pChildMesh->SetPivot(0.5f, 0.5f, 0.f);

	/*if (0 == m_iStyle)
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticle0");
	}
	else if (1 == m_iStyle)
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticle1");
	}
	else
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticle2");
	}*/
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Empty");
	
	m_pMesh->SetMaterial(pMaterial);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(1.f, 1.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	
	int speed = RandomNumber::GetRandomNumber(10, 50);

	m_pMovement->SetMoveSpeed((float)speed);


	return true;
}

void GrassParticle::Begin()
{
	CGameObject::Begin();
}

void GrassParticle::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (false == m_bJumping)
	{
		// m_fOriginForce = 2.f;
		m_fForce = 400;

		m_pMovement->SetRotationSpeed(100.f);
		m_fGravitySpeed = 1.f;

		m_iDir = RandomNumber::GetRandomNumber(1, 2);
		m_iRotDir = RandomNumber::GetRandomNumber(1, 2);

		// m_pRotPivot->SetRotationSpeed
	}

	// 좌 또는 우로 움직이기
	MoveX();
	
	// 빙글 돌기
	if (1 == m_iRotDir)
	{
		m_pRotPivot->AddRelativeRotationZ(180.f * fTime);
	}
	else
	{
		m_pRotPivot->AddRelativeRotationZ(-180.f * fTime);
	}
	
	

	if (m_fForce < 140)
	{
		m_fGravitySpeed -= 0.06f;

		if (m_fGravitySpeed < 0.02f)
		{
			m_fGravitySpeed = 0.02f;
		}
	}
	



	// 하강
	m_fJumpTime += fTime;
	m_bJumping = true;





	if (m_fJumpTime >= 2.f)
	{
		Kill();
	}


}

void GrassParticle::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void GrassParticle::MoveX()
{
	if (1 == m_iDir)
	{
		m_pMovement->AddMovement(GetWorldAxis(AXIS_X));
	}
	else
	{
		m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * -1.f);
	}
}
