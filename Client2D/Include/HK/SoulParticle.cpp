#include "SoulParticle.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"


#include "../RandomNumber.h"


SoulParticle::SoulParticle()
	: m_bIsOn(false)
	, m_vVelo(Vector3::Zero)
	, m_pMaterial(nullptr)
{
}

SoulParticle::~SoulParticle()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pMaterial);
}

bool SoulParticle::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	float speed = (float)RandomNumber::GetRandomNumber(30, 100);

	m_pMovement->SetMoveSpeed(speed);

	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);


	m_pMesh->SetAnimation2D(m_pAnimation);


	m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("DarknessMaterial");
	m_pMesh->SetMaterial(m_pMaterial);
	
	m_pAnimation->AddAnimation2DSequence("SOUL_EFFECT");



	SetRoot(m_pMesh);

	SAFE_RELEASE(pMesh);
	// SAFE_RELEASE(m_pMaterial);


	m_fTotalSize = (float)RandomNumber::GetRandomNumber(50, 100) * 0.01f * 30.f;

		// 0.5f~1.f
	m_pMesh->SetRelativeScale(m_fSize, m_fSize, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	m_fLifeTime = (float)RandomNumber::GetRandomNumber(100, 500) * 0.01f;
	// 1.f ~ 5.f

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("SOUL_EFFECT");




	float axisX = RandomNumber::GetRandomNumberTime(1, 30) - 1;
	float axisY = RandomNumber::GetRandomNumberTime(1, 30) - 1;

	axisX *= 30.f;
	axisY *= 30.f;

	m_iDir = RandomNumber::GetRandomNumber(1, 2);

	if (2 == m_iDir)
	{
		m_iDir = -1;
	}

	int iDirY = RandomNumber::GetRandomNumber(1, 2);

	if (2 == iDirY)
	{
		iDirY = -1;
	}

	m_vVelo = GetWorldAxis(AXIS_X) * m_iDir * axisX + GetWorldAxis(AXIS_Y) * axisY * iDirY;

	// m_fTime2 = m_fLifeTime * 0.5f;
	return true;
}

void SoulParticle::Begin()
{
	CGameObject::Begin();
}

void SoulParticle::Update(float fTime)
{
	CGameObject::Update(fTime);

	m_fTime += fTime;



	if (m_fTime >= m_fLifeTime)
	{
		Kill();
	}

	// 작아지기
	if (m_fTime >= m_fLifeTime * 0.5f)
	{

		m_fTime2 -= fTime;

		m_fSize -= 1 * fTime*m_fLifeTime*0.5f;

		if (m_fSize <= 0.f)
		{
			m_fSize = 0.f;
		}

		// m_pMesh->SetRelativeScale(m_fSize, m_fSize, 1.f);



		m_pMaterial->SetSubsetDiffuse(Vector4(1.f, 1.f, 1.f, m_fTime2));

		m_pMesh->SetMaterial(m_pMaterial);
	}
	// 커지기
	else
	{
		m_fSize += m_fTotalSize * fTime*m_fLifeTime*0.5f;

		if (m_fSize >= m_fTotalSize)
		{
			m_fSize = m_fTotalSize;
		}

		m_pMesh->SetRelativeScale(m_fSize, m_fSize, 1.f);
	}

	m_pMovement->AddMovement(m_vVelo);
}

void SoulParticle::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void SoulParticle::Start(float fTime, const Vector3 & vPos)
{
}

void SoulParticle::SetAnimation(int style)
{
	if (0 == style)
	{
		m_pAnimation->ChangeAnimation("DAMAGED_BLACK");
	}
	else if (1 == style)
	{
		m_pAnimation->ChangeAnimation("EFFECT_BLOOD");
		m_pMesh->SetRelativeScale(150.f, 150.f, 1.f);
		m_pMesh->SetPivot(0.5f, 0.53f, 0.f);
	}
	else
	{
		BOOM;
	}
}

