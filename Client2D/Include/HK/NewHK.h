#pragma once

#include "Object/GameObject.h"
#include "../Client.h"





class NewHK : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	NewHK();
	~NewHK();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	DIR_TYPE GetDirection() const;

	void MoveX(float fScale, float fTime);

	void Fire(float fTime);
	void Attack(float fTime);
	void Jump(float fTime);
	void JumpEnd(float fTime);
	void JumpOver(float fTime);

	void Heal(float fTime);





	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void BeginOverlap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	void EndOverlap(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);
	// void HitStay(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);


	void SetEffect(class HKAttackEffect* attackEffect);


private:
	void SetCurrentState(PLAYER_STATE state);
	void ReturnSequence(float fTime);

	void UpdateHeal(float fTime);

	void Reverse(float fTime);

	void SetAnimation();
	void SetKey();

	void SetHP();




private:
	class CStaticMeshComponent*	m_pMesh;
	class CCharacterMovementComponent*	m_pMovement;
	class CCameraComponent*		m_pCamera;
	class CMaterial* m_pMaterial;
	class CAnimation2D* m_pAnimation;

	class Healing* m_pHealing;

	// COLLIDER
	class CColliderRect* m_pBody;

	// EFFECT
	class HKAttackEffect* m_pAttackEffect;



	//////////////////////////////////////////////////////////////////////////////////
	PLAYER_STATE m_eState;
	std::vector<std::string> m_vecStateName;

	DIR_TYPE m_eDirType;
	float m_fHealTime;
	bool m_bFire;
	bool m_bIsHealing;
	bool m_bHealOver;
	bool m_bHealStart;

	bool m_bTurnStart;
	float m_fTurningTime;
	bool m_bTurnOver;

	float m_fFireTime;
	bool m_bFireOn;

	float m_fJumpTime;
	float m_fJumpTotalTime;
	bool m_bHitStage;


	float m_fDamagedTime;
	float m_fDamagedTotalTime;

	DIR_TYPE m_eMonsterDir;

	int m_iHP;

	std::vector<class UIHP*> m_stackHP;
	int m_iHPCount;

	float m_fDustTime = 0.f;
	float m_fDustTotalTime = 0.03f;

	bool m_bDamaged = false;
	float m_fBlackTime = 0.f;
};

