#pragma once
#include "MovementComponent.h"
class ENGINE_DLL CProjectileMovementComponent :
	public CMovementComponent
{
	friend class CGameObject;

protected:
	CProjectileMovementComponent();
	CProjectileMovementComponent(const CProjectileMovementComponent& com);
	virtual ~CProjectileMovementComponent();

private:
	float		m_fDistance;

public:
	void SetDistance(float fDist);
	float GetDistance()	const;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
};

