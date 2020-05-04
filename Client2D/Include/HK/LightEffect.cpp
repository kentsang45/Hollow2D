#include "LightEffect.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"

#include "HollowKnight.h"



LightEffect::LightEffect()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

LightEffect::~LightEffect()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
}

bool LightEffect::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);


	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("DarknessMaterial");
	pMaterial->SetSubsetDiffuse(Vector4(.5f, .5f, .5f, 0.5f));
	m_pMesh->SetMaterial(pMaterial);

	m_pAnimation->AddAnimation2DSequence("LIGHT");
	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);



	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(600.f, 600.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("LIGHT");



	return true;
}

void LightEffect::Begin()
{
	CGameObject::Begin();

	m_pHK = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();
}

void LightEffect::Update(float fTime)
{
	CGameObject::Update(fTime);

	SetWorldPos(m_pHK->GetWorldPos() + Vector3(0.f, 0.f, -3.f));

}

void LightEffect::Render(float fTime)
{
	CGameObject::Render(fTime);
}

