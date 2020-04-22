#include "StartGameMode.h"
#include "../Object/StartButton.h"
#include "Scene/Scene.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "Resource/Animation2DSequence.h"


CStartGameMode::CStartGameMode()
{
}

CStartGameMode::~CStartGameMode()
{
}

bool CStartGameMode::Init()
{
	CGameMode::Init();

	CStartButton*	pStartButton = m_pScene->SpawnObject<CStartButton>();

	SAFE_RELEASE(pStartButton);

	GET_SINGLE(CResourceManager)->CreateAnimation2DSequence("MouseDefault", true, 1.f, 13);

	for (int i = 0; i <= 12; ++i)
	{
		TCHAR	strFileName[MAX_PATH] = {};

		wsprintf(strFileName, TEXT("Mouse/Default/%d.png"), i);

		char	strKey[256] = {};
		sprintf_s(strKey, "MouseDefault%d", i);

		GET_SINGLE(CResourceManager)->AddAnimation2DSequenceTexture("MouseDefault", strKey, strFileName);
	}

	GET_SINGLE(CResourceManager)->SetAnimation2DSequenceFrameInfoAll("MouseDefault", Vector2(0.f, 0.f),
		Vector2(32.f, 31.f));

	GET_SINGLE(CInput)->CreateAnim2D();
	GET_SINGLE(CInput)->AddAnim2DSequence("MouseDefault");
	GET_SINGLE(CInput)->AlphaBlendEnable();

	return true;
}
