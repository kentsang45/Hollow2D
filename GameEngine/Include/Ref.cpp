#include "Ref.h"

CRef::CRef()	:
	m_iRef(1),
	m_bEnable(true),
	m_bActive(true)
{
}

CRef::~CRef()
{
}

size_t CRef::GetTypeID() const
{
	return m_iTypeID;
}

void CRef::AddRef()
{
	++m_iRef;
}

int CRef::Release()
{
	--m_iRef;

	if (m_iRef == 0)
	{
		delete	this;
		return 0;
	}

	return m_iRef;
}

void CRef::SetName(const string & strName)
{
	m_strName = strName;
}

const string & CRef::GetName() const
{
	return m_strName;
}

void CRef::Enable(bool bEnable)
{
	m_bEnable = bEnable;
}

void CRef::Kill()
{
	m_bActive = false;
}

bool CRef::IsEnable() const
{
	return m_bEnable;
}

bool CRef::IsActive() const
{
	return m_bActive;
}
