#include "HPEffect.h"

#include "Component/UIAnimation.h"
#include "Component/UIImage.h"

#include "EngineGlobals.h"

#include "Resource/Animation2DSequence.h"
#include "Component/Animation2D.h"

#include "Resource/ResourceManager.h"
#include "Resource/Material.h"

#include "../RandomNumber.h"

HPEffect::HPEffect()
{
	m_bOn = true;

	m_pUI = nullptr;
	m_bEmpty = false;
	m_iDir = 1;
}

HPEffect::~HPEffect()
{
	SAFE_RELEASE(m_pUI);

}

bool HPEffect::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pUI = CGameObject::CreateComponent<CUIImage>("HPEffect");

	SetRoot(m_pUI);

	// m_pUI->SetRelativePos(330.f, 930.f, 0.f);
	// m_pUI->SetTexture("HP", TEXT("HP0.png"));

	//m_pUI->CreateAnim2D();

	//m_pUI->AddAnim2DSequence("HPEffect");

	//m_pUI->ChangeAnimation("HPEffect");

	m_pUI->SetTexture("HPEffect", TEXT("HOLLOW/Effect/Soft.png"));

	int ran = RandomNumber::GetRandomNumber(0, 40);
	
	m_pUI->SetRelativeScale(1.f + (float)ran, 1.f + (float)ran, 1.f);

	m_fLifeTotalTime = .1f + RandomNumber::GetRandomNumber(0, 70) / 100.f;

	m_fMoveSpeed = (float)RandomNumber::GetRandomNumber(5, 30) * 0.2f;


	// m_pUI->Begin();
	// m_pUI->Unable();

	return true;
}

void HPEffect::Begin()
{
	CGameObject::Begin();

}

void HPEffect::Update(float fTime)
{
	CGameObject::Update(fTime);

	// ÀÌµ¿
	Vector3 newPos = GetRelativePos() + Vector3(0.f, (float)(m_fMoveSpeed * m_iDir), 0.f);
	m_pUI->SetRelativePos(newPos);









	if (m_fLifeTime < m_fLifeTotalTime)
	{
		m_fLifeTime += fTime;
	}
	else
	{
		Kill();
	}
}

void HPEffect::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void HPEffect::SetDown()
{
	m_iDir = -1.f;
}

