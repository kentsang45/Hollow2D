#pragma once

#include "GameEngine.h"

class ENGINE_DLL CEngine
{
private:
	static bool	m_bLoop;

private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	Resolution	m_tRS;
	class CTimer*	m_pTimer;

	bool m_bEditorBegin;

public:
	bool IsEditorBegin()	const
	{
		return m_bEditorBegin;
	}

	void EditorBegin()
	{
		m_bEditorBegin = true;
	}

	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}

	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	Resolution GetResolution()	const
	{
		return m_tRS;
	}

public:
	bool Init(const TCHAR* pClass, const TCHAR* pTitle,
		HINSTANCE hInst, int iIconID, int iSmallIconID,
		int iWidth, int iHeight, bool bWindowMode = true);
	bool Init(HINSTANCE hInst, HWND hWnd, 
		int iWidth, int iHeight, bool bWindowMode = true);
	int Run();
	void Logic();

private:
	int Update(float fTime);
	int PostUpdate(float fTime);
	void Render(float fTime);

private:
	ATOM Register(const TCHAR* pClass, int iIconID,
		int iSmallIconID);
	BOOL Create(const TCHAR* pClass,
		const TCHAR* pTitle);

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CEngine)
};

