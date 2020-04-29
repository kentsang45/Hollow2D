#include "PowerWave.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"

// #include "PowerWaveHit.h"

int PowerWave::m_iStyle = 0;

PowerWave::PowerWave()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
	, m_pAnimation(nullptr)
{
}

PowerWave::~PowerWave()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pBody);
}

bool PowerWave::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pBody = CreateComponent<CColliderRect>("WaveBody");


	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);

	m_pAnimation->AddAnimation2DSequence("FK_WAVE1_");
	m_pAnimation->AddAnimation2DSequence("FK_WAVE2_");
	m_pAnimation->AddAnimation2DSequence("FK_WAVE3_");
	m_pMesh->SetAnimation2D(m_pAnimation);

	m_iSpeedStyle = m_iStyle;

	if (12 < m_iStyle|| 0 > m_iStyle)
	{
		BOOM;
	}

	char strKey[256] = {};

	if (m_iStyle <= 4)
	{
		sprintf_s(strKey, "FK_WAVE3_");
	}
	else if (m_iStyle <= 8)
	{
		sprintf_s(strKey, "FK_WAVE2_");
	}
	else
	{
		sprintf_s(strKey, "FK_WAVE1_");
	}




	++m_iStyle;

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pMesh->SetMaterial(pMaterial);

	SetRoot(m_pMesh);

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("PowerWaveMovement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	///////////////////////////////////////////////////////////


	m_pBody->AddBlockCallback<PowerWave>(this, &PowerWave::OnBlock);
	m_pBody->SetCollisionProfile("MonsterProjectile");

	m_pMesh->AddChild(m_pBody, TR_POS);
	m_pBody->SetExtent(m_fCScaleX, 100.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(m_fScaleX, 400.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pMovement->SetMoveSpeed(2000.f);

	m_fMoveSpeed = 1000.f;

	m_pAnimation->ChangeAnimation(strKey);

	return true;
}

void PowerWave::Begin()
{
	CGameObject::Begin();
}

void PowerWave::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (0 == m_iDir)
	{
		int a = 0;
	}

	m_fCScaleX += m_fCScaleX * 4.f * fTime;
	m_fScaleX += m_fScaleX * 4.f * fTime;

	if (m_fCScaleX >= 100.f)
	{
		m_fCScaleX = 100.f;
	}
	if (m_fScaleX >= 400.f)
	{
		m_fScaleX = 400.f;
	}


	m_pBody->SetExtent(m_fCScaleX, 100.f);
	m_pMesh->SetRelativeScale(m_fScaleX, 400.f, 1.f);


	m_fMoveSpeed += 500.f * fTime * fTime * (10 + m_iSpeedStyle);
	

	

	m_pMovement->SetMoveSpeed(m_fMoveSpeed);

	m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * m_iDir);
}

void PowerWave::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void PowerWave::SetDir(int dir)
{
	m_iDir = dir;
	Flip(dir);
}

void PowerWave::Start(float fTime, const Vector3 & vPos)
{
}

void PowerWave::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	


}

CColliderRect * PowerWave::GetBody() const
{
	return m_pBody;
}

