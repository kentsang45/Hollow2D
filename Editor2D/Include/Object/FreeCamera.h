#pragma once

#include "Object\GameObject.h"

class CFreeCamera :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CFreeCamera();
	~CFreeCamera();

private:
	class CCameraComponent*	m_pCamera;
	class CCharacterMovementComponent*	m_pMovement;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

public:
	void MoveUp(float fScale, float fTime);
	void MoveSide(float fScale, float fTime);
};

