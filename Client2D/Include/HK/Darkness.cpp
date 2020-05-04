#include "Darkness.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"

#include "HollowKnight.h"



Darkness::Darkness()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

Darkness::~Darkness()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
}

bool Darkness::Init()
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
	// pMaterial->SetSubsetDiffuse(Vector4(1.f, 1.f, 1.f, 0.9f));
	m_pMesh->SetMaterial(pMaterial);

	m_pAnimation->AddAnimation2DSequence("DARKNESS");
	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);



	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(3840.f, 2160.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("DARKNESS");

	

	return true;
}

void Darkness::Begin()
{
	CGameObject::Begin();

	m_pHK = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();
}

void Darkness::Update(float fTime)
{
	CGameObject::Update(fTime);

	SetWorldPos(m_pHK->GetWorldPos() + Vector3(0.f, 0.f, -3.f));

}

void Darkness::Render(float fTime)
{
	CGameObject::Render(fTime);
}

