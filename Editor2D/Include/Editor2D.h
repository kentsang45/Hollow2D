
// Editor2D.h : main header file for the Editor2D application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CEditor2DApp:
// See Editor2D.cpp for the implementation of this class
//

class CEditor2DApp : public CWinApp
{
public:
	CEditor2DApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CEditor2DApp theApp;
