#pragma once
#include "ObjectComponent.h"
class ENGINE_DLL CMovementComponent :
	public CObjectComponent
{
	friend class CGameObject;

protected:
	CMovementComponent();
	CMovementComponent(const CMovementComponent& com);
	virtual ~CMovementComponent() = 0;

protected:
	class CSceneComponent*	m_pUpdateComponent;
	float	m_fMoveSpeed;
	float	m_fRotationSpeed;
	float	m_fVelocity;
	Vector3	m_vVelocity;
	Vector3	m_vRotation;
	Vector3	m_vTarget;
	list<Vector3>	m_PathList;

public:
	float GetVelocity()	const;

public:
	void SetUpdateComponent(class CSceneComponent* pUpdateComponent);
	void SetMoveSpeed(float fMoveSpeed);
	void SetRotationSpeed(float fRotationSpeed);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
	virtual void Render(float fTime);

public:
	virtual void AddMovement(const Vector3& vVelocity);
	virtual void AddMovementTarget(const Vector3& vTarget);
	virtual void AddRotation(const Vector3& vRotation);
	virtual void AddRotationX(float fAngle);
	virtual void AddRotationY(float fAngle);
	virtual void AddRotationZ(float fAngle);
	virtual void AddRotationTarget(const Vector3& vTarget);
	virtual void TeleportMovement(const Vector3& vVelocity);
	virtual void TeleportMovementTarget(const Vector3& vTarget);

	virtual void MoveNav(const Vector3& vTarget);
};

