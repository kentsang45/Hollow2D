#include "Switch.h"

#include "../Client.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"
#include "Component/CameraComponent.h"
#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"



#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderRect.h"

#include "RockParticle.h"
#include "BarrelParticle.h"

#include "../RandomNumber.h"

#include "HollowKnight.h"
#include "FalseKing.h"
#include "BossText.h"
#include "Door.h"

Switch::Switch()
	: m_pMesh(nullptr)
	, m_pBody(nullptr)
	// , m_strAniName("Switch")

{


}

Switch::~Switch()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pBody);

}

bool Switch::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}


	m_pBody = CreateComponent<CColliderRect>("SwitchBody");

	m_pBody->AddBeginOverlapCallback<Switch>(this, &Switch::BeginOverlap);
	m_pBody->AddBlockCallback<Switch>(this, &Switch::OnBlock);

	m_pBody->SetCollisionProfile("Object");


	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);


	m_pMesh->AddChild(m_pBody, TR_POS);


	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Empty");
	m_pMesh->SetMaterial(pMaterial);
	SAFE_RELEASE(pMaterial);




	m_pMesh->SetRelativeScale(1.f, 1.f, 1.f);
	m_pBody->SetExtent(50.f, 100.f);

	m_iSizeX = 250;
	m_iSizeY = 250;


	m_pBody->SetPivot(0.5f, 0.5f, 0.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);




	SetRoot(m_pMesh);

	return true;
}

void Switch::Begin()
{
	CGameObject::Begin();
}

void Switch::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (true == m_bDead)
	{
		return;
	}


}

void Switch::Render(float fTime)
{
	CGameObject::Render(fTime);
}





void Switch::PlaceAt(int sizeX, int sizeY, float leftTopX, float leftTopY, int iStyle, bool bSwitch)
{

	float X = (m_iStageNumber - 1) * 10000.f + (sizeX * 50.f) * 0.5f + leftTopX * 50.f;
	float Y = (sizeY * 50.f) * 0.5f + leftTopY * 50.f;

	SetRelativePos(X, -Y, 0.f);

	m_pBody->SetExtent(sizeX * 50.f, sizeY * 50.f);
}





void Switch::BeginOverlap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (pDest == nullptr)
	{
		return;
	}
	if (true == pDest->IsStage())
	{
		return;
	}

	int a = 0;
}

void Switch::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (pDest == nullptr || true == m_bDead)
	{
		return;
	}

	int a = 0;

	if (pDest->IsPlayer() == true)
	{
		HollowKnight* hk = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();
		hk->BossOn(true);

		// ¿Þ
		Door* d1 = m_pScene->SpawnObject<Door>(Vector3(40000.f + 23*50.f, -33*50.f, 0.f));
		SAFE_RELEASE(d1);

		// ¿À¸¥
		Door* d2 = m_pScene->SpawnObject<Door>(Vector3(40000.f + 70 * 50.f, -33 * 50.f, 0.f));
		d2->Flip(-1);
		SAFE_RELEASE(d2);
		
		// ¸ÕÁö ÃÑ Ãâµ¿



		// ÀÌ¸§
		BossText* bt = m_pScene->SpawnObject<BossText>();
		SAFE_RELEASE(bt);

		Kill();
	}
}
