#pragma once

#include "ColliderBase.h"

class ENGINE_DLL CColliderRect :
	public CColliderBase
{
	friend class CGameObject;

protected:
	CColliderRect();
	CColliderRect(const CColliderRect& com);
	virtual ~CColliderRect();

protected:
	Vector3		m_vExtent;
	Vector3		m_vMin;
	Vector3		m_vMax;

public:
	void SetExtent(float x, float y);
	Vector3 GetExtent()	const;
	Vector3 GetMin()	const;
	Vector3 GetMax()	const;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
	virtual void RenderInstancing(float fTime, PInstancingBuffer pBuffer);

public:
	virtual bool Collision(CColliderBase* pDest);
	virtual bool Collision(const Vector2& vMousePos);
};

