#include "BabyFace.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"




BabyFace::BabyFace()
	: m_bIsOn(false)
	, m_vPlayerPos(Vector3::Zero)
{
}

BabyFace::~BabyFace()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pBody);
}

bool BabyFace::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	m_pMesh = CreateComponent <CStaticMeshComponent>("Mesh");
	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();
	m_pBody = CreateComponent<CColliderRect>("FireBody");


	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);


	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("AttackEffectMaterial");
	m_pMesh->SetMaterial(pMaterial);

	m_pAnimation->AddAnimation2DSequence("BF_DIE");
	m_pAnimation->AddAnimation2DSequence("BF_DIELAND");
	m_pAnimation->AddAnimation2DSequence("BF_DEAD");
	m_pMesh->SetAnimation2D(m_pAnimation);

	SetRoot(m_pMesh);

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("BabyFaceMovement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	///////////////////////////////////////////////////////////


	m_pBody->AddBlockCallback<BabyFace>(this, &BabyFace::OnBlock);
	m_pBody->SetCollisionProfile("Object");

	m_pMesh->AddChild(m_pBody, TR_POS);
	m_pBody->SetExtent(100.f, 100.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(300.f, 300.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.4f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("BF_DIE");

	m_pMovement->SetMoveSpeed(600.f);

	SetPhysics(true);

	m_eAnimState = BS_DIE;

	return true;
}

void BabyFace::Begin()
{
	CGameObject::Begin();
}

void BabyFace::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (true == m_bDead)
	{
		ClearGravity();
		return;
	}

	switch (m_eAnimState)
	{
	case BS_DIE:
		Die(fTime);
		break;
	}

	if (true == m_bIsOn)
	{
		m_pAnimation->ChangeAnimation("BF_DIELAND");
		m_eAnimState = BS_DEAD;
		m_bIsOn = false;
	}

	if (m_eAnimState == BS_DEAD && m_pAnimation->IsSequenceEnd())
	{
		m_pAnimation->ChangeAnimation("BF_DEAD");
		m_bDead = true;

		return;
	}








	if (0 == m_iDir)
	{
		int a = 0;
	}

	m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * m_iDir);
}

void BabyFace::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void BabyFace::Start(float fTime, const Vector3 & vPos)
{
}

void BabyFace::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (true == pDest->IsStage())
	{
		ClearGravity();
		m_bIsOn = true;
		m_eAnimState = BS_DIELAND;
	}
}

CColliderRect * BabyFace::GetBody() const
{
	return m_pBody;
}

void BabyFace::Die(float fTime)
{
	if (false == m_bJump)
	{
		float m_fCurrentForce = 400.f;

		m_fForce = m_fCurrentForce;

		m_bJump = true;
		m_bOnLand = false;
	}

	m_pMovement->AddMovement(GetWorldAxis(AXIS_X) * m_iDir);
}

//void BabyFace::SetAnim(BUG_STATE eState)
//{
//	if (eState == m_eAnimState)
//	{
//		return;
//	}
//
//	// m_eState = eState;
//	m_eAnimState = eState;
//
//
//	std::string stateName = m_strAniName;
//	stateName.append("_");
//	stateName.append(m_vecStateName[eState]);
//
//	m_pAnimation->ChangeAnimation(stateName);
//
//}
//
