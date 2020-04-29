#include "ColliderBase.h"
#include "../CollisionManager.h"
#include "../Resource/StaticMesh.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Material.h"
#include "Transform.h"

CColliderBase::CColliderBase()	:
	m_pDebugMesh(nullptr),
	m_pMaterial(nullptr),
	m_bOverlap(false),
	m_bMouseCollision(false)

	, m_bIsColliding(false)
	, m_bOn(true)
	, m_bMonster(false)
	, m_bStage(false)

	, m_iZOrder(0)
{
	m_pProfile = GET_SINGLE(CCollisionManager)->FindProfile("Static");
	m_vecSectionIndex.resize(10);
	m_iAddSectionCount = 0;

	m_ePlayerPos = PP_END;
}

CColliderBase::CColliderBase(const CColliderBase & com)	:
	CSceneComponent(com)
{
	m_iZOrder = com.m_iZOrder;
	m_bOverlap = com.m_bOverlap;
	m_vSectionMin = com.m_vSectionMin;
	m_vSectionMax = com.m_vSectionMax;
	m_eColliderType = com.m_eColliderType;
	m_bMouseCollision	= false;

	m_pDebugMesh = com.m_pDebugMesh;

	m_pProfile = nullptr;

	if (com.m_pProfile)
	{
		m_pProfile = GET_SINGLE(CCollisionManager)->FindProfile(com.m_pProfile->strName);
	}

	if (com.m_pMaterial)
	{
		m_pMaterial = new CMaterial;
		m_pMaterial->CopyMaterial(com.m_pMaterial);
	}

	else
		m_pMaterial = nullptr;

	if (m_pDebugMesh)
		m_pDebugMesh->AddRef();

	m_vecSectionIndex.resize(10);
	m_iAddSectionCount = 0;
}

CColliderBase::~CColliderBase()
{
	auto	iter = m_CollisionList.begin();
	auto	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}

	m_CollisionList.clear();

	SAFE_RELEASE(m_pMaterial);
	SAFE_RELEASE(m_pDebugMesh);
}
void CColliderBase::SetZOrder(int iZOrder)
{
	m_iZOrder = iZOrder;
}

int CColliderBase::GetZOrder() const
{
	return m_iZOrder;
}

void CColliderBase::SetStage(bool bStage)
{
	m_bStage = bStage;
}

bool CColliderBase::IsStage() const
{
	return m_bStage;
}

void CColliderBase::IsColliding(bool is)
{
	 m_bIsColliding = is; 
}

void CColliderBase::SetOnOff(bool bOn)
{
	m_bOn = bOn;
}

bool CColliderBase::IsOn() const
{
	return m_bOn;
}

Vector3 CColliderBase::GetIntersect() const
{
	return m_vIntersect;
}


CMaterial * CColliderBase::GetMaterial() const
{
	m_pMaterial->AddRef();
	return m_pMaterial;
}

bool CColliderBase::IsMouseCollision() const
{
	return m_bMouseCollision;
}

void CColliderBase::CollisionMouse(bool bCollision)
{
	m_bMouseCollision	= bCollision;
}

COLLIDER_TYPE CColliderBase::GetColliderType() const
{
	return m_eColliderType;
}

Vector3 CColliderBase::GetColliderSectionMin() const
{
	return m_vSectionMin;
}

Vector3 CColliderBase::GetColliderSectionMax() const
{
	return m_vSectionMax;
}

PCollisionProfile CColliderBase::GetCollisionProfile() const
{
	return m_pProfile;
}

bool CColliderBase::IsOverlap() const
{
	return m_bOverlap;
}

bool CColliderBase::IsCurrentFrameCollision(CColliderBase * pCollider) const
{
	auto	iter = m_CurrentFrameCollision.begin();
	auto	iterEnd = m_CurrentFrameCollision.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == pCollider)
			return true;
	}

	return false;
}

bool CColliderBase::IsCollisionList(CColliderBase * pCollider) const
{
	auto	iter = m_CollisionList.begin();
	auto	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == pCollider)
			return true;
	}

	return false;
}

void CColliderBase::AddSectionIndex(int iIndex)
{
	if (m_iAddSectionCount == m_vecSectionIndex.size())
	{
		m_vecSectionIndex.push_back(iIndex);
	}

	else
	{
		m_vecSectionIndex[m_iAddSectionCount] = iIndex;
	}
	++m_iAddSectionCount;
}

void CColliderBase::ClearSectionIndex()
{
	m_iAddSectionCount = 0;
}

bool CColliderBase::IsInSection(int iIndex)
{
	for (size_t i = 0; i < m_iAddSectionCount; ++i)
	{
		if (m_vecSectionIndex[i] == iIndex)
			return true;
	}

	return false;
}

void CColliderBase::CollisionFromSection(float fTime)
{
	auto	iter = m_CollisionList.begin();
	auto	iterEnd = m_CollisionList.end();

	bool	bIsInSection = false;
	for (; iter != iterEnd;)
	{
		CColliderBase*	pDest = *iter;
		bIsInSection = false;
		for (size_t i = 0; i < m_iAddSectionCount; ++i)
		{
			if (pDest->IsInSection(m_vecSectionIndex[i]))
			{
				bIsInSection = true;
				break;
			}
		}

		if (!bIsInSection)
		{
			iter = m_CollisionList.erase(iter);
			iterEnd = m_CollisionList.end();

			pDest->DeleteCollisionList(this);

			if (IsOverlap())
			{
				CallEndOverlap(pDest, fTime);
			}
			if (pDest->IsOverlap())
			{
				pDest->CallEndOverlap(this, fTime);
			}
			

		}

		else
			++iter;
	}
}

void CColliderBase::SetDebugMesh(const string & strName)
{
	SAFE_RELEASE(m_pDebugMesh);
	m_pDebugMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh(strName);

	if (m_pDebugMesh)
	{
		m_pTransform->SetMeshSize(m_pDebugMesh->GetMax() - m_pDebugMesh->GetMin());

		if (!m_pMaterial)
			m_pMaterial = new CMaterial;

		CMaterial*	pMaterial = m_pDebugMesh->GetMaterial();

		m_pMaterial->CopyMaterial(pMaterial);

		SAFE_RELEASE(pMaterial);
	}
}

void CColliderBase::SetMaterial(const string & strName)
{
	if (!m_pMaterial)
		m_pMaterial = new CMaterial;

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial(strName);

	if (pMaterial)
		m_pMaterial->CopyMaterial(pMaterial);

	SAFE_RELEASE(pMaterial);
}

void CColliderBase::SetCollisionProfile(const string & strName)
{
	m_pProfile = GET_SINGLE(CCollisionManager)->FindProfile(strName);
}

void CColliderBase::EnableOverlap(bool bOverlap)
{
	m_bOverlap = bOverlap;
}

void CColliderBase::ClearCurrentFrameCollision()
{
	m_CurrentFrameCollision.clear();
}

void CColliderBase::AddCurrentFrameCollision(CColliderBase * pCollider)
{
	m_CurrentFrameCollision.push_back(pCollider);
}

void CColliderBase::AddCollisionList(CColliderBase * pCollider)
{
	m_CollisionList.push_back(pCollider);
}

void CColliderBase::DeleteCollisionList(CColliderBase * pCollider)
{
	auto	iter = m_CollisionList.begin();
	auto	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == pCollider)
		{
			m_CollisionList.erase(iter);
			return;
		}
	}
}

bool CColliderBase::Init()
{
	if (!CSceneComponent::Init())
		return false;

	SetMaterial("ColliderMtrl");

	return true;
}

void CColliderBase::Begin()
{
	CSceneComponent::Begin();

	GET_SINGLE(CCollisionManager)->AddCollider(this);
}

void CColliderBase::Update(float fTime)
{
	CSceneComponent::Update(fTime);
}

void CColliderBase::Render(float fTime)
{
	CSceneComponent::Render(fTime);

	if (m_pDebugMesh)
	{
		if (!m_CollisionList.empty() || m_bMouseCollision)
		{
			m_pMaterial->SetSubsetDiffuse(Vector4::Red);

		}

		else
		{
			m_pMaterial->SetSubsetDiffuse(Vector4::Green);
	
		}

		size_t	iContainer = m_pDebugMesh->GetContainerCount();

		for (size_t i = 0; i < iContainer; ++i)
		{
			size_t	iSubset = m_pDebugMesh->GetSubsetCount(i);

			if (iSubset > 0)
			{
				for (size_t j = 0; j < iSubset; ++j)
				{
					m_pMaterial->SetMaterial(i, j);
					m_pDebugMesh->Render(i, j);
				}
			}

			else
			{
				m_pMaterial->SetMaterial(i, 0);
				m_pDebugMesh->Render(i, 0);
			}
		}

		m_pMaterial->ResetState();
	}
}

void CColliderBase::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
	CSceneComponent::RenderInstancing(fTime, pBuffer);

	if (m_pDebugMesh)
	{
		size_t	iContainer = m_pDebugMesh->GetContainerCount();

		for (size_t i = 0; i < iContainer; ++i)
		{
			size_t	iSubset = m_pDebugMesh->GetSubsetCount(i);

			if (iSubset > 0)
			{
				for (size_t j = 0; j < iSubset; ++j)
				{
					m_pMaterial->SetMaterialInstancing(i, j);
					m_pDebugMesh->RenderInstancing(i, j, pBuffer);
				}
			}

			else
			{
				m_pMaterial->SetMaterialInstancing(i, 0);
				m_pDebugMesh->RenderInstancing(i, 0, pBuffer);
			}
		}

		m_pMaterial->ResetState();
	}
}

void CColliderBase::ComputeColor()
{
	if (!m_CollisionList.empty() || m_bMouseCollision)
	{
		m_pMaterial->SetSubsetDiffuse(Vector4::Red);


	}

	else
	{
		m_pMaterial->SetSubsetDiffuse(Vector4::Green);

	}
}

void CColliderBase::AddBlockCallback(void(*pFunc)(CColliderBase *, CColliderBase *, float))
{
	function<void(CColliderBase*, CColliderBase*, float)>	func;

	func = bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3);

	m_vecBlockCallback.push_back(func);
}

void CColliderBase::AddBeginOverlapCallback(void(*pFunc)(CColliderBase *, CColliderBase *, float))
{
	function<void(CColliderBase*, CColliderBase*, float)>	func;

	func = bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3);

	m_vecBeginOverlapCallback.push_back(func);
}

void CColliderBase::AddEndOverlapCallback(void(*pFunc)(CColliderBase *, CColliderBase *, float))
{
	function<void(CColliderBase*, CColliderBase*, float)>	func;

	func = bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3);

	m_vecEndOverlapCallback.push_back(func);
}

void CColliderBase::CallBlock(CColliderBase * pDest, float fTime)
{
	size_t	iSize = m_vecBlockCallback.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecBlockCallback[i](this, pDest, fTime);
	}
}

void CColliderBase::CallBeginOverlap(CColliderBase * pDest, float fTime)
{
	size_t	iSize = m_vecBeginOverlapCallback.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecBeginOverlapCallback[i](this, pDest, fTime);
	}
}

void CColliderBase::CallEndOverlap(CColliderBase * pDest, float fTime)
{
	size_t	iSize = m_vecEndOverlapCallback.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecEndOverlapCallback[i](this, pDest, fTime);
	}
}
