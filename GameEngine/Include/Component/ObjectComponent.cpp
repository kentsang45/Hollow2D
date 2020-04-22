#include "ObjectComponent.h"



CObjectComponent::CObjectComponent()
{
	m_eComType = CT_OBJECT;
}

CObjectComponent::CObjectComponent(const CObjectComponent & com)	:
	CComponent(com)
{
	m_eComType = CT_OBJECT;
}


CObjectComponent::~CObjectComponent()
{
}

bool CObjectComponent::Init()
{
	return true;
}

void CObjectComponent::Begin()
{
}

void CObjectComponent::Update(float fTime)
{
}

void CObjectComponent::PostUpdate(float fTime)
{
}
