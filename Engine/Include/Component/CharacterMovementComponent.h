#pragma once
#include "MovementComponent.h"
class ENGINE_DLL CCharacterMovementComponent :
	public CMovementComponent
{
	friend class CGameObject;

protected:
	CCharacterMovementComponent();
	CCharacterMovementComponent(const CCharacterMovementComponent& com);
	virtual ~CCharacterMovementComponent();

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
};

