#pragma once

#include "Object/GameObject.h"

class CStartButton :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CStartButton();
	~CStartButton();

private:
	class CUIButton*	m_pButton;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

public:
	void ClickCallback(float fTime);
};

