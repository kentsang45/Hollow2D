#include "Grass.h"


#include "EngineGlobals.h"

#include "Scene/Scene.h"
#include "Component/CameraComponent.h"
#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"



#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderRect.h"

#include "GrassParticle.h"

#include "../RandomNumber.h"

Grass::Grass()
	: m_pMesh(nullptr)
	, m_pAnimation(nullptr)
	, m_pBody(nullptr)
{
}

Grass::~Grass()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pBody);
}

bool Grass::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}


	m_pBody = CreateComponent<CColliderRect>("GrassBody");
	m_pBody->SetExtent(200.f, 200.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);
	m_pBody->AddBeginOverlapCallback<Grass>(this, &Grass::BeginOverlap);
	m_pBody->AddBlockCallback<Grass>(this, &Grass::OnBlock);
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

	m_pMesh->SetRelativeScale(200.f, 200.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	m_pAnimation->AddAnimation2DSequence("GRASS_1_IDLE");
	m_pAnimation->AddAnimation2DSequence("GRASS_1_MOVE");
	m_pAnimation->AddAnimation2DSequence("GRASS_1_DEATH");

	m_pMesh->SetAnimation2D(m_pAnimation);


	SetRoot(m_pMesh);

	m_pAnimation->ChangeAnimation("GRASS_1_IDLE");

	return true;
}

void Grass::Begin()
{
	CGameObject::Begin();
}

void Grass::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (true == m_bDead)
	{
		return;
	}

	if (true == m_pAnimation->IsSequenceEnd() && m_bIsOn == true)
	{
		m_pAnimation->ChangeAnimation("GRASS_1_MOVE");
		m_bIsOn = false;
		return;
	}

	if (true == m_pAnimation->IsSequenceEnd() && m_bIsOn == false)
	{
		m_pAnimation->ChangeAnimation("GRASS_1_IDLE");
		m_bIsOn = false;
	}

}

void Grass::Render(float fTime)
{
	CGameObject::Render(fTime);
}





void Grass::PlaceAt(int sizeX, int sizeY, int leftTopX, int leftTopY)
{
	// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
	float X = (sizeX * 50.f) * 0.5f + leftTopX * 50.f;
	float Y = (sizeY * 50.f) * 0.5f + leftTopY * 50.f;

	m_pMesh->SetRelativeScale(sizeX * 50.f, sizeY * 50.f, 1.f);
	m_pBody->SetExtent(sizeX * 50.f, sizeY * 50.f);
	// m_pMesh->SetRelativePos(X, -Y, -1.f);
	// m_pBody->SetRelativePos(X, -Y, 0.f);
	SetRelativePos(X, -Y, -1.f);
	m_pBody->SetRelativePos(0.f, 0.f, 1.f);
}




void Grass::BeginOverlap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (pDest == nullptr)
	{
		return;
	}
	if (true == pDest->IsStage())
	{
		return;
	}

	else
	{
		m_pAnimation->ChangeAnimation("GRASS_1_MOVE");
	}
}

void Grass::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
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


		for (int i = 0; i < 50; ++i)
		{
			int x = RandomNumber::GetRandomNumber(1, 200) - 100;
			int y = RandomNumber::GetRandomNumber(1, 200) - 100;

			int iStyle = RandomNumber::GetRandomNumber(1, 3);

			GrassParticle* gp = m_pScene->SpawnObject<GrassParticle>();
			// hk->SetRelativePos(Vector3((131.f * 50.f) * 0.5f, 100.f, 0.f));
			gp->SetRelativePos(GetWorldPos() + Vector3((float)x, (float)y, 0.f));

			if (x <= 0)
			{
				gp->SetDirection(2);
			}


			SAFE_RELEASE(gp);
		}

		





		m_pAnimation->ChangeAnimation("GRASS_1_DEATH");
		m_bDead = true;
	}
	else
	{
		m_pAnimation->ChangeAnimation("GRASS_1_MOVE");
		m_bIsOn = true;
	}


}
