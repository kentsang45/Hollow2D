#include "Minion.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Scene/GameMode.h"
#include "Scheduler.h"
#include "Bullet.h"
#include "Component/ColliderRect.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"

CMinion::CMinion()
{
	m_pBodyOBB2D = nullptr;
	m_pBodySphere = nullptr;
	m_pBody = nullptr;
	m_pMesh = nullptr;
	m_pMovement = nullptr;
}

CMinion::~CMinion()
{
	SAFE_RELEASE(m_pBodyOBB2D);
	SAFE_RELEASE(m_pBodySphere);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

bool CMinion::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	//m_pBody = CreateComponent<CColliderRect>("MinionBody");
	m_pBodySphere = CreateComponent<CColliderSphere2D>("MinionBodySphere");
	m_pBodyOBB2D = CreateComponent<CColliderOBB2D>("MinionBodyOBB2D");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("ColorTri");

	m_pMesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);

	SetRoot(m_pMesh);

	//m_pMesh->AddChild(m_pBody, TR_POS);
	m_pMesh->AddChild(m_pBodySphere, TR_POS);
	m_pMesh->AddChild(m_pBodyOBB2D, TR_ROT | TR_POS);

	//m_pBody->SetExtent(200.f, 200.f);
	//m_pBody->SetCollisionProfile("Monster");
	//m_pBody->AddBlockCallback<CMinion>(this, &CMinion::OnBlock);

	m_pBodySphere->SetSphere(Vector3(-200.f, 0.f, 0.f), 100.f);

	m_pBodySphere->AddBlockCallback<CMinion>(this, &CMinion::OnBlock);
	m_pBodySphere->SetCollisionProfile("Monster");

	m_pBodyOBB2D->SetOBB2D(Vector3(0.f, 0.f, 0.f), 100.f, 100.f);

	m_pBodyOBB2D->AddBlockCallback<CMinion>(this, &CMinion::OnBlock);
	m_pBodyOBB2D->SetCollisionProfile("Monster");

	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetRelativeScale(200.f, 200.f, 1.f);

	m_pMovement->SetMoveSpeed(100.f);

	//GET_SINGLE(CScheduler)->AddSchedule<CMinion>("MinionFire", true, 1.f, this, &CMinion::Fire);

	return true;
}

void CMinion::Begin()
{
	CGameObject::Begin();
}

void CMinion::Update(float fTime)
{
	CGameObject::Update(fTime);

	LookAt(m_pScene->GetGameMode()->GetPlayer());

	//m_pMovement->AddMovement(GetWorldAxis(AXIS_Y));
}

void CMinion::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CMinion::Fire()
{
	CBullet*	pBullet = m_pScene->SpawnObject<CBullet>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		GetRelativeRot());

	pBullet->LookAt(m_pScene->GetGameMode()->GetPlayer());

	CColliderRect* pBody = pBullet->GetBody();

	pBody->SetCollisionProfile("MonsterProjectile");

	SAFE_RELEASE(pBullet);
}

void CMinion::OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime)
{
}
