#include "CollisionManager.h"
#include "SectionManager.h"
#include "Component/ColliderBase.h"
#include "Device.h"
#include "Input.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()	:
	m_pSectionManager(nullptr),
	m_pUISectionManager(nullptr),
	m_pPrevMouseCollision(nullptr),
	m_pCurrentMouseCollision(nullptr)
{
}

CCollisionManager::~CCollisionManager()
{
	SAFE_RELEASE_VECLIST(m_ColliderList);
	SAFE_DELETE_NORMAL_VECLIST(m_ChannelList);
	SAFE_DELETE_NORMAL_MAP(m_mapProfile);
	SAFE_DELETE(m_pUISectionManager);
	SAFE_DELETE(m_pSectionManager);
}

void CCollisionManager::SetPrevMouseCollision(CColliderBase * pCollider)
{
	m_pPrevMouseCollision	= pCollider;
}

void CCollisionManager::SetCurrentMouseCollision(CColliderBase * pCollider)
{
	m_pCurrentMouseCollision	= pCollider;
}

bool CCollisionManager::Init()
{
	m_pSectionManager = new CSectionManager;
	m_pUISectionManager	= new CSectionManager;

	Resolution	tRS = _RESOLUTION;

	m_pUISectionManager->m_vDefaultSectionSize	= Vector3(tRS.iWidth, tRS.iHeight, 1.f);
	m_pUISectionManager->CreateSection(Vector3(0.f, 0.f, 0.f), Vector3(tRS.iWidth, tRS.iHeight, 1.f), true);

	CreateChannel("Static", CT_BLOCK);
	CreateChannel("Mouse", CT_BLOCK);

	CreateProfile("Static", "Static");

	CreateSection(Vector3(0.f, 0.f, 0.f), Vector3(10000.f, 10000.f, 1.f));

	return true;
}

bool CCollisionManager::CreateSection(const Vector3& vMin, const Vector3& vMax)
{
	if (!m_pSectionManager->CreateSection(vMin, vMax))
		return false;

	return true;
}

bool CCollisionManager::CreateChannel(const string & strName, COLLISION_TYPE eType)
{
	// 같은 채널이 있는지 판단한다.
	auto	iter = m_ChannelList.begin();
	auto	iterEnd = m_ChannelList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->strName == strName)
			return false;
	}

	PCollisionChannel	pChannel = new CollisionChannel;

	pChannel->strName = strName;
	pChannel->eType = eType;

	m_ChannelList.push_back(pChannel);

	auto	iterP = m_mapProfile.begin();
	auto	iterPEnd = m_mapProfile.end();

	for (; iterP != iterPEnd; ++iterP)
	{
		iterP->second->ChannelList.push_back(*pChannel);
	}

	return true;
}

bool CCollisionManager::CreateProfile(const string & strName, const string & strChannelName)
{
	PCollisionProfile	pProfile = FindProfile(strName);

	if (pProfile)
		return false;

	pProfile = new CollisionProfile;

	pProfile->strName = strName;
	pProfile->strChannelName = strChannelName;

	auto	iter = m_ChannelList.begin();
	auto	iterEnd = m_ChannelList.end();

	for (; iter != iterEnd; ++iter)
	{
		pProfile->ChannelList.push_back(**iter);
	}

	hash<string>	h;
	size_t iKey = h(strName);
	m_mapProfile.insert(make_pair(iKey, pProfile));

	return true;
}

bool CCollisionManager::UpdateProfileChannel(const string & strName, const string & strChannelName,
	COLLISION_TYPE eType)
{
	PCollisionProfile	pProfile = FindProfile(strName);

	if (!pProfile)
		return false;

	auto	iter = pProfile->ChannelList.begin();
	auto	iterEnd = pProfile->ChannelList.end();

	for (; iter != iterEnd; ++iter)
	{
		if ((*iter).strName == strChannelName)
		{
			(*iter).eType = eType;
			break;
		}
	}

	return true;
}

PCollisionProfile CCollisionManager::FindProfile(const string & strName)
{
	hash<string>	h;
	size_t iKey = h(strName);

	auto	iter = m_mapProfile.find(iKey);

	if (iter == m_mapProfile.end())
		return nullptr;

	return iter->second;
}

void CCollisionManager::AddCollider(CColliderBase * pCollider)
{
	if (pCollider)
		pCollider->AddRef();

	m_ColliderList.push_back(pCollider);

	//m_pSectionManager->AddCollider(pCollider);
}

void CCollisionManager::Clear()
{
	m_pSectionManager->Clear();
	m_pUISectionManager->Clear();
}

void CCollisionManager::ChangeScene()
{
	m_pSectionManager->Clear();
	m_pUISectionManager->Clear();
	m_pPrevMouseCollision = nullptr;
	m_pCurrentMouseCollision = nullptr;
}

void CCollisionManager::Collision(float fTime)
{
	auto	iter = m_ColliderList.begin();
	auto	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd;)
	{
		CColliderBase*	pCollider = *iter;

		if (!pCollider->IsActive())
		{
			SAFE_RELEASE(pCollider);
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
			continue;
		}

		else if (!pCollider->IsEnable())
		{
			++iter;
			continue;
		}

		pCollider->ClearCurrentFrameCollision();
		pCollider->ClearSectionIndex();

		if(pCollider->IsUI())
			m_pUISectionManager->AddCollider(pCollider);

		else
			m_pSectionManager->AddCollider(pCollider);

		++iter;
	}

	iter = m_ColliderList.begin();
	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->CollisionFromSection(fTime);
	}

	// m_pSectionManager->Sort();
	m_pUISectionManager->Sort();

	m_pCurrentMouseCollision	= nullptr;

	// UI와 마우스를 체크한다.
	if (!m_pUISectionManager->CollisionMouse(GET_SINGLE(CInput)->GetMousePos(), fTime))
	{
		if (m_pSectionManager->CollisionMouse(GET_SINGLE(CInput)->GetMouseWorldPos(), fTime))
		{
			if (m_pPrevMouseCollision != m_pCurrentMouseCollision &&
				m_pPrevMouseCollision)
			{
				m_pPrevMouseCollision->CallEndOverlap(nullptr, fTime);
				m_pPrevMouseCollision->CollisionMouse(false);
				m_pPrevMouseCollision = nullptr;
			}
		}

		else if (m_pPrevMouseCollision != m_pCurrentMouseCollision &&
			m_pPrevMouseCollision)
		{
			m_pPrevMouseCollision->CallEndOverlap(nullptr, fTime);
			m_pPrevMouseCollision->CollisionMouse(false);
			m_pPrevMouseCollision = nullptr;
		}
	}

	else if (m_pPrevMouseCollision != m_pCurrentMouseCollision &&
		m_pPrevMouseCollision)
	{
		m_pPrevMouseCollision->CallEndOverlap(nullptr, fTime);
		m_pPrevMouseCollision->CollisionMouse(false);
		m_pPrevMouseCollision	= nullptr;
	}

	m_pPrevMouseCollision	= m_pCurrentMouseCollision;

	m_pUISectionManager->Collision(fTime);

	m_pSectionManager->Collision(fTime);

	iter = m_ColliderList.begin();
	iterEnd = m_ColliderList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->ComputeColor();
	}
}
