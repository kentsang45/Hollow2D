#pragma once

#include "Object/GameObject.h"

class BossText : public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	BossText();
	~BossText();

private:
	class CText*	m_pText;
	class HollowKnight* m_pHK;


	float m_fLifeTime = 0.f;
	float m_fLifeTotalTime = 4.f;


public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);




};

