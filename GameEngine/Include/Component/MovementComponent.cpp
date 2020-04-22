#include "MovementComponent.h"
#include "SceneComponent.h"

#include "../Scene/Navigation2D.h"
#include "../Scene/Scene.h"

CMovementComponent::CMovementComponent() :
	m_pUpdateComponent(nullptr),
	m_fMoveSpeed(500.f),
	m_fRotationSpeed(1000.f),
	m_fVelocity(0.f)
{
}

CMovementComponent::CMovementComponent(const CMovementComponent & com)	:
	CObjectComponent(com)
{
	m_pUpdateComponent = nullptr;
	m_fMoveSpeed = com.m_fMoveSpeed;
	m_fRotationSpeed = com.m_fRotationSpeed;
}

CMovementComponent::~CMovementComponent()
{
	SAFE_RELEASE(m_pUpdateComponent);
}

float CMovementComponent::GetVelocity() const
{
	return m_fVelocity;
}

void CMovementComponent::SetUpdateComponent(CSceneComponent * pUpdateComponent)
{
	SAFE_RELEASE(m_pUpdateComponent);
	m_pUpdateComponent = pUpdateComponent;

	if (m_pUpdateComponent)
		m_pUpdateComponent->AddRef();
}

void CMovementComponent::SetMoveSpeed(float fMoveSpeed)
{
	m_fMoveSpeed = fMoveSpeed;
}

void CMovementComponent::SetRotationSpeed(float fRotationSpeed)
{
	m_fRotationSpeed = fRotationSpeed;
}

bool CMovementComponent::Init()
{
	if (!CComponent::Init())
		return false;

	return true;
}

void CMovementComponent::Begin()
{
	CComponent::Begin();
}

void CMovementComponent::Update(float fTime)
{
	CComponent::Update(fTime);
}

void CMovementComponent::PostUpdate(float fTime)
{
	CComponent::PostUpdate(fTime);

	float	fLength = m_vVelocity.Length();
	if (fLength > 0.f)
	{
		Vector3	vDir = m_vVelocity;
		vDir.Normalize();

		// 이동할 크기를 구한다.
		float fMove = m_fMoveSpeed * fTime;

		m_pUpdateComponent->AddRelativePos(vDir * fMove);

		if (fMove > fLength)
			m_vVelocity = Vector3::Zero;

		else
			m_vVelocity -= (vDir * fMove);
	}

	if (fLength == 1000.f)
	{
		int a = 0;
	}

	fLength = m_vRotation.Length();
	if (fLength > 0.f)
	{
		m_pUpdateComponent->AddRelativeRotation(m_vRotation * fTime);

		m_vRotation = Vector3::Zero;
	}
}

void CMovementComponent::Render(float fTime)
{
	if (m_fVelocity == 1000.f)
	{
		int a = 0;
	}

	m_fVelocity = 0.f;
	m_vVelocity = Vector3::Zero;
}

void CMovementComponent::AddMovement(const Vector3 & vVelocity)
{
	if (!m_pUpdateComponent)
		return;

	if (vVelocity.y == 1000.f)
	{
		int a = 0;
	}

	m_vVelocity += vVelocity;

	m_fVelocity = m_vVelocity.Length();
}

void CMovementComponent::AddMovementTarget(const Vector3 & vTarget)
{
	if (!m_pUpdateComponent)
		return;

	m_vTarget = vTarget;

	m_vVelocity = vTarget - m_pUpdateComponent->GetWorldPos();

	m_fVelocity = m_vVelocity.Length();
}

void CMovementComponent::AddRotation(const Vector3 & vRotation)
{
	if (!m_pUpdateComponent)
		return;

	m_vRotation = vRotation;
}

void CMovementComponent::AddRotationX(float fAngle)
{
	m_vRotation.x = fAngle;
}

void CMovementComponent::AddRotationY(float fAngle)
{
	m_vRotation.y = fAngle;
}

void CMovementComponent::AddRotationZ(float fAngle)
{
	m_vRotation.z = fAngle;
}

void CMovementComponent::AddRotationTarget(const Vector3 & vTarget)
{
}

void CMovementComponent::TeleportMovement(const Vector3 & vVelocity)
{
	if (!m_pUpdateComponent)
		return;

	m_pUpdateComponent->SetWorldPos(m_pUpdateComponent->GetWorldPos() + vVelocity);
	m_vVelocity = Vector3::Zero;
}

void CMovementComponent::TeleportMovementTarget(const Vector3 & vTarget)
{
	if (!m_pUpdateComponent)
		return;

	m_pUpdateComponent->SetWorldPos(vTarget);
	m_vVelocity = Vector3::Zero;

}


void CMovementComponent::MoveNav(const Vector3 & vTarget)
{
	CNavigation2D*	pNav = (CNavigation2D*)m_pScene->GetNavigation(RM_2D);

	if (pNav)
	{
		if (pNav->FindPath(m_pUpdateComponent->GetWorldPos(), vTarget))
		{
			m_PathList.clear();
			m_PathList = pNav->GetPathList();
		}
	}
}