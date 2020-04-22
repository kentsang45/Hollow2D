
#include "BGMObject.h"
#include "Component/Audio.h"

BGMObject::BGMObject() :
	m_pAudio(nullptr)
{
}

BGMObject::~BGMObject()
{
	SAFE_RELEASE(m_pAudio);
}

bool BGMObject::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pAudio = CGameObject::CreateComponent<CAudio>("BGM");

	m_pAudio->SetSound("CrossroadsBass", true, "CrossroadsBass.wav");
	m_pAudio->Play();

	SetRoot(m_pAudio);

	return true;
}

void BGMObject::Begin()
{
	CGameObject::Begin();
}

void BGMObject::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void BGMObject::Render(float fTime)
{
	CGameObject::Render(fTime);
}
