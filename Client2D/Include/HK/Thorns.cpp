#include "Thorns.h"


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

Thorns::Thorns()
	: m_pMesh(nullptr)
	, m_pAnimation(nullptr)
	, m_pBody(nullptr)
	, m_strIdleName("Thorns_")
	, m_strMoveName("Thorns_")
	, m_strDeathName("Thorns_")
{
}

Thorns::~Thorns()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pBody);
}

bool Thorns::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}


	m_pBody = CreateComponent<CColliderRect>("ThornsBody");
	m_pBody->SetExtent(139.f, 70.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);
	m_pBody->AddBlockCallback<Thorns>(this, &Thorns::OnBlock);
	m_pBody->SetCollisionProfile("Object");


	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);


	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pMesh->SetAnimation2D(m_pAnimation);
	m_pMesh->AddChild(m_pBody, TR_POS);


	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pMesh->SetMaterial(pMaterial);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(139.f, 105.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);


	m_pAnimation->AddAnimation2DSequence("SPIKE_STILL");
	m_pAnimation->AddAnimation2DSequence("SPIKE");

	m_pAnimation->ChangeAnimation("SPIKE");

	SetRoot(m_pMesh);

	m_pBody->SetMonster(true);

	int a = RandomNumber::GetRandomNumber(150, 350);

	m_fWaitTotalTime = (float)a * 0.01f;

	return true;
}

void Thorns::Begin()
{
	CGameObject::Begin();
}

void Thorns::Update(float fTime)
{
	CGameObject::Update(fTime);



	if (false == m_bShiny)
	{
		m_fWaitTime += fTime;

		if (m_fWaitTime >= 0.4f)
		{
			m_pAnimation->ChangeAnimation("SPIKE_STILL");
		}

		if (m_fWaitTime >= m_fWaitTotalTime)
		{
			m_bShiny = true;
			m_fWaitTime = 0.f;
		}
		else
		{
			return;
		}
	}

	m_pAnimation->ChangeAnimation("SPIKE"); 
	m_bShiny = false;
	

}

void Thorns::Render(float fTime)
{
	CGameObject::Render(fTime);
}





void Thorns::PlaceAt(int sizeX, int sizeY, float leftTopX, float leftTopY, int iStyle)
{
	// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
	float X = (m_iStageNumber - 1) * 10000.f + (139) * 0.5f + leftTopX * 50.f;
	float Y = (105) * 0.5f + leftTopY * 50.f;


	SetRelativePos(X, -Y, -1.f);
	m_pBody->SetRelativePos(0.f, 0.f, 1.f);
}




void Thorns::BeginOverlap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{

}

void Thorns::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (pDest == nullptr || true == m_bDead)
	{
		return;
	}

	if (true == pDest->IsPlayer())
	{
		HollowKnight* hk = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();
		hk->ResetPosition();
	}




}

void Thorns::Reverse()
{
	Flip(-1);
}
