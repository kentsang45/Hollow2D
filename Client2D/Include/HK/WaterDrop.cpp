#include "WaterDrop.h"

#include "EngineGlobals.h"

#include "Scene/Scene.h"

#include "Device.h"
#include "Resource/ResourceManager.h"
#include "Component/Animation2D.h"
#include "Resource/Animation2DSequence.h"
#include "Component/ColliderRect.h"

#include "HKMode.h"

#include "../RandomNumber.h"
#include "EffectSound.h"
#include "HollowKnight.h"

WaterDrop::WaterDrop()
{
}

WaterDrop::~WaterDrop()
{
	SAFE_RELEASE(m_pAnimation);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
	SAFE_RELEASE(m_pBody);
}

bool WaterDrop::Init()
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
	m_pMesh->SetAnimation2D(m_pAnimation);

	m_pAnimation->AddAnimation2DSequence("WATER_DROP");
	m_pAnimation->AddAnimation2DSequence("WATER_DROPING");
	m_pAnimation->AddAnimation2DSequence("WATER_DROP_END");


	SetRoot(m_pMesh);

	m_pMovement = CGameObject::CreateComponent<CProjectileMovementComponent>("WaterDropMovement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	///////////////////////////////////////////////////////////


	m_pBody->AddBlockCallback<WaterDrop>(this, &WaterDrop::OnBlock);
	m_pBody->SetCollisionProfile("Object");

	m_pMesh->AddChild(m_pBody, TR_POS);
	m_pBody->SetExtent(100.f, 100.f);
	m_pBody->SetPivot(0.5f, 0.5f, 0.f);

	SAFE_RELEASE(pMesh);
	SAFE_RELEASE(pMaterial);

	m_pMesh->SetRelativeScale(100.f, 100.f, 1.f);
	m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	m_pAnimation->ChangeAnimation("WATER_DROP");

	m_pMovement->SetMoveSpeed(1000.f);


	m_fWaitTotalTime = (float)RandomNumber::GetRandomNumberTime(400, 600) * 0.01f;
	// 4초 ~ 6초

	m_iStyle = RandomNumber::GetRandomNumberTime(1, 4);


	return true;
}

void WaterDrop::Begin()
{
	CGameObject::Begin();

	m_pHK = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();
}

void WaterDrop::Update(float fTime)
{
	CGameObject::Update(fTime);

	m_fWaitTime += fTime;



	if (0 == m_iDir)
	{
		int a = 0;
	}

	if (true == m_bStart)
	{
		m_pMesh->SetPivot(0.5f, 0.5f, 0.f);

		if (true == m_pAnimation->IsSequenceEnd())
		{
			m_bStart = false;
			m_bFalling = true;
			m_pAnimation->ChangeAnimation("WATER_DROPING");
		}
	}
	else if (true == m_bFalling)
	{
		m_pMovement->AddMovement(GetWorldAxis(AXIS_Y) * -1.f);
	}
	else if(true == m_bEnd)
	{
		if (true == m_pAnimation->IsSequenceEnd())
		{
			m_bStart = false;
			m_bFalling = false;
			m_bEnd = false;
		}

	}

	if (m_fWaitTime >= m_fWaitTotalTime)
	{
		m_fWaitTime = 0.f;
		m_bStart = true;
		m_bFalling = false;
		m_bEnd = false;
		SetRelativePos(m_vStartPos);
		m_pAnimation->ChangeAnimation("WATER_DROP");
	}
}

void WaterDrop::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void WaterDrop::Start(float fTime, const Vector3 & vPos)
{
}

void WaterDrop::OnBlock(CColliderBase * pSrc, CColliderBase * pDest, float fTime)
{
	if (nullptr == pDest)
	{
		return;
	}

	if (true == pDest->IsStage() || true == pDest->IsPlayer())
	{
		if (true == m_bFalling)
		{
			m_bStart = false;
			m_bFalling = false;
			m_bEnd = false;
			m_pAnimation->ChangeAnimation("WATER_DROP_END");
			m_pMesh->SetPivot(0.5f, 0.4f, 0.f);


			EffectSound*	pFireSound = m_pScene->SpawnObject<EffectSound>(GetWorldPos() + GetWorldAxis(AXIS_Y) * 200.f,
				Vector3(0.f, 0.f, GetRelativeRot().z));

			if (1 == m_iStyle)
			{
				m_strSoundName = "water_drip_1";
				m_strSoundFileName = m_strSoundName;
				m_strSoundFileName.append(".wav");
			}
			else if (2 == m_iStyle)
			{
				m_strSoundName = "water_drip_2";
				m_strSoundFileName = m_strSoundName;
				m_strSoundFileName.append(".wav");
			}
			else if (3 == m_iStyle)
			{
				m_strSoundName = "water_drip_3";
				m_strSoundFileName = m_strSoundName;
				m_strSoundFileName.append(".wav");
			}
			else if (4 == m_iStyle)
			{
				m_strSoundName = "water_drip_4";
				m_strSoundFileName = m_strSoundName;
				m_strSoundFileName.append(".wav");
			}

			pFireSound->SetSound(m_strSoundName, m_strSoundFileName.c_str());

			float dis = m_pHK->GetWorldPos().x - GetWorldPos().x;

			if (dis < 0)
			{
				dis *= -1.f;
			}


			// 1000 이상이면 0, 0이면 100
			dis = dis * 0.1f;

			dis = 100.f - dis;

			if (dis < 0)
			{
				dis = 0;
			}

			pFireSound->SetVol((int)dis);



			SAFE_RELEASE(pFireSound);
		}		
	}



}

CColliderRect * WaterDrop::GetBody() const
{
	return m_pBody;
}




void WaterDrop::PlaceAt(int sizeX, int sizeY, int leftTopX, int leftTopY, int iStyle)
{
	int m_iSizeX = 100;
	int m_iSizeY = 100;

	// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
	float X = (m_iStageNumber - 1) * 10000.f + m_iSizeX * 0.5f + leftTopX * 50.f;
	float Y = m_iSizeY * 0.5f + leftTopY * 50.f;

	// m_pMesh->SetRelativePos(X, -Y, -1.f);
	// m_pBody->SetRelativePos(X, -Y, 0.f);
	m_vStartPos = Vector3(X, -Y, 0.f);

	SetRelativePos(m_vStartPos);
	m_pBody->SetRelativePos(0.f, 0.f, 0.f);

	m_vStartPos = Vector3(X, -Y, 0.f);

}
