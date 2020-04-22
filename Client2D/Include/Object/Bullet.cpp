#include "Bullet.h"
#include "EngineGlobals.h"
#include "Scene/Scene.h"
#include "Component/ColliderRect.h"
#include "Resource/Material.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

CColliderRect * CBullet::GetBody() const
{
	return m_pBody;
}

bool CBullet::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CGameObject::CreateComponent<CStaticMeshComponent>("Mesh");
	m_pBody = CreateComponent<CColliderRect>("BulletBody");

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("BulletMaterial");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SAFE_RELEASE(pMesh);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pBody, TR_POS);

	m_pBody->SetExtent(100.f, 100.f);

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);
	m_pMesh->SetRelativeScale(100.f, 100.f, 1.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	return true;
}

void CBullet::Begin()
{
	CGameObject::Begin();
}

void CBullet::Update(float fTime)
{
	CGameObject::Update(fTime);

	m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * 500.f);
}

void CBullet::Render(float fTime)
{
	CGameObject::Render(fTime);
}
