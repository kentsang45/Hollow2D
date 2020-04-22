#pragma once

#include "Mesh.h"

class ENGINE_DLL CStaticMesh :
	public CMesh
{
	friend class CResourceManager;

private:
	CStaticMesh();
	~CStaticMesh();
};

