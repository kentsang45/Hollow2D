#pragma once

#include "ColliderBase.h"

class ENGINE_DLL CColliderOBB2D :
	public CColliderBase
{
	friend class CGameObject;
	friend class CCollision;

protected:
	CColliderOBB2D();
	CColliderOBB2D(const CColliderOBB2D& com);
	virtual ~CColliderOBB2D();

protected:
	Vector3		m_vRelativeCenter;
	Vector3		m_vRelativeAxis[2];
	Vector3		m_vCenter;
	Vector3		m_vAxis[2];
	float		m_fLength[2];

public:
	void SetOBB2D(const Vector3& vRelativeCenter, float fLengthX, float fLengthY);
	Vector3 GetCenter()	const;
	Vector3 GetAxis(int idx)	const;
	float GetLength(int idx)	const;

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

