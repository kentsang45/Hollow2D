#include "DustEffect.h"


#include "EngineGlobals.h"
#include "Scene/Scene.h"

#include "Resource/Material.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"

#include "../RandomNumber.h"

DustEffect::DustEffect()
{
	m_fLifeTime = 0.f;
	m_pAnimation = nullptr;
	m_pRotPivot = nullptr;
}

DustEffect::~DustEffect()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pRotPivot);
}

bool DustEffect::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMaterial");
	m_pMesh->SetMaterial(pMaterial);

	m_pRotPivot = CreateComponent<CSceneComponent>("RotPivot");
	m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);

	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pAnimation->AddAnimation2DSequence("DUST_EFFECT_STATIC");
	m_pMesh->SetAnimation2D(m_pAnimation);

	SAFE_RELEASE(pMaterial);

	SAFE_RELEASE(pMesh);

	SetRoot(m_pMesh);

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	int ran = RandomNumber::GetRandomNumber(0, 70);

	m_pMesh->SetRelativeScale(1.f + (float)ran, 1.f + (float)ran, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	m_pMovement->SetMoveSpeed(200.f);

	// m_pAnimation->ChangeAnimation("DUSTEFFECT");
	// m_pAnimation->ChangeAnimation("DUST_EFFECT_FRAME");
	m_pAnimation->ChangeAnimation("DUST_EFFECT_STATIC");

	m_fLifeTotalTime = 0.1f + RandomNumber::GetRandomNumber(0, 140) / 100.f;

	// m_pMovement->SetRotationSpeed(200.f);

	return true;
}

void DustEffect::Begin()
{
	CGameObject::Begin();
}

void DustEffect::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (false == m_bSizeDecider)
	{
		m_iDir = RandomNumber::GetRandomNumber(0, 10) % 2;
	}


	if (false == m_bStop)
	{
		if (false == m_bDirDecider)
		{
			m_pMovement->AddMovement(GetWorldAxis(AXIS_Y));
			m_bDirDecider = true;
		}
		else
		{
			// LEFT
			if (0 == m_iDir)
			{
				m_pMovement->AddMovement(GetWorldAxis(AXIS_X));
			}
			else
			{
				m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * -1.f);
			}
			m_bDirDecider = false;
		}
	}
	else
	{
		int a = 0;
	}



	// 회전	
	// 자전
	m_pMesh->SetRelativeRotationZ(180.f * fTime);


	if (m_fLifeTime < m_fLifeTotalTime)
	{
		m_fLifeTime += fTime;
	}
	else
	{
		Kill();
	}


}

void DustEffect::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void DustEffect::SetMaxSize(float fSize)
{
	int ran = RandomNumber::GetRandomNumber(0, fSize);

	m_pMesh->SetRelativeScale(1.f + (float)ran, 1.f + (float)ran, 1.f);
}

void DustEffect::SetStaticSize(float fSize)
{
	m_pMesh->SetRelativeScale(fSize, fSize, 1.f);
}

void DustEffect::SetStop()
{
	m_bStop = true;
}
