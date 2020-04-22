#include "CameraManager.h"
#include "Component/CameraComponent.h"
#include "Device.h"

CCameraManager::CCameraManager()	:
	m_pMainCamera(nullptr),
	m_pUICamera(nullptr),
	m_pDefaultCamera(nullptr)
{
}

CCameraManager::~CCameraManager()
{
	SAFE_RELEASE(m_pDefaultCamera);
	SAFE_RELEASE_VECLIST(m_CameraList);
}

CCameraComponent * CCameraManager::GetMainCamera() const
{
	return m_pMainCamera;
}

CCameraComponent * CCameraManager::GetUICamera() const
{
	return m_pUICamera;
}

bool CCameraManager::Init()
{
	m_pMainCamera = new CCameraComponent;

	m_pMainCamera->SetName("DefaultCamera");
	m_pMainCamera->SetScene(m_pScene);

	if (!m_pMainCamera->Init())
	{
		SAFE_RELEASE(m_pMainCamera);
		return false;
	}

	m_CameraList.push_back(m_pMainCamera);
	m_pMainCamera->SetRelativeScale(_RESOLUTION.iWidth, _RESOLUTION.iHeight, 1.f);

	m_pDefaultCamera = m_pMainCamera;
	m_pMainCamera->AddRef();

	m_pUICamera = new CCameraComponent;

	m_pUICamera->SetName("UICamera");
	m_pUICamera->SetScene(m_pScene);
	m_pUICamera->SetRelativeScale(_RESOLUTION.iWidth, _RESOLUTION.iHeight, 1.f);

	if (!m_pUICamera->Init())
	{
		SAFE_RELEASE(m_pUICamera);
		return false;
	}

	m_pUICamera->SetCameraType(CT_ORTHOGONAL);

	m_CameraList.push_back(m_pUICamera);

	return true;
}

bool CCameraManager::AddCamera(CCameraComponent * pCamera)
{
	m_CameraList.push_back(pCamera);

	if (!m_pMainCamera)
		m_pMainCamera = pCamera;

	return true;
}

bool CCameraManager::DeleteCamera(CCameraComponent * pCamera)
{
	auto	iter = m_CameraList.begin();
	auto	iterEnd = m_CameraList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == pCamera)
		{
			m_CameraList.erase(iter);
			break;
		}
	}

	if (m_pMainCamera == pCamera)
	{
		if (m_CameraList.empty())
			m_pMainCamera = nullptr;

		else
			m_pMainCamera = m_CameraList.front();
	}

	return true;
}

bool CCameraManager::ChangeMainCamera(CCameraComponent * pCamera)
{
	auto	iter = m_CameraList.begin();
	auto	iterEnd = m_CameraList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == pCamera)
		{
			SAFE_RELEASE(m_pMainCamera);
			m_pMainCamera = *iter;
			m_pMainCamera->AddRef();
			return true;
		}
	}

	return false;
}

bool CCameraManager::ChangeMainCamera(const string & strName)
{
	auto	iter = m_CameraList.begin();
	auto	iterEnd = m_CameraList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strName)
		{
			SAFE_RELEASE(m_pMainCamera);
			m_pMainCamera = *iter;
			m_pMainCamera->AddRef();
			return true;
		}
	}

	return false;
}
