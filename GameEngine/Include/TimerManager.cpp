#include "TimerManager.h"
#include "Timer.h"
#include "Scheduler.h"

DEFINITION_SINGLE(CTimerManager)

CTimerManager::CTimerManager()
{
}

CTimerManager::~CTimerManager()
{
	SAFE_DELETE_NORMAL_MAP(m_mapTimer);
}

bool CTimerManager::Init()
{
	return true;
}

void CTimerManager::Update()
{
	// char	strText[256] = {};
	// sprintf_s(strText, ("%d\n"), m_bSlowMotion);
	// OutputDebugStringA(strText);

	if (true == m_bSlowMotion)
	{
		if (0 >= m_fSlowTotalTime)
		{
			StopSlowMotion();
			return;
		}


		CTimer* main = FindTimer("Main");
		float fTime = main->GetDeltaTime();


		m_fSlowTotalTime -= 0.1f;

		int result = m_fSlowTotalTime * m_fSlowTotalTime;
		// int result = m_fSlowTotalTime;

		Sleep((DWORD)result);


		main->m_fDeltaTime = 0.01f;
	}




	
}

bool CTimerManager::CreateTimer(const string & strName)
{
	CTimer*	pTimer = FindTimer(strName);

	if (pTimer)
		return false;

	pTimer = new CTimer;

	pTimer->Init();

	hash<string>	hs;
	size_t iKey = hs(strName);

	m_mapTimer.insert(make_pair(iKey, pTimer));

	return true;
}

CTimer * CTimerManager::FindTimer(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapTimer.find(iKey);

	if (iter == m_mapTimer.end())
		return nullptr;

	return iter->second;
}

void CTimerManager::CreateSlowMotion(float fSetTime)
{
	m_bSlowMotion = true;

	m_fSlowTotalTime = fSetTime;

	GET_SINGLE(CScheduler)->AddSchedule("SlowMotion", false, fSetTime, this, &CTimerManager::StopSlowMotion);
}

void CTimerManager::StopSlowMotion()
{
	m_bSlowMotion = false;
	m_fSlowTotalTime = 0;
}
