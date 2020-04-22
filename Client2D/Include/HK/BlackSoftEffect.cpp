#include "BlackSoftEffect.h"


#include "EngineGlobals.h"
#include "Scene/Scene.h"

#include "Component/ColliderRect.h"

#include "Resource/Material.h"

#include "../RandomNumber.h"

BlackSoftEffect::BlackSoftEffect()
{
	m_fLifeTime = 0.f;
}

BlackSoftEffect::~BlackSoftEffect()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

bool BlackSoftEffect::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BlackSoftMaterial");
	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SAFE_RELEASE(pMesh);

	SetRoot(m_pMesh);

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	int ran = RandomNumber::GetRandomNumber(0, 60);

	m_pMesh->SetRelativeScale(.1f + (float)ran, .1f + (float)ran, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	int speed = RandomNumber::GetRandomNumber(0, 1000);
	m_pMovement->SetMoveSpeed(500.f + (float)speed);

	// m_iDirDecider = RandomNumber::GetRandomNumber(1, 2);

	m_fLifeTotalTime = 3.f;

	m_fXTime = RandomNumber::GetRandomNumber(0, 500) * 0.001f;
	return true;
}

void BlackSoftEffect::Begin()
{
	CGameObject::Begin();
}

void BlackSoftEffect::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (false == m_bVertical)
	{
		int XORY = RandomNumber::GetRandomNumber(1, 7);


		if (0.01f + m_fXTime > m_fYTime)
		{
			XORY = RandomNumber::GetRandomNumber(4, 10);
		}
		else
		{
			int speed = RandomNumber::GetRandomNumber(100, 500);
			m_pMovement->SetMoveSpeed((float)speed);
		}

		m_fYTime += fTime;

		if (5 < XORY)
		{
			if (1 == m_iXDecider)
			{
				m_pMovement->AddMovement(GetWorldAxis(AXIS_X));
			}
			else
			{
				m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * -1.f);
			}
		}
		else
		{
			m_pMovement->AddMovement(GetWorldAxis(AXIS_Y));
		}
	}
	else
	{
		m_pMovement->SetMoveSpeed(250.f);

		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y));
	}
	






	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	if (m_fLifeTime < m_fLifeTotalTime)
	{
		m_fLifeTime += fTime;
	}
	else
	{
		Kill();
	}


}

void BlackSoftEffect::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void BlackSoftEffect::SetLeft()
{
	m_iXDecider = 2;
}

