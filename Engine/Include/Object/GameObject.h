#pragma once

#include "../Ref.h"
#include "../Component/SceneComponent.h"
#include "../Component/ObjectComponent.h"

class ENGINE_DLL CGameObject :
	public CRef
{
	friend class CScene;

protected:
	CGameObject();
	~CGameObject();

protected:
	class CSceneComponent*	m_pRootComponent;
	class CScene*			m_pScene;
	vector<class CObjectComponent*>	m_vecObjComponent;
	vector<CGameObject*>			m_vecChild;
	float							m_fActiveTime;
	list<class CComponent*>			m_BeginList;

	// GRAVITY
	bool m_bPhysics;
	float m_fGravityTime;
	float m_fGravitySpeed = 1.f;

	float m_fOriginForce;
	float m_fForce;
	bool m_bOnLand;
	bool m_bFalling;
	bool m_bJumping = false;
	bool m_bMove;
	int m_iDir;

	class CTimer* m_pTimer;

	bool m_bSlowAdjust = false;
public:
	class CScene* GetScene()	const;

public:

	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

	void SetPhysics(bool bPhysics);
	bool GetPhysics() const;
	void ClearGravity();
	void SlowGravity();

	void SetForce(float fForce) { m_fOriginForce = fForce; }

	void Jump();

	void Flip(int iFlip);
	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////



	void SetActiveTime(float fTime);
	void SetRoot(class CSceneComponent* pRoot);
	class CTransform* GetTransform()	const;
	void AddChild(CGameObject* pChild, int iTransformRule = TR_ALL);
	void AddChild(CGameObject* pChild, const string& strParentName, int iTransformRule = TR_ALL);
	void AddChild(CGameObject* pChild, class CSceneComponent* pParent, int iTransformRule = TR_ALL);
	void DeleteChild(CGameObject* pChild);
	void DeleteChild(const string& strName);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(float fTime);

private:
	void Render(class CSceneComponent* pComponent, float fTime);

public:
	void SetRelativeScale(const Vector3& vScale);
	void SetRelativeScale(float x, float y, float z);
	void SetRelativeRotation(const Vector3& vRot);
	void SetRelativeRotation(float x, float y, float z);
	void SetRelativeRotationX(float x);
	void SetRelativeRotationY(float y);
	void SetRelativeRotationZ(float z);
	void SetRelativePos(const Vector3& vPos);
	void SetRelativePos(float x, float y, float z);
	void AddRelativeScale(const Vector3& vScale);
	void AddRelativeScale(float x, float y, float z);
	void AddRelativePos(const Vector3& vPos);
	void AddRelativePos(float x, float y, float z);
	void AddRelativeRotation(const Vector3& vRot);
	void AddRelativeRotation(float x, float y, float z);
	void AddRelativeRotationX(float x);
	void AddRelativeRotationY(float y);
	void AddRelativeRotationZ(float z);

public:
	Vector3 GetRelativeScale()	const;
	Vector3 GetRelativeRot()	const;
	Vector3 GetRelativePos()	const;
	Vector3 GetRelativeAxis(AXIS eAxis)	const;

public:
	void SetWorldScale(const Vector3& vScale);
	void SetWorldScale(float x, float y, float z);
	void SetWorldRotation(const Vector3& vRot);
	void SetWorldRotation(float x, float y, float z);
	void SetWorldRotationX(float x);
	void SetWorldRotationY(float y);
	void SetWorldRotationZ(float z);
	void SetWorldPos(const Vector3& vPos);
	void SetWorldPos(float x, float y, float z);
	void AddWorldScale(const Vector3& vScale);
	void AddWorldScale(float x, float y, float z);
	void AddWorldPos(const Vector3& vPos);
	void AddWorldPos(float x, float y, float z);
	void AddWorldRotation(const Vector3& vRot);
	void AddWorldRotation(float x, float y, float z);
	void AddWorldRotationX(float x);
	void AddWorldRotationY(float y);
	void AddWorldRotationZ(float z);

public:
	Vector3 GetWorldScale()	const;
	Vector3 GetWorldRot()	const;
	Vector3 GetWorldPos()	const;
	Vector3 GetWorldAxis(AXIS eAxis)	const;

	Matrix GetScaleMatrix()	const;
	Matrix GetRotMatrix()	const;
	Matrix GetTranslationMatrix()	const;
	Matrix GetWorldMatrix()	const;

public:
	Vector3 GetFrameScale()	const;
	Vector3 GetFrameRot()	const;
	Vector3	GetFramePos()	const;

public:
	void LookAt(class CSceneComponent* pCom);
	void LookAt(CTransform* pTransform);
	void LookAt(class CGameObject* pObj);
	void LookAt(const Vector3& vLookAt);

private:
	void CheckCamera(class CComponent* pCom);

public:
	template <typename T>
	T* CreateComponent(const string& strName = "")
	{
		T*	pCom = new T;

		pCom->SetName(strName);
		pCom->SetOwner(this);
		pCom->SetScene(m_pScene);

		if (!pCom->Init())
		{
			SAFE_RELEASE(pCom);
			return nullptr;
		}

		if (pCom->GetComponentType() == CT_OBJECT)
		{
			pCom->AddRef();
			m_vecObjComponent.push_back((CObjectComponent*)pCom);
		}

		pCom->AddRef();
		m_BeginList.push_back(pCom);

		CheckCamera(pCom);

		return pCom;
	}

	template <typename T>
	T* FindSceneComponent(const string& strName)
	{
		return (T*)m_pRootComponent->FindComponentFromName(strName);
	}

	template <typename T>
	T* FindObjectComponent(const string& strName)
	{
		size_t	iSize = m_vecObjComponent.size();

		for (size_t i = 0; i < iSize; ++i)
		{
			if (m_vecObjComponent[i]->GetName() == strName)
			{
				m_vecObjComponent[i]->AddRef();
				return m_vecObjComponent[i];
			}
		}

		return nullptr;
	}

	template <typename T>
	T* FindSceneComponent()
	{
		return (T*)m_pRootComponent->FindComponentFromTypeID(typeid(T).hash_code());
	}

	template <typename T>
	T* FindObjectComponent()
	{
		size_t	iSize = m_vecObjComponent.size();

		size_t	iTypeID = typeid(T).hash_code();

		for (size_t i = 0; i < iSize; ++i)
		{
			if (m_vecObjComponent[i]->GetTypeID() == iTypeID)
			{
				m_vecObjComponent[i]->AddRef();
				return (T*)m_vecObjComponent[i];
			}
		}

		return nullptr;
	}
};

