#include "Cart.h"

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

#include "EffectSound.h"

Cart::Cart()
	: m_pMesh(nullptr)
	, m_pAnimation(nullptr)
	, m_pBody(nullptr)
	// , m_strAniName("CART")

{


}

Cart::~Cart()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pBody);

}

bool Cart::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}


	m_pBody = CreateComponent<CColliderRect>("CartBody");

	m_pBody->AddBeginOverlapCallback<Cart>(this, &Cart::BeginOverlap);
	m_pBody->AddBlockCallback<Cart>(this, &Cart::OnBlock);
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




	m_pMesh->SetRelativeScale(250.f, 250.f, 1.f);
	m_pBody->SetExtent(200.f, 200.f);
	m_iSizeX = 250;
	m_iSizeY = 250;


	m_pBody->SetPivot(0.5f, 0.5f, 0.f);
	m_pMesh->SetPivot(0.5f, 0.57f, 0.f);




	SetRoot(m_pMesh);

	return true;
}

void Cart::Begin()
{
	CGameObject::Begin();
}

void Cart::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (true == m_bDead)
	{
		return;
	}


}

void Cart::Render(float fTime)
{
	CGameObject::Render(fTime);
}





void Cart::PlaceAt(int sizeX, int sizeY, float leftTopX, float leftTopY, int iStyle, bool bCart)
{


	m_iStyle = iStyle;

	float X = (m_iStageNumber - 1) * 10000.f + (200) * 0.5f + leftTopX * 50.f;
	float Y = (200) * 0.5f + leftTopY * 50.f;

	m_bCart = bCart;

	if (true == bCart)
	{
		m_strAniName = "CART";
		X = (m_iStageNumber - 1) * 10000.f + (200) * 0.5f + leftTopX * 50.f;
		Y = (200) * 0.5f + leftTopY * 50.f;


	}
	else
	{
		m_strAniName = "BARREL";
		X = (m_iStageNumber - 1) * 10000.f + (100) * 0.5f + leftTopX * 50.f;
		Y = (100) * 0.5f + leftTopY * 50.f;

		m_pMesh->SetRelativeScale(150.f, 150.f, 1.f);
		m_pBody->SetExtent(100.f, 100.f);

		m_pMesh->SetPivot(0.5f, 0.7f, 0.f);
	}


	char number[20];
	itoa(m_iStyle, number, 20);
	m_strAniName.append(number);
	m_pAnimation->AddAnimation2DSequence(m_strAniName);

	m_pMesh->SetAnimation2D(m_pAnimation);





	// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.


	// m_pMesh->SetRelativePos(X, -Y, -1.f);
	// m_pBody->SetRelativePos(X, -Y, 0.f);
	SetRelativePos(X, -Y, 0.f);
	m_pBody->SetRelativePos(0.f, 0.f, 0.f);

	m_pAnimation->ChangeAnimation(m_strAniName);
}

void Cart::ChangeAnimation(int iAnim)
{

}




void Cart::BeginOverlap(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
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

void Cart::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
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

		if (true == m_bCart)
		{
			for (int i = 0; i < 30; ++i)
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
		}
		else
		{
			for (int i = 0; i < 6; ++i)
			{
				int x = RandomNumber::GetRandomNumber(1, 100) - 50;
				int y = RandomNumber::GetRandomNumber(1, 100);

				BarrelParticle* bp = m_pScene->SpawnObject<BarrelParticle>();
				// hk->SetRelativePos(Vector3((131.f * 50.f) * 0.5f, 100.f, 0.f));
				bp->SetWorldPos(GetWorldPos() + Vector3((float)x, (float)y, 0.f));

				if (DIR_LEFT == type)
				{
					bp->SetDirection(2);
				}
				else
				{
					bp->SetDirection(1);
				}

				if (5 == i)
				{
					bp->ResetStyle();
				}

				SAFE_RELEASE(bp);
			}
		}

		

		EffectSound*	pFireSound = m_pScene->SpawnObject<EffectSound>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
			Vector3(0.f, 0.f, GetRelativeRot().z));

		if (false == m_bCart)
		{
			m_strSoundName = "Cart_Break";
			m_strSoundFileName = m_strSoundName;
			m_strSoundFileName.append(".wav");
		}
		else
		{
			m_strSoundName = "Barrel_Break";
			m_strSoundFileName = m_strSoundName;
			m_strSoundFileName.append(".wav");
		}



		pFireSound->SetSound(m_strSoundName, m_strSoundFileName.c_str());

		SAFE_RELEASE(pFireSound);





		Kill();
	}



}
