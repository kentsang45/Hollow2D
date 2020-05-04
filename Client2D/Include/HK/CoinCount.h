#pragma once

#include "Object/GameObject.h"

class CoinCount : public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CoinCount();
	~CoinCount();

private:
	class CText*	m_pText;
	class HollowKnight* m_pHK;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

