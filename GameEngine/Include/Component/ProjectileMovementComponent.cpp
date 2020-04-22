#include "ProjectileMovementComponent.h"
#include "../Object/GameObject.h"

CProjectileMovementComponent::CProjectileMovementComponent()
{
	SetTypeID<CProjectileMovementComponent>();
	m_fDistance = 0.f;
}

CProjectileMovementComponent::CProjectileMovementComponent(const CProjectileMovementComponent & com) :
	CMovementComponent(com)
{
	m_fDistance = com.m_fDistance;
}

CProjectileMovementComponent::~CProjectileMovementComponent()
{
}

void CProjectileMovementComponent::SetDistance(float fDist)
{
	m_fDistance = fDist;
}

float CProjectileMovementComponent::GetDistance() const
{
	return m_fDistance;
}

bool CProjectileMovementComponent::Init()
{
	if (!CMovementComponent::Init())
		return false;

	return true;
}

void CProjectileMovementComponent::Begin()
{
	CMovementComponent::Begin();
}

void CProjectileMovementComponent::Update(float fTime)
{
	CMovementComponent::Update(fTime);

	if (m_fDistance > 0.f)
	{
		float fMove = m_fMoveSpeed * fTime;
		m_fDistance -= fMove;

		if (m_fDistance <= 0.f)
		{
			m_pOwner->Kill();
		}
	}
}
