
#include "ColliderSphere2D.h"
#include "Transform.h"
#include "Collision.h"
#include "ColliderRect.h"

CColliderSphere2D::CColliderSphere2D()
{
	m_bTickUpdate = true;

	SetTypeID<CColliderSphere2D>();

	m_fRadius = 30.f;

	m_vSectionMin = Vector3(-30.f, -30.f, 0.f);
	m_vSectionMax = Vector3(30.f, 30.f, 0.f);

	m_eColliderType = COLLIDER_SPHERE2D;
}

CColliderSphere2D::CColliderSphere2D(const CColliderSphere2D & com) :
	CColliderBase(com)
{
	m_vRelativeCenter = com.m_vRelativeCenter;
	m_vCenter = com.m_vCenter;
	m_fRadius = com.m_fRadius;
}

CColliderSphere2D::~CColliderSphere2D()
{
}

void CColliderSphere2D::SetSphere(const Vector3 & vRelativeCenter, float fRadius)
{
	m_vRelativeCenter = vRelativeCenter;
	m_fRadius = fRadius;

	SetRelativePos(m_vRelativeCenter);
}

Vector3 CColliderSphere2D::GetCenter() const
{
	return m_vCenter;
}

float CColliderSphere2D::GetRadius() const
{
	return m_fRadius;
}

bool CColliderSphere2D::Init()
{
	if (!CColliderBase::Init())
		return false;

	SetDebugMesh("ColliderSphere2D");

	return true;
}

void CColliderSphere2D::Begin()
{
	CColliderBase::Begin();
}

void CColliderSphere2D::Update(float fTime)
{
	CColliderBase::Update(fTime);

	m_vCenter = m_pTransform->GetWorldPos();// + m_vRelativeCenter;

	Vector3	vMin = m_vCenter - m_fRadius;
	Vector3	vMax = m_vCenter + m_fRadius;

	m_vSectionMin = vMin;
	m_vSectionMax = vMax;

	m_vSectionMin.z = 0.f;
	m_vSectionMax.z = 0.f;
	SetRelativeScale(m_fRadius, m_fRadius, 1.f);
}

void CColliderSphere2D::Render(float fTime)
{
	CColliderBase::Render(fTime);
}

void CColliderSphere2D::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
	CColliderBase::RenderInstancing(fTime, pBuffer);
}

bool CColliderSphere2D::Collision(CColliderBase * pDest)
{
	switch (pDest->GetColliderType())
	{
	case COLLIDER_RECT:
		//return CCollision::CollisionRectToRect(this, (CColliderRect*)pDest);
		break;
	case COLLIDER_SPHERE2D:
		return CCollision::CollisionSphere2DToSphere2D(this, (CColliderSphere2D*)pDest);
	case COLLIDER_OBB2D:
		break;
	case COLLIDER_PIXEL:
		break;
	case COLLIDER_POINT:
		break;
	}

	return false;
}

bool CColliderSphere2D::Collision(const Vector2 & vMousePos)
{
	return CCollision::CollisionSphere2DToMouse(this, vMousePos);
}
