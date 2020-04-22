#include "Timer.h"
#include "Engine.h"



CTimer::CTimer()	:
	m_fDeltaTime(0.f),
	m_fFPS(0.f),
	m_fFPSTime(0.f),
	m_iTick(0)
{
}

CTimer::~CTimer()
{
}

bool CTimer::Init()
{
	QueryPerformanceFrequency(&m_tSecond);
	QueryPerformanceCounter(&m_tTick);

	return true;
}

void CTimer::Update()
{
	LARGE_INTEGER	tTick;
	QueryPerformanceCounter(&tTick);

	m_fDeltaTime = (tTick.QuadPart - m_tTick.QuadPart) /
		(float)m_tSecond.QuadPart;

	// 지연
	// m_iDelay = (int)m_tTick.QuadPart;

	// m_iDelay = m_iInterval - (m_iDelay - 




	// deltaTime 제한
	if (m_fDeltaTime >= 0.15f)
	{
		m_fDeltaTime = 0.15f;
	}

	m_tTick = tTick;

	++m_iTick;
	m_fFPSTime += m_fDeltaTime;

	if (m_iTick == 60)
	{
		m_fFPS = m_iTick / m_fFPSTime;
		m_fFPSTime = 0.f;
		m_iTick = 0;

		char	strFPS[256] = {};
		sprintf_s(strFPS, "FPS : %.4f", m_fFPS);

		SetWindowTextA(WINDOWHANDLE, strFPS);
	}



	
}

void CTimer::PostUpdate()
{
	LARGE_INTEGER	tTick;
	QueryPerformanceCounter(&tTick);

	DWORD delay = (m_iInterval - (tTick.QuadPart - m_tTick.QuadPart) / m_tSecond.QuadPart);

	if (delay > 0)
	{
		int a = 0;
		
		if (delay > 1000.f)
		{
			delay = 1000.f;
		}
		
		Sleep(delay);
	}

}



