
#include "TestButton.h"
#include "Component/UIButton.h"
#include "EngineGlobals.h"

CTestButton::CTestButton()
{
	m_pButton = nullptr;
}

CTestButton::~CTestButton()
{
	SAFE_RELEASE(m_pButton);
}

bool CTestButton::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pButton = CGameObject::CreateComponent<CUIButton>("Button");

	SetRoot(m_pButton);

	m_pButton->SetRelativeScale(200.f, 200.f, 1.f);
	m_pButton->SetRelativePos(800.f, 200.f, 0.f);

	m_pButton->SetButtonStyleTexture(BS_NORMAL, "StartButton", TEXT("Start.png"));
	m_pButton->SetButtonStyleTexture(BS_MOUSEON, "StartButton", TEXT("Start.png"));
	m_pButton->SetButtonStyleTexture(BS_CLICK, "StartButton", TEXT("Start.png"));
	m_pButton->SetButtonStyleTexture(BS_DISABLE, "StartButton", TEXT("Start.png"));

	m_pButton->SetButtonStyleColor(BS_NORMAL, Vector4(0.8f, 0.8f, 0.8f, 1.f));
	m_pButton->SetButtonStyleColor(BS_MOUSEON, Vector4(1.f, 1.f, 1.f, 1.f));
	m_pButton->SetButtonStyleColor(BS_CLICK, Vector4(0.6f, 0.6f, 0.6f, 1.f));
	m_pButton->SetButtonStyleColor(BS_DISABLE, Vector4(0.3f, 0.3f, 0.3f, 1.f));

	m_pButton->SetButtonEvent(BE_CLICK, this, &CTestButton::ClickCallback);

	return true;
}

void CTestButton::Begin()
{
	CGameObject::Begin();
}

void CTestButton::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void CTestButton::Render(float fTime)
{
	CGameObject::Render(fTime);
}

void CTestButton::ClickCallback(float fTime)
{
	//MessageBox(nullptr, TEXT("Click"), TEXT("Click"), MB_OK);
}
