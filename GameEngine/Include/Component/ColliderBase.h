#pragma once

#include "SceneComponent.h"

class ENGINE_DLL CColliderBase :
	public CSceneComponent
{
	friend class CGameObject;
	friend class CCollision;

protected:
	CColliderBase();
	CColliderBase(const CColliderBase& com);
	virtual ~CColliderBase();

protected:
	class CStaticMesh*	m_pDebugMesh;
	class CMaterial*	m_pMaterial;
	COLLIDER_TYPE		m_eColliderType;
	Vector3		m_vSectionMin;
	Vector3		m_vSectionMax;
	Vector3		m_vIntersect;
	vector<function<void(CColliderBase*, CColliderBase*, float)>>	m_vecBlockCallback;
	vector<function<void(CColliderBase*, CColliderBase*, float)>>	m_vecBeginOverlapCallback;
	vector<function<void(CColliderBase*, CColliderBase*, float)>>	m_vecEndOverlapCallback;
	PCollisionProfile	m_pProfile;
	bool		m_bOverlap;
	list<CColliderBase*>	m_CurrentFrameCollision;
	list<CColliderBase*>	m_CollisionList;
	vector<unsigned int>	m_vecSectionIndex;
	size_t					m_iAddSectionCount;
	bool					m_bMouseCollision;

	int m_iZOrder;


	bool m_bIsColliding;

	bool m_bOn;
	bool m_bStage;
	bool m_bMonster;
	PLAYER_POSITION m_ePlayerPos;

	bool m_bBlocking = false;

public:

	void SetZOrder(int iZOrder);
	int GetZOrder()	const;

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	void SetStage(bool bState);
	bool IsStage() const;

	void SetMonster(bool bMonster) { m_bMonster = bMonster; }
	bool IsMonster() const { return m_bMonster; }

	void SetOnOff(bool bOn);
	bool IsOn() const;

	Vector3 GetIntersect() const;

	bool IsColliding() const { return m_bIsColliding; }

	void SetBlock(bool bBlock) { m_bBlocking = bBlock; }
	bool GetBlock() const { return m_bBlocking; }
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////

	virtual class CMaterial* GetMaterial()	const;
	bool IsMouseCollision()	const;
	void CollisionMouse(bool bCollision);
	COLLIDER_TYPE GetColliderType()	const;
	Vector3 GetColliderSectionMin()	const;
	Vector3 GetColliderSectionMax()	const;
	PCollisionProfile GetCollisionProfile()	const;
	bool IsOverlap()	const;
	bool IsCurrentFrameCollision(CColliderBase* pCollider)	const;
	bool IsCollisionList(CColliderBase* pCollider)	const;
	void AddSectionIndex(int iIndex);
	void ClearSectionIndex();
	bool IsInSection(int iIndex);
	void CollisionFromSection(float fTime);

public:
	void SetDebugMesh(const string& strName);
	void SetMaterial(const string& strName);
	void SetCollisionProfile(const string& strName);
	void EnableOverlap(bool bOverlap);
	void ClearCurrentFrameCollision();
	void AddCurrentFrameCollision(CColliderBase* pCollider);
	void AddCollisionList(CColliderBase* pCollider);
	void DeleteCollisionList(CColliderBase* pCollider);

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);
	virtual void RenderInstancing(float fTime, PInstancingBuffer pBuffer);

public:
	void ComputeColor();

public:
	virtual bool Collision(CColliderBase* pDest) = 0;
	virtual bool Collision(const Vector2& vMousePos) = 0;

public:
	void AddBlockCallback(void(*pFunc)(CColliderBase*, CColliderBase*, float));
	void AddBeginOverlapCallback(void(*pFunc)(CColliderBase*, CColliderBase*, float));
	void AddEndOverlapCallback(void(*pFunc)(CColliderBase*, CColliderBase*, float));
	void CallBlock(CColliderBase* pDest, float fTime);
	void CallBeginOverlap(CColliderBase* pDest, float fTime);
	void CallEndOverlap(CColliderBase* pDest, float fTime);

	template <typename T>
	void AddBlockCallback(T* pObj, void(T::*pFunc)(CColliderBase*, CColliderBase*, float))
	{
		function<void(CColliderBase*, CColliderBase*, float)>	func;

		func = bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3);

		m_vecBlockCallback.push_back(func);
	}

	template <typename T>
	void AddBeginOverlapCallback(T* pObj, void(T::*pFunc)(CColliderBase*, CColliderBase*, float))
	{
		function<void(CColliderBase*, CColliderBase*, float)>	func;

		func = bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3);

		m_vecBeginOverlapCallback.push_back(func);
	}

	template <typename T>
	void AddEndOverlapCallback(T* pObj, void(T::*pFunc)(CColliderBase*, CColliderBase*, float))
	{
		function<void(CColliderBase*, CColliderBase*, float)>	func;

		func = bind(pFunc, pObj, placeholders::_1, placeholders::_2, placeholders::_3);

		m_vecEndOverlapCallback.push_back(func);
	}
};

