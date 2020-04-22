#include "TestBar.h"
#include "Component/UIBar.h"
#include "Component/UIImage.h"
#include "EngineGlobals.h"

CTestBar::CTestBar()
{
	m_pBar = nullptr;
}

CTestBar::~CTestBar()
{
	SAFE_RELEASE(m_pBack);
	SAFE_RELEASE(m_pBar);
}

bool CTestBar::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pBar = CGameObject::CreateComponent<CUIBar>("Bar");
	m_pBack = CGameObject::CreateComponent<CUIImage>("Back");

	SetRoot(m_pBack);

	m_pBack->AddChild(m_pBar, TR_POS);

	m_pBack->SetRelativeScale(220.f, 40.f, 1.f);
	m_pBack->SetRelativePos(400.f, 200.f, 0.f);

	m_pBar->SetRelativeScale(200.f, 30.f, 1.f);
	m_pBar->SetRelativePos(10.f, 5.f, 0.f);

	m_pBack->SetTexture("BarBack", TEXT("BarBack.png"));
	m_pBar->SetTexture("Bar", TEXT("BarDefault.bmp"));

	m_fHP = 1000;
	m_fHPMax = 1000;

	return true;
}

void CTestBar::Begin()
{
	CGameObject::Begin();
}

void CTestBar::Update(float fTime)
{
	CGameObject::Update(fTime);

	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_fHP -= 300.f * fTime;

		if(m_fHP < 0)
			m_fHP = 0;

		m_pBar->SetPercent(m_fHP / m_fHPMax);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fHP += 300.f * fTime;

		if (m_fHP >= m_fHPMax)
			m_fHP = m_fHPMax;

		m_pBar->SetPercent(m_fHP / m_fHPMax);
	}
}

void CTestBar::Render(float fTime)
{
	CGameObject::Render(fTime);
}
