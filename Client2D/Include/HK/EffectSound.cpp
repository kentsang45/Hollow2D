#include "EffectSound.h"
#include "Component/Audio.h"

EffectSound::EffectSound() :
	m_pAudio(nullptr)
{
}

EffectSound::~EffectSound()
{
	SAFE_RELEASE(m_pAudio);
}

void EffectSound::SetSound(const string & strKey, const char * pFileName)
{
	m_pAudio->SetSound(strKey, false, pFileName);
	m_pAudio->Play();
}

bool EffectSound::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pAudio = CGameObject::CreateComponent<CAudio>("BGM");

	/*m_pAudio->SetSound("Demasia", false, "Demasia.mp3");
	m_pAudio->Play();*/

	SetRoot(m_pAudio);

	return true;
}

void EffectSound::Begin()
{
	CGameObject::Begin();
}

void EffectSound::Update(float fTime)
{
	CGameObject::Update(fTime);

	if (!m_pAudio->IsPlay())
	{
		Kill();
	}
}

void EffectSound::Render(float fTime)
{
	CGameObject::Render(fTime);
}
