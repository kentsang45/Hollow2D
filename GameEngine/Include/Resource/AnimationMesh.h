#pragma once
#include "Mesh.h"
class ENGINE_DLL CAnimationMesh :
	public CMesh
{
	friend class CResourceManager;

private:
	CAnimationMesh();
	~CAnimationMesh();
};

