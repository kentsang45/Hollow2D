#pragma once

#include "SceneComponent.h"

class ENGINE_DLL CAudio :
	public CSceneComponent
{
	friend class CGameObject;

protected:
	CAudio();
	CAudio(const CAudio& com);
	virtual ~CAudio();

private:
	class CSound*	m_pSound;
	string	m_strChannelGroup;
	bool	m_bPlay;
	int		m_iVolume;
	function<void()>	m_FinishCallback;

public:
	bool IsPlay()	const;

public:
	void SetSound(const string& strName);
	void SetSound(const string& strName, bool bLoop, const char* pFileName, const string& strPathName = SOUND_PATH);
	void SetChannelGroup(const string& strChannelGroup);
	void SetVolume(int iVolume);

public:
	void Play();
	void Pause();
	void Stop();
	void Mute();
	void UnMute();

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

