#include "HealOver.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"
#include "Healing.h"





HealOver::HealOver()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

HealOver::~HealOver()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
}

bool HealOver::Init()
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

	m_pAnimation->AddAnimation2DSequence("HEAL_OVER");
	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(1200.f, 1200.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("HEAL_START");

	return true;
}

void HealOver::Begin()
{
	CGameObject::Begin();
}

void HealOver::Update(float fTime)
{
	CGameObject::Update(fTime);



	if (true == m_pAnimation->IsSequenceEnd())
	{
		Kill();
	}
}

void HealOver::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void HealOver::Start(float fTime, const Vector3 & vPos)
{
}

