#pragma once

#include "Object/GameObject.h"
#include "../Client.h"

class FlyingBug : public CGameObject
{
	GAMEOBJECT_DEFAULT();

public:
	FlyingBug();
	~FlyingBug();

	virtual bool Init();
	virtual void Begin();
	virtual void Update(float fTime);
	virtual void Render(float fTime);

	bool IsBlocking() const { return m_bBlocking; }

	void MoveX(float fTime);
	void Reverse();
	void CheckFront();
	void CheckCollision();
	void MoveBack(float fTime);
	void JumpBack(float fTime);

	void JumpEnd(float fTime);

	void TurnOff() { m_bTurn = false; }


	void SetCurrentState(BUG_STATE  eState);
	void SetAnimation(const string& strAniName);



	void OnBlock(class CColliderBase* pSrc, class CColliderBase* pDest, float fTime);

	void PlaceAt(int leftTopX, int leftTopY);

	bool CheckPlayer();

	void RandomIdle(float fTime);

	void SetStageNumber(int stage) { m_iStageNumber = stage; }

	void GetHitSound();
	void DeathSound();
protected:
	class HollowKnight* m_pHK;

	class CStaticMeshComponent* m_pMesh;

	class CCharacterMovementComponent* m_pMovement;
	class CAnimation2D* m_pAnimation;
	float m_fFireTime;

	class CColliderRect* m_pBody;
	int rotationNumber;

	// SENCER
	class Sencer* m_pRightSencer;
	class Sencer* m_pLeftSencer;
	// class MonsterEffect* m_pEffect;

	bool m_bDead = false;

	DIR_TYPE m_eDir;
	DIR_TYPE m_eVertical;

	DIR_TYPE m_eMoveBackDir;

	bool m_bMoveBack;
	float m_fMoveBackTimeMax;
	float m_fMoveBackTime;

	int m_iHP;

	BUG_STATE m_eState;
	std::vector<std::string> m_vecStateName;

	// 날아가며 죽기
	float m_fJumpTime = 0.f;
	float m_fJumpTotalTime = 1.f;
	bool m_bJump = false;

	float m_fCurrentForce;

	// 충돌
	bool m_bNoRight = false;
	bool m_bNoLeft = false;
	bool m_bLandPhysics = false; // 땅에 닿을때 방향 전환 방지
	bool m_bNoMoveBack = false; // true면 MoveBack 안한다.

	// 애니 앞부분 이름
	string m_strAniName;

	// 이동 속도
	float m_fMoveSpeed;
	float m_fWalkSpeed;

	// 돌기 
	bool m_bTurn = true;

	// DIELAND
	bool m_bDieLand = false;

	// Child 의 업데이트를 막는다
	// Turn 할때 막는다. 
	bool m_bChildUpdate = true;

	// false 면 Parent의 업데이트를 막는다.
	bool m_bParentUpdate = true;

	// 막기
	bool m_bBlocking = false;

	// 플레이어를 쫓아가고 있느냐
	bool m_bFollowing = false;
	Vector3 m_vHK;
	Vector3 m_vSrc;

	bool m_bFlying = false;

	// 위로 날기
	bool m_bFlyUp = false;
	float m_fUpTime = 0.f;
	float m_fUpTotalTime = 1.f;

	// 아래로 날기
	bool m_bFlyDown = false;
	float m_fDownTime = 0.f;
	float m_fDownTotalTime = 0.5f;

	// 튕김
	bool m_bBounceRight = false;
	float m_fBounceTime = 0.f;

	bool m_bBounceLeft = false;

	int m_iStageNumber = 0;

	string m_strSoundName;
	string m_strSoundFileName;

	class SoundObject* m_pFootsteps = nullptr;

	bool m_bWalkSound = false;

	float m_fSoundTime = 0.f;
	float m_fSoundTotalTime = 1.75f;
};


