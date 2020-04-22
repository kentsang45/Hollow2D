
// Editor2DView.cpp : implementation of the CEditor2DView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Editor2D.h"
#endif



#include "Editor2DDoc.h"
#include "Editor2DView.h"




#include "Editor2DDoc.h"
#include "Editor2DView.h"
#include "Engine.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "GameMode/EditGameMode.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////

// CEditor2DView

IMPLEMENT_DYNCREATE(CEditor2DView, CView)

BEGIN_MESSAGE_MAP(CEditor2DView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CEditor2DView construction/destruction

CEditor2DView::CEditor2DView() noexcept
{
	// TODO: add construction code here

}

CEditor2DView::~CEditor2DView()
{
}

BOOL CEditor2DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEditor2DView drawing

void CEditor2DView::OnDraw(CDC* /*pDC*/)
{
	CEditor2DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CEditor2DView printing

BOOL CEditor2DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEditor2DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEditor2DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEditor2DView diagnostics

#ifdef _DEBUG
void CEditor2DView::AssertValid() const
{
	CView::AssertValid();
}

void CEditor2DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditor2DDoc* CEditor2DView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditor2DDoc)));
	return (CEditor2DDoc*)m_pDocument;
}
#endif //_DEBUG


// CEditor2DView message handlers








void CEditor2DView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	GET_SINGLE(CEngine)->Init(AfxGetInstanceHandle(), m_hWnd, 1920, 1080);

	CScene*	pScene = GET_SINGLE(CSceneManager)->GetScene();

	pScene->SetGameMode<CEditGameMode>();

	//pScene->Begin();
}


void CEditor2DView::OnDestroy()
{
	CView::OnDestroy();

	DESTROY_SINGLE(CEngine);
}
