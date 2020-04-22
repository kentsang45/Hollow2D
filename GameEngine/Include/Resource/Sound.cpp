#include "Sound.h"

CSound::CSound() :
	m_pSound(nullptr),
	m_pChannel(nullptr)
{
}

CSound::CSound(const CSound & sound)
{
	m_pSound = sound.m_pSound;
	m_pChannel = nullptr;
}

CSound::~CSound()
{
	m_pSound->release();
}

Channel * CSound::GetChannel() const
{
	return m_pChannel;
}
