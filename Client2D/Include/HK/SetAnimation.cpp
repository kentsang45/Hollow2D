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
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("TURN_HK", true, 0.1f, frameCount);

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

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_02", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_02_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_02%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_02", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_02", Vector2(0.f, 0.f),
		Vector2(250.f, 281.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("STATUE_02_BASE", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Objects/Statue/statue_02_base_%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "STATUE_02_BASE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("STATUE_02_BASE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("STATUE_02_BASE", Vector2(0.f, 0.f),
		Vector2(250.f, 281.f));

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

