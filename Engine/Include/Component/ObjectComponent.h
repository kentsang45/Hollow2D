#pragma once

#include "Component.h"

class ENGINE_DLL CObjectComponent :
	public CComponent
{
	friend class CGameObject;

protected:
	CObjectComponent();
	CObjectComponent(const CObjectComponent& com);
	virtual ~CObjectComponent() = 0;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void PostUpdate(float fTime);
};

