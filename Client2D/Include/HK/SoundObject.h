#pragma once

#include "Object/GameObject.h"

class SoundObject :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	SoundObject();
	~SoundObject();

private:
	class CAudio*	m_pAudio;


public:
	void SetSound(const string& strKey, const char* pFileName);

	void StopSO();
	void PlaySO();

	bool IsPlaying() const;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	class CAudio* GetAudio() const { return m_pAudio; }

	string m_pSoundName;
	string m_pFileName;
};

