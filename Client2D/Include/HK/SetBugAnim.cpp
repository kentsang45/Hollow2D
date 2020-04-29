#include "HKMode.h"

#include "Scene/Scene.h"
#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "Resource/Animation2DSequence.h"

#include "CollisionManager.h"

#include "HollowKnight.h"
#include "Bug.h"

#include "HKAttackEffect.h"



void HKMode::SetBug()
{
	// Bug
	int frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BUG_WALK", true, 0.5f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/BUG/BUG%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "BUG_WALK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BUG_WALK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BUG_WALK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// Bug Turn
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BUG_TURN", true, 0.1f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/BUG/BUG_TURN%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "BUG_TURN%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BUG_TURN", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BUG_TURN", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));




	// BUG DIE
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BUG_DIE", false, 0.8f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/BUG/BUG_DIE%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "BUG_DIE%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BUG_DIE", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BUG_DIE", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// BUG DEAD
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BUG_DEAD", false, 0.2f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/BUG/BUG_DEAD%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "BUG_DEAD%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BUG_DEAD", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BUG_DEAD", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Dashing Bug
	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DB_WALK", true, 0.8f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/DASHING_BUG/WALK/DB_WALK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "DB_WALK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DB_WALK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DB_WALK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// DB Turn
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DB_TURN", true, 0.1f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/DASHING_BUG/TURN/DB_TURN%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "DB_TURN%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DB_TURN", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DB_TURN", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));




	// DB DIE
	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DB_DIE", true, 0.8f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/DASHING_BUG/DIE/DB_DIE%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "DB_DIE%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DB_DIE", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DB_DIE", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// DB DASH
	frameCount = 7;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DB_DASH", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/DASHING_BUG/RUN/DB_RUN%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "DB_DASH%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DB_DASH", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DB_DASH", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// DB DEAD
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DB_DEAD", false, 0.1f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/DASHING_BUG/DEAD/DB_DEAD%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "DB_DEAD%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DB_DEAD", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DB_DEAD", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// DB BWALK
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DB_BWALK", false, 0.2f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/DASHING_BUG/BWALK/DB_BWALK%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "DB_BWALK%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DB_BWALK", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DB_BWALK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// DB STAND
	frameCount = 7;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("DB_STAND", true, 1.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/DASHING_BUG/STANDING/DB_STANDING%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "DB_STAND%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("DB_STAND", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("DB_STAND", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Dashing Bug
	frameCount = 7;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HB_WALK", true, 0.8f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/HORN_BUG/WALK/HB_WALK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "HB_WALK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HB_WALK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HB_WALK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// HB Turn
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HB_TURN", true, 0.1f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/HORN_BUG/TURN/HB_TURN%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "HB_TURN%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HB_TURN", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HB_TURN", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));




	// HB DIE
	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HB_DIE", true, 0.5f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/HORN_BUG/DIE/HB_DIE%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "HB_DIE%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HB_DIE", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HB_DIE", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// HB DASH
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HB_DASH", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/HORN_BUG/RUN/HB_RUN%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "HB_DASH%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HB_DASH", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HB_DASH", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// HB DEAD
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HB_DEAD", false, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/HORN_BUG/DEAD/HB_DEAD%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "HB_DEAD%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HB_DEAD", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HB_DEAD", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// HB BRUN
	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("HB_BDASH", false, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/HORN_BUG/BRUN/HB_BRUN%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "HB_BDASH%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("HB_BDASH", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("HB_BDASH", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Jump Bug
	frameCount = 7;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JB_WALK", true, 0.8f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/JUMP_BUG/WALK/JB_WALK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "JB_WALK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JB_WALK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JB_WALK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// JB Turn
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JB_TURN", true, 0.1f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/JUMP_BUG/TURN/JB_TURN%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "JB_TURN%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JB_TURN", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JB_TURN", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));




	// JB DIE
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JB_DIE", true, 0.5f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/JUMP_BUG/DIE/JB_DIE%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "JB_DIE%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JB_DIE", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JB_DIE", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// JB DIELAND
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JB_DIELAND", true, 0.4f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/JUMP_BUG/DIELAND/JB_DIELAND%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "JB_DIELAND%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JB_DIELAND", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JB_DIELAND", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// JB DEAD
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JB_DEAD", false, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/JUMP_BUG/DEAD/JB_DEAD%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "JB_DEAD%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JB_DEAD", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JB_DEAD", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// JB BJUMP
	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JB_BJUMP", false, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/JUMP_BUG/BJUMP/JB_BJUMP%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "JB_BJUMP%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JB_BJUMP", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JB_BJUMP", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// JB JUMP
	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JB_JUMP", false, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/JUMP_BUG/JUMP/JB_JUMP%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "JB_JUMP%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JB_JUMP", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JB_JUMP", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	// JB ATTACK
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JB_ATTACK", false, 0.3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/JUMP_BUG/ATTACK/JB_ATTACK%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "JB_ATTACK%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JB_ATTACK", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JB_ATTACK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	// JB STAND
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("JB_STAND", false, 0.3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/JUMP_BUG/STAND/JB_STAND%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "JB_STAND%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("JB_STAND", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("JB_STAND", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Shield Bug
	frameCount = 7;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_WALK", true, 0.8f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/WALK/SB_WALK%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_WALK%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_WALK", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_WALK", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));


	// SB Turn
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_TURN", true, 0.1f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/TURN/SB_TURN%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_TURN%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_TURN", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_TURN", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));




	// SB DIE
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_DIE", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/DIE/SB_DIE%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_DIE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_DIE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_DIE", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));


	// SB DIELAND
	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_DIELAND", true, 0.6f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/DIELAND/SB_DIELAND%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_DIELAND%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_DIELAND", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_DIELAND", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));

	// SB DEAD
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_DEAD", false, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/DEAD/SB_DEAD%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_DEAD%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_DEAD", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_DEAD", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));

	// SB ATTACK A
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_ATTACKA", false, 0.2f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/ATTACKA/SB_ATTACKA%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_ATTACKA%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_ATTACKA", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_ATTACKA", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));


	// SB ATTACK B
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_ATTACKB", false, 0.2f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/ATTACKB/SB_ATTACKB%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_ATTACKB%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_ATTACKB", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_ATTACKB", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));

	// SB ATTACK C
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_ATTACKC", false, 0.2f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/ATTACKC/SB_ATTACKC%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_ATTACKC%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_ATTACKC", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_ATTACKC", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));

	// SB AFTER ATTACK
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_AATTACK", false, 0.2f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/AATTACK/SB_AATTACK%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_AATTACK%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_AATTACK", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_AATTACK", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));

	// SB BLOCK
	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_BLOCK", false, 0.8f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/BLOCK/SB_BLOCK%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_BLOCK%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_BLOCK", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_BLOCK", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));


	// SB STAND
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_STAND", true, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/STAND/SB_STAND%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_STAND%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_STAND", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_STAND", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));

	// SB WAIT
	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_WAIT", true, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/WAIT/SB_WAIT%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_WAIT%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_WAIT", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_WAIT", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));

	// SB BLOCKHIT
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_BLOCKHIT", false, 0.2f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/BLOCKHIT/SB_BLOCKHIT%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_BLOCKHIT%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_BLOCKHIT", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_BLOCKHIT", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));

	// SB BEFORE ATTACK
	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SB_BATTACK", true, 0.1f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/SHIELD_BUG/BATTACK/SB_BATTACK%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "SB_BATTACK%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SB_BATTACK", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SB_BATTACK", Vector2(0.f, 0.f),
		Vector2(600.f, 600.f));


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Small Bug
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SMB_WALK", true, 0.5f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/SMALL_BUG/WALK/SB_WALK%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "SMB_WALK%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SMB_WALK", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SMB_WALK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));



	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SMB_TURN", true, 0.3f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/SMALL_BUG/TURN/SB_TURN%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "SMB_TURN%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SMB_TURN", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SMB_TURN", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));




	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SMB_DIE", true, 0.3f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/SMALL_BUG/DIE/SB_DIE%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "SMB_DIE%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SMB_DIE", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SMB_DIE", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));



	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("SMB_DEAD", false, 0.3f, frameCount);

	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("HOLLOW/Monster/SMALL_BUG/DEAD/SB_DEAD%d.png"), i);

		char strKey[256] = {};
		sprintf_s(strKey, "SMB_DEAD%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("SMB_DEAD", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("SMB_DEAD", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////// FYING BUG

	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FB_STAND", true, 0.3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FLYING_BUG/IDLE/FB_IDLE%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FB_STAND%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FB_STAND", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FB_STAND", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	frameCount = 7;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FB_WALK", true, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FLYING_BUG/RUN/FB_RUN%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FB_WALK%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FB_WALK", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FB_WALK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FB_BWALK", true, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FLYING_BUG/BRUN/FB_BRUN%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FB_BWALK%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FB_BWALK", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FB_BWALK", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FB_TURN", true, 0.2f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FLYING_BUG/TURN/FB_TURN%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FB_TURN%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FB_TURN", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FB_TURN", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	//frameCount = 2;
	//GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FB_TURN", true, 0.2f, frameCount);
	//for (int i = 0; i < frameCount; ++i)
	//{
	//	TCHAR	strFileName[MAX_PATH] = {};
	//	wsprintf(strFileName, TEXT("HOLLOW/Monster/FLYING_BUG/TURN/FB_TURN%d.png"), i);
	//	char strKey[256] = {};
	//	sprintf_s(strKey, "FB_TURN%d", i);
	//	GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FB_TURN", strKey, strFileName);
	//}
	//GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FB_TURN", Vector2(0.f, 0.f),
	//	Vector2(400.f, 400.f));



	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FB_DIE", true, 0.3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FLYING_BUG/DIE/FB_DIE%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FB_DIE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FB_DIE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FB_DIE", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));


	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FB_DEAD", false, 0.2f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FLYING_BUG/DEAD/FB_DEAD%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FB_DEAD%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FB_DEAD", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FB_DEAD", Vector2(0.f, 0.f),
		Vector2(400.f, 400.f));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// THE FALSE KING

	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_STAND", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/IDLE/FK_IDLE%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_STAND%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_STAND", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_STAND", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 6;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_JUMP", false, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/JUMPING/FK_JUMPING%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_JUMP%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_JUMP", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_JUMP", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	// JUMP ATTACK
	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_ATTACKC", false, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/JUMPING/JUMPATTACK/FK_ATTACKC%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_ATTACKC%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_ATTACKC", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_ATTACKC", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_JUMPB", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/JUSTJUMPING/FK_JJUMPING%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_JUMPB%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_JUMPB", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_JUMPB", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_LAND", true, .25f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/LAND/FK_LAND%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_LAND%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_LAND", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_LAND", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 7;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_ATTACK", true, 0.7f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/ATTACK/FK_ATTACK%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_ATTACK%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_ATTACK", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_ATTACK", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	// ²á²Î²á²Î
	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_ATTACKB", true, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/ATTACK/FK_ATTACK%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_ATTACKB%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_ATTACKB", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_ATTACKB", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));




	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_BATTACK", true, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/BATTACK/FK_BATTACK%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_BATTACK%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_BATTACK", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_BATTACK", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_BJUMP", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/BJUMP/FK_BJUMP%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_BJUMP%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_BJUMP", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_BJUMP", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 8;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_GETHIT", false, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/GETHIT/FK_GETHIT%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_GETHIT%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_GETHIT", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_GETHIT", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_GETHIT_LAND", false, .4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/GETHIT/LAND/FK_GETHIT_LAND%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_GETHIT_LAND%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_GETHIT_LAND", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_GETHIT_LAND", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 12;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_OPEN", false, .7f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/GETHIT/OPEN/FK_OPEN%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_OPEN%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_OPEN", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_OPEN", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_DAMAGED", true, .2f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/GETHIT/GETDAMAGED/FK_GETDAMAGED%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_DAMAGED%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_DAMAGED", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_DAMAGED", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_GETHIT_IDLE", true, .3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/GETHIT/IDLE/FK_GETHIT_IDLE%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_GETHIT_IDLE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_GETHIT_IDLE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_GETHIT_IDLE", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));



	frameCount = 4;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_GETUP", true, 0.4f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/GETHIT/GETUP/FK_GETUP%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_GETUP%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_GETUP", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_GETUP", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_LAID", true, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/LAID/FK_LAID%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_LAID%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_LAID", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_LAID", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 3;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_DIE", false, .3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/DIE/FK_DIE%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_DIE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_DIE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_DIE", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("FK_DEAD", false, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/DEAD/FK_DEAD%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "FK_DEAD%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("FK_DEAD", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("FK_DEAD", Vector2(0.f, 0.f),
		Vector2(1200.f, 1200.f));









	frameCount = 5;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BF_DIE", false, 1.f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/BABYFACE/DIE/BF_DIE%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "BF_DIE%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BF_DIE", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BF_DIE", Vector2(0.f, 0.f),
		Vector2(400, 400));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BF_DIELAND", false, 0.5f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/BABYFACE/DIE/BF_DIELAND%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "BF_DIELAND%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BF_DIELAND", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BF_DIELAND", Vector2(0.f, 0.f),
		Vector2(400, 400));

	frameCount = 2;
	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("BF_DEAD", false, 0.3f, frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};
		wsprintf(strFileName, TEXT("HOLLOW/Monster/FALSE_KING/BABYFACE/DIE/BF_DEAD%d.png"), i);
		char strKey[256] = {};
		sprintf_s(strKey, "BF_DEAD%d", i);
		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("BF_DEAD", strKey, strFileName);
	}
	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("BF_DEAD", Vector2(0.f, 0.f),
		Vector2(400, 400));
}



