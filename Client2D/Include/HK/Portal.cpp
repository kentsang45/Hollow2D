#include "Portal.h"

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

Portal::Portal()
	: m_pMesh(nullptr)
	, m_pBody(nullptr)
	// , m_strAniName("Portal")

{


}

Portal::~Portal()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pBody);

}

bool Portal::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}


	m_pBody = CreateComponent<CColliderRect>("PortalBody");

	m_pBody->AddBeginOverlapCallback<Portal>(this, &Portal::BeginOverlap);
	m_pBody->AddBlockCallback<Portal>(this, &Portal::OnBlock);

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

void Portal::Begin()
{
	CGameObject::Begin();
}

void Portal::Update(float fTime)
{
	CGameObject::Update(fTime);
	
	if (true == m_bDead)
	{
		return;
	}


}

void Portal::Render(float fTime)
{
	CGameObject::Render(fTime);
}





void Portal::PlaceAt(int sizeX, int sizeY, float leftTopX, float leftTopY, int iStyle, bool bPortal)
{

	float X = (m_iStageNumber - 1) * 10000.f +  (sizeX * 50.f) * 0.5f + leftTopX * 50.f;
	float Y = (sizeY * 50.f) * 0.5f + leftTopY * 50.f;

	SetRelativePos(X, -Y, 0.f);	

	m_pBody->SetExtent(sizeX * 50.f, sizeY * 50.f);
}





void Portal::BeginOverlap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
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

void Portal::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (pDest == nullptr || true == m_bDead)
	{
		return;
	}

	int a = 0;

	if (pDest->IsPlayer() == true)
	{
		if (true == m_bStart)
		{
			HollowKnight* hk = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();
			hk->GoToPrev();
		}
		else
		{
			HollowKnight* hk = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();
			hk->GoToNext();
		}
	}
	

}
