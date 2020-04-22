#include "AnimationMeshComponent.h"
#include "../Resource/AnimationMesh.h"
#include "../Resource/Material.h"
#include "Transform.h"

CAnimationMeshComponent::CAnimationMeshComponent()	:
	m_pMesh(nullptr)
{
	m_bTickUpdate = false;

	SetTypeID<CAnimationMeshComponent>();
}

CAnimationMeshComponent::CAnimationMeshComponent(const CAnimationMeshComponent & com)	:
	CSceneComponent(com)
{
}

CAnimationMeshComponent::~CAnimationMeshComponent()
{
	SAFE_RELEASE(m_pMesh);
}

void CAnimationMeshComponent::SetAnimationMesh(CAnimationMesh * pMesh)
{
	SAFE_RELEASE(m_pMesh);

	m_pMesh = pMesh;

	if (m_pMesh)
	{
		m_pMesh->AddRef();

		/*CMaterial*	pMaterial = m_pMesh->GetMaterial();

		m_pMaterial->CopyMaterial(pMaterial);

		SAFE_RELEASE(pMaterial);*/

		m_pTransform->SetMeshSize(m_pMesh->GetMax() - m_pMesh->GetMin());
	}
}

CMaterial * CAnimationMeshComponent::GetMaterial() const
{
	return nullptr;
}

bool CAnimationMeshComponent::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CAnimationMeshComponent::Begin()
{
	CSceneComponent::Begin();
}

void CAnimationMeshComponent::Update(float fTime)
{
	CSceneComponent::Update(fTime);
}

void CAnimationMeshComponent::Render(float fTime)
{
	CSceneComponent::Render(fTime);

	if (m_pMesh)
		m_pMesh->Render();
}
