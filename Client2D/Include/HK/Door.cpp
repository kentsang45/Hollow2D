#include "Door.h"


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



Door::Door()
	: m_iStyle(0)
	, m_pMesh(nullptr)
	, m_pBody(nullptr)
	, m_pAnimation(nullptr)
{


	m_fRot = (float)RandomNumber::GetRandomNumber(0, 360);
}

Door::~Door()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pAnimation);
}

bool Door::Init()
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


	// CHILD MESH

	SAFE_RELEASE(pMesh);

	// CHILD MATERIAL
	int style = RandomNumber::GetRandomNumber(1, 4);
	CMaterial* pMaterial = nullptr;

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pMesh->SetMaterial(pMaterial);
	

	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(90.f, 331.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);



	// COLLIDER
	m_pBody = CGameObject::CreateComponent<CColliderRect>("ParticleBody");


	m_pBody->SetExtent(90.f, 331.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	m_pBody->SetCollisionProfile("Object");
	m_pBody->AddBlockCallback<Door>(this, &Door::OnBlock);

	m_pBody->SetStage(true);

	m_pMesh->AddChild(m_pBody, TR_POS);


	// 중력 적용
	// SetForce(m_fCurrentForce * 1.2f);

	m_fGravitySpeed = 30.f;


	m_pAnimation->AddAnimation2DSequence("DOOR_OPEN");
	m_pAnimation->AddAnimation2DSequence("DOOR_CLOSE");
	m_pMesh->SetAnimation2D(m_pAnimation);
	m_pAnimation->ChangeAnimation("DOOR_CLOSE");


	return true;
}

void Door::Begin()
{
	CGameObject::Begin();
}

void Door::Update(float fTime)
{
	CGameObject::Update(fTime);




}

void Door::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void Door::MoveX()
{

}

void Door::JumpEnd(float fTime)
{
	m_fForce = 0.f;
}

void Door::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (nullptr == pDest)
	{
		return;
	}




}

void Door::SetDirection(int dir)
{
	Flip(dir);
}



void Door::PlaceAt(int sizeX, int sizeY, float leftTopX, float leftTopY, int iStyle, bool bSwitch)
{

	/*float X = 40000.f + (sizeX * 50.f) * 0.5f + leftTopX * 50.f;
	float Y = (sizeY * 50.f) * 0.5f + leftTopY * 50.f;

	SetRelativePos(X, -Y, 0.f);*/

	// m_pBody->SetExtent(sizeX * 50.f, sizeY * 50.f);
}

