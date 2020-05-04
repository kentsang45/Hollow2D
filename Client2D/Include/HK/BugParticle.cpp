#include "BugParticle.h"


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

BugParticle::BugParticle()
	: m_iStyle(0)
	, m_pMesh(nullptr)
	, m_pMovement(nullptr)
	,  m_pAnimation(nullptr)
	, m_pRotPivot(nullptr)
	, m_pChildMesh(nullptr)
{

}

BugParticle::~BugParticle()
{
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pRotPivot);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pChildMesh);
	SAFE_RELEASE(m_pAnimation);
}

bool BugParticle::Init()
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


	// CHILD MESH
	m_pChildMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pChildMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);

	// CHILD MATERIAL
	int style = RandomNumber::GetRandomNumber(1, 4);



	



	CMaterial* pMaterial = nullptr;


	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMaterial");
	m_pChildMesh->SetMaterial(pMaterial);
		
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	m_pAnimation->AddAnimation2DSequence("FLY_PARTICLE");

	m_pAnimation->AddAnimation2DSequence("TF_PARTICLE");
	m_pAnimation->AddAnimation2DSequence("FB_PARTICLE");
	m_pAnimation->AddAnimation2DSequence("SPIDER_PARTICLE");


	m_pChildMesh->SetAnimation2D(m_pAnimation);

	SAFE_RELEASE(pMaterial);

	

	// ROT PIVOT
	m_pRotPivot = CreateComponent<CSceneComponent>("RotPivot");


	m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);
	m_pRotPivot->AddChild(m_pChildMesh, TR_POS | TR_ROT);

	/*if (1 == style)
	{
		m_pChildMesh->SetRelativeScale(50.f, 50.f, 0.f);
	}
	else
	{
		m_pChildMesh->SetRelativeScale(150.f, 150.f, 0.f);
	}*/

	float scale = (float)RandomNumber::GetRandomNumberTime(100.f, 600.f);

	m_pChildMesh->SetRelativeScale(scale, scale, 0.f);
	

	m_pChildMesh->SetRelativePos(0.f, 0.f, 0.f);
	m_pChildMesh->SetPivot(0.5f, 0.5f, 0.f);

	/*if (0 == m_iStyle)
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BugParticle0");
	}
	else if (1 == m_iStyle)
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BugParticle1");
	}
	else
	{
		pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BugParticle2");
	}*/
	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Empty");

	m_pMesh->SetMaterial(pMaterial);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(1.f, 1.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);


	int speed = RandomNumber::GetRandomNumber(1500, 3000);

	m_pMovement->SetMoveSpeed((float)speed);



	// float ran = (float)RandomNumber::GetRandomNumber(1, 360);
	// m_pRotPivot->AddRelativeRotationZ(ran);




	switch (style)
	{
	case 1:
		m_pAnimation->ChangeAnimation("FLY_PARTICLE");
		break;
	case 2:
		m_pAnimation->ChangeAnimation("TF_PARTICLE");
		break;	
	case 3:
		m_pAnimation->ChangeAnimation("FB_PARTICLE");
		break;
	case 4:
		m_pAnimation->ChangeAnimation("SPIDER_PARTICLE");
		break;
	}


	float axisX = RandomNumber::GetRandomNumberTime(1, 30) - 1;
	float axisY = RandomNumber::GetRandomNumberTime(1, 30) - 1;

	axisX *= 30.f;
	axisY *= 30.f;

	m_iDir = RandomNumber::GetRandomNumber(1, 2);

	if (2 == m_iDir)
	{
		m_iDir = -1;
	}

	int iDirY = RandomNumber::GetRandomNumber(1, 2);

	if (2 == iDirY)
	{
		iDirY = -1;
	}

	m_vVelo = GetWorldAxis(AXIS_X) * m_iDir * axisX + GetWorldAxis(AXIS_Y) * axisY * iDirY;

	if (m_vVelo.x < 0)
	{
		Flip(-1);
	}



	return true;
}

void BugParticle::Begin()
{
	CGameObject::Begin();
}

void BugParticle::Update(float fTime)
{
	CGameObject::Update(fTime);

	m_pMovement->AddMovement(m_vVelo);

	m_fLifeTime += fTime;

	if (m_fLifeTime >= 5.f)
	{
		Kill();
	}

}

void BugParticle::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void BugParticle::MoveX()
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
