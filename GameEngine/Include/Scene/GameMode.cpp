#include "GameMode.h"
#include "Scene.h"
#include "../CameraManager.h"
#include "../Component/CameraComponent.h"
#include "../Object/GameObject.h"

CGameMode::CGameMode()
{
}

CGameMode::~CGameMode()
{
}

CGameObject * CGameMode::GetPlayer() const
{
	return m_pPlayer;
}

void CGameMode::SetPlayer(CGameObject * pPlayer)
{
	m_pPlayer = pPlayer;

	CCameraComponent*	pCamera = pPlayer->FindSceneComponent<CCameraComponent>();

	if (pCamera)
	{
		m_pScene->GetCameraManager()->ChangeMainCamera(pCamera);

		SAFE_RELEASE(pCamera);
	}
}

bool CGameMode::Init()
{
	return true;
}

void CGameMode::Begin()
{
}

void CGameMode::Update(float fTime)
{
}

void CGameMode::Render(float fTime)
{
}
