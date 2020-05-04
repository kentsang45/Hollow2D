#include "HKMode.h"

#include "Scene/Scene.h"
#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Resource/Animation2DSequence.h"

#include "CollisionManager.h"

#include "HollowKnight.h"
#include "Bug.h"

#include "HKAttackEffect.h"




void HKMode::SetHK()
{
	int frameCount = 0;



	// IDLE
	frameCount = 8;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("IDLE_HK", true, 0.9f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/IDLE/IDLE%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "IDLE%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("IDLE_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("IDLE_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// BEFORE WALK
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BWALK_HK", true, 0.2f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/WALK/BWALK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "BWALK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BWALK_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BWALK_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// WALKING
	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("WALK_HK", true, 0.8f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/WALK/WALK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "WALK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("WALK_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("WALK_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// AFTER WALK
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("AWALK_HK", true, 0.2f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/WALK/AWALK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "AWALK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("AWALK_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("AWALK_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// ATTACK
	frameCount = 8;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("ATTACK_HK", true, 0.3f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/ATTACK/ATTACK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "ATTACK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("ATTACK_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("ATTACK_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// FIRE
	frameCount = 8;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FIRE_HK", true, 0.6f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/FIRE/FIRE%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "FIRE%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FIRE_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FIRE_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// BHEAL
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BHEAL_HK", true, 0.2f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/HEAL/BHEAL%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "BHEAL%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BHEAL_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BHEAL_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// HEAL
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HEAL_HK", true, 0.3f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/HEAL/HEAL%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "HEAL%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HEAL_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HEAL_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// AHEAL
	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("AHEAL_HK", true, 0.3f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/HEAL/AHEAL%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "AHEAL%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("AHEAL_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("AHEAL_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// TURN
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("TURN_HK", true, 0.05f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/WALK/TURN%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "TURN_HK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("TURN_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("TURN_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// JUMP
	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JUMP_HK", false, 0.5f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/JUMP/JUMP%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "JUMP_HK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JUMP_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JUMP_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// FALL
	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FALL_HK", false, 0.5f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/JUMP/FALL%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "FALL_HK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FALL_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FALL_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// FALLING
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FALLING_HK", true, 0.2f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/JUMP/FALLING/FALLING%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "FALLING_HK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FALLING_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FALLING_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// LAND
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("LAND_HK", true, 0.2f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/JUMP/LAND%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "LAND_HK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("LAND_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("LAND_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));



	////////////////////////////////////////////////////////////////////////////////////////////////// EFFECT
	////////////////////////////////////////////////////////////////////////////////////////////////// EFFECT
	////////////////////////////////////////////////////////////////////////////////////////////////// EFFECT
	// Attack Effect
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("ATTACK_EFFECT", true, 0.2f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/Attack/ATTACK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "ATTACK_EFFECT%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("ATTACK_EFFECT", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("ATTACK_EFFECT", Vector2(0.f, 0.f),
		Vector2(800.f, 800.f));




	// Hit Effect
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HIT_EFFECT", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/GetHit/HitEffect%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "HIT_EFFECT%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HIT_EFFECT", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HIT_EFFECT", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));



	// Side Effect
	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SIDE_EFFECT", true, 0.3f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/GetHit/SideEffect/SideEffect%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "SIDE_EFFECT%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SIDE_EFFECT", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SIDE_EFFECT", Vector2(0.f, 0.f),
		Vector2(1000.f, 1000.f));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////// FIREBALL
	// Fire Ball
	frameCount = 12;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FIREBALL", true, 0.5f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/FireBall/FireBall%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "FIREBALL%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FIREBALL", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FIREBALL", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// Fire Ball Hit
	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FIREBALL_HIT", true, 0.5f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/FireBallHit/FireBallHit%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "FIREBALL_HIT%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FIREBALL_HIT", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FIREBALL_HIT", Vector2(0.f, 0.f),
		Vector2(800.f, 800.f));

	// Fire Ball Start
	frameCount = 8;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FIREBALL_START", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/FireBallStart/FireBallStart%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "FIREBALL_START%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FIREBALL_START", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FIREBALL_START", Vector2(0.f, 0.f),
		Vector2(800.f, 800.f));



	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////// HEAL
	// HEAL START
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HEAL_START", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/Heal/HealStart%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "HEAL_START%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HEAL_START", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HEAL_START", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// HEALING
	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HEALING", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/Heal/Healing%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "HEALING%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HEALING", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HEALING", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// HEAL OVER
	frameCount = 8;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HEAL_OVER", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/Heal/HealOver%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "HEAL_OVER%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HEAL_OVER", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HEAL_OVER", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));




	// GET HIT
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DAMAGED_HK", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Move/DAMAGED/GetDamaged%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "DAMAGED_HK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DAMAGED_HK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DAMAGED_HK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// GET DAMAGED EFFECT
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DAMAGED_BLACK", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/GetDamaged/DAMAGED_BLACK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "DAMAGED_BLACK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DAMAGED_BLACK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DAMAGED_BLACK", Vector2(0.f, 0.f),
		Vector2(800.f, 800.f));



	// Monster Hit Effect
	frameCount = 7;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MONSTER_HIT_EFFECT", true, 0.6f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Effect/MonsterHitEffect/HitEffect%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "MONSTER_HIT_EFFECT%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MONSTER_HIT_EFFECT", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MONSTER_HIT_EFFECT", Vector2(0.f, 0.f),
		Vector2(800.f, 800.f));

	// BURST EFFECT
	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BURST_EFFECT", true, 0.5f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Effect/SoulBurst/Burst%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "BURST_EFFECT%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BURST_EFFECT", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BURST_EFFECT", Vector2(0.f, 0.f),
		Vector2(444.f, 444.f));

	// CRACK
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CRACK_EFFECT", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/Crack/CRACK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "CRACK_EFFECT%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CRACK_EFFECT", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CRACK_EFFECT", Vector2(0.f, 0.f),
		Vector2(800.f, 800.f));


	// DUST EFFECT

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DUSTEFFECT", true, 1.f, 7);
	GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DUSTEFFECT", "DUSTEFFECT",
		TEXT("HOLLOW/Effect/Dust/explode_particle.png"));

	for (int i = 0; i < 13; ++i)
	{
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceFrameInfo("DUSTEFFECT", Vector2(80.f * i, 0.f),
			Vector2(80.f * (i + 1), 100.f));
	}

	

}



void HKMode::SetUI()
{
	// NORMAP HP
	int frameCount = 9;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("UIHP", true, 0.5f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/UIEFFECT/HP/HP%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "UIHP%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("UIHP", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("UIHP", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));


	// BREAK HP
	frameCount = 22;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BREAKHP", true, 0.6f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/UIEFFECT/HP/BREAKHP%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "BREAKHP%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BREAKHP", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BREAKHP", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	// EMPTY HP
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("EMPTYHP", true, 1.0f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/UIEFFECT/HP/EMPTYHP%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "EMPTYHP%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("EMPTYHP", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("EMPTYHP", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	// cOIN UI
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("COIN_UI", true, 1.0f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/UIEFFECT/COIN_UI%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "COIN_UI%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("COIN_UI", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("COIN_UI", Vector2(0.f, 0.f),
		Vector2(62.f, 62.f));




	// Block Hit Effect
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BLOCKHIT_EFFECT", true, 0.6f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Effect/BlockHit/BlockHit%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "BLOCKHIT_EFFECT%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BLOCKHIT_EFFECT", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BLOCKHIT_EFFECT", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));

	// Block Hit Effect
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BLOCKHIT_B_EFFECT", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Effect/BlockHitB/BlockHitB%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "BLOCKHIT_B_EFFECT%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BLOCKHIT_B_EFFECT", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BLOCKHIT_B_EFFECT", Vector2(0.f, 0.f),
		Vector2(220.f, 225.f));

	// Dust Effect Frame
	frameCount = 13;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DUST_EFFECT_FRAME", true, 1.f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Effect/DustFrame/DUST_EFFECT%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "DUST_EFFECT_FRAME%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DUST_EFFECT_FRAME", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DUST_EFFECT_FRAME", Vector2(0.f, 0.f),
		Vector2(100.f, 100.f));


	// Dust Effect Frame
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DUST_EFFECT_STATIC", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Effect/DustStatic/DUST_EFFECT_STATIC%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "DUST_EFFECT_STATIC%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DUST_EFFECT_STATIC", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DUST_EFFECT_STATIC", Vector2(0.f, 0.f),
		Vector2(100.f, 100.f));





	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_1_IDLE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS1/grass1_idle%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_1_IDLE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_1_IDLE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_1_IDLE", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));


	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_1_MOVE", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS1/grass1_move%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_1_MOVE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_1_MOVE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_1_MOVE", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_1_DEATH", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS1/grass_01_death%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_1_DEATH%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_1_DEATH", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_1_DEATH", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_2_IDLE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS2/grass2_idle%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_2_IDLE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_2_IDLE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_2_IDLE", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));


	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_2_MOVE", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS2/grass2_move%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_2_MOVE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_2_MOVE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_2_MOVE", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_2_DEATH", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS2/grass_02_death%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_2_DEATH%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_2_DEATH", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_2_DEATH", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_3_IDLE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS3/grass3_idle%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_3_IDLE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_3_IDLE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_3_IDLE", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));


	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_3_MOVE", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS3/grass3_move%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_3_MOVE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_3_MOVE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_3_MOVE", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_3_DEATH", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS3/grass_03_death%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_3_DEATH%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_3_DEATH", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_3_DEATH", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_4_IDLE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS4/grass4_idle%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_4_IDLE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_4_IDLE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_4_IDLE", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));


	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_4_MOVE", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS4/grass4_move%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_4_MOVE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_4_MOVE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_4_MOVE", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_4_DEATH", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS4/grass_04_death%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_4_DEATH%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_4_DEATH", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_4_DEATH", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	////////////////////////////////////////////////////////////////////////////////////////////////////// GRASS
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_5_IDLE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS5/grass5_idle%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_5_IDLE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_5_IDLE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_5_IDLE", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));


	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_5_MOVE", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS5/grass5_move%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_5_MOVE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_5_MOVE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_5_MOVE", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("GRASS_5_DEATH", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/GRASS5/grass_05_death%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "GRASS_5_DEATH%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("GRASS_5_DEATH", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("GRASS_5_DEATH", Vector2(0.f, 0.f),
		Vector2(200.f, 200.f));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////// STATUE

	for (size_t k = 2; k < 9; ++k)
	{
		if (k == 5)
		{
			continue;
		}

		frameCount = 2;

		char number[20];
		itoa(k, number, 20);


		string temp = "STATUE_0";
		temp.append(number);

		GET_SINGLE(CResourceManager)->CreateAnimation2DSequence(temp, true, 1.f, frameCount);
		for (int i = 0; i < frameCount; ++i)
		{
			TCHAR	strFileName[MAX_PATH] = {};
			wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_0%d_%d.png"), k, i);
			char strKey[256] = {};
			sprintf_s(strKey, "STATUE_0%d%d", k, i);
			GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture(temp, strKey, strFileName);
		}

		if (2 == k)
		{
			GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll(temp, Vector2(0.f, 0.f),
				Vector2(250.f, 281.f));
		}
		else
		{
			GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll(temp, Vector2(0.f, 0.f),
				Vector2(250.f, 250.f));
		}

	}



	for (size_t k = 2; k < 9; ++k)
	{
		if (k == 5)
		{
			continue;
		}

		frameCount = 2;

		char number[20];
		itoa(k, number, 20);


		string temp = "STATUE_0";
		temp.append(number);
		temp.append("_BASE");

		GET_SINGLE(CResourceManager)->CreateAnimation2DSequence(temp, true, 1.f, frameCount);
		for (int i = 0; i < frameCount; ++i)
		{
			TCHAR	strFileName[MAX_PATH] = {};
			wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_0%d_base_%d.png"), k, i);
			char strKey[256] = {};
			sprintf_s(strKey, temp.c_str());
			GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture(temp, strKey, strFileName);
		}

		if (2 == k)
		{
			GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll(temp, Vector2(0.f, 0.f),
				Vector2(250.f, 281.f));
		}
		else
		{
			GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll(temp, Vector2(0.f, 0.f),
				Vector2(250.f, 250.f));
		}
		
	}








	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CART2", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/brk_cart_02_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "CART2%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CART2", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CART2", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("CART3", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/brk_cart_03_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "CART3%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("CART3", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("CART3", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));


	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BARREL1", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/brk_barrel_01_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "BARREL1%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BARREL1", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BARREL1", Vector2(0.f, 0.f),
		Vector2(150.f, 150.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BARREL2", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/brk_barrel_02_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "BARREL2%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BARREL2", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BARREL2", Vector2(0.f, 0.f),
		Vector2(150.f, 150.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BARREL3", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/brk_barrel_03_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "BARREL3%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BARREL3", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BARREL3", Vector2(0.f, 0.f),
		Vector2(150.f, 150.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BARREL4", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/brk_barrel_04_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "BARREL4%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BARREL4", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BARREL4", Vector2(0.f, 0.f),
		Vector2(150.f, 150.f));



	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MIGHTY_EFFECT", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Player/Effect/MightyZote/MZ%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "MIGHTY_EFFECT%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MIGHTY_EFFECT", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MIGHTY_EFFECT", Vector2(0.f, 0.f),
		Vector2(400.f, 178.f));



	/////////////////////////////////////////////////////////////

	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_WAVE1_", true, 0.3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/Effect/1/FK_WAVE%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_WAVE1_%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_WAVE1_", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_WAVE1_", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_WAVE2_", true, 0.3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/Effect/2/FK_WAVE%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_WAVE2_%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_WAVE2_", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_WAVE2_", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_WAVE3_", true, 0.3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/Effect/3/FK_WAVE%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_WAVE3_%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_WAVE3_", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_WAVE3_", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("EFFECT_BLOOD", true, 0.3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Effect/Blood/EFFECT_BLOOD%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "EFFECT_BLOOD%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("EFFECT_BLOOD", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("EFFECT_BLOOD", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	frameCount = 13;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BLOOD_DUST", true, 0.6f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Effect/BloodFrame/BLOOD_FRAME%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "BLOOD_DUST%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BLOOD_DUST", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BLOOD_DUST", Vector2(0.f, 0.f),
		Vector2(100.f, 100.f));

	frameCount = 8;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("COIN", true, 0.6f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Coin/COIN%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "COIN%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("COIN", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("COIN", Vector2(0.f, 0.f),
		Vector2(40.f, 40.f));




	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SPIKE_STILL", false, 1.0f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Spike/spikes_still_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SPIKE_STILL%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SPIKE_STILL", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SPIKE_STILL", Vector2(0.f, 0.f),
		Vector2(139.f, 105.f));



	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SPIKE", true, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Spike/spikes000%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SPIKE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SPIKE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SPIKE", Vector2(0.f, 0.f),
		Vector2(139.f, 105.f));


	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DARKNESS", true, 10.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Darkness/Darkness%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "DARKNESS%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DARKNESS", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DARKNESS", Vector2(0.f, 0.f),
		Vector2(3840.f, 2160.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("LIGHT", true, 10.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Effect/White_Light/white_light%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "LIGHT%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("LIGHT", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("LIGHT", Vector2(0.f, 0.f),
		Vector2(300.f, 300.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HP_HEAD", true, 10.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/UIEFFECT/HPUI/HealthUI%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "HP_HEAD%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HP_HEAD", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HP_HEAD", Vector2(0.f, 0.f),
		Vector2(172.f, 106.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("COIN_EFFECT", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Effect/CoinEffect/CoinEffect%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "COIN_EFFECT%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("COIN_EFFECT", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("COIN_EFFECT", Vector2(0.f, 0.f),
		Vector2(345.f, 51.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SOUL_EFFECT", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Effect/SoulOrb/Default_Particle%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SOUL_EFFECT%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SOUL_EFFECT", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SOUL_EFFECT", Vector2(0.f, 0.f),
		Vector2(64.f, 64.f));



	///////////////////////////////////////////////////////////////////

	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DOOR_OPEN", false, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Door/Open/White_Gate000%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "DOOR_OPEN%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DOOR_OPEN", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DOOR_OPEN", Vector2(0.f, 0.f),
		Vector2(90.f, 331.f));

	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DOOR_CLOSE", false, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Door/Close/White_Gate_Close%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "DOOR_CLOSE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DOOR_CLOSE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DOOR_CLOSE", Vector2(0.f, 0.f),
		Vector2(90.f, 331.f));




	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HIT_ORANGE", false, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Effect/HitOrange/hit_orange%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "HIT_ORANGE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HIT_ORANGE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HIT_ORANGE", Vector2(0.f, 0.f),
		Vector2(128.f, 128.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BINDING_SHIELD", false, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Effect/BindingShield/binding_shield%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "BINDING_SHIELD%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BINDING_SHIELD", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BINDING_SHIELD", Vector2(0.f, 0.f),
		Vector2(207.f, 207.f));





	// water drop
	frameCount = 8;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("WATER_DROP", false, 0.6f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Particle/WaterDrop/WaterDrop%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "WATER_DROP%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("WATER_DROP", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("WATER_DROP", Vector2(0.f, 0.f),
		Vector2(100.f, 100.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("WATER_DROPING", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Particle/WaterDrop/WaterDroping%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "WATER_DROPING%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("WATER_DROPING", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("WATER_DROPING", Vector2(0.f, 0.f),
		Vector2(100.f, 100.f));

	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("WATER_DROP_END", false, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Particle/WaterDrop/WaterDropEnd%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "WATER_DROP_END%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("WATER_DROP_END", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("WATER_DROP_END", Vector2(0.f, 0.f),
		Vector2(100.f, 100.f));


	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	frameCount = 7;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FB_PARTICLE", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Particle/FlyBugParticle/FBParticle%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FB_PARTICLE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FB_PARTICLE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FB_PARTICLE", Vector2(0.f, 0.f),
		Vector2(150.f, 150.f));

	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SPIDER_PARTICLE", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Particle/SpiderParticle/SpiderParticle%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SPIDER_PARTICLE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SPIDER_PARTICLE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SPIDER_PARTICLE", Vector2(0.f, 0.f),
		Vector2(150.f, 150.f));

	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("TF_PARTICLE", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Particle/ThinFlyParticle/ThinFlyParticle%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "TF_PARTICLE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("TF_PARTICLE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("TF_PARTICLE", Vector2(0.f, 0.f),
		Vector2(150.f, 150.f));

	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FLY_PARTICLE", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Particle/FlyParticle/FlyParticle%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FLY_PARTICLE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FLY_PARTICLE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FLY_PARTICLE", Vector2(0.f, 0.f),
		Vector2(50.f, 50.f));

/*
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_03", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_03_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_03%d", i);
		bool rs = GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_03", strKey, strFileName);
		if (false == rs)
		{
			BOOM;
		}
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_03", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_03_BASE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_03_base_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_03_BASE%d", i);
		bool rs = GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_03_BASE", strKey, strFileName);

		if (false == rs)
		{
			BOOM;
		}
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_03_BASE", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_04", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_04_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_04%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_04", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_04", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_04_BASE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_04_base_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_04_BASE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_04_BASE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_04_BASE", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_05", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_05_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_05%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_05", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_05", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_05_BASE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_05_base_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_05_BASE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_05_BASE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_05_BASE", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_06", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_06_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_06%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_06", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_06", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_06_BASE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_06_base_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_06_BASE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_06_BASE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_06_BASE", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_07", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_07_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_07%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_07", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_07", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_07_BASE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_07_base_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_07_BASE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_07_BASE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_07_BASE", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_08", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_08_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_08%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_08", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_08", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_08_BASE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_08_base_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_08_BASE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_08_BASE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_08_BASE", Vector2(0.f, 0.f),
		Vector2(250.f, 250.f));*/

}

