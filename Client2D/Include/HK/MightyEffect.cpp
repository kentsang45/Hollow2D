#include "MightyEffect.h"


#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"





MightyEffect::MightyEffect()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
	, m_pBody(nullptr)
{
}

MightyEffect::~MightyEffect()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pBody);
}

bool MightyEffect::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pBody = CreateComponent<CColliderRect>("MightyBody");

	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);


	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pMesh->SetMaterial(pMaterial);

	m_pAnimation->AddAnimation2DSequence("MIGHTY_EFFECT");
	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(400.f * 2, 178.f * 2, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pBody->AddBlockCallback<MightyEffect>(this, &MightyEffect::OnBlock);
	m_pBody->SetCollisionProfile("MonsterProjectile");

	m_pMesh->AddChild(m_pBody, TR_POS);
	m_pBody->SetExtent(200.f, 300.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);







	m_pAnimation->ChangeAnimation("MIGHTY_EFFECT");

	return true;
}

void MightyEffect::Begin()
{
	CGameObject::Begin();
}

void MightyEffect::Update(float fTime)
{
	CGameObject::Update(fTime);





	if (true == m_pAnimation->IsSequenceEnd())
	{
		Kill();
	}
}

void MightyEffect::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void MightyEffect::Start(float fTime, const Vector3 & vPos)
{
}

void MightyEffect::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
}

