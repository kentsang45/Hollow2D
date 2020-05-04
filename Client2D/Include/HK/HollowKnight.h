#pragma once

#include "Object/GameObject.h"
#include "../Client.h"





class HollowKnight : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	HollowKnight();
	~HollowKnight();

	void PlaceAt(int stageNumber, bool bStart);

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

	void AddCoinCount() { ++m_iCoinCount; }
	int GetCoinCount() const { return m_iCoinCount; }

	void CameraControl(float fTime);

	void CameraShake(float fTime);
	void CameraShakeOn(float fSetTime = 0.5f, int iIntensity = 30);

	void SetHPCoin(int hp, int coin) { m_iHP = hp; m_iCoinCount = coin; }

	void SetStage(int iStage, bool bStart);

	void GoToNext();
	void GoToPrev();
	int GetStageNumber() const { return m_iStageNumber; }

	void NextStage(float fTime);
	void PrevStage(float fTime);

	void BossOn(bool on) { m_bBossOn = on; }
	bool BossOn() const {		return m_bBossOn;	}

	void PlaceStart();
	void ResetPosition() { m_bReset = true; }

	void SetSoulEffect(float fTime);
	void SetBugEffect(float fTime);

	void SoundTestOn(float fTime);
	void SoundTestOff(float fTime);

	void SetEffectSound(const string& strKey, const char* pFileName);

private:
	void SetCurrentState(PLAYER_STATE state);
	void ReturnSequence(float fTime);

	void UpdateHeal(float fTime);

	void Reverse(float fTime);

	void SetAnimation();
	void SetKey();

	void SetHP();

	void UpdateCamera();

	

private:

	class Darkness* m_pDark = nullptr;

	class CStaticMeshComponent*	m_pMesh;

	class CStaticMeshComponent*	m_pDarkMesh;
	class CAnimation2D* m_pDarkAnimation;

	class CCharacterMovementComponent*	m_pMovement;
	class CCameraComponent*		m_pCamera;
	class CMaterial* m_pMaterial;
	class CAnimation2D* m_pAnimation;

	class Healing* m_pHealing;

	// COLLIDER
	class CColliderRect* m_pBody;

	// EFFECT
	class HKAttackEffect* m_pAttackEffect;

	// Stage
	class HKStage* m_pCurrentStage = nullptr;



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

	float m_fDustTime		= 0.f;
	float m_fDustTotalTime	= 0.03f;

	bool m_bDamaged = false;
	float m_fBlackTime = 0.f;

	// 충돌
	bool m_bNoRight = false;
	bool m_bNoLeft = false;
	bool m_bCeiling = false;

	// 공격모션
	bool m_bAttacking = false;
	float m_fAttackTime = 0.f;
	float m_fAttackTotalTime = 0.3f;

	// 중력
	bool m_bLandUp = false; // true면 땅에서 꺼진 만큼 위로 올라가야한다.
	float m_fUp = 0.f;

	bool m_bColliding = false;

	// STAGE
	int m_iStageNumber;
	float m_fStageSizeX;
	float m_fStageSizeY;

	float m_fNormalSpeed = 500.f;

	Vector3 m_vNoRight = Vector3::Zero;
	Vector3 m_vNoLeft = Vector3::Zero;

	// 콜리젼 빠져나오기
	bool m_bEscape = false;
	float m_fEscapeTime = 0.f;
	float m_fEscapeTotalTime = 0.01f;

	// 잠시 무적상태
	bool m_bInvincible = false;
	float m_fInvincibleTime = 0.f;
	float m_fInvincibleTotalTime = 0.5f;

	// 카메라 쉐이크
	bool m_bShake = false;
	float m_fShakeTime = 0.f;
	float m_fShakeTotalTime = 0.5f;

	int m_iIntensity;

	Vector3 m_vPrevPos = Vector3::Zero;

	// 동전
	int m_iCoinCount = 0;

	bool m_bNext = false;
	bool m_bPrev = false;

	// 공중부양 상태
	bool m_bAir= false;
	float m_fAirTime = 0.f;
	float m_fAirTotalTime = 0.5f;

	// 두둥등장
	bool m_bBossOn = false;

	bool m_bReset = false;
	float m_fResetTime = 0.f;
	float m_fResetTotalTime = 0.5f;


	//bool m_bBright = false;
	//float m_fBrightTime = 0.f;
	//float m_fBrightTotalTime = 0.5f;



	class SoundObject* m_pFootsteps = nullptr;

	bool m_bWalkSound = false;
};

