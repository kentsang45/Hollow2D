#pragma once

#include "Object/GameObject.h"

class BGMObject : public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	BGMObject();
	~BGMObject();

private:
	class CAudio*	m_pAudio;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

