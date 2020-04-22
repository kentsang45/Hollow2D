
// CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include <string>
#include "TCHAR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}



BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, m_strResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strResult = "0";
	m_iScreenResult = 0;
	m_eOperator = OT_END;
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);



	DDX_Control(pDX, IDC_NUM_BUTTON1, m_Button1);
	DDX_Control(pDX, IDC_NUM_BUTTON2, m_Button2);
	DDX_Control(pDX, IDC_NUM_BUTTON3, m_Button3);
	DDX_Control(pDX, IDC_NUM_BUTTON4, m_Button4);
	DDX_Control(pDX, IDC_NUM_BUTTON5, m_Button5);
	DDX_Control(pDX, IDC_NUM_BUTTON6, m_Button6);
	DDX_Control(pDX, IDC_NUM_BUTTON9, m_Button7);
	DDX_Control(pDX, IDC_NUM_BUTTON8, m_Button8);
	DDX_Control(pDX, IDC_NUM_BUTTON7, m_Button9);
	DDX_Control(pDX, IDC_NUM_BUTTON10, m_Button0);


	DDX_Control(pDX, IDC_PLUS_BUTTON, m_ButtonPlus);
	DDX_Control(pDX, IDC_MINUS_BUTTON, m_ButtonMinus);
	DDX_Control(pDX, IDC_MULTI_BUTTON, m_ButtonMultiply);
	DDX_Control(pDX, IDC_DEVIDE_BUTTON, m_ButtonDivide);
	DDX_Control(pDX, IDC_EQUAL_BUTTON, m_ButtonEqual);

	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_ButtonClear);
	DDX_Text(pDX, IDC_NUM_SCREEN, m_strResult);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NUM_BUTTON1, &CCalculatorDlg::OnBnClickedNumButton1)
	ON_BN_CLICKED(IDC_NUM_BUTTON2, &CCalculatorDlg::OnBnClickedNumButton2)
	ON_BN_CLICKED(IDC_NUM_BUTTON3, &CCalculatorDlg::OnBnClickedNumButton3)
	ON_BN_CLICKED(IDC_NUM_BUTTON4, &CCalculatorDlg::OnBnClickedNumButton4)
	ON_BN_CLICKED(IDC_NUM_BUTTON5, &CCalculatorDlg::OnBnClickedNumButton5)
	ON_BN_CLICKED(IDC_NUM_BUTTON6, &CCalculatorDlg::OnBnClickedNumButton6)
	ON_BN_CLICKED(IDC_NUM_BUTTON9, &CCalculatorDlg::OnBnClickedNumButton9)
	ON_BN_CLICKED(IDC_NUM_BUTTON8, &CCalculatorDlg::OnBnClickedNumButton8)
	ON_BN_CLICKED(IDC_NUM_BUTTON7, &CCalculatorDlg::OnBnClickedNumButton7)
	ON_BN_CLICKED(IDC_NUM_BUTTON10, &CCalculatorDlg::OnBnClickedNumButton10)
	ON_BN_CLICKED(IDC_PLUS_BUTTON, &CCalculatorDlg::OnBnClickedPlusButton)
	ON_BN_CLICKED(IDC_MINUS_BUTTON, &CCalculatorDlg::OnBnClickedMinusButton)
	ON_BN_CLICKED(IDC_MULTI_BUTTON, &CCalculatorDlg::OnBnClickedMultiButton)
	ON_BN_CLICKED(IDC_DEVIDE_BUTTON, &CCalculatorDlg::OnBnClickedDevideButton)
	ON_BN_CLICKED(IDC_EQUAL_BUTTON, &CCalculatorDlg::OnBnClickedEqualButton)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalculatorDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::OnBnClickedNumButton1()
{
	// AfxMessageBox(_T("HI"));

	if ("0" == m_strResult)
	{
		m_strResult = "1";
	}
	else
	{
		m_strResult += "1";
	}


	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNumButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ("0" == m_strResult)
	{
		m_strResult = "2";
	}
	else
	{
		m_strResult += "2";
	}

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNumButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ("0" == m_strResult)
	{
		m_strResult = "3";
	}
	else
	{
		m_strResult += "3";
	}

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNumButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ("0" == m_strResult)
	{
		m_strResult = "4";
	}
	else
	{
		m_strResult += "4";
	}

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNumButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ("0" == m_strResult)
	{
		m_strResult = "5";
	}
	else
	{
		m_strResult += "5";
	}

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNumButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ("0" == m_strResult)
	{
		m_strResult = "6";
	}
	else
	{
		m_strResult += "6";
	}

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNumButton9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ("0" == m_strResult)
	{
		m_strResult = "7";
	}
	else
	{
		m_strResult += "7";
	}

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNumButton8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ("0" == m_strResult)
	{
		m_strResult = "8";
	}
	else
	{
		m_strResult += "8";
	}

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNumButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ("0" == m_strResult)
	{
		m_strResult = "9";
	}
	else
	{
		m_strResult += "9";
	}

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedNumButton10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ("0" == m_strResult)
	{
		m_strResult = "0";
	}
	else
	{
		m_strResult += "0";
	}

	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedPlusButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_iScreenResult = _ttoi(m_strResult);

	m_strResult = "0";

	m_eOperator = OT_PLUS;
}



void CCalculatorDlg::OnBnClickedMinusButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_iScreenResult = _ttoi(m_strResult);

	m_strResult = "0";

	m_eOperator = OT_MINUS;
}


void CCalculatorDlg::OnBnClickedMultiButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_iScreenResult = _ttoi(m_strResult);

	m_strResult = "0";

	m_eOperator = OT_MULTIPLY;
}


void CCalculatorDlg::OnBnClickedDevideButton()
{

	/*m_iScreenResult /= _ttoi(m_strResult);

	m_strResult.Format(_T("%d"), m_iScreenResult);

	m_eOperator = OT_DIVIDE;*/

	AfxMessageBox(_T("NOT SUPPORTED"));
}


void CCalculatorDlg::OnBnClickedEqualButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	switch (m_eOperator)
	{
	case OT_PLUS:
		m_iScreenResult += _ttoi(m_strResult);
		break;
	case OT_MINUS:
		m_iScreenResult -= _ttoi(m_strResult);
		break;
	case OT_MULTIPLY:
		m_iScreenResult *= _ttoi(m_strResult);
		break;
	case OT_DIVIDE:
	// 	m_iScreenResult /= _ttoi(m_strResult);
		break;
	default:
		// assert(false);
		m_iScreenResult = 0;
		m_strResult = "0";
		m_eOperator = OT_END;
		break;
	}

	m_strResult.Format(_T("%d"), m_iScreenResult);


	UpdateData(FALSE);
}


void CCalculatorDlg::OnBnClickedButtonClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_iScreenResult = 0;
	m_strResult = "0";
	m_eOperator = OT_END;
}

