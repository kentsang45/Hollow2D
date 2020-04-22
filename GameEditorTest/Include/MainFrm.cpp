
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "GameEditorTest.h"

#include "MainFrm.h"
#include "TileMapEditorDlg.h"
#include "MaterialDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_TILEMAP_EDITOR, &CMainFrame::OnTilemapEditor)
	ON_COMMAND(ID_MATERIAL_CREATE, &CMainFrame::OnMaterialCreate)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	m_pTileMapEditor	= nullptr;
	m_pMaterialEditor	= nullptr;
}

CMainFrame::~CMainFrame()
{
	if (m_pTileMapEditor)
	{
		delete	m_pTileMapEditor;
		m_pTileMapEditor	= nullptr;
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
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.cx = 1600;
	cs.cy = 800;
	cs.x = 1921;
	cs.y = 100;

	return TRUE;
}

// CMainFrame 진단

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


// CMainFrame 메시지 처리기


// 타일맵 에디터를 열어준다.
void CMainFrame::OnTilemapEditor()
{
	if (!m_pTileMapEditor)
	{
		m_pTileMapEditor	= new CTileMapEditorDlg;

		m_pTileMapEditor->Create(IDD_DIALOG_TILEMAP_EDITOR);
	}

	m_pTileMapEditor->ShowWindow(SW_SHOW);
}


void CMainFrame::OnMaterialCreate()
{
	if (!m_pMaterialEditor)
	{
		m_pMaterialEditor = new CMaterialDlg;

		m_pMaterialEditor->Create(IDD_DIALOG_MATERIAL);
	}

	m_pMaterialEditor->ShowWindow(SW_SHOW);
}
