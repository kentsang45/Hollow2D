
#include "resource.h"
#include "Engine.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "GameMode/MainGameMode.h"
#include "GameMode/StartGameMode.h"

#include "HK/HKMode.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	if (!GET_SINGLE(CEngine)->Init(TEXT("Client2D"), TEXT("Client2D"),
		hInstance, IDI_ICON1, IDI_ICON1, 1920, 1080))
	{
		DESTROY_SINGLE(CEngine);
		return 0;
	}

	CScene*	pScene = GET_SINGLE(CSceneManager)->GetScene();

	// pScene->SetGameMode<CMainGameMode>();
	// pScene->SetGameMode<CStartGameMode>();

	pScene->SetGameMode<HKMode>();

	pScene->Begin();



	int iRet = GET_SINGLE(CEngine)->Run();

	DESTROY_SINGLE(CEngine);

	return iRet;
}
