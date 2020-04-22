#pragma once

#include "../GameEngine.h"

class ENGINE_DLL CGameMode
{
	friend class CScene;

protected:
	CGameMode();
	virtual ~CGameMode();

protected:
	class CScene*	m_pScene;
	class CGameObject*	m_pPlayer;

public:
	class CGameObject* GetPlayer()	const;
	void SetPlayer(class CGameObject* pPlayer);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
};

