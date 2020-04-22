#include "Healing.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"





Healing::Healing()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

Healing::~Healing()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
}

bool Healing::Init()
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

	// pMaterial->SetSubsetDiffuse(Vector4(1.f, 1.f, 1.f, 1.f));


	m_pAnimation->AddAnimation2DSequence("HEALING");
	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(400.f, 400.f, 1.f);
	m_pMesh->SetPivot(0.52f, 0.52f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("HEAL_START");

	return true;
}

void Healing::Begin()
{
	CGameObject::Begin();
}

void Healing::Update(float fTime)
{
	CGameObject::Update(fTime);



	
}

void Healing::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void Healing::Start(float fTime, const Vector3 & vPos)
{
	Kill();
}

