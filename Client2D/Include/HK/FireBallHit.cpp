#include "FireBallHit.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"





FireBallHit::FireBallHit()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

FireBallHit::~FireBallHit()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
}

bool FireBallHit::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);


	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pMesh->SetMaterial(pMaterial);

	m_pAnimation->AddAnimation2DSequence("FIREBALL_HIT");
	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(800.f, 800.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("FIREBALL_HIT");

	return true;
}

void FireBallHit::Begin()
{
	CGameObject::Begin();
}

void FireBallHit::Update(float fTime)
{
	CGameObject::Update(fTime);





	if (true == m_pAnimation->IsSequenceEnd())
	{
		Kill();
	}
}

void FireBallHit::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void FireBallHit::Start(float fTime, const Vector3 & vPos)
{
}

