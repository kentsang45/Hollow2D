#include "TestObject.h"
#include "EngineGlobals.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Bullet.h"
#include "Component/ProjectileMovementComponent.h"
#include "Component/CameraComponent.h"
#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Scheduler.h"
#include "Component/ColliderRect.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderOBB2D.h"


CTestObject::CTestObject()
{
	m_pBodyOBB2D = nullptr;
	m_pBodySphere = nullptr;
	m_pBody = nullptr;
	m_pAnimation = nullptr;
	m_pCamera = nullptr;
	m_pRotPivot1 = nullptr;
	m_pRotPivot2 = nullptr;
	m_pRotPivot = nullptr;
	m_pChild2Mesh = nullptr;
	m_pChild1Mesh = nullptr;
	m_pChild3Mesh = nullptr;
	m_pChild4Mesh = nullptr;
	m_pMesh = nullptr;
	m_pMovement = nullptr;
}

CTestObject::~CTestObject()
{
	SAFE_RELEASE(m_pBodyOBB2D);
	SAFE_RELEASE(m_pBodySphere);
	SAFE_RELEASE(m_pBody);
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pCamera);
	SAFE_RELEASE(m_pRotPivot1);
	SAFE_RELEASE(m_pRotPivot2);
	SAFE_RELEASE(m_pRotPivot);
	SAFE_RELEASE(m_pChild2Mesh);
	SAFE_RELEASE(m_pChild1Mesh);
	SAFE_RELEASE(m_pChild3Mesh);
	SAFE_RELEASE(m_pChild4Mesh);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

bool CTestObject::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pRotPivot = CreateComponent<CSceneComponent>("RotPivot");
	m_pRotPivot1 = CreateComponent<CSceneComponent>("RotPivot1");
	m_pRotPivot2 = CreateComponent<CSceneComponent>("RotPivot2");
	m_pChild1Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pChild2Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pChild3Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pChild4Mesh = CreateComponent<CStaticMeshComponent>("Mesh");
	m_pCamera = CreateComponent<CCameraComponent>("Camera");
	m_pBody = CreateComponent<CColliderRect>("PlayerBody");
	//m_pBodySphere = CreateComponent<CColliderSphere2D>("PlayerBodySphere");
	//m_pBodyOBB2D = CreateComponent<CColliderOBB2D>("PlayerBodyOBB2D");

	m_pAnimation = CAnimation2D::CreateAnimation2D<CAnimation2D>();

	m_pAnimation->AddAnimation2DSequence("MinionIdle");
	m_pAnimation->AddAnimation2DSequence("MinionWalk");
	m_pAnimation->AddAnimation2DSequence("MinionKick");

	m_pAnimation->SetReturnSequenceName("MinionKick", "MinionIdle");

	m_pMesh->SetAnimation2D(m_pAnimation);

	m_pMesh->AddChild(m_pBody, TR_POS);
	//m_pMesh->AddChild(m_pBodySphere, TR_POS);
	//m_pMesh->AddChild(m_pBodyOBB2D, TR_ROT | TR_POS);

	m_pBody->SetExtent(200.f, 200.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	m_pBody->AddBlockCallback<CTestObject>(this, &CTestObject::OnBlock);
	m_pBody->SetCollisionProfile("Player");

	/*m_pBodySphere->SetSphere(Vector3(200.f, 0.f, 0.f), 100.f);

	m_pBodySphere->AddBlockCallback<CTestObject>(this, &CTestObject::OnBlock);
	m_pBodySphere->SetCollisionProfile("Player");

	m_pBodyOBB2D->SetOBB2D(Vector3(0.f, 0.f, 0.f), 100.f, 100.f);

	m_pBodyOBB2D->AddBlockCallback<CTestObject>(this, &CTestObject::OnBlock);
	m_pBodyOBB2D->SetCollisionProfile("Player");*/

	CStaticMesh*	pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");

	m_pMesh->SetStaticMesh(pMesh);
	m_pChild1Mesh->SetStaticMesh(pMesh);
	m_pChild2Mesh->SetStaticMesh(pMesh);
	m_pChild3Mesh->SetStaticMesh(pMesh);
	m_pChild4Mesh->SetStaticMesh(pMesh);

	SAFE_RELEASE(pMesh);

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerMtrl");

	m_pChild1Mesh->SetMaterial(pMaterial);
	m_pChild2Mesh->SetMaterial(pMaterial);
	m_pChild3Mesh->SetMaterial(pMaterial);
	m_pChild4Mesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("PlayerAnimOutLineMtrl");

	m_pMesh->SetMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);

	SetRoot(m_pMesh);

	m_pMesh->AddChild(m_pCamera, TR_POS);

	m_pCamera->SetCameraType(CT_ORTHOGONAL);

	m_pCamera->SetRelativePos(_RESOLUTION.iWidth / -2.f, _RESOLUTION.iHeight / -2.f, -20.f);

	m_pChild1Mesh->SetRelativePos(-200, 0.f, 0.f);
	m_pChild1Mesh->SetRelativeScale(100.f, 100.f, 1.f);

	m_pChild2Mesh->SetRelativePos(200, 0.f, 0.f);
	m_pChild2Mesh->SetRelativeScale(100.f, 100.f, 1.f);

	m_pChild3Mesh->SetRelativePos(-100, 0.f, 0.f);
	m_pChild3Mesh->SetRelativeScale(50.f, 50.f, 1.f);

	m_pChild4Mesh->SetRelativePos(100, 0.f, 0.f);
	m_pChild4Mesh->SetRelativeScale(50.f, 50.f, 1.f);

	m_pMesh->AddChild(m_pRotPivot, TR_POS | TR_ROT);

	m_pRotPivot->AddChild(m_pChild1Mesh, TR_POS | TR_ROT);
	m_pRotPivot->AddChild(m_pChild2Mesh, TR_POS | TR_ROT);

	m_pChild1Mesh->AddChild(m_pRotPivot1, TR_POS | TR_ROT);
	m_pChild2Mesh->AddChild(m_pRotPivot2, TR_POS | TR_ROT);

	m_pRotPivot1->AddChild(m_pChild3Mesh, TR_POS | TR_ROT);
	m_pRotPivot2->AddChild(m_pChild4Mesh, TR_POS | TR_ROT);

	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	m_pMesh->SetRelativePos(500.f, 500.f, 0.f);
	m_pMesh->SetRelativeScale(200.f, 200.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	GET_SINGLE(CInput)->AddAxisKey("MoveUpDown", DIK_W, 1.f);
	GET_SINGLE(CInput)->AddAxisKey("MoveUpDown", DIK_S, -1.f);
	GET_SINGLE(CInput)->BindAxis<CTestObject>("MoveUpDown", this, &CTestObject::MoveUpDown);

	GET_SINGLE(CInput)->AddAxisKey("RotationZ", DIK_D, 1.f);
	GET_SINGLE(CInput)->AddAxisKey("RotationZ", DIK_A, -1.f);
	GET_SINGLE(CInput)->BindAxis<CTestObject>("RotationZ", this, &CTestObject::MoveSide);

	GET_SINGLE(CInput)->AddActionKey("Fire", DIK_SPACE);
	GET_SINGLE(CInput)->BindAction<CTestObject>("Fire", AKS_PUSH, this, &CTestObject::Fire);

	GET_SINGLE(CInput)->AddActionKey("DeleteChild", DIK_RETURN);
	GET_SINGLE(CInput)->BindAction<CTestObject>("DeleteChild", AKS_PRESS, this, &CTestObject::Delete);

	GET_SINGLE(CInput)->AddActionKey("AttackSpeedUp", DIK_1);
	GET_SINGLE(CInput)->BindAction<CTestObject>("AttackSpeedUp", AKS_PRESS, this, &CTestObject::AttackSpeedUp);

	m_pAnimation->CreateNotify("MinionKick", "Attack", 3);
	m_pAnimation->AddNotifyFunction<CTestObject>("MinionKick", "Attack", this, &CTestObject::AnimAttackNotify);

	return true;
}

void CTestObject::Begin()
{
	CGameObject::Begin();
}

void CTestObject::Update(float fTime)
{
	CGameObject::Update(fTime);

	m_pRotPivot->AddRelativeRotationZ(180.f * fTime);
	m_pRotPivot1->AddRelativeRotationZ(180.f * fTime);
	m_pRotPivot2->AddRelativeRotationZ(180.f * fTime);

	OutLineCBuffer	tBuffer = {};
	tBuffer.iPixelSize = 5;

	Animation2DFrameInfo	tFrameInfo = m_pAnimation->GetAnimFrame();

	tBuffer.vScale	= Vector2(m_pMesh->GetWorldScale().x, m_pMesh->GetWorldScale().y);
	tBuffer.vImageSize = tFrameInfo.vEnd - tFrameInfo.vStart;

	m_pMesh->UpdateMaterialCBufferNode(OUTLINE_CBUFFER, &tBuffer);

	//if (m_pMovement->GetVelocity() == 0.f)
	//	m_pAnimation->ChangeAnimation("MinionIdle");
}

void CTestObject::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CTestObject::MoveUpDown(float fScale, float fTime)
{
	/*char	strText[256] = {};
	sprintf_s(strText, "Scale : %.f\n", fScale);

	OutputDebugStringA(strText);*/

	static bool	bMove = false;

	m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * fScale);

	if (fScale != 0.f)
	{
		bMove = true;
		m_pAnimation->ChangeAnimation("MinionWalk");
	}

	else
	{
		if (bMove)
		{
			m_pAnimation->ChangeAnimation("MinionIdle");
			bMove = false;
		}
	}
}

void CTestObject::MoveSide(float fScale, float fTime)
{
	static bool	bMove = false;

	if (fScale != 0.f)
	{
		bMove = true;
		m_pAnimation->ChangeAnimation("MinionWalk");

		if (fScale < 0.f)
			m_pMesh->SetRelativeRotationY(180.f);

		else
			m_pMesh->SetRelativeRotationY(0.f);

		m_pMovement->AddMovement(GetWorldAxis(AXIS_X));
	}

	else
	{
		if (bMove)
		{
			m_pAnimation->ChangeAnimation("MinionIdle");
			bMove = false;
		}
	}
}

void CTestObject::RotationZ(float fScale, float fTime)
{
	m_pMovement->AddRotationZ(180.f * fScale);
}

void CTestObject::Fire(float fTime)
{
	m_pAnimation->ChangeAnimation("MinionKick");

	CBullet*	pBullet = m_pScene->SpawnObject<CBullet>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		Vector3(0.f, 0.f, GetRelativeRot().z));

	CProjectileMovementComponent*	pMovement = pBullet->FindObjectComponent<CProjectileMovementComponent>();

	pMovement->SetDistance(500.f);

	SAFE_RELEASE(pMovement);

	CColliderRect* pBody = pBullet->GetBody();

	pBody->SetCollisionProfile("PlayerProjectile");

	SAFE_RELEASE(pBullet);
}

void CTestObject::Delete(float fTime)
{
	/*CGameObject*	pChild = m_vecChild[0];

	if (pChild)
		DeleteChild(pChild);*/

	DeleteChild("Child");
}

void CTestObject::AnimAttackNotify(float fTime)
{
	/*CBullet*	pBullet = m_pScene->SpawnObject<CBullet>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
		GetRelativeRot());

	CProjectileMovementComponent*	pMovement = pBullet->FindObjectComponent<CProjectileMovementComponent>();

	pMovement->SetDistance(500.f);

	SAFE_RELEASE(pMovement);
	
	CColliderRect* pBody = pBullet->GetBody();

	pBody->SetCollisionProfile("PlayerProjectile");

	SAFE_RELEASE(pBullet);*/
}

void CTestObject::AttackSpeedUp(float fTime)
{
	CAnimation2DSequence* pSequence = m_pAnimation->FindAnimSequence("MinionKick");

	if (pSequence)
	{
		pSequence->SetPlayScale(1.5f);
		SAFE_RELEASE(pSequence);

		GET_SINGLE(CScheduler)->AddSchedule<CTestObject>("AttackSpeedUp", false, 5.f, this, &CTestObject::AttackBufEnd);
	}
}

void CTestObject::AttackBufEnd()
{
	CAnimation2DSequence* pSequence = m_pAnimation->FindAnimSequence("MinionKick");

	if (pSequence)
	{
		pSequence->SetPlayScale(1.f);
		SAFE_RELEASE(pSequence);
	}
}

void CTestObject::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	// OutputDebugString(TEXT("Block\n"));
}
