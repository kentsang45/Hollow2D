#pragma once

#include "ColliderBase.h"

class ENGINE_DLL CColliderPoint :
	public CColliderBase
{
	friend class CGameObject;
	friend class CCollision;

protected:
	CColliderPoint();
	CColliderPoint(const CColliderPoint& com);
	virtual ~CColliderPoint();

protected:
	Vector3		m_vRelativePoint;
	Vector3		m_vPoint;

public:
	void SetPoint(const Vector3& vRelativePoint);
	Vector3 GetPoint()	const;

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

