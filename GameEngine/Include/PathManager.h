#pragma once

#include "GameEngine.h"

class ENGINE_DLL CPathManager
{
private:
	TCHAR	m_strRoot[MAX_PATH];
	char	m_strPath[MAX_PATH];
	unordered_map<size_t, TCHAR*>	m_mapPath;

public:
	bool Init();
	void CreatePath(const string& strName, const TCHAR* pPath,
		const string& strBasePath = ROOT_PATH);
	const TCHAR* FindPath(const string& strName);
	const char* FindPathMultibyte(const string& strName);

	DECLARE_SINGLE(CPathManager)
};

