#pragma once


// CTileMapEditorDialog 대화 상자

class CTileMapEditorDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTileMapEditorDialog)

public:
	CTileMapEditorDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTileMapEditorDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILEMAP_EDITOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditTilecountx();
	afx_msg void OnEnChangeEditTilecounty();
	afx_msg void OnEnChangeEditTilesizex();
	afx_msg void OnEnChangeEditTilesizey();
	afx_msg void OnEnChangeImageName();
	afx_msg void	OnEnChangeEditImagesizex();
	afx_msg void	OnEnChangeEditImagesizey();
	afx_msg void OnCbnSelchangeComboTiletype();
	afx_msg void OnCbnSelchangeComboTileoption();
	afx_msg void OnBnClickedButtonCreateTilemap();
	afx_msg void OnBnClickedButtonLoadTilemapImage();
	int m_iTileCountX;
	int m_iTileCountY;
	int m_iTileSizeX;
	int m_iTileSizeY;
	CString m_strImageName;
	int m_iTileImageSizeX;
	int m_iTileImageSizeY;
	CComboBox m_TileTypeCombo;
	CComboBox m_TileOptionCombo;

	CListBox m_MaterialList;

	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeListTilemapMaterial();
	afx_msg LRESULT OnMaterialUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonTilemapSetMaterial();

private:
	CString m_strTexturePath;
	class CEditMapObject* m_pTileMapObj;
};
