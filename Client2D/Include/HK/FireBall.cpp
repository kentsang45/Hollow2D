#include "FireBall.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"

#include "FireBallHit.h"



FireBall::FireBall()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

FireBall::~FireBall()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pBody);
}

bool FireBall::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pBody = CreateComponent<CColliderRect>("FireBody");


	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);


	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pMesh->SetMaterial(pMaterial);

	m_pAnimation->AddAnimation2DSequence("FIREBALL");
	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("FireBallMovement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	///////////////////////////////////////////////////////////


	m_pBody->AddBlockCallback<FireBall>(this, &FireBall::OnBlock);
	m_pBody->SetCollisionProfile("PlayerProjectile");

	m_pMesh->AddChild(m_pBody, TR_POS);
	m_pBody->SetExtent(100.f, 100.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(400.f, 400.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("FIREBALL");

	m_pMovement->SetMoveSpeed(2000.f);
	return true;
}

void FireBall::Begin()
{
	CGameObject::Begin();
}

void FireBall::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (0 == m_iDir)
	{
		int a = 0;
	}

	m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * 500.f * m_iDir);

	if (true == m_pAnimation->IsSequenceEnd())
	{
		Kill();
	}
}

void FireBall::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void FireBall::Start(float fTime, const Vector3 & vPos)
{
}

void FireBall::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	FireBallHit* hit = m_pScene->SpawnObject<FireBallHit>(pSrc->GetIntersect() + Vector3(0.f, 0.f, -0.5f));

	SAFE_RELEASE(hit);
}

CColliderRect * FireBall::GetBody() const
{
	return m_pBody;
}

