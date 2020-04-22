#pragma once

#include "../GameEngine.h"

class ENGINE_DLL CTransform
{
	friend class CSceneComponent;
	friend class CInput;

private:
	CTransform();
	~CTransform();

private:
	CTransform*	m_pParent;
	vector<CTransform*>	m_vecChild;
	int			m_iTransformRule;
	Vector3		m_vScaleRatio;
	class CScene*	m_pScene;
	class CSceneComponent*	m_pOwner;
	TransformCBuffer	m_tCBuffer;

public:
	const TransformCBuffer& GetCBuffer()	const;

public:
	void SetScene(class CScene* pScene);
	void PostUpdate(float fTime);

public:
	void SetTransformRule(int iTransformRule);
	
private:
	void ComputeScaleRatio();
	void ComputeRotation();
	void ComputePos();

private:	// Relative
	Vector3		m_vRelativeScale;
	Vector3		m_vRelativeRot;
	Vector3		m_vRelativePos;
	Vector3		m_vRelativeAxis[AXIS_MAX];

	int m_iFlip = 1;

public:
	void Flip(int iFlip);




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

private:	// World
	Vector3		m_vWorldScale;
	Vector3		m_vWorldRot;
	Vector3		m_vWorldPos;
	Vector3		m_vWorldAxis[AXIS_MAX];
	Vector3		m_vPivot;
	Vector3		m_vMeshSize;

	Matrix		m_matScale;
	Matrix		m_matRot;
	Matrix		m_matTranslation;
	Matrix		m_matWorld;

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
	void SetPivot(const Vector3& vPivot);
	void SetPivot(float x, float y, float z);
	void SetMeshSize(const Vector3& vSize);

public:
	Vector3 GetWorldScale()	const;
	Vector3 GetWorldRot()	const;
	Vector3 GetWorldPos()	const;
	Vector3 GetWorldAxis(AXIS eAxis)	const;
	Vector3 GetPivot()	const;

	Matrix GetScaleMatrix()	const;
	Matrix GetRotMatrix()	const;
	Matrix GetTranslationMatrix()	const;
	Matrix GetWorldMatrix()	const;

private:	// Movement
	Vector3		m_vFrameScale;
	Vector3		m_vFrameRot;
	Vector3		m_vFramePos;
	Vector3		m_vCurScale;
	Vector3		m_vCurRot;
	Vector3		m_vCurPos;

public:
	Vector3 GetFrameScale()	const;
	Vector3 GetFrameRot()	const;
	Vector3	GetFramePos()	const;
	Vector3 GetCurScale()	const;
	Vector3 GetCurRot()	const;
	Vector3	GetCurPos()	const;
	void ClearFrameInfo();

public:
	void LookAt(class CSceneComponent* pCom);
	void LookAt(CTransform* pTransform);
	void LookAt(class CGameObject* pObj);
	void LookAt(const Vector3& vLookAt);

public:
	void ComputeTransform();
	void SetTransform();
	static Vector3 GetRotationAngle(Matrix& matRot);
};

