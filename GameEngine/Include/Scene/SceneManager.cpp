#include "SceneManager.h"
#include "Scene.h"
#include "../Resource/ResourceManager.h"
#include "../CollisionManager.h"

DEFINITION_SINGLE(CSceneManager)

CSceneManager::CSceneManager()	:
	m_pScene(nullptr),
	m_pNextScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	SAFE_RELEASE(m_pScene);
	SAFE_RELEASE(m_pNextScene);
}

CScene * CSceneManager::GetScene()
{
	return m_pScene;
}

bool CSceneManager::Init()
{
	m_pScene = new CScene;

	m_pScene->Init();

	return true;
}

SCENE_CHANGE CSceneManager::Update(float fTime)
{
	m_pScene->Update(fTime);

	return ChangeScene();
}

SCENE_CHANGE CSceneManager::PostUpdate(float fTime)
{
	m_pScene->PostUpdate(fTime);

	return ChangeScene();
}

void CSceneManager::Render(float fTime)
{
	m_pScene->Render(fTime);
}

CScene * CSceneManager::CreateNextScene()
{
	m_pNextScene = new CScene;

	m_pNextScene->Init();

	return m_pNextScene;
}

SCENE_CHANGE CSceneManager::ChangeScene()
{
	if (m_pNextScene)
	{
		GET_SINGLE(CCollisionManager)->ChangeScene();
		SAFE_RELEASE(m_pScene);
		m_pScene = m_pNextScene;
		m_pNextScene = nullptr;
		m_pScene->Begin();

		GET_SINGLE(CResourceManager)->ChangeScene();

		return SC_CHANGE;
	}

	return SC_NONE;
}
