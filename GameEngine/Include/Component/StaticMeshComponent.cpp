#include "StaticMeshComponent.h"
#include "../Resource/StaticMesh.h"
#include "../Resource/Material.h"
#include "Transform.h"
#include "Animation2D.h"
#include "../Resource/Animation2DSequence.h"

CStaticMeshComponent::CStaticMeshComponent() :
	m_pMesh(nullptr),
	m_pAnimation2D(nullptr)
{
	m_bTickUpdate = false;

	SetTypeID<CStaticMeshComponent>();
	m_pMaterial = new CMaterial;

	m_pMaterial->Init();
}

CStaticMeshComponent::CStaticMeshComponent(const CStaticMeshComponent & com)	:
	CSceneComponent(com)
{
	m_pMesh = com.m_pMesh;

	if (m_pMesh)
		m_pMesh->AddRef();

	m_pMaterial = new CMaterial(*com.m_pMaterial);

	m_pAnimation2D = nullptr;
}

CStaticMeshComponent::~CStaticMeshComponent()
{
	SAFE_RELEASE(m_pAnimation2D);
	SAFE_RELEASE(m_pMaterial);
	SAFE_RELEASE(m_pMesh);
}

bool CStaticMeshComponent::IsAnimation2D() const
{
	return m_pAnimation2D != nullptr;
}

CMaterial * CStaticMeshComponent::GetMaterial() const
{
	if (m_pMaterial)
		m_pMaterial->AddRef();

	return m_pMaterial;
}

void CStaticMeshComponent::SetStaticMesh(CStaticMesh * pMesh)
{
	SAFE_RELEASE(m_pMesh);

	m_pMesh = pMesh;

	if (m_pMesh)
	{
		m_pMesh->AddRef();

		CMaterial*	pMaterial = m_pMesh->GetMaterial();

		m_pMaterial->CopyMaterial(pMaterial);

		SAFE_RELEASE(pMaterial);

		m_pTransform->SetMeshSize(m_pMesh->GetMax() - m_pMesh->GetMin());

		if (m_pMaterial && m_pAnimation2D)
		{
			CAnimation2DSequence*	pSequence = m_pAnimation2D->m_pSequence;

			if (pSequence)
			{
				pSequence->SetMaterialTexture(m_pMaterial);
			}
		}
	}
}

void CStaticMeshComponent::SetMaterial(CMaterial * pMaterial)
{

	m_pMaterial->CopyMaterial(pMaterial);

	if (m_pMaterial && m_pAnimation2D)
	{
		CAnimation2DSequence*	pSequence = m_pAnimation2D->m_pSequence;

		if (pSequence)
		{
			pSequence->SetMaterialTexture(m_pMaterial);
		}
	}
}

void CStaticMeshComponent::SetAnimation2D(CAnimation2D * pAnimation)
{
	SAFE_RELEASE(m_pAnimation2D);
	m_pAnimation2D = pAnimation;

	if (m_pAnimation2D)
		m_pAnimation2D->AddRef();

	if (m_pMaterial && m_pAnimation2D)
	{
		CAnimation2DSequence*	pSequence = m_pAnimation2D->m_pSequence;

		if (pSequence)
		{
			pSequence->SetMaterialTexture(m_pMaterial);
		}
	}

	if (m_pAnimation2D)
	{
		m_pAnimation2D->m_pOwner = this;
		m_pAnimation2D->SetMaterial(m_pMaterial);
	}
}

bool CStaticMeshComponent::UpdateMaterialCBufferNode(const string & strName, void * pData)
{
	return m_pMaterial->UpdateCBufferNode(strName, pData);
}

bool CStaticMeshComponent::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CStaticMeshComponent::Begin()
{
	CSceneComponent::Begin();
}

void CStaticMeshComponent::Update(float fTime)
{
	CSceneComponent::Update(fTime);

	if (m_pAnimation2D)
		m_pAnimation2D->Update(fTime);
}

void CStaticMeshComponent::Render(float fTime)
{
	CSceneComponent::Render(fTime);

	if (m_pMesh)
	{
		if (m_pAnimation2D)
			m_pAnimation2D->SetShader();

		size_t	iContainer = m_pMesh->GetContainerCount();

		for (size_t i = 0; i < iContainer; ++i)
		{
			size_t	iSubset = m_pMesh->GetSubsetCount(i);

			for (size_t j = 0; j < iSubset; ++j)
			{
				m_pMaterial->SetMaterial(i, j);
				m_pMesh->Render(i, j);

				m_pMaterial->ResetState();
			}
		}
	}
}

void CStaticMeshComponent::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
	CSceneComponent::RenderInstancing(fTime, pBuffer);

	if (m_pMesh)
	{
		if (m_pAnimation2D)
			m_pAnimation2D->SetShader();

		size_t	iContainer = m_pMesh->GetContainerCount();

		for (size_t i = 0; i < iContainer; ++i)
		{
			size_t	iSubset = m_pMesh->GetSubsetCount(i);

			for (size_t j = 0; j < iSubset; ++j)
			{
				m_pMaterial->SetMaterialInstancing(i, j);
				m_pMesh->RenderInstancing(i, j, pBuffer);

				m_pMaterial->ResetState();
			}
		}
	}
}
