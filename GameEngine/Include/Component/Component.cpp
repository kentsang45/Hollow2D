#include "Component.h"

CComponent::CComponent()
{
	m_bTickUpdate = true;
	m_pScene = nullptr;
}

CComponent::CComponent(const CComponent & com)
{
	*this = com;
}

CComponent::~CComponent()
{
}

COMPONENT_TYPE CComponent::GetComponentType() const
{
	return m_eComType;
}

void CComponent::SetOwner(CGameObject * pOwner)
{
	m_pOwner = pOwner;
}

CGameObject * CComponent::GetOwner() const
{
	return m_pOwner;
}

void CComponent::SetScene(CScene * pScene)
{
	m_pScene = pScene;
}

CScene * CComponent::GetScene() const
{
	return m_pScene;
}

bool CComponent::Init()
{
	return true;
}

void CComponent::Begin()
{
}

void CComponent::Update(float fTime)
{
}

void CComponent::PostUpdate(float fTime)
{
}

void CComponent::Render(float fTime)
{
}

void CComponent::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
}
