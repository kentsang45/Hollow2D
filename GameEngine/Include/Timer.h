#pragma once

#include "GameEngine.h"

class ENGINE_DLL CTimer
{
	friend class CTimerManager;

private:
	CTimer();
	~CTimer();

private:
	LARGE_INTEGER	m_tSecond;
	LARGE_INTEGER	m_tTick;

	float		m_fDeltaTime;
	float		m_fFPS;
	float		m_fFPSTime;
	int			m_iTick;

	int m_iDelay = 0;
	int m_iInterval = (int)(1000 / 120);

public:
	float GetDeltaTime()	const
	{
		return m_fDeltaTime;
	}

	float GetFPS()	const
	{
		return m_fFPS;
	}

private:
	bool Init();

public:
	void Update();
	void PostUpdate();
};

