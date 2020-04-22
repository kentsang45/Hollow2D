
// GameEditorTestView.cpp: CGameEditorTestView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GameEditorTest.h"
#endif

#include "GameEditorTestDoc.h"
#include "GameEditorTestView.h"
#include "Engine.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "GameMode/EditGameMode.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameEditorTestView

IMPLEMENT_DYNCREATE(CGameEditorTestView, CView)

BEGIN_MESSAGE_MAP(CGameEditorTestView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CGameEditorTestView 생성/소멸

CGameEditorTestView::CGameEditorTestView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGameEditorTestView::~CGameEditorTestView()
{
}

BOOL CGameEditorTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGameEditorTestView 그리기

void CGameEditorTestView::OnDraw(CDC* /*pDC*/)
{
	CGameEditorTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGameEditorTestView 인쇄

BOOL CGameEditorTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGameEditorTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGameEditorTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CGameEditorTestView 진단

#ifdef _DEBUG
void CGameEditorTestView::AssertValid() const
{
	CView::AssertValid();
}

void CGameEditorTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameEditorTestDoc* CGameEditorTestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameEditorTestDoc)));
	return (CGameEditorTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameEditorTestView 메시지 처리기


void CGameEditorTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	GET_SINGLE(CEngine)->Init(AfxGetInstanceHandle(), m_hWnd, 1920, 1080);

	CScene* pScene = GET_SINGLE(CSceneManager)->GetScene();

	CEditGameMode* pGameMode = pScene->SetGameMode<CEditGameMode>();

	pGameMode->SetMainFrame((CMainFrame*)AfxGetMainWnd());

	//pScene->Begin();
}


void CGameEditorTestView::OnDestroy()
{
	CView::OnDestroy();

	DESTROY_SINGLE(CEngine);
}
