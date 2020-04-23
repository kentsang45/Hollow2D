#include "Statue.h"

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

#include "../RandomNumber.h"

#include "HollowKnight.h"

Statue::Statue()
	: m_pMesh(nullptr)
	, m_pAnimation(nullptr)
	, m_pBody(nullptr)
	, m_strAniName("STATUE_0")
	, m_strBaseName("STATUE_0")
{


}

Statue::~Statue()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pBody);

}

bool Statue::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}


	m_pBody = CreateComponent<CColliderRect>("StatueBody");

	m_pBody->AddBeginOverlapCallback<Statue>(this, &Statue::BeginOverlap);
	m_pBody->AddBlockCallback<Statue>(this, &Statue::OnBlock);
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

	int style = RandomNumber::GetRandomNumber(3, 8);


	// TEST
	//////////////////////////////////
	style = 2;


	// STATUE_08


	char number[20];
	
	itoa(style, number, 20);

	m_strAniName.append(number);
	m_strBaseName.append(number);
	m_strBaseName.append("_BASE");

	

	if (2 == style)
	{
		m_pMesh->SetRelativeScale(250.f, 281.f, 1.f);
		m_pBody->SetExtent(250.f, 281.f);
		m_iSizeX = 250;
		m_iSizeY = 281;
	}
	else
	{
		m_pMesh->SetRelativeScale(250.f, 250.f, 1.f);
		m_pBody->SetExtent(250.f, 250.f);
		m_iSizeX = 250;
		m_iSizeY = 250;
	}

	m_pBody->SetPivot(0.5f, 0.5f, 0.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	m_pAnimation->AddAnimation2DSequence(m_strAniName);
	m_pAnimation->AddAnimation2DSequence(m_strBaseName);



	SetRoot(m_pMesh);

	m_pAnimation->ChangeAnimation(m_strAniName);

	return true;
}

void Statue::Begin()
{
	CGameObject::Begin();
}

void Statue::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (true == m_bDead)
	{
		return;
	}


}

void Statue::Render(float fTime)
{
	CGameObject::Render(fTime);
}





void Statue::PlaceAt(int sizeX, int sizeY, int leftTopX, int leftTopY)
{
	// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
	float X = (m_iSizeX) * 0.5f + leftTopX * 50.f;
	float Y = (m_iSizeY) * 0.5f + leftTopY * 50.f;

	// m_pMesh->SetRelativePos(X, -Y, -1.f);
	// m_pBody->SetRelativePos(X, -Y, 0.f);
	SetRelativePos(X, -Y, 0.f);
	m_pBody->SetRelativePos(0.f, 0.f, 0.f);
}




void Statue::BeginOverlap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (pDest == nullptr)
	{
		return;
	}
	if (true == pDest->IsStage())
	{
		return;
	}
}

void Statue::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (pDest == nullptr || true == m_bDead)
	{
		return;
	}

	if (true == pDest->IsStage())
	{
		return;
	}


	else if (pDest->GetCollisionProfile()->strName == "PlayerProjectile")
	{
		HollowKnight* hk = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();
		DIR_TYPE type = hk->GetDirection();

		for (int i = 0; i < 20; ++i)
		{
			int x = RandomNumber::GetRandomNumber(1, 200) - 100;
			int y = RandomNumber::GetRandomNumber(1, 200);

			RockParticle* gp = m_pScene->SpawnObject<RockParticle>();
			// hk->SetRelativePos(Vector3((131.f * 50.f) * 0.5f, 100.f, 0.f));
			gp->SetWorldPos(GetWorldPos() + Vector3((float)x, (float)y, 0.f));

			if (DIR_LEFT == type)
			{
				gp->SetDirection(2);
			}
			else
			{
				gp->SetDirection(1);
			}

			SAFE_RELEASE(gp);
		}







		m_pAnimation->ChangeAnimation(m_strBaseName);
		m_bDead = true;
	}



}
