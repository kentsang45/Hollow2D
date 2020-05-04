#include "HKStage.h"

#include "EngineGlobals.h"
#include "Input.h"

#include "Scene/Scene.h"

#include "Device.h"

#include "Component/CameraComponent.h"
#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"



#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Component/ColliderSphere2D.h"
#include "Component/ColliderRect.h"

#include "HK/HollowKnight.h"


HKStage::HKStage()
	: m_pMaterial(nullptr)
	, m_pMesh(nullptr)
	, m_pMovement(nullptr)
{
}

HKStage::~HKStage()
{
	SAFE_RELEASE(m_pMaterial);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMovement);
}

bool HKStage::Init()
{
	if (false == CGameObject::Init())
	{
		return false;
	}

	int scaleX = 100.f;
	int scaleY = 100.f;

	
	m_pMesh = CreateComponent<CStaticMeshComponent>("Mesh");
	CStaticMesh* pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pMesh->SetStaticMesh(pMesh);
	SAFE_RELEASE(pMesh);


	SetRoot(m_pMesh);

	m_pMesh->SetRelativePos(0.f, 0.f, 0.f);
	m_pMesh->SetRelativeScale(scaleX, scaleY, 1.f);
	m_pMesh->SetPivot(.5f, .5f, 0.f);

	m_pMovement = CGameObject::CreateComponent<CCharacterMovementComponent>("Movement");
	m_pMovement->SetUpdateComponent(m_pMesh);

	return true;
}

void HKStage::Begin()
{
	CGameObject::Begin();
}

void HKStage::Update(float fTime)
{
	CGameObject::Update(fTime);

	// 플레이어가 지도 중심에서 X만큼 움직인 경우 배경은 X * ratio 만큼 움직인다.
	Vector3 hkPos = m_pHK->GetWorldPos();
	
	float hkX = hkPos.x;
	float centerX = m_iSizeX * 0.5f + ((m_iStage - 1 ) * 10000.f) ;
	float centerY = m_iSizeY * 0.5f;

	float distance = hkX - centerX;

	float ratio = 0.f;

	switch (m_iDepth)
	{
	case 0:
		ratio = 0.009f;
		break;
	case 1:
		ratio = 0.f;
		break;
	case 2:
		ratio = 0.009f;
		break;
	case 3:
		ratio = 0.02f;
		break;
	case 4:
		ratio = 0.1f;
		break;
	case 5:
		ratio = 0.3f;
		break;
	default:
		BOOM;
		break;
	}

	Vector3 pos = Vector3(centerX + distance * ratio, -m_iSizeY * 0.5f, (float)m_iDepth);

	SetRelativePos(pos);

}

void HKStage::Render(float fTime)
{
	if (m_pHK->GetStageNumber() == m_iStage)
	{
		if (2 == m_pHK->GetStageNumber())
		{
			int a = 0;
		}

		CGameObject::Render(fTime);
	}
}

void HKStage::SetScale(const Vector3 & vScale)
{
	m_pMesh->SetRelativeScale(Vector3(vScale.x, vScale.y, 1.f));
}

// Z가 낮을수록 먼저 렌더링
void HKStage::PlaceAt(int level, int layerLevel)
{
	m_iStage = level;

	float X = 0.f;
	float Y = 0.f;
	int sizeX = 0 + (level-1) * 10000;
	int sizeY = 0;

	switch (level)
	{
	case 1:
		// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
		sizeX = 6700;
		sizeY = 1800;
		X = (level - 1) * 10000 + sizeX * 0.5f;
		Y = sizeY * 0.5f;

		m_pMesh->SetRelativeScale(6700, 1800.f, 1.f);

		switch (layerLevel)
		{
		case 0:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 1.f);
	
			break;
		case 1:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1M_BACK");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 2.f);
		
			break;
		case 2:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1M_BACK2");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 3.f);
		
			break;
		case 3:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1M_BACK3");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 4.f);
		
			break;
		case 4:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1M_BACK4");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 5.f);

			break;
		case 5:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage1M_FRONT");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 0.f);
	
			break;
		default:
			BOOM; 
			break;
		}

		break;

	case 2:

		// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
		sizeX = 5200;
		sizeY = 1750;
		X = (level - 1) * 10000 + sizeX * 0.5f;
		Y = sizeY * 0.5f;

		m_pMesh->SetRelativeScale((float)5200, (float)1750, 1.f);

		switch (layerLevel)
		{
		case 0:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 1.f);
			break;
		case 1:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2M_BACK");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 2.f);
			break;
		case 2:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2M_BACK2");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 3.f);
			break;
		case 3:
			 m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2M_BACK3");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			 SetRelativePos(X, -Y, 4.f);
			break;
		case 4:
			 m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2M_BACK4");
			 m_pMesh->SetRelativePos(X, -Y, 0.f);
			 SetRelativePos(X, -Y, 5.f);
			break;
		case 5:
		 	m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage2M_FRONT");
		 	m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 0.f);
			break;
		default:
			BOOM;
			break;
		}
		break;

	case 3:

		// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
		sizeX = 1950;
		sizeY = 4800;
		X = (level - 1) * 10000 + sizeX * 0.5f;
		Y = sizeY * 0.5f;
		m_pMesh->SetRelativeScale((float)1950, (float)4800, 1.f);

		switch (layerLevel)
		{
		case 0:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 1.f);
			break;
		case 1:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3M_BACK");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 2.f);
			break;
		case 2:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3M_BACK2");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 3.f);
			break;
		case 3:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3M_BACK3");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 4.f);
			break;
		case 4:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3M_BACK4");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 5.f);
			break;
		case 5:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage3M_FRONT");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 0.f);
			break;
		default:
			BOOM;
			break;
		}

		break;

	case 4:
		
		// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
		sizeX = 6900;
		sizeY = 1800;
		X = (level - 1) * 10000 + sizeX  * 0.5f;
		Y = sizeY  * 0.5f;

		m_pMesh->SetRelativeScale((float)6900, (float)1800, 1.f);

		switch (layerLevel)
		{
		case 0:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 1.f);
			break;
		case 1:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4M_BACK");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 2.f);
			break;
		case 2:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4M_BACK2");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 3.f);
			break;
		case 3:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4M_BACK3");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 4.f);
			break;
		case 4:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4M_BACK4");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 5.f);
			break;
		case 5:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage4M_FRONT");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 0.f);
			break;
		default:
			BOOM;
			break;
		}

		break;

	case 5:

		// 사이즈의 절반만큼 간다. + 여태까지 위치만큼 간다.
		sizeX = 5000;
		sizeY = 1950;
		X = (level - 1) * 10000 + sizeX * 0.5f;
		Y = sizeY * 0.5f;
		m_pMesh->SetRelativeScale((float)5000, (float)1950, 1.f);

		switch (layerLevel)
		{
		case 0:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 1.f);
			break;
		case 1:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5M_BACK");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 2.f);
			break;
		case 2:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5M_BACK2");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 3.f);
			break;
		case 3:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5M_BACK3");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 4.f);
			break;
		case 4:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5M_BACK4");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 5.f);
			break;
		case 5:
			m_pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("Stage5M_FRONT");
			m_pMesh->SetRelativePos(X, -Y, 0.f);
			SetRelativePos(X, -Y, 0.f);
			break;
		default:
			BOOM;
			break;
		}

		break;
	default:
		BOOM;
		break;
	}

	switch (layerLevel)
	{
	case 0:
		m_iDepth = 1;
		break;
	case 1:
		m_iDepth = 2;
		break;
	case 2:
		m_iDepth = 3;
		break;
	case 3:
		m_iDepth = 4;
		break;
	case 4:
		m_iDepth = 5;
		break;
	case 5:
		m_iDepth = 0;
		break;
	default:
		BOOM;
		break;
	}




	m_iSizeX = sizeX;
	m_iSizeY = sizeY;

	m_pMesh->SetMaterial(m_pMaterial);
}
	

