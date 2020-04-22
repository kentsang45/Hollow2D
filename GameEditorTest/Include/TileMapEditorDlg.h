#pragma once
#include "afxwin.h"


// CTileMapEditorDlg 대화 상자
#include "GameEngine.h"

class CTileMapEditorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTileMapEditorDlg)

public:
	CTileMapEditorDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTileMapEditorDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TILEMAP_EDITOR };
#endif

private:
	CString		m_strTexturePath;
	class CEditMapObject*	m_pTileMapObj;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_iTileCountX;
	afx_msg void OnEnChangeEditTilecountx();
	int m_iTileCountY;
	afx_msg void OnEnChangeEditTilecounty();
	int m_iTileSizeX;
	afx_msg void OnEnChangeEditTilesizex();
	int m_iTileSizeY;
	afx_msg void OnEnChangeEditTilesizey();
	CString m_strImageName;
	afx_msg void OnEnChangeEditTileimagename();
	int m_iTileImgSizeX;
	afx_msg void OnEnChangeEditTileimagesizex();
	int m_iTileImgSizeY;
	afx_msg void OnEnChangeEditTileimagesizey();
	CComboBox m_TileTypeCombo;
	afx_msg void OnCbnSelchangeComboTiletype();
	CComboBox m_TileOptionCombo;
	afx_msg void OnCbnSelchangeComboTileoption();
	afx_msg void OnBnClickedButtonCreateTilemap();
	afx_msg void OnBnClickedButtonLoadTilemapImage();
	CListBox m_MaterialList;
	afx_msg void OnLbnSelchangeListTilemapMaterial();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnMaterialUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonTilemapSetMaterial();
	int m_iTileposX;
	int m_iTileposY;
	CComboBox m_UpdateTypeCombo;
	Vector2 m_vFrameStart;
	Vector2 m_vFrameEnd;
	Vector2 m_vFrameSize;
	afx_msg void OnCbnSelchangeComboUpdateType();
	void UpdateFrameData();
	afx_msg void OnBnClickedButtonSaveTilemap();
	afx_msg void OnBnClickedButtonLoadTilemap();

	int GetTileOption()	const;
};
