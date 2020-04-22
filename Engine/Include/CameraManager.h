#pragma once

#include "GameEngine.h"

class ENGINE_DLL CCameraManager
{
	friend class CScene;

private:
	CCameraManager();
	~CCameraManager();

private:
	list<class CCameraComponent*>	m_CameraList;
	class CCameraComponent*		m_pMainCamera;
	class CCameraComponent*		m_pDefaultCamera;
	class CCameraComponent*		m_pUICamera;
	class CScene*				m_pScene;

public:
	class CCameraComponent* GetMainCamera()	const;
	class CCameraComponent* GetUICamera()	const;

public:
	bool Init();
	bool AddCamera(class CCameraComponent* pCamera);
	bool DeleteCamera(class CCameraComponent* pCamera);
	bool ChangeMainCamera(class CCameraComponent* pCamera);
	bool ChangeMainCamera(const string& strName);
};

