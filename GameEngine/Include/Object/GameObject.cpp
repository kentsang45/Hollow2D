#include "GameObject.h"
#include "../Component/Transform.h"
#include "../Component/CameraComponent.h"
#include "../Scene/Scene.h"
#include "../Render/RenderManager.h"

#include "../Timer.h"
#include "../TimerManager.h"

CGameObject::CGameObject()
{
	SetTypeID<CGameObject>();

	m_pRootComponent = new CSceneComponent;

	m_pRootComponent->m_pOwner = this;
	m_pRootComponent->SetName("DefaultSceneRoot");

	m_fActiveTime = 0.f;

	m_bPhysics = false;
	m_bOnLand = false;
	m_fGravityTime = 1.f;
	m_fForce = 0.f;
	m_fOriginForce = 0.f;
	m_bFalling = false;
	m_bJumping = false;
	m_iDir = 1;

	m_pTimer = GET_SINGLE(CTimerManager)->FindTimer("Main");

	if (nullptr == m_pTimer)
	{
		BOOM;
	}
}

CGameObject::~CGameObject()
{
	size_t	iSize = m_vecChild.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		CSceneComponent*	pParent = m_vecChild[i]->m_pRootComponent->m_pParent;

		if (!pParent)
			return;

		pParent->DeleteChild(m_vecChild[i]->m_pRootComponent);

		m_vecChild[i]->Release();
	}

	SAFE_RELEASE_VECLIST(m_BeginList);
	//SAFE_RELEASE_VECLIST(m_vecChild);
	for (size_t i = 0; i < m_vecObjComponent.size(); ++i)
	{
		m_vecObjComponent[i]->Kill();
	}

	SAFE_RELEASE_VECLIST(m_vecObjComponent);

	m_pRootComponent->Kill();
	SAFE_RELEASE(m_pRootComponent);
}

CScene * CGameObject::GetScene() const
{
	return m_pScene;
}

void CGameObject::SetPhysics(bool bPhysics)
{
	m_bPhysics = bPhysics;
}

bool CGameObject::GetPhysics() const
{
	return m_bPhysics;
}

void CGameObject::ClearGravity()
{
	m_fGravityTime = 0.f;
	m_fForce = 0.f;
	m_bJumping = false;
}

void CGameObject::SlowGravity()
{
	m_fGravityTime = 0.3f;
}

void CGameObject::Jump()
{
	BOOM
}

void CGameObject::Flip(int iFlip)
{
	// -1 은 왼쪽, 1은 오른쪽
	m_pRootComponent->GetTransform()->Flip(iFlip);
	m_iDir = iFlip;
}

void CGameObject::SetActiveTime(float fTime)
{
	m_fActiveTime = fTime;
}

void CGameObject::SetRoot(CSceneComponent * pRoot)
{
	SAFE_RELEASE(m_pRootComponent);

	m_pRootComponent = pRoot;
	m_pRootComponent->AddRef();

	m_pRootComponent->m_pOwner = this;
}

CTransform * CGameObject::GetTransform() const
{
	return m_pRootComponent->GetTransform();
}

void CGameObject::AddChild(CGameObject * pChild, int iTransformRule)
{
	pChild->AddRef();

	m_vecChild.push_back(pChild);

	m_pRootComponent->AddChild(pChild->m_pRootComponent, iTransformRule);
}

void CGameObject::AddChild(CGameObject * pChild, const string & strParentName, int iTransformRule)
{
	CSceneComponent*	pParent = m_pRootComponent->FindComponentFromName(strParentName);

	if (!pParent)
		return;

	pChild->AddRef();

	m_vecChild.push_back(pChild);
	
	pParent->AddChild(pChild->m_pRootComponent, iTransformRule);
}

void CGameObject::AddChild(CGameObject * pChild, CSceneComponent * pParent, int iTransformRule)
{
	pChild->AddRef();

	m_vecChild.push_back(pChild);

	pParent->AddChild(pChild->m_pRootComponent, iTransformRule);
}

void CGameObject::DeleteChild(CGameObject * pChild)
{
	CSceneComponent*	pParent = pChild->m_pRootComponent->m_pParent;

	if (!pParent)
		return;

	pParent->DeleteChild(pChild->m_pRootComponent);

	size_t	iSize = m_vecChild.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecChild[i] == pChild)
		{
			pChild->Release();
			auto	iter = m_vecChild.begin() + i;
			m_vecChild.erase(iter);
			return;
		}
	}
}

void CGameObject::DeleteChild(const string & strName)
{
	CGameObject*	pChild = nullptr;

	size_t	iSize = m_vecChild.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		if (m_vecChild[i]->GetName() == strName)
		{
			pChild = m_vecChild[i];
			pChild->Release();
			auto	iter = m_vecChild.begin() + i;
			m_vecChild.erase(iter);
			break;
		}
	}

	if (!pChild)
		return;

	CSceneComponent*	pParent = pChild->m_pRootComponent->m_pParent;

	pParent->DeleteChild(pChild->m_pRootComponent);
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Begin()
{
	if (!m_BeginList.empty())
	{
		auto	iter = m_BeginList.begin();
		auto	iterEnd = m_BeginList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Begin();
		}

		SAFE_RELEASE_NORMAL_VECLIST(m_BeginList);
	}
}

void CGameObject::Update(float fTime)
{
	if (m_fActiveTime > 0.f)
	{
		m_fActiveTime -= fTime;

		if (m_fActiveTime <= 0.f)
		{
			Kill();
			return;
		}
	}

	m_pRootComponent->Update(fTime);

	size_t	iCount = m_vecObjComponent.size();

	for (size_t i = 0; i < iCount; ++i)
	{
		if (m_vecObjComponent[i]->m_bTickUpdate)
			m_vecObjComponent[i]->Update(fTime);
	}

	if (!m_BeginList.empty())
	{
		auto	iter = m_BeginList.begin();
		auto	iterEnd = m_BeginList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Begin();
		}

		SAFE_RELEASE_NORMAL_VECLIST(m_BeginList);
	}



	// GRAVITY
	if (true == m_bPhysics)
	{
		/*m_fGravityTime += (fTime * m_fGravitySpeed);

		float fForce = 0.f;

		if (true == m_bJumping)
		{
			fForce = m_fForce * m_fGravityTime;
		}


		float total = fForce - 0.5f * GRAVITY * m_fGravityTime * m_fGravityTime;

		m_pRootComponent->AddRelativePos(GetWorldAxis(AXIS_Y) * total);*/


		///////////////////////////////// NEW GRAVITY

		m_fGravityTime += fTime;

		m_fForce -= GRAVITY * m_fGravityTime * m_fGravityTime * m_fGravitySpeed;

		// 속도 제한
		if (m_fForce <= -1500.f)
		{
			m_fForce = -1500.f;
		}

		m_pRootComponent->AddRelativePos(GetWorldAxis(AXIS_Y) * 1.f * m_fForce * fTime);



	}
}

void CGameObject::PostUpdate(float fTime)
{
	if (m_fActiveTime > 0.f)
	{
		m_fActiveTime -= fTime;

		if (m_fActiveTime <= 0.f)
		{
			Kill();
			return;
		}
	}

	m_pRootComponent->PostUpdate(fTime);

	size_t	iCount = m_vecObjComponent.size();

	for (size_t i = 0; i < iCount; ++i)
	{
		if (m_vecObjComponent[i]->m_bTickUpdate)
			m_vecObjComponent[i]->PostUpdate(fTime);
	}

	if (!m_BeginList.empty())
	{
		auto	iter = m_BeginList.begin();
		auto	iterEnd = m_BeginList.end();

		for (; iter != iterEnd; ++iter)
		{
			(*iter)->Begin();
		}

		SAFE_RELEASE_NORMAL_VECLIST(m_BeginList);
	}
}

void CGameObject::Render(float fTime)
{
	Render(m_pRootComponent, fTime);

	size_t	iCount = m_vecObjComponent.size();

	for (size_t i = 0; i < iCount; ++i)
	{
		m_vecObjComponent[i]->Render(fTime);
	}
}

void CGameObject::Render(CSceneComponent * pComponent, float fTime)
{
	//pComponent->Render(fTime);
	if(pComponent->IsEnable())
		GET_SINGLE(CRenderManager)->AddRenderer(pComponent);
	
	size_t	iSize = pComponent->m_vecChild.size();

	for (size_t i = 0; i < iSize; ++i)
	{
		Render(pComponent->m_vecChild[i], fTime);
	}
}

void CGameObject::SetRelativeScale(const Vector3 & vScale)
{
	m_pRootComponent->GetTransform()->SetRelativeScale(vScale);
}

void CGameObject::SetRelativeScale(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->SetRelativeScale(x, y, z);
}

void CGameObject::SetRelativeRotation(const Vector3 & vRot)
{
	m_pRootComponent->GetTransform()->SetRelativeRotation(vRot);
}

void CGameObject::SetRelativeRotation(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->SetRelativeRotation(x, y, z);
}

void CGameObject::SetRelativeRotationX(float x)
{
	m_pRootComponent->GetTransform()->SetRelativeRotationX(x);
}

void CGameObject::SetRelativeRotationY(float y)
{
	m_pRootComponent->GetTransform()->SetRelativeRotationY(y);
}

void CGameObject::SetRelativeRotationZ(float z)
{
	m_pRootComponent->GetTransform()->SetRelativeRotationZ(z);
}

void CGameObject::SetRelativePos(const Vector3 & vPos)
{
	m_pRootComponent->GetTransform()->SetRelativePos(vPos);
}

void CGameObject::SetRelativePos(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->SetRelativePos(x, y, z);
}

void CGameObject::AddRelativeScale(const Vector3 & vScale)
{
	m_pRootComponent->GetTransform()->AddRelativeScale(vScale);
}

void CGameObject::AddRelativeScale(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->AddRelativeScale(x, y, z);
}

void CGameObject::AddRelativePos(const Vector3 & vPos)
{
	m_pRootComponent->GetTransform()->AddRelativePos(vPos);
}

void CGameObject::AddRelativePos(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->AddRelativePos(x, y, z);
}

void CGameObject::AddRelativeRotation(const Vector3 & vRot)
{
	m_pRootComponent->GetTransform()->AddRelativeRotation(vRot);
}

void CGameObject::AddRelativeRotation(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->AddRelativeRotation(x, y, z);
}

void CGameObject::AddRelativeRotationX(float x)
{
	m_pRootComponent->GetTransform()->AddRelativeRotationX(x);
}

void CGameObject::AddRelativeRotationY(float y)
{
	m_pRootComponent->GetTransform()->AddRelativeRotationY(y);
}

void CGameObject::AddRelativeRotationZ(float z)
{
	m_pRootComponent->GetTransform()->AddRelativeRotationZ(z);
}

Vector3 CGameObject::GetRelativeScale() const
{
	return m_pRootComponent->GetTransform()->GetRelativeScale();
}

Vector3 CGameObject::GetRelativeRot() const
{
	return m_pRootComponent->GetTransform()->GetRelativeRot();
}

Vector3 CGameObject::GetRelativePos() const
{
	return m_pRootComponent->GetTransform()->GetRelativePos();
}

Vector3 CGameObject::GetRelativeAxis(AXIS eAxis) const
{
	return m_pRootComponent->GetTransform()->GetRelativeAxis(eAxis);
}

// =================== World ===================
void CGameObject::SetWorldScale(const Vector3 & vScale)
{
	m_pRootComponent->GetTransform()->SetWorldScale(vScale);
}

void CGameObject::SetWorldScale(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->SetWorldScale(x, y, z);
}

void CGameObject::SetWorldRotation(const Vector3 & vRot)
{
	m_pRootComponent->GetTransform()->SetWorldRotation(vRot);
}

void CGameObject::SetWorldRotation(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->SetWorldRotation(x, y, z);
}

void CGameObject::SetWorldRotationX(float x)
{
	m_pRootComponent->GetTransform()->SetWorldRotationX(x);
}

void CGameObject::SetWorldRotationY(float y)
{
	m_pRootComponent->GetTransform()->SetWorldRotationY(y);
}

void CGameObject::SetWorldRotationZ(float z)
{
	m_pRootComponent->GetTransform()->SetWorldRotationZ(z);
}

void CGameObject::SetWorldPos(const Vector3 & vPos)
{
	m_pRootComponent->GetTransform()->SetWorldPos(vPos);
}

void CGameObject::SetWorldPos(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->SetWorldPos(x, y, z);
}

void CGameObject::AddWorldScale(const Vector3 & vScale)
{
	m_pRootComponent->GetTransform()->AddWorldScale(vScale);
}

void CGameObject::AddWorldScale(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->AddWorldScale(x, y, z);
}

void CGameObject::AddWorldPos(const Vector3 & vPos)
{
	m_pRootComponent->GetTransform()->AddWorldPos(vPos);
}

void CGameObject::AddWorldPos(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->AddWorldPos(x, y, z);
}

void CGameObject::AddWorldRotation(const Vector3 & vRot)
{
	m_pRootComponent->GetTransform()->AddWorldRotation(vRot);
}

void CGameObject::AddWorldRotation(float x, float y, float z)
{
	m_pRootComponent->GetTransform()->AddWorldRotation(x, y, z);
}

void CGameObject::AddWorldRotationX(float x)
{
	m_pRootComponent->GetTransform()->AddWorldRotationX(x);
}

void CGameObject::AddWorldRotationY(float y)
{
	m_pRootComponent->GetTransform()->AddWorldRotationY(y);
}

void CGameObject::AddWorldRotationZ(float z)
{
	m_pRootComponent->GetTransform()->AddWorldRotationZ(z);
}

Vector3 CGameObject::GetWorldScale() const
{
	return m_pRootComponent->GetTransform()->GetWorldScale();
}

Vector3 CGameObject::GetWorldRot() const
{
	return m_pRootComponent->GetTransform()->GetWorldRot();
}

Vector3 CGameObject::GetWorldPos() const
{
	return m_pRootComponent->GetTransform()->GetWorldPos();
}

Vector3 CGameObject::GetWorldAxis(AXIS eAxis) const
{
	return m_pRootComponent->GetTransform()->GetWorldAxis(eAxis);
}

Matrix CGameObject::GetScaleMatrix() const
{
	return m_pRootComponent->GetTransform()->GetScaleMatrix();
}

Matrix CGameObject::GetRotMatrix() const
{
	return m_pRootComponent->GetTransform()->GetRotMatrix();
}

Matrix CGameObject::GetTranslationMatrix() const
{
	return m_pRootComponent->GetTransform()->GetTranslationMatrix();
}

Matrix CGameObject::GetWorldMatrix() const
{
	return m_pRootComponent->GetTransform()->GetWorldMatrix();
}

Vector3 CGameObject::GetFrameScale() const
{
	return m_pRootComponent->GetTransform()->GetFrameScale();
}

Vector3 CGameObject::GetFrameRot() const
{
	return m_pRootComponent->GetTransform()->GetFrameRot();
}

Vector3 CGameObject::GetFramePos() const
{
	return m_pRootComponent->GetTransform()->GetFramePos();
}

void CGameObject::LookAt(CSceneComponent * pCom)
{
	m_pRootComponent->LookAt(pCom);
}

void CGameObject::LookAt(CTransform * pTransform)
{
	m_pRootComponent->LookAt(pTransform);
}

void CGameObject::LookAt(CGameObject * pObj)
{
	m_pRootComponent->LookAt(pObj);
}

void CGameObject::LookAt(const Vector3 & vLookAt)
{
	m_pRootComponent->LookAt(vLookAt);
}

void CGameObject::CheckCamera(CComponent * pCom)
{
	if (pCom->GetTypeID() == typeid(CCameraComponent).hash_code())
	{
		m_pScene->AddCamera((CCameraComponent*)pCom);
	}
}
