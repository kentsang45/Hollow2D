#pragma once

#include "Object/GameObject.h"

class EffectSound :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	EffectSound();
	~EffectSound();

private:
	class CAudio*	m_pAudio;

public:
	void SetSound(const string& strKey, const char* pFileName);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

