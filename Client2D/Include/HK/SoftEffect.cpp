#include "SoftEffect.h"


#include "EngineGlobals.h"
#include "Scene/Scene.h"

#include "Component/ColliderRect.h"

#include "Resource/Material.h"

#include "../RandomNumber.h"

SoftEffect::SoftEffect()
{
	m_fLifeTime = 0.f;
}

SoftEffect::~SoftEffect()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

bool SoftEffect::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("SoftMaterial");
	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SAFE_RELEASE(pMesh);

	SetRoot(m_pMesh);

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	int ran = RandomNumber::GetRandomNumber(0, 40);

	if (0 > ran)
	{
		BOOM
	}

	m_pMesh->SetRelativeScale(1.f + (float)ran, 1.f + (float)ran, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	m_pMovement->SetMoveSpeed(300.f);

	m_iDirDecider = RandomNumber::GetRandomNumber(1, 2);

	return true;
}

void SoftEffect::Begin()
{
	CGameObject::Begin();
}

void SoftEffect::Update(float fTime)
{
	CGameObject::Update(fTime);


	if (1 == m_iDirDecider)
	{
		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) );
	}
	else
	{
		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * -1.f);
	}

	if (m_fLifeTime < 1.f)
	{
		m_fLifeTime += fTime;
	}
	else
	{
		Kill();
	}


}

void SoftEffect::Render(float fTime)
{
	CGameObject::Render(fTime);
}
