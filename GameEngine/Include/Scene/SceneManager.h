#pragma once

#include "../GameEngine.h"

class ENGINE_DLL CSceneManager
{
private:
	class CScene*	m_pScene;
	class CScene*	m_pNextScene;

public:
	class CScene* GetScene();

public:
	bool Init();
	SCENE_CHANGE Update(float fTime);
	SCENE_CHANGE PostUpdate(float fTime);
	void Render(float fTime);

public:
	class CScene* CreateNextScene();

private:
	SCENE_CHANGE ChangeScene();

	DECLARE_SINGLE(CSceneManager)
};

