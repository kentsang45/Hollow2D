
#include "ColliderPoint.h"
#include "Transform.h"
#include "Collision.h"
#include "ColliderRect.h"
#include "ColliderOBB2D.h"
#include "ColliderSphere2D.h"

CColliderPoint::CColliderPoint()
{
	m_bTickUpdate = true;

	SetTypeID<CColliderPoint>();

	m_eColliderType = COLLIDER_POINT;
}

CColliderPoint::CColliderPoint(const CColliderPoint & com) :
	CColliderBase(com)
{
	m_vRelativePoint = com.m_vRelativePoint;
	m_vPoint = com.m_vPoint;
}

CColliderPoint::~CColliderPoint()
{
}

void CColliderPoint::SetPoint(const Vector3 & vRelativePoint)
{
	m_vRelativePoint = vRelativePoint;

	SetRelativePos(m_vRelativePoint);
}

Vector3 CColliderPoint::GetPoint() const
{
	return m_vPoint;
}

bool CColliderPoint::Init()
{
	if (!CColliderBase::Init())
		return false;

	SetDebugMesh("ColliderRect");

	return true;
}

void CColliderPoint::Begin()
{
	CColliderBase::Begin();
}

void CColliderPoint::Update(float fTime)
{
	CColliderBase::Update(fTime);

	m_vPoint = m_pTransform->GetWorldPos();// + m_vRelativeCenter;

	m_vSectionMin = m_vPoint;
	m_vSectionMax = m_vPoint;
	m_vSectionMin.z = 0.f;
	m_vSectionMax.z = 0.f;
	SetRelativeScale(3.f, 3.f, 1.f);
}

void CColliderPoint::Render(float fTime)
{
	CColliderBase::Render(fTime);
}

void CColliderPoint::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
	CColliderBase::RenderInstancing(fTime, pBuffer);
}

bool CColliderPoint::Collision(CColliderBase * pDest)
{
	switch (pDest->GetColliderType())
	{
	case COLLIDER_RECT:
		//return CCollision::CollisionRectToRect(this, (CColliderRect*)pDest);
		break;
	case COLLIDER_SPHERE2D:
		//return CCollision::CollisionSphere2DToSphere2D(this, (CColliderPoint*)pDest);
		break;
	case COLLIDER_OBB2D:
		//return CCollision::CollisionOBB2DToOBB2D(this, (CColliderPoint*)pDest);
		break;
	case COLLIDER_PIXEL:
		break;
	case COLLIDER_POINT:
		break;
	}

	return false;
}

bool CColliderPoint::Collision(const Vector2 & vMousePos)
{
	return false;
}
