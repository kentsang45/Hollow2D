#include "CoinEffect.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"

#include "../RandomNumber.h"

#include "HollowKnight.h"


CoinEffect ::CoinEffect ()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

CoinEffect ::~CoinEffect ()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pChildMesh);
	SAFE_RELEASE(m_pRotPivot);
}

bool CoinEffect ::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pChildMesh = CreateComponent <CStaticMeshComponent>("Mesh");



	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);

	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pChildMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pChildMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Empty");
	m_pMesh->SetMaterial(pMaterial);

	m_pMesh->SetRelativeScale(1.f, 1.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	m_pAnimation->AddAnimation2DSequence("COIN_EFFECT");


	m_pChildMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	SAFE_RELEASE(pMaterial);






	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("COIN_EFFECT");



	m_pRotPivot = CreateComponent<CSceneComponent>("RotPivot");
	m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);
	m_pRotPivot->AddChild(m_pChildMesh, TR_POS | TR_ROT);

	m_fRandom = (float)RandomNumber::GetRandomNumber(100, 200) * 0.01f;
	// 1.f ~ 2.f
	m_pChildMesh->SetRelativeScale(345.f * m_fRandom * 0.5f, 51.f * m_fRandom * 0.5f, 1.f);
	m_pChildMesh->SetPivot(0.5f, 0.5f, 0.f);

	float ran = (float)RandomNumber::GetRandomNumber(1, 360);

	m_pRotPivot->AddRelativeRotationZ(ran);


	return true;
}

void CoinEffect ::Begin()
{
	CGameObject::Begin();

	m_pHK = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();
}

void CoinEffect ::Update(float fTime)
{
	CGameObject::Update(fTime);



	m_fTime += fTime;

	float x = 345.f * m_fRandom * 0.5f - 200.f * fTime;
	float y = 51.f * m_fRandom * 0.5f - 50.f * fTime;

	if(x <= 0)
	{
		x = 1.f;
	}
	if (y <= 0)
	{
		y = 1.f;
	}

	m_pChildMesh->SetRelativeScale(x, y, 1.f);


	if (true == m_pAnimation->IsSequenceEnd())
	{
		Kill();
	}

	// SetWorldPos(m_pHK->GetWorldPos());
}

void CoinEffect ::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CoinEffect ::Start(float fTime, const Vector3 & vPos)
{
}

