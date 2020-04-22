
// CalculatorDlg.h : header file
//

#pragma once





enum OPERATOR_TYPE
{
	OT_PLUS,
	OT_MINUS,
	OT_MULTIPLY,
	OT_DIVIDE,
	OT_END
};






// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	OPERATOR_TYPE m_eOperator;

	int m_iScreenResult;
	CButton m_Button1;
	CButton m_Button2;
	CButton m_Button3;
	CButton m_Button4;
	CButton m_Button5;
	CButton m_Button6;
	CButton m_Button7;
	CButton m_Button8;
	CButton m_Button9;
	CButton m_Button0;

	CButton m_ButtonPlus;
	CButton m_ButtonMinus;
	CButton m_ButtonMultiply;
	CButton m_ButtonDivide;
	CButton m_ButtonEqual;

	CButton m_ButtonClear;
	afx_msg void OnBnClickedNumButton1();
	afx_msg void OnBnClickedNumButton2();
	afx_msg void OnBnClickedNumButton3();
	afx_msg void OnBnClickedNumButton4();
	afx_msg void OnBnClickedNumButton5();
	afx_msg void OnBnClickedNumButton6();
	afx_msg void OnBnClickedNumButton9();
	afx_msg void OnBnClickedNumButton8();
	afx_msg void OnBnClickedNumButton7();
	afx_msg void OnBnClickedNumButton10();
	afx_msg void OnBnClickedPlusButton();
	afx_msg void OnBnClickedMinusButton();
	afx_msg void OnBnClickedMultiButton();
	afx_msg void OnBnClickedDevideButton();
	afx_msg void OnBnClickedEqualButton();
	afx_msg void OnBnClickedButtonClear();
	CString m_strResult;
};
