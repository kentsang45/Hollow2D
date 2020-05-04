#include "GetHit.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"

#include "../RandomNumber.h"



GetHit::GetHit()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

GetHit::~GetHit()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
}

bool GetHit::Init()
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

	m_pAnimation->AddAnimation2DSequence("DAMAGED_BLACK");

	m_pAnimation->AddAnimation2DSequence("EFFECT_BLOOD");

	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(800.f, 800.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("DAMAGED_BLACK");

	return true;
}

void GetHit::Begin()
{
	CGameObject::Begin();
}

void GetHit::Update(float fTime)
{
	CGameObject::Update(fTime);





	if (true == m_pAnimation->IsSequenceEnd())
	{
		Kill();
	}
}

void GetHit::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void GetHit::Start(float fTime, const Vector3 & vPos)
{
}

void GetHit::SetAnimation(int style, bool bNormal)
{
	if (0 == style)
	{
		m_pAnimation->ChangeAnimation("DAMAGED_BLACK");
	}
	else if (1 == style)
	{
		float scale = (float)RandomNumber::GetRandomNumber(120, 220);

		m_pAnimation->ChangeAnimation("EFFECT_BLOOD");
		m_pMesh->SetRelativeScale(scale, scale, 1.f);
		m_pMesh->SetPivot(0.5f, 0.53f, 0.f);

		if (true == bNormal)
		{
			float scale = (float)RandomNumber::GetRandomNumber(70, 100);

			m_pMesh->SetRelativeScale(scale, scale, 1.f);
		}

	}
	else
	{
		BOOM;
	}
}

