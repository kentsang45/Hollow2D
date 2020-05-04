#pragma once

#include "../Ref.h"
#include "GameMode.h"

class ENGINE_DLL CScene :
	public CRef
{
	friend class CSceneManager;

private:
	CScene();
	~CScene();

private:
	CGameMode*	m_pGameMode;
	class CCameraManager*	m_pCameraManager;
	class CNavigation*		m_pNavigation[NT_END];

public:
	CGameMode* GetGameMode()	const;
	class CCameraManager* GetCameraManager()	const;
	class CNavigation* GetNavigation(RENDER_MODE eMode) const;

private:
	list<class CGameObject*>	m_ObjList;
	list<class CGameObject*>	m_BeginList;

public:
	bool Init();
	void Begin();
	void Update(float fTime);
	void PostUpdate(float fTime);
	void Render(float fTime);

public:
	bool AddCamera(class CCameraComponent* pCamera);
	bool DeleteCamera(class CCameraComponent* pCamera);

public:
	template <typename T>
	T* SpawnObject(const Vector3& vPos = Vector3::Zero,
		const Vector3& vRot = Vector3::Zero,
		const Vector3& vScale = Vector3::One)
	{
		return SpawnObject<T>("GameObject", vPos, vRot, vScale);
	}


	template <typename T>
	T* SpawnObject(const string& strName, 
		const Vector3& vPos = Vector3::Zero,
		const Vector3& vRot = Vector3::Zero,
		const Vector3& vScale = Vector3::One)
	{
		T*	pObj = new T;

		pObj->m_pScene = this;
		pObj->SetTypeID<T>();
		pObj->SetName(strName);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return nullptr;
		}

		if (vScale != Vector3::One)
			pObj->SetRelativeScale(vScale);

		if (vRot != Vector3::Zero)
			pObj->SetRelativeRotation(vRot);

		if (vPos != Vector3::Zero)
			pObj->SetRelativePos(vPos);

		pObj->AddRef();

		m_ObjList.push_back(pObj);

		pObj->AddRef();
		m_BeginList.push_back(pObj);

		return pObj;
	}

	template <typename T>
	T* SetGameMode()
	{
		SAFE_DELETE(m_pGameMode);

		m_pGameMode = new T;

		m_pGameMode->m_pScene = this;

		/*if (!m_pGameMode->Init())
		{
			SAFE_DELETE(m_pGameMode);
			return nullptr;
		}*/

		return (T*)m_pGameMode;
	}
};

