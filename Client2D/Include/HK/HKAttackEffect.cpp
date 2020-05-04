#include "HKAttackEffect.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"
#include "HitEffect.h"
#include "SideEffect.h"

#include "HollowKnight.h"

HKAttackEffect::HKAttackEffect()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

HKAttackEffect::~HKAttackEffect()
{
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

bool HKAttackEffect::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pBody = CreateComponent<CColliderRect>("AttackBody");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();


	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);


	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pMesh->SetMaterial(pMaterial);

	m_pAnimation->AddAnimation2DSequence("ATTACK_EFFECT");
	m_pMesh->SetAnimation2D(m_pAnimation);

	m_pMesh->AddChild(m_pBody, TR_POS);
	m_pBody->SetExtent(150.f, 150.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);
	m_pBody->AddBlockCallback<HKAttackEffect>(this, &HKAttackEffect::OnBlock);
	m_pBody->SetCollisionProfile("PlayerProjectile");

	SetRoot(m_pMesh);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	// m_pMesh->SetRelativePos(900.f, 900.f, -0.5f);
	m_pMesh->SetRelativeScale(800.f, 800.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);
	// 

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("ATTACK_EFFECT");

	return true;
}

void HKAttackEffect::Begin()
{
	CGameObject::Begin();
}

void HKAttackEffect::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (true == m_bIsOn)
	{
		if (true == m_pBody->IsOverlap())
		{
			// m_pHitEffect->Start(fTime, m_pBody->GetColliderIntersection());
			m_bIsOn = false;
		}
	}


	if (true == m_pAnimation->IsSequenceEnd())
	{
		Enable(false);
		// m_pBody->Enable(false);
		// m_pBody->SetOnOff(false);

		m_bIsOn = false;

		m_pBody->SetWorldPos(Vector3::Zero);

		Kill();
	}
}

void HKAttackEffect::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void HKAttackEffect::Start(float fTime, const Vector3& vPos)
{
	Enable(true);
	m_pBody->Enable(true);
	m_pBody->SetOnOff(true);

	m_bIsOn = true;

	m_vPlayerPos = vPos + Vector3(151.f, 0.f, -0.5f);

	m_pBody->SetWorldPos(vPos + Vector3(151.f, 0.f, -0.5f));
	m_pMesh->SetWorldPos(vPos + Vector3(151.f, 0.f, -0.5f));


}



void HKAttackEffect::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	// HitEffect
	if (nullptr == pDest)
	{
		return;
	}

	if (true == pDest->IsMonster())
	{
		if (false == pDest->GetBlock())
		{
			HitEffect* attack = m_pScene->SpawnObject<HitEffect>(pSrc->GetIntersect() + Vector3(0.f, 0.f, -0.51f));

			SAFE_RELEASE(attack);

			SideEffect* side = m_pScene->SpawnObject<SideEffect>(pSrc->GetIntersect() + Vector3(0.f, 0.f, -0.52f));

			SAFE_RELEASE(side);


			HollowKnight* hk = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();
			hk->CameraShakeOn(0.4f, 10);
		}
		else
		{

		}
	}
	else
	{
		if ("Sencer" == pDest->GetCollisionProfile()->strName)
		{
			return;
		}

		HitEffect* attack = m_pScene->SpawnObject<HitEffect>(pSrc->GetIntersect() + Vector3(0.f, 0.f, -0.51f));

		SAFE_RELEASE(attack);

		SideEffect* side = m_pScene->SpawnObject<SideEffect>(pSrc->GetIntersect() + Vector3(0.f, 0.f, -0.52f));

		SAFE_RELEASE(side);
	}

}

CColliderRect * HKAttackEffect::GetBody() const
{
	return m_pBody;
}

void HKAttackEffect::Flip(int iFlip)
{

		CGameObject::Flip(iFlip);




}

