#pragma once

#include "Object/GameObject.h"


class HKMouse : public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	HKMouse();
	~HKMouse();


private:
	class CColliderPoint* m_pBody;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
};

