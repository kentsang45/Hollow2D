#include "PathManager.h"

DEFINITION_SINGLE(CPathManager)

CPathManager::CPathManager()
{
	memset(m_strRoot, 0, sizeof(TCHAR) * MAX_PATH);
	memset(m_strPath, 0, sizeof(char) * MAX_PATH);
}

CPathManager::~CPathManager()
{
	auto	iter = m_mapPath.begin();
	auto	iterEnd = m_mapPath.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE_ARRAY(iter->second);
	}

	m_mapPath.clear();
}

bool CPathManager::Init()
{
	GetModuleFileName(nullptr, m_strRoot, MAX_PATH);

	// 실행파일 이름을 문자열에서 제거한다.
	int	iLength = lstrlen(m_strRoot);
	for (int i = iLength - 1; i >= 0; --i)
	{
		// aa/bb.exe 9개, 2번인덱스 3 ~ 8번까지 제거
		if (m_strRoot[i] == '/' || m_strRoot[i] == '\\')
		{
			memset(&m_strRoot[i + 1], 0, sizeof(TCHAR) * (iLength - (i + 1)));
			break;
		}
	}

	TCHAR*	pPath = new TCHAR[MAX_PATH];
	memset(pPath, 0, sizeof(TCHAR) * MAX_PATH);

	lstrcpy(pPath, m_strRoot);

	hash<string>	hs;

	size_t	iKey = hs(ROOT_PATH);

	m_mapPath.insert(make_pair(iKey, pPath));

	CreatePath(RESOURCE_PATH, TEXT("Resource\\"));
	CreatePath(SHADER_PATH, TEXT("Shader\\"), RESOURCE_PATH);
	CreatePath(TEXTURE_PATH, TEXT("Texture\\"), RESOURCE_PATH);
	CreatePath(SOUND_PATH, TEXT("Sound\\"), RESOURCE_PATH);

	return true;
}

void CPathManager::CreatePath(const string & strName,
	const TCHAR * pPath, const string & strBasePath)
{
	if (FindPath(strName))
		return;

	const TCHAR* pBasePath = FindPath(strBasePath);

	TCHAR*	strPath = new TCHAR[MAX_PATH];

	memset(strPath, 0, sizeof(TCHAR) * MAX_PATH);

	if (pBasePath)
		lstrcpy(strPath, pBasePath);

	lstrcat(strPath, pPath);

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapPath.insert(make_pair(iKey, strPath));
}

const TCHAR * CPathManager::FindPath(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapPath.find(iKey);

	if (iter == m_mapPath.end())
		return nullptr;

	return iter->second;
}

const char * CPathManager::FindPathMultibyte(const string & strName)
{
	const TCHAR*	pPath = FindPath(strName);

	if (!pPath)
		return nullptr;

	memset(m_strPath, 0, MAX_PATH);

	WideCharToMultiByte(CP_ACP, 0, pPath, -1, m_strPath,
		lstrlen(pPath), nullptr, nullptr);

	return m_strPath;
}
