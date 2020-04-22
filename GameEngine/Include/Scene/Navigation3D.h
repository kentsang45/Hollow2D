#pragma once

#include "Navigation.h"

class ENGINE_DLL CNavigation3D :
	public CNavigation
{
	friend class CScene;

protected:
	CNavigation3D();
	~CNavigation3D();
};

