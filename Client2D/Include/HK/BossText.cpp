#include "BossText.h"
#include "Component/Text.h"
#include "EngineGlobals.h"
#include "Input.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "../GameMode/MainGameMode.h"

#include <Windows.h>

#include "HollowKnight.h"

BossText::BossText()
{
	m_pText = nullptr;
	m_pHK = nullptr;
}


BossText::~BossText()
{
	SAFE_RELEASE(m_pText);
}

bool BossText::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pText = CGameObject::CreateComponent<CText>("BossText");

	SetRoot(m_pText);

	m_pText->SetRelativePos(1320.f, 100.f, 0.f);
	m_pText->SetRenderArea(1320.f, 100.f, 1920.f, 0.f);

	m_pText->SetText(TEXT("FALSE KING"));
	m_pText->SetShadow(true);
	m_pText->SetShadowColor(0.2f, 0.2f, 0.2f, 1.f);
	m_pText->SetShadowOffset(Vector3(2.f, -2.f, 0.f));
	m_pText->SetShadowOpacity(0.6f);
	m_pText->ShadowAlphaBlend(true);
	m_pText->SetFont("NormalText1");
	m_pText->SetSize(80.f);

	m_pText->SetColor(1.f, 1.f, 1.f, 1.f);
	m_pText->SetOpacity(1.f);
	m_pText->AlphaBlend(true);

	m_pHK = (HollowKnight*)m_pScene->GetGameMode()->GetPlayer();

	return true;
}

void BossText::Begin()
{
	CGameObject::Begin();
}

void BossText::Update(float fTime)
{
	CGameObject::Update(fTime);

	m_fLifeTime += fTime;

	if (m_fLifeTime >= m_fLifeTotalTime)
	{
		Kill();

	}

	m_pText->SetOpacity(m_fLifeTotalTime - m_fLifeTime);

}

void BossText::Render(float fTime)
{
	CGameObject::Render(fTime);
}
