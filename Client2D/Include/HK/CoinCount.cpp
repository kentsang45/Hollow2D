#include "CoinCount.h"
#include "Component/Text.h"
#include "EngineGlobals.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../GameMode/MainGameMode.h"

#include <Windows.h>

#include "HollowKnight.h"

CoinCount::CoinCount()
{
	m_pText = nullptr;
	m_pHK = nullptr;
}


CoinCount::~CoinCount()
{
	SAFE_RELEASE(m_pText);
}

bool CoinCount::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pText = CGameObject::CreateComponent<CText>("CoinCount");

	SetRoot(m_pText);

	m_pText->SetRelativePos(420.f, 810.f, 0.f);
	m_pText->SetRenderArea(420.f, 810.f, 600.f, 700.f);

	m_pText->SetText(TEXT("0"));
	m_pText->SetShadow(true);
	m_pText->SetShadowColor(0.2f, 0.2f, 0.2f, 1.f);
	m_pText->SetShadowOffset(Vector3(2.f, -2.f, 0.f));
	m_pText->SetShadowOpacity(0.6f);
	m_pText->ShadowAlphaBlend(true);
	m_pText->SetFont("NormalText1");
	m_pText->SetSize(40.f);

	m_pText->SetColor(1.f, 1.f, 1.f, 1.f);
	m_pText->SetOpacity(1.f);
	m_pText->AlphaBlend(true);

	m_pHK = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();

	return true;
}

void CoinCount::Begin()
{
	CGameObject::Begin();
}

void CoinCount::Update(float fTime)
{
	CGameObject::Update(fTime);

	int count = m_pHK->GetCoinCount();

	int   iNum = 1234;
	TCHAR szNum[10];
	swprintf(szNum, TEXT("%d"), count);

	m_pText->SetText(szNum);

}

void CoinCount::Render(float fTime)
{
	CGameObject::Render(fTime);
}
