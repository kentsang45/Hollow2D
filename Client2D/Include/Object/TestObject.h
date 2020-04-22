#pragma once

#include "Object/GameObject.h"

class CTestObject :
	public CGameObject
{
	GAMEOBJECT_DEFAULT()

public:
	CTestObject();
	~CTestObject();

private:
	class CStaticMeshComponent*	m_pMesh;
	class CSceneComponent*		m_pRotPivot;
	class CStaticMeshComponent*	m_pChild1Mesh;
	class CStaticMeshComponent*	m_pChild2Mesh;
	class CSceneComponent*		m_pRotPivot1;
	class CSceneComponent*		m_pRotPivot2;
	class CStaticMeshComponent*	m_pChild3Mesh;
	class CStaticMeshComponent*	m_pChild4Mesh;
	class CCharacterMovementComponent*	m_pMovement;
	class CCameraComponent*		m_pCamera;
	class CAnimation2D*			m_pAnimation;
	class CColliderRect*		m_pBody;
	class CColliderSphere2D*	m_pBodySphere;
	class CColliderOBB2D*		m_pBodyOBB2D;

public:
	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

public:
	void MoveUpDown(float fScale, float fTime);
	void MoveSide(float fScale, float fTime);
	void RotationZ(float fScale, float fTime);
	void Fire(float fTime);
	void Delete(float fTime);
	void AnimAttackNotify(float fTime);
	void AttackSpeedUp(float fTime);
	void AttackBufEnd();

public:
	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
};

