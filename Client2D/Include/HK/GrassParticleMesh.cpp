#include "GrassParticleMesh.h"


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

GrassParticleMesh::GrassParticleMesh()
	: m_pMesh(nullptr)
	, m_iStyle(0)
	, m_pMovement(nullptr)
	, m_fJumpTime(0.5f)
	, m_pRotPivot(nullptr)
{


	m_fRot = (float)RandomNumber::GetRandomNumber(0, 360);
}

GrassParticleMesh::~GrassParticleMesh()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pRotPivot);
}

bool GrassParticleMesh::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}



	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);

	CMaterial* pMaterial = nullptr;

	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);
	SetPhysics(true);



	m_pRotPivot = CreateComponent<CSceneComponent>("RotPivot");

	// m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);
	m_pRotPivot->AddChild(m_pMesh, TR_POS | TR_ROT);

	m_pRotPivot->SetWorldPos(Vector3::Zero);

	if (0 == m_iStyle)
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticleMesh0");
	}
	else if (1 == m_iStyle)
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticleMesh1");
	}
	else
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("GrassParticleMesh2");
	}


	m_pMesh->SetMaterial(pMaterial);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(50.f, 50.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	SetRoot(m_pMesh);


	return true;
}

void GrassParticleMesh::Begin()
{
	CGameObject::Begin();
}

void GrassParticleMesh::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (false == m_bJumping)
	{
		// m_fOriginForce = 2.f;
		m_fForce = 400;

		m_pMovement->SetMoveSpeed(10.f);
		m_pMovement->SetRotationSpeed(100.f);
		m_fGravitySpeed = 0.0002f;

		m_iDir = RandomNumber::GetRandomNumber(1, 2);

		// m_pRotPivot->SetRotationSpeed
	}

	// m_pRotPivot->SetWorldPos(m_pMesh->GetWorldPos());
	// m_pRotPivot->AddRelativeRotationZ(180.f * fTime);

	m_pMovement->AddRotationZ(1.f);

	if (1 == m_iDir)
	{
		m_fRot -= 0.2f;
	}
	else
	{
		m_fRot += 0.2f;
	}

	// m_pMesh->SetRelativeRotationZ(m_fRot);


	m_fJumpTime += fTime;
	m_bJumping = true;

	if (m_fJumpTime >= 2.f)
	{
		Kill();
	}


}

void GrassParticleMesh::Render(float fTime)
{
	CGameObject::Render(fTime);
}





