#pragma once

#include "GameEngine.h"

struct ENGINE_DLL _tagScheduleInfo
{
	string	strName;
	bool	bLoop;
	float	fTime;
	float	fRepeatTime;
	function<void()>	func;

	_tagScheduleInfo()
	{
		fTime = 0.f;
		fRepeatTime = 0.f;
		bLoop = false;
	}
};

class ENGINE_DLL CScheduler
{
private:
	list<_tagScheduleInfo*>	m_ScheduleList;

public:
	bool Init();
	void Update(float fTime);
	void AddSchedule(const string& strName, bool bLoop, float fRepeatTime, void(*pFunc)());
	template <typename T>
	void AddSchedule(const string& strName, bool bLoop, float fRepeatTime, T* pObj, void(T::*pFunc)())
	{
		_tagScheduleInfo*	pInfo = new _tagScheduleInfo;

		pInfo->strName = strName;
		pInfo->bLoop = bLoop;
		pInfo->fRepeatTime = fRepeatTime;
		pInfo->func = bind(pFunc, pObj);

		m_ScheduleList.push_back(pInfo);
	}

	void DeleteSchedule(const string& strName);

	DECLARE_SINGLE(CScheduler)
};

