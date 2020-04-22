#include "UIHP.h"

#include "Component/UIAnimation.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Resource/ResourceManager.h"
#include "Resource/Material.h"



UIHP::UIHP()
{
	m_bOn = true;

	m_pUI = nullptr;
	m_bEmpty = false;
	m_eState = HP_NORMAL;
}

UIHP::~UIHP()
{
	SAFE_RELEASE(m_pUI);

}

bool UIHP::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pUI = CGameObject::CreateComponent<CUIAnimation>("UIHP");

	SetRoot(m_pUI);

	m_pUI->SetRelativeScale(100.f, 100.f, 1.f);
	// m_pUI->SetRelativePos(330.f, 930.f, 0.f);

	// m_pUI->SetTexture("HP", TEXT("HP0.png"));

	m_pUI->CreateAnim2D();

	m_pUI->AddAnim2DSequence("UIHP");
	m_pUI->AddAnim2DSequence("BREAKHP");
	m_pUI->AddAnim2DSequence("EMPTYHP");

	m_pUI->ChangeAnimation("UIHP");



	return true;
}

void UIHP::Begin()
{
	CGameObject::Begin();
}

void UIHP::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (HP_BREAKING == m_eState && true == m_pUI->IsAnimationOver())
	{
		Empty();
	}
}

void UIHP::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void UIHP::BreakHP()
{
	m_pUI->ChangeAnimation("BREAKHP");
	m_bEmpty = true;
	m_eState = HP_BREAKING;
}

void UIHP::Normal()
{
	m_pUI->ChangeAnimation("UIHP");
	m_eState = HP_NORMAL;
}

void UIHP::Empty()
{
	m_pUI->ChangeAnimation("EMPTYHP");
	m_eState = HP_EMPTY;
}
