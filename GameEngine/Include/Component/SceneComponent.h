#pragma once
#include "Component.h"
class ENGINE_DLL CSceneComponent :
	public CComponent
{
	friend class CGameObject;

protected:
	CSceneComponent();
	CSceneComponent(const CSceneComponent& com);
	virtual ~CSceneComponent();

protected:
	CSceneComponent*			m_pParent;
	vector<CSceneComponent*>	m_vecChild;
	class CTransform*			m_pTransform;
	bool						m_bUI;
	Vector3						m_vComponentMin;
	Vector3						m_vComponentMax;

public:
	Vector3 GetComponentMin()	const;
	Vector3 GetComponentMax()	const;

public:
	void EnableUI();
	bool IsUI()	const;
	class CTransform* GetTransform()	const;
	CSceneComponent* FindComponentFromName(const string& strName);
	CSceneComponent* FindComponentFromTypeID(size_t iTypeID);
	virtual class CMaterial* GetMaterial()	const;

public:
	void AddChild(CSceneComponent* pChild, int iTransformRule = TR_ALL);
	void DeleteChild(CSceneComponent* pChild);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(float fTime);
	virtual void RenderInstancing(float fTime, PInstancingBuffer pBuffer);

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
	void SetPivot(const Vector3& vPivot);
	void SetPivot(float x, float y, float z);

public:
	Vector3 GetRelativeScale()	const;
	Vector3 GetRelativeRot()	const;
	Vector3 GetRelativePos()	const;
	Vector3 GetRelaitveAxis(AXIS eAxis)	const;
	Vector3 GetPivot()	const;

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
};

