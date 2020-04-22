#include "ColliderRect.h"
#include "Transform.h"
#include "Collision.h"
#include "ColliderPixel.h"

CColliderRect::CColliderRect()
{
	m_bTickUpdate = true;

	SetTypeID<CColliderRect>();

	m_vExtent.x = 30.f;
	m_vExtent.y = 30.f;

	m_vSectionMin = Vector3(0.f, 0.f, 0.f);
	m_vSectionMax = Vector3(30.f, 30.f, 0.f);

	m_eColliderType = COLLIDER_RECT;
}

CColliderRect::CColliderRect(const CColliderRect & com) :
	CColliderBase(com)
{
	m_vExtent = com.m_vExtent;
}

CColliderRect::~CColliderRect()
{
}

void CColliderRect::SetExtent(float x, float y)
{
	m_vExtent.x = x;
	m_vExtent.y = y;
	m_vExtent.z = 0.f;

	SetRelativeScale(m_vExtent.x, m_vExtent.y, 1.f);
}

Vector3 CColliderRect::GetExtent() const
{
	return m_vExtent;
}

Vector3 CColliderRect::GetMin() const
{
	return m_vMin;
}

Vector3 CColliderRect::GetMax() const
{
	return m_vMax;
}

bool CColliderRect::Init()
{
	if (!CColliderBase::Init())
		return false;

	SetDebugMesh("ColliderRect");

	return true;
}

void CColliderRect::Begin()
{
	CColliderBase::Begin();

	SetRelativeScale(m_vExtent.x, m_vExtent.y, 1.f);
}

void CColliderRect::Update(float fTime)
{
	CColliderBase::Update(fTime);

	m_vMin = m_pTransform->GetWorldPos() - m_pTransform->GetPivot() * m_vExtent;
	m_vMax = m_vMin + m_vExtent;

	m_vSectionMin = m_vMin;
	m_vSectionMax = m_vMax;
}

void CColliderRect::Render(float fTime)
{
	CColliderBase::Render(fTime);
}

void CColliderRect::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
	CColliderBase::RenderInstancing(fTime, pBuffer);
}

bool CColliderRect::Collision(CColliderBase * pDest)
{
	switch (pDest->GetColliderType())
	{
	case COLLIDER_RECT:
		return CCollision::CollisionRectToRect(this, (CColliderRect*)pDest);
	case COLLIDER_SPHERE2D:
		break;
	case COLLIDER_OBB2D:
		break;
	case COLLIDER_PIXEL:
		return CCollision::CollisionRectToPixel(this, (CColliderPixel*)pDest);
	case COLLIDER_POINT:
		break;
	}

	return false;
}

bool CColliderRect::Collision(const Vector2 & vMousePos)
{
	return CCollision::CollisionRectToMouse(this, vMousePos);
}
