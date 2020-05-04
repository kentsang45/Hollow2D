#include "HPHead.h"

#include "Component/UIAnimation.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Resource/ResourceManager.h"
#include "Resource/Material.h"



HPHead::HPHead()
{
	m_bOn = true;

	m_pUI = nullptr;
	m_bEmpty = false;
}

HPHead::~HPHead()
{
	SAFE_RELEASE(m_pUI);

}

bool HPHead::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pUI = CGameObject::CreateComponent<CUIAnimation>("HPHead");

	SetRoot(m_pUI);

	m_pUI->SetRelativeScale(172.f * 1.5f, 106.f * 1.5f, 1.f);
	m_pUI->SetRelativePos(200.f, 870.f, 1.f);

	// m_pUI->SetTexture("HP", TEXT("HP0.png"));

	m_pUI->CreateAnim2D();

	m_pUI->AddAnim2DSequence("HP_HEAD");

	m_pUI->ChangeAnimation("HP_HEAD");
	m_pUI->SetZOrder(-1);


	return true;
}

void HPHead::Begin()
{
	CGameObject::Begin();
}

void HPHead::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void HPHead::Render(float fTime)
{
	CGameObject::Render(fTime);
}
