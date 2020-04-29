#pragma once


#include "Object/GameObject.h"
#include "../Client.h"



class Sencer : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	Sencer();
	~Sencer();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	class CColliderRect* GetBody() const { return m_pBody;  }

	bool IsOverlap() const;
	bool IsPlayer() const;
	void ClearOverlap() { m_bFree = false; }
	void SetOverlap(bool free);
	void SetStyle(int style) { m_iStyle = style; }

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void OffBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void Clear();

	void SetCheck(int check) { m_iCheck = check; };

private:
	class CCharacterMovementComponent*	m_pMovement;
	class CColliderRect* m_pBody;

	bool m_bFree = true;
	bool m_bPlayer = false;

	int m_iCheck = 0;

	int m_iStyle = 0;
	// left 1. up 2. right 3. bot 4
	
};

