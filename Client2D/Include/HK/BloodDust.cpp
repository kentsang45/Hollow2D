#include "BloodDust.h"


#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"

#include "../RandomNumber.h"



BloodDust::BloodDust()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
	, m_pMovement(nullptr)
{
}

BloodDust::~BloodDust()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

bool BloodDust::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	
	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("FireBallMovement");
	m_pMovement->SetUpdateComponent(m_pMesh);


	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);


	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pMesh->SetMaterial(pMaterial);

	m_pAnimation->AddAnimation2DSequence("BLOOD_DUST");

	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	int scale = RandomNumber::GetRandomNumber(100, 200);


	m_pMesh->SetRelativeScale(scale, scale, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	// m_pMesh->AddChild(m_pBody, TR_POS);



	float moveSpeed = (float)RandomNumber::GetRandomNumber(1000, 2000);

	m_pMovement->SetMoveSpeed(moveSpeed);


	m_pAnimation->ChangeAnimation("BLOOD_DUST");

	float axisX = RandomNumber::GetRandomNumber(1, 30) - 1;
	float axisY = RandomNumber::GetRandomNumber(1, 30) - 1;

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

	return true;
}

void BloodDust::Begin()
{
	CGameObject::Begin();
}

void BloodDust::Update(float fTime)
{
	CGameObject::Update(fTime);



	

	m_pMovement->AddMovement(m_vVelo);



	if (true == m_pAnimation->IsSequenceEnd())
	{
		Kill();
	}
}

void BloodDust::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void BloodDust::Start(float fTime, const Vector3 & vPos)
{
}

void BloodDust::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{

}

void BloodDust::SetDir(int dir)
{
	float y = 1.f;
	float x = 1.f;

	// 오른쪽
	if (dir > 0)
	{
		// 근데 왼쪽
		if (m_vVelo.x < 0)
		{
			x = -1.f;
		}
	}
	// 왼쪽
	else
	{
		// 근데 오른쪽
		if (m_vVelo.x > 0)
		{
			x = -1.f;
		}
	}

	

	if (0 > m_vVelo.y)
	{
		y = -1.f;
	}


	m_vVelo *= Vector3(x, y, 1.f);

	// m_vVelo = GetWorldAxis(AXIS_X) * m_iDir * axisX + GetWorldAxis(AXIS_Y) * axisY * iDirY;
}

void BloodDust::SetNormalMonster()
{
	int scale = RandomNumber::GetRandomNumber(70, 100);


	m_pMesh->SetRelativeScale(scale, scale, 1.f);
}

