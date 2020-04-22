#pragma once

#include "GameEngine.h"

class ENGINE_DLL CCollisionManager
{
private:
	class CSectionManager*	m_pSectionManager;
	class CSectionManager*	m_pUISectionManager;
	class CColliderBase*	m_pPrevMouseCollision;
	class CColliderBase*	m_pCurrentMouseCollision;

public:
	void SetPrevMouseCollision(class CColliderBase* pCollider);
	void SetCurrentMouseCollision(class CColliderBase* pCollider);

private:
	list<PCollisionChannel>	m_ChannelList;
	unordered_map<size_t, PCollisionProfile>	m_mapProfile;
	list<class CColliderBase*>	m_ColliderList;

public:
	bool Init();
	bool CreateSection(const Vector3& vMin, const Vector3& vMax);
	bool CreateChannel(const string& strName, COLLISION_TYPE eType);
	bool CreateProfile(const string& strName, const string& strChannelName);
	bool UpdateProfileChannel(const string& strName, const string& strChannelName,
		COLLISION_TYPE eType);
	PCollisionProfile FindProfile(const string& strName);
	void AddCollider(class CColliderBase* pCollider);
	void Clear();
	void ChangeScene();
	void Collision(float fTime);

	DECLARE_SINGLE(CCollisionManager)
};

