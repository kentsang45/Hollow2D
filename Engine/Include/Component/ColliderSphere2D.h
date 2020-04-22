#pragma once

#include "ColliderBase.h"

class ENGINE_DLL CColliderSphere2D :
	public CColliderBase
{
	friend class CGameObject;

protected:
	CColliderSphere2D();
	CColliderSphere2D(const CColliderSphere2D& com);
	virtual ~CColliderSphere2D();

protected:
	Vector3		m_vRelativeCenter;
	Vector3		m_vCenter;
	float		m_fRadius;

public:
	void SetSphere(const Vector3& vRelativeCenter, float fRadius);
	Vector3 GetCenter()	const;
	float GetRadius()	const;

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

