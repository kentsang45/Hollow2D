#include "SceneComponent.h"
#include "../Object/GameObject.h"
#include "Transform.h"

CSceneComponent::CSceneComponent()	:
	m_pParent(nullptr)
{
	SetTypeID<CSceneComponent>();
	m_pTransform = new CTransform;

	m_pTransform->m_pOwner	= this;

	m_eComType = CT_SCENE;
	m_bUI	= false;
}

CSceneComponent::CSceneComponent(const CSceneComponent & com)	:
	CComponent(com)
{
	m_eComType = CT_SCENE;
	m_pOwner = nullptr;
	m_pParent = nullptr;

	m_vecChild.clear();

	m_pTransform = new CTransform(*com.m_pTransform);

	m_pTransform->m_pOwner = this;

	m_pTransform->m_pParent = nullptr;

	size_t	iSize = com.m_vecChild.size();

	for(size_t i = 0; i < iSize; ++i)
	{
		//CSceneComponent*	pCom = new 
	}

	m_bUI	= com.m_bUI;
}

CSceneComponent::~CSceneComponent()
{
	SAFE_DELETE(m_pTransform);

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Kill();
	}

	SAFE_RELEASE_VECLIST(m_vecChild);
}

Vector3 CSceneComponent::GetComponentMin() const
{
	return m_vComponentMin;
}

Vector3 CSceneComponent::GetComponentMax() const
{
	return m_vComponentMax;
}

void CSceneComponent::EnableUI()
{
	m_bUI	= true;
}

bool CSceneComponent::IsUI() const
{
	return m_bUI;
}

CTransform * CSceneComponent::GetTransform() const
{
	return m_pTransform;
}

CSceneComponent * CSceneComponent::FindComponentFromName(const string & strName)
{
	if (m_strName == strName)
	{
		AddRef();
		return this;
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		CSceneComponent*	pFind = m_vecChild[i]->FindComponentFromName(strName);

		if (pFind)
			return pFind;
	}

	return nullptr;
}

CSceneComponent * CSceneComponent::FindComponentFromTypeID(size_t iTypeID)
{
	if (m_iTypeID == iTypeID)
	{
		AddRef();
		return this;
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		CSceneComponent*	pFind = m_vecChild[i]->FindComponentFromTypeID(iTypeID);

		if (pFind)
			return pFind;
	}

	return nullptr;
}

CMaterial * CSceneComponent::GetMaterial() const
{
	return nullptr;
}

void CSceneComponent::AddChild(CSceneComponent * pChild, int iTransformRule)
{
	pChild->SetOwner(m_pOwner);
	pChild->m_pParent = this;
	pChild->m_pTransform->SetTransformRule(iTransformRule);
	m_vecChild.push_back(pChild);

	m_pTransform->m_vecChild.push_back(pChild->m_pTransform);

	pChild->m_pTransform->m_pParent = m_pTransform;

	pChild->m_pTransform->ComputeScaleRatio();
	pChild->m_pTransform->ComputeRotation();
	pChild->m_pTransform->ComputePos();

	pChild->AddRef();
}

void CSceneComponent::DeleteChild(CSceneComponent * pChild)
{
	size_t	iSize = m_vecChild.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecChild[i] == pChild)
		{
			pChild->m_pParent = nullptr;
			auto	iter = m_vecChild.begin() + i;
			m_vecChild.erase(iter);
			pChild->Release();

			auto	iterTr = m_pTransform->m_vecChild.begin() + i;
			m_pTransform->m_vecChild.erase(iterTr);
			pChild->m_pTransform->m_pParent = nullptr;
			pChild->m_pTransform->SetRelativePos(m_pTransform->GetWorldPos() + pChild->m_pTransform->GetRelativePos());
			pChild->m_pTransform->SetRelativeRotation(m_pTransform->GetWorldRot() + pChild->m_pTransform->GetRelativeRot());
			return;
		}
	}
}

bool CSceneComponent::Init()
{
	if (!CComponent::Init())
		return false;

	m_pTransform->m_pScene = m_pScene;

	return true;
}

void CSceneComponent::Begin()
{
	CComponent::Begin();
}

void CSceneComponent::Update(float fTime)
{
	CComponent::Update(fTime);

	size_t	iSize = m_vecChild.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecChild[i]->Update(fTime);
	}
}

void CSceneComponent::PostUpdate(float fTime)
{
	CComponent::PostUpdate(fTime);

	m_pTransform->PostUpdate(fTime);

	m_vComponentMin	= m_pTransform->GetWorldPos() - m_pTransform->GetPivot() * m_pTransform->GetWorldScale();
	m_vComponentMax = m_vComponentMin + m_pTransform->GetWorldScale();

	size_t	iSize = m_vecChild.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		m_vecChild[i]->PostUpdate(fTime);
	}
}

void CSceneComponent::Render(float fTime)
{
	CComponent::Render(fTime);

	// Transform 정보를 만들고 Shader로 보내준다.
	m_pTransform->SetTransform();
}

void CSceneComponent::RenderInstancing(float fTime, PInstancingBuffer pBuffer)
{
	CComponent::RenderInstancing(fTime, pBuffer);

	// Transform 정보를 만들고 Shader로 보내준다.
	m_pTransform->SetTransform();
}

void CSceneComponent::SetRelativeScale(const Vector3 & vScale)
{
	if (nullptr != m_pTransform)
	{
		m_pTransform->SetRelativeScale(vScale);
	}
}

void CSceneComponent::SetRelativeScale(float x, float y, float z)
{
	m_pTransform->SetRelativeScale(x, y, z);
}

void CSceneComponent::SetRelativeRotation(const Vector3 & vRot)
{
	m_pTransform->SetRelativeRotation(vRot);
}

void CSceneComponent::SetRelativeRotation(float x, float y, float z)
{
	m_pTransform->SetRelativeRotation(x, y, z);
}

void CSceneComponent::SetRelativeRotationX(float x)
{
	m_pTransform->SetRelativeRotationX(x);
}

void CSceneComponent::SetRelativeRotationY(float y)
{
	m_pTransform->SetRelativeRotationY(y);
}

void CSceneComponent::SetRelativeRotationZ(float z)
{
	m_pTransform->SetRelativeRotationZ(z);
}

void CSceneComponent::SetRelativePos(const Vector3 & vPos)
{
	m_pTransform->SetRelativePos(vPos);
}

void CSceneComponent::SetRelativePos(float x, float y, float z)
{
	m_pTransform->SetRelativePos(x, y, z);
}

void CSceneComponent::AddRelativeScale(const Vector3 & vScale)
{
	m_pTransform->AddRelativeScale(vScale);
}

void CSceneComponent::AddRelativeScale(float x, float y, float z)
{
	m_pTransform->AddRelativeScale(x, y, z);
}

void CSceneComponent::AddRelativePos(const Vector3 & vPos)
{
	m_pTransform->AddRelativePos(vPos);
}

void CSceneComponent::AddRelativePos(float x, float y, float z)
{
	m_pTransform->AddRelativePos(x, y, z);
}

void CSceneComponent::AddRelativeRotation(const Vector3 & vRot)
{
	m_pTransform->AddRelativeRotation(vRot);
}

void CSceneComponent::AddRelativeRotation(float x, float y, float z)
{
	m_pTransform->AddRelativeRotation(x, y, z);
}

void CSceneComponent::AddRelativeRotationX(float x)
{
	m_pTransform->AddRelativeRotationX(x);
}

void CSceneComponent::AddRelativeRotationY(float y)
{
	m_pTransform->AddRelativeRotationY(y);
}

void CSceneComponent::AddRelativeRotationZ(float z)
{
	m_pTransform->AddRelativeRotationZ(z);
}

void CSceneComponent::SetPivot(const Vector3 & vPivot)
{
	m_pTransform->SetPivot(vPivot);
}

void CSceneComponent::SetPivot(float x, float y, float z)
{
	m_pTransform->SetPivot(x, y, z);
}

Vector3 CSceneComponent::GetRelativeScale() const
{
	return m_pTransform->GetRelativeScale();
}

Vector3 CSceneComponent::GetRelativeRot() const
{
	return m_pTransform->GetRelativeRot();
}

Vector3 CSceneComponent::GetRelativePos() const
{
	return m_pTransform->GetRelativePos();
}

Vector3 CSceneComponent::GetRelaitveAxis(AXIS eAxis) const
{
	return m_pTransform->GetRelativeAxis(eAxis);
}

Vector3 CSceneComponent::GetPivot() const
{
	return m_pTransform->GetPivot();
}

// =================== World ===================
void CSceneComponent::SetWorldScale(const Vector3 & vScale)
{
	m_pTransform->SetWorldScale(vScale);
}

void CSceneComponent::SetWorldScale(float x, float y, float z)
{
	m_pTransform->SetWorldScale(x, y, z);
}

void CSceneComponent::SetWorldRotation(const Vector3 & vRot)
{
	m_pTransform->SetWorldRotation(vRot);
}

void CSceneComponent::SetWorldRotation(float x, float y, float z)
{
	m_pTransform->SetWorldRotation(x, y, z);
}

void CSceneComponent::SetWorldRotationX(float x)
{
	m_pTransform->SetWorldRotationX(x);
}

void CSceneComponent::SetWorldRotationY(float y)
{
	m_pTransform->SetWorldRotationY(y);
}

void CSceneComponent::SetWorldRotationZ(float z)
{
	m_pTransform->SetWorldRotationZ(z);
}

void CSceneComponent::SetWorldPos(const Vector3 & vPos)
{
	m_pTransform->SetWorldPos(vPos);
}

void CSceneComponent::SetWorldPos(float x, float y, float z)
{
	m_pTransform->SetWorldPos(x, y, z);
}

void CSceneComponent::AddWorldScale(const Vector3 & vScale)
{
	m_pTransform->AddWorldScale(vScale);
}

void CSceneComponent::AddWorldScale(float x, float y, float z)
{
	m_pTransform->AddWorldScale(x, y, z);
}

void CSceneComponent::AddWorldPos(const Vector3 & vPos)
{
	m_pTransform->AddWorldPos(vPos);
}

void CSceneComponent::AddWorldPos(float x, float y, float z)
{
	m_pTransform->AddWorldPos(x, y, z);
}

void CSceneComponent::AddWorldRotation(const Vector3 & vRot)
{
	m_pTransform->AddWorldRotation(vRot);
}

void CSceneComponent::AddWorldRotation(float x, float y, float z)
{
	m_pTransform->AddWorldRotation(x, y, z);
}

void CSceneComponent::AddWorldRotationX(float x)
{
	m_pTransform->AddWorldRotationX(x);
}

void CSceneComponent::AddWorldRotationY(float y)
{
	m_pTransform->AddWorldRotationY(y);
}

void CSceneComponent::AddWorldRotationZ(float z)
{
	m_pTransform->AddWorldRotationZ(z);
}

Vector3 CSceneComponent::GetWorldScale() const
{
	return m_pTransform->GetWorldScale();
}

Vector3 CSceneComponent::GetWorldRot() const
{
	return m_pTransform->GetWorldRot();
}

Vector3 CSceneComponent::GetWorldPos() const
{
	return m_pTransform->GetWorldPos();
}

Vector3 CSceneComponent::GetWorldAxis(AXIS eAxis) const
{
	return m_pTransform->GetWorldAxis(eAxis);
}

Matrix CSceneComponent::GetScaleMatrix() const
{
	return m_pTransform->GetScaleMatrix();
}

Matrix CSceneComponent::GetRotMatrix() const
{
	return m_pTransform->GetRotMatrix();
}

Matrix CSceneComponent::GetTranslationMatrix() const
{
	return m_pTransform->GetTranslationMatrix();
}

Matrix CSceneComponent::GetWorldMatrix() const
{
	return m_pTransform->GetWorldMatrix();
}

Vector3 CSceneComponent::GetFrameScale() const
{
	return m_pTransform->GetFrameScale();
}

Vector3 CSceneComponent::GetFrameRot() const
{
	return m_pTransform->GetFrameRot();
}

Vector3 CSceneComponent::GetFramePos() const
{
	return m_pTransform->GetFramePos();
}

void CSceneComponent::LookAt(CSceneComponent * pCom)
{
	m_pTransform->LookAt(pCom);
}

void CSceneComponent::LookAt(CTransform * pTransform)
{
	m_pTransform->LookAt(pTransform);
}

void CSceneComponent::LookAt(CGameObject * pObj)
{
	m_pTransform->LookAt(pObj);
}

void CSceneComponent::LookAt(const Vector3 & vLookAt)
{
	m_pTransform->LookAt(vLookAt);
}
