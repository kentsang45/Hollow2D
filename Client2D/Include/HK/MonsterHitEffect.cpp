#include "MonsterHitEffect.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"





MonsterHitEffect::MonsterHitEffect()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

MonsterHitEffect::~MonsterHitEffect()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
}

bool MonsterHitEffect::Init()
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

	m_pAnimation->AddAnimation2DSequence("MONSTER_HIT_EFFECT");
	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(1200.f, 1200.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("MONSTER_HIT_EFFECT");

	return true;
}

void MonsterHitEffect::Begin()
{
	CGameObject::Begin();
}

void MonsterHitEffect::Update(float fTime)
{
	CGameObject::Update(fTime);





	if (true == m_pAnimation->IsSequenceEnd())
	{
		Kill();
	}
}

void MonsterHitEffect::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void MonsterHitEffect::Start(float fTime, const Vector3 & vPos)
{
}

