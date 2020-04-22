
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Editor2D.h"

#include "MainFrm.h"

#include "TileMapEditorDialog.h"
#include "MaterialDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_TILEMAPEDITOR, &CMainFrame::OnTilemapEditor)
	ON_COMMAND(ID_MATERIAL_CREATE, &CMainFrame::OnMaterialCreate) 

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
	m_pTileMapEditor = nullptr;
	m_pMaterialEditor = nullptr;
}

CMainFrame::~CMainFrame()
{
	if (m_pTileMapEditor)
	{
		delete	m_pTileMapEditor;
		m_pTileMapEditor = nullptr;
	}

	if (m_pMaterialEditor)
	{
		delete	m_pMaterialEditor;
		m_pMaterialEditor = nullptr;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.cx = 1600;
	cs.cy = 800;
	cs.x = 0;
	cs.y = 100;

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



void CMainFrame::OnTilemapEditor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!m_pTileMapEditor)
	{
		m_pTileMapEditor = new CTileMapEditorDialog;

		m_pTileMapEditor->Create(IDD_TILEMAP_EDITOR_DIALOG);
	}

	m_pTileMapEditor->ShowWindow(SW_SHOW);
}

void CMainFrame::OnMaterialCreate()
{
	if (!m_pMaterialEditor)
	{
		m_pMaterialEditor = new CMaterialDialog;

		m_pMaterialEditor->Create(IDD_MATERIAL_DIALOG);
	}

	m_pMaterialEditor->ShowWindow(SW_SHOW);
}
