#pragma once

#include "Navigation.h"

class ENGINE_DLL CNavigation2D :
	public CNavigation
{
	friend class CScene;

protected:
	CNavigation2D();
	~CNavigation2D();

private:
	class CTileMap*	m_pTileMap;
	list<Vector3>	m_PathList;
	vector<class CTile*>	m_vecOpen;
	vector<class CTile*>	m_vecUse;
	int				m_iOpenCount;
	int				m_iUseCount;

public:
	list<Vector3> GetPathList() const;
	
	void SetTileMap(class CTileMap* pTileMap);
	bool FindPath(const Vector3& vStart, const Vector3& vEnd);

private:
	bool FindNode(class CTile* pNode, class CTile* pEnd, const Vector3& vEnd);
};
