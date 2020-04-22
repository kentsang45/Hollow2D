#include "HKButton.h"

#include "Component/UIButton.h"
#include "EngineGlobals.h"

HKButton::HKButton()
{
	m_bOn = true;
	m_pButton = nullptr;
}

HKButton::~HKButton()
{
	SAFE_RELEASE(m_pButton);
}

bool HKButton::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pButton = CGameObject::CreateComponent<CUIButton>("Button");

	SetRoot(m_pButton);

	m_pButton->SetRelativeScale(200.f, 200.f, 1.f);
	m_pButton->SetRelativePos(100.f, 800.f, 0.f);

	m_pButton->SetButtonStyleTexture(BS_NORMAL, "ButtonOn", TEXT("HKBUTTON_ON.png"));
	// m_pButton->SetButtonStyleTexture(BS_MOUSEON, "ButtonOn", TEXT("HKBUTTON_ON.png"));
	// m_pButton->SetButtonStyleTexture(BS_CLICK, "ButtonOn", TEXT("HKBUTTON_ON.png"));
	// m_pButton->SetButtonStyleTexture(BS_DISABLE, "ButtonOn", TEXT("HKBUTTON_ON.png"));

	// m_pButton->SetButtonStyleColor(BS_NORMAL, Vector4(1.f, 1.f, 1.f, 1.f));
	// m_pButton->SetButtonStyleColor(BS_MOUSEON, Vector4(1.f, 1.f, 1.f, 1.f));
	// m_pButton->SetButtonStyleColor(BS_CLICK, Vector4(.5f, .5f, .5f, 1.f));
	// m_pButton->SetButtonStyleColor(BS_DISABLE, Vector4(1.f, 1.f, 1.f, 1.f));

	m_pButton->SetButtonEvent(BE_CLICK, this, &HKButton::ClickCallback);

	return true;
}

void HKButton::Begin()
{
	CGameObject::Begin();
}

void HKButton::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void HKButton::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void HKButton::ClickCallback(float fTime)
{
	if (true == m_bOn)
	{
		m_pButton->SetButtonStyleTexture(BS_NORMAL, "ButtonOff", TEXT("HKBUTTON_OFF.png"));
		m_bOn = false;
	}
	else
	{		
		m_pButton->SetButtonStyleTexture(BS_NORMAL, "ButtonOn", TEXT("HKBUTTON_ON.png"));
		m_bOn = true;
	}
	
}
