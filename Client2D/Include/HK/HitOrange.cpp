#include "HitOrange.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"





HitOrange::HitOrange()
	: m_pMaterial(nullptr)
{
}

HitOrange::~HitOrange()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMaterial);
}

bool HitOrange::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);


	m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimMaterial");
	m_pMesh->SetMaterial(m_pMaterial);
	m_pMesh->SetAnimation2D(m_pAnimation);
	m_pAnimation->AddAnimation2DSequence("HIT_ORANGE");
	m_pAnimation->AddAnimation2DSequence("BINDING_SHIELD");




	SetRoot(m_pMesh);

	SAFE_RELEASE(pMesh);


	m_pMesh->SetRelativeScale(128.f * 3.f, 128.f * 3.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("HIT_ORANGE");

	return true;
}

void HitOrange::Begin()
{
	CGameObject::Begin();
}

void HitOrange::Update(float fTime)
{
	CGameObject::Update(fTime);

	m_fLifeTime += fTime;

	if (m_fLifeTime >= m_fLifeTotalTime)
	{
		Kill();
	}

	m_pMaterial->SetSubsetDiffuse(Vector4(1.f, 1.f, 1.f, 1.f - m_fLifeTime));

	m_pMesh->SetMaterial(m_pMaterial);

	if (true == m_bBind)
	{
		m_fCurScale += 350.f * fTime;

		m_pMesh->SetRelativeScale(m_fCurScale, m_fCurScale, 1.f);
	}

}

void HitOrange::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void HitOrange::Start(float fTime, const Vector3 & vPos)
{
}

void HitOrange::SetAnimation(int style)
{
}

void HitOrange::SetBinding()
{
	m_pAnimation->ChangeAnimation("BINDING_SHIELD");
	m_fLifeTotalTime = 2.f;
	m_bBind = true;
}

