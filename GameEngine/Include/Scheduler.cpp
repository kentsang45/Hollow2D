#include "Scheduler.h"

DEFINITION_SINGLE(CScheduler)

CScheduler::CScheduler()
{
}

CScheduler::~CScheduler()
{
	SAFE_DELETE_NORMAL_VECLIST(m_ScheduleList);
}

bool CScheduler::Init()
{
	return true;
}

void CScheduler::Update(float fTime)
{
	auto	iter = m_ScheduleList.begin();
	auto	iterEnd = m_ScheduleList.end();

	for (; iter != iterEnd;)
	{
		(*iter)->fTime += fTime;

		if ((*iter)->fTime >= (*iter)->fRepeatTime)
		{
			(*iter)->func();

			if ((*iter)->bLoop)
			{
				(*iter)->fTime -= (*iter)->fRepeatTime;
			}

			else
			{
				SAFE_DELETE((*iter));
				iter = m_ScheduleList.erase(iter);
			}
		}

		else
			++iter;
	}
}

void CScheduler::AddSchedule(const string & strName, bool bLoop, float fRepeatTime, 
	void(*pFunc)())
{
	_tagScheduleInfo*	pInfo = new _tagScheduleInfo;

	pInfo->strName = strName;
	pInfo->bLoop = bLoop;
	pInfo->fRepeatTime = fRepeatTime;
	pInfo->func = bind(pFunc);

	m_ScheduleList.push_back(pInfo);
}

void CScheduler::DeleteSchedule(const string & strName)
{
	auto	iter = m_ScheduleList.begin();
	auto	iterEnd = m_ScheduleList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->strName == strName)
		{
			SAFE_DELETE((*iter));
			m_ScheduleList.erase(iter);
			return;
		}
	}
}
