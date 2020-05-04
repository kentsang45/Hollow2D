#include "SoundObject.h"
#include "Component/Audio.h"

SoundObject::SoundObject() :
	m_pAudio(nullptr)
{
}

SoundObject::~SoundObject()
{
	SAFE_RELEASE(m_pAudio);
}

void SoundObject::SetSound(const string & strKey, const char * pFileName)
{
	m_pAudio->SetSound(strKey, false, pFileName);

	m_pSoundName = strKey;
	m_pFileName = pFileName;
	// m_pAudio->SetSound(strKey, false, pFileName);
	m_pAudio->Play();
}

void SoundObject::StopSO()
{


	//if (nullptr != m_pAudio)
	//{
	//	m_pAudio->Pause();
	//	m_pAudio->Kill();
	//	m_pAudio = nullptr;
	//}
	
	 m_pAudio->Stop();
}

void SoundObject::PlaySO()
{
	if (nullptr == m_pAudio)
	{
		m_pAudio = CGameObject::CreateComponent<CAudio>("BGM");
		SetRoot(m_pAudio);
		m_pAudio->SetSound(m_pSoundName, false, m_pFileName.c_str());
	}

	m_pAudio->Play();
}

bool SoundObject::IsPlaying() const
{
	if (nullptr == m_pAudio)
	{
		return false;
	}

	// return true;

	if (true == m_pAudio->IsPause())
	{
		return false;
	}

	if (true == m_pAudio->IsPlay())
	{
		return false;
	}

	return m_pAudio->IsPlay();
}

bool SoundObject::Init()
{
	if (!CGameObject::Init())
		return false;

	m_pAudio = CGameObject::CreateComponent<CAudio>("BGM");
	SetRoot(m_pAudio);

	/*m_pAudio->SetSound("Demasia", false, "Demasia.mp3");
	m_pAudio->Play();*/



	return true;
}

void SoundObject::Begin()
{
	CGameObject::Begin();
}

void SoundObject::Update(float fTime)
{
	CGameObject::Update(fTime);
}

void SoundObject::Render(float fTime)
{
	CGameObject::Render(fTime);
}
