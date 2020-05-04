#include "CoinUI.h"

#include "Component/UIAnimation.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Resource/ResourceManager.h"
#include "Resource/Material.h"



CoinUI::CoinUI()
{
	m_bOn = true;

	m_pUI = nullptr;
	m_bEmpty = false;
}

CoinUI::~CoinUI()
{
	SAFE_RELEASE(m_pUI);

}

bool CoinUI::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pUI = CGameObject::CreateComponent<CUIAnimation>("CoinUI");

	SetRoot(m_pUI);

	m_pUI->SetRelativeScale(62.f, 62.f, 1.f);
	m_pUI->SetRelativePos(350.f, 860.f, 0.f);

	// m_pUI->SetTexture("HP", TEXT("HP0.png"));

	m_pUI->CreateAnim2D();

	m_pUI->AddAnim2DSequence("COIN_UI");

	m_pUI->ChangeAnimation("COIN_UI");



	return true;
}

void CoinUI::Begin()
{
	CGameObject::Begin();
}

void CoinUI::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CoinUI::Render(float fTime)
{
	CGameObject::Render(fTime);
}
