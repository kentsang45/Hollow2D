#pragma once

#include "../Engine.h"

class ENGINE_DLL CNavigation
{
	friend class CScene;

protected:
	CNavigation();
	virtual ~CNavigation();

private:
	class CScene* m_pScene;
};

