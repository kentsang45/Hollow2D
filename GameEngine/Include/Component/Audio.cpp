#include "Audio.h"
#include "../Resource/Sound.h"
#include "../Resource/ResourceManager.h"

CAudio::CAudio() :
	m_pSound(nullptr),
	m_bPlay(false),
	m_strChannelGroup("Normal"),
	m_iVolume(100)
{
	m_bTickUpdate = true;

	SetTypeID<CAudio>();
}

CAudio::CAudio(const CAudio & com) :
	CSceneComponent(com)
{
	m_pSound = com.m_pSound;
	m_iVolume = com.m_iVolume;

	if (m_pSound)
		m_pSound->AddRef();

	m_bPlay = false;

	m_strChannelGroup = com.m_strChannelGroup;
}


CAudio::~CAudio()
{
	SAFE_RELEASE(m_pSound);
}

bool CAudio::IsPlay() const
{
	if (!m_pSound)
		return false;

	bool	bPlaying = false;
	m_pSound->GetChannel()->isPlaying(&bPlaying);

	return bPlaying;
}

void CAudio::SetSound(const string & strName)
{
	SAFE_RELEASE(m_pSound);

	m_pSound = GET_SINGLE(CResourceManager)->FindSound(strName);
}

void CAudio::SetSound(const string & strName, bool bLoop, const char * pFileName, const string & strPathName)
{
	GET_SINGLE(CResourceManager)->LoadSound(strName, bLoop, pFileName, strPathName);

	SAFE_RELEASE(m_pSound);

	m_pSound = GET_SINGLE(CResourceManager)->FindSound(strName);
}

void CAudio::SetChannelGroup(const string & strChannelGroup)
{
	m_strChannelGroup = strChannelGroup;
}

void CAudio::Play()
{
	GET_SINGLE(CResourceManager)->Play(m_pSound, m_strChannelGroup);

	if (!m_pSound->GetChannel())
		return;

	m_pSound->GetChannel()->setVolume(m_iVolume / 100.f);
}

void CAudio::Pause()
{
	GET_SINGLE(CResourceManager)->Pause(m_pSound, m_strChannelGroup);
}

void CAudio::Stop()
{
	if (!m_pSound->GetChannel())
		return;

	bool	bIsPlay = false;
	m_pSound->GetChannel()->isPlaying(&bIsPlay);

	if (bIsPlay)
		m_pSound->GetChannel()->stop();
}

void CAudio::SetVolume(int iVolume)
{
	m_iVolume = iVolume;

	if (!m_pSound->GetChannel())
		return;

	m_pSound->GetChannel()->setVolume(m_iVolume / 100.f);
}

void CAudio::Mute()
{
	if (!m_pSound->GetChannel())
		return;

	m_pSound->GetChannel()->setMute(true);
}

void CAudio::UnMute()
{
	if (!m_pSound->GetChannel())
		return;

	m_pSound->GetChannel()->setMute(false);
}

bool CAudio::Init()
{
	CSceneComponent::Init();

	return true;
}

void CAudio::Begin()
{
	CSceneComponent::Begin();
}

void CAudio::Update(float fTime)
{
	CSceneComponent::Update(fTime);
}

void CAudio::Render(float fTime)
{
	CSceneComponent::Render(fTime);
}
