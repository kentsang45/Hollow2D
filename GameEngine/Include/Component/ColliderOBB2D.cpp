
#include "ColliderOBB2D.h"
#include "Transform.h"
#include "Collision.h"
#include "ColliderRect.h"
#include "ColliderSphere2D.h"
#include "ColliderPoint.h"

CColliderOBB2D::CColliderOBB2D()
{
	m_bTickUpdate = true;

	SetTypeID<CColliderOBB2D>();

	m_vRelativeAxis[0] = Vector3::Axis[AXIS_X];
	m_vRelativeAxis[1] = Vector3::Axis[AXIS_Y];
	m_vAxis[0] = Vector3::Axis[AXIS_X];
	m_vAxis[1] = Vector3::Axis[AXIS_Y];

	m_fLength[0] = 30.f;
	m_fLength[1] = 30.f;

	m_vSectionMin = Vector3(-30.f, -30.f, 0.f);
	m_vSectionMax = Vector3(30.f, 30.f, 0.f);

	m_eColliderType = COLLIDER_OBB2D;
}

CColliderOBB2D::CColliderOBB2D(const CColliderOBB2D & com) :
	CColliderBase(com)
{
	m_vRelativeCenter = com.m_vRelativeCenter;
	memcpy(m_vRelativeAxis, com.m_vRelativeAxis, sizeof(Vector3) * 2);
	memcpy(m_vAxis, com.m_vAxis, sizeof(Vector3) * 2);
	memcpy(m_fLength, com.m_fLength, sizeof(float) * 2);
}

CColliderOBB2D::~CColliderOBB2D()
{
}

void CColliderOBB2D::SetOBB2D(const Vector3 & vRelativeCenter, float fLengthX,
	float fLengthY)
{
	m_vRelativeCenter = vRelativeCenter;

	m_fLength[0] = fLengthX;
	m_fLength[1] = fLengthY;

	m_vRelativeAxis[0] = Vector3::Axis[AXIS_X];
	m_vRelativeAxis[1] = Vector3::Axis[AXIS_Y];

	SetRelativePos(m_vRelativeCenter);
}

Vector3 CColliderOBB2D::GetCenter() const
{
	return m_vCenter;
}

Vector3 CColliderOBB2D::GetAxis(int idx) const
{
	return m_vAxis[idx];
}

float CColliderOBB2D::GetLength(int idx) const
{
	return m_fLength[idx];
}

bool CColliderOBB2D::Init()
{
	if (!CColliderBase::Init())
		return false;

	SetDebugMesh("ColliderOBB2D");

	return true;
}

void CColliderOBB2D::Begin()
{
	CColliderBase::Begin();
}

void CColliderOBB2D::Update(float fTime)
{
	CColliderBase::Update(fTime);

	m_vCenter = m_pTransform->GetWorldPos();// + m_vRelativeCenter;

	m_vAxis[AXIS_X] = m_pTransform->GetWorldAxis(AXIS_X);
	m_vAxis[AXIS_Y] = m_pTransform->GetWorldAxis(AXIS_Y);

	Vector3	vPos[4] = {};

	vPos[0] = m_vCenter - m_vAxis[AXIS_X] * m_fLength[0] - m_vAxis[AXIS_Y] * m_fLength[1];
	vPos[1] = m_vCenter - m_vAxis[AXIS_X] * m_fLength[0] + m_vAxis[AXIS_Y] * m_fLength[1];
	vPos[2] = m_vCenter + m_vAxis[AXIS_X] * m_fLength[0] - m_vAxis[AXIS_Y] * m_fLength[1];
	vPos[3] = m_vCenter + m_vAxis[AXIS_X] * m_fLength[0] + m_vAxis[AXIS_Y] * m_fLength[1];

	m_vSectionMin = vPos[0];
	m_vSectionMax = vPos[0];

	for (int i = 1; i < 4; ++i)
	{
		m_vSectionMin.x = m_vSectionMin.x > vPos[i].x ? vPos[i].x : m_vSectionMin.x;
		m_vSectionMin.y = m_vSectionMin.y > vPos[i].y ? vPos[i].y : m_vSectionMin.y;

		m_vSectionMax.x = m_vSectionMax.x < vPos[i].x ? vPos[i].x : m_vSectionMax.x;
		m_vSectionMax.y = m_vSectionMax.y < vPos[i].y ? vPos[i].y : m_vSectionMax.y;
	}

	m_vSectionMin.z = 0.f;
	m_vSectionMax.z = 0.f;
	SetRelativeScale(m_fLength[0], m_fLength[1], 1.f);
}

void CColliderOBB2D::Render(float fTime)
{
	CColliderBase::Render(fTime);
}

void CColliderOBB2D::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
	CColliderBase::RenderInstancing(fTime, pBuffer);
}

bool CColliderOBB2D::Collision(CColliderBase * pDest)
{
	switch (pDest->GetColliderType())
	{
	case COLLIDER_RECT:
		//return CCollision::CollisionRectToRect(this, (CColliderRect*)pDest);
		break;
	case COLLIDER_SPHERE2D:
		//return CCollision::CollisionSphere2DToSphere2D(this, (CColliderOBB2D*)pDest);
		break;
	case COLLIDER_OBB2D:
		return CCollision::CollisionOBB2DToOBB2D(this, (CColliderOBB2D*)pDest);
	case COLLIDER_PIXEL:
		break;
	case COLLIDER_POINT:
		break;
	}

	return false;
}

bool CColliderOBB2D::Collision(const Vector2 & vMousePos)
{
	return CCollision::CollisionOBB2DToMouse(this, vMousePos);
}
