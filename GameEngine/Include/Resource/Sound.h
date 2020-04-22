#pragma once

#include "../Ref.h"

class ENGINE_DLL CSound :
	public CRef
{
	friend class CResourceManager;

private:
	CSound();
	CSound(const CSound& sound);
	~CSound();

private:
	Sound*		m_pSound;
	Channel*	m_pChannel;

public:
	Channel* GetChannel()	const;
};

