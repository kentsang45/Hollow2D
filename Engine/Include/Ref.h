#pragma once

#include "GameEngine.h"

class ENGINE_DLL CRef
{
protected:
	CRef();
	virtual ~CRef() = 0;

protected:
	int		m_iRef;
	string	m_strName;
	bool	m_bEnable;
	bool	m_bActive;
	size_t	m_iTypeID;

public:
	size_t GetTypeID()	const;

public:
	void AddRef();
	int Release();
	void SetName(const string& strName);
	const string& GetName()	const;
	void Enable(bool bEnable);
	void Kill();
	bool IsEnable()	const;
	bool IsActive()	const;

public:
	template <typename T>
	void SetTypeID()
	{
		m_iTypeID = typeid(T).hash_code();
	}
};

