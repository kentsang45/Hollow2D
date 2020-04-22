// TileMapEditorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GameEditorTest.h"
#include "TileMapEditorDlg.h"
#include "afxdialogex.h"
#include "Object/EditMapObject.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/ResourceManager.h"
#include "Resource/Texture.h"
#include "Resource/Material.h"
#include "Component/TileMap.h"
#include "GameMode\EditGameMode.h"


// CTileMapEditorDlg 대화 상자

IMPLEMENT_DYNAMIC(CTileMapEditorDlg, CDialogEx)

CTileMapEditorDlg::CTileMapEditorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TILEMAP_EDITOR, pParent)
	, m_iTileCountX(0)
	, m_iTileCountY(0)
	, m_iTileSizeX(0)
	, m_iTileSizeY(0)
	, m_strImageName(_T(""))
	, m_iTileImgSizeX(0)
	, m_iTileImgSizeY(0)
	, m_pTileMapObj(nullptr)
	, m_iTileposX(0)
	, m_iTileposY(0)
{

}

CTileMapEditorDlg::~CTileMapEditorDlg()
{
	SAFE_RELEASE(m_pTileMapObj);
}

void CTileMapEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TILECOUNTX, m_iTileCountX);
	DDX_Text(pDX, IDC_EDIT_TILECOUNTY, m_iTileCountY);
	DDX_Text(pDX, IDC_EDIT_TILESIZEX, m_iTileSizeX);
	DDX_Text(pDX, IDC_EDIT_TILESIZEY, m_iTileSizeY);
	DDX_Text(pDX, IDC_EDIT_TILEIMAGENAME, m_strImageName);
	DDX_Text(pDX, IDC_EDIT_TILEIMAGESIZEX, m_iTileImgSizeX);
	DDX_Text(pDX, IDC_EDIT_TILEIMAGESIZEY, m_iTileImgSizeY);
	DDX_Control(pDX, IDC_COMBO_TILETYPE, m_TileTypeCombo);
	DDX_Control(pDX, IDC_COMBO_TILEOPTION, m_TileOptionCombo);
	DDX_Control(pDX, IDC_LIST_TILEMAP_MATERIAL, m_MaterialList);
	DDX_Text(pDX, IDC_EDIT_TILEPOSX, m_iTileposX);
	DDX_Text(pDX, IDC_EDIT_TILEPOSY, m_iTileposY);
	DDX_Control(pDX, IDC_COMBO_UPDATE_TYPE, m_UpdateTypeCombo);
	DDX_Text(pDX, IDC_EDIT_TILE_FRAME_STARTX, m_vFrameStart.x);
	DDX_Text(pDX, IDC_EDIT_TILE_FRAME_STARTY, m_vFrameStart.y);
	DDX_Text(pDX, IDC_EDIT_TILE_FRAME_ENDX, m_vFrameEnd.x);
	DDX_Text(pDX, IDC_EDIT_TILE_FRAME_ENDY, m_vFrameEnd.y);
	DDX_Text(pDX, IDC_EDIT_TILE_FRAME_SIZEX, m_vFrameSize.x);
	DDX_Text(pDX, IDC_EDIT_TILE_FRAME_SIZEY, m_vFrameSize.y);
}


BEGIN_MESSAGE_MAP(CTileMapEditorDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_TILECOUNTX, &CTileMapEditorDlg::OnEnChangeEditTilecountx)
	ON_EN_CHANGE(IDC_EDIT_TILECOUNTY, &CTileMapEditorDlg::OnEnChangeEditTilecounty)
	ON_EN_CHANGE(IDC_EDIT_TILESIZEX, &CTileMapEditorDlg::OnEnChangeEditTilesizex)
	ON_EN_CHANGE(IDC_EDIT_TILESIZEY, &CTileMapEditorDlg::OnEnChangeEditTilesizey)
	ON_EN_CHANGE(IDC_EDIT_TILEIMAGENAME, &CTileMapEditorDlg::OnEnChangeEditTileimagename)
	ON_EN_CHANGE(IDC_EDIT_TILEIMAGESIZEX, &CTileMapEditorDlg::OnEnChangeEditTileimagesizex)
	ON_EN_CHANGE(IDC_EDIT_TILEIMAGESIZEY, &CTileMapEditorDlg::OnEnChangeEditTileimagesizey)
	ON_CBN_SELCHANGE(IDC_COMBO_TILETYPE, &CTileMapEditorDlg::OnCbnSelchangeComboTiletype)
	ON_CBN_SELCHANGE(IDC_COMBO_TILEOPTION, &CTileMapEditorDlg::OnCbnSelchangeComboTileoption)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_TILEMAP, &CTileMapEditorDlg::OnBnClickedButtonCreateTilemap)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_TILEMAP_IMAGE, &CTileMapEditorDlg::OnBnClickedButtonLoadTilemapImage)
	ON_LBN_SELCHANGE(IDC_LIST_TILEMAP_MATERIAL, &CTileMapEditorDlg::OnLbnSelchangeListTilemapMaterial)
	ON_MESSAGE(UM_MATERIAL_UPDATE, &CTileMapEditorDlg::OnMaterialUpdate)
	ON_BN_CLICKED(IDC_BUTTON_TILEMAP_SET_MATERIAL, &CTileMapEditorDlg::OnBnClickedButtonTilemapSetMaterial)
	ON_CBN_SELCHANGE(IDC_COMBO_UPDATE_TYPE, &CTileMapEditorDlg::OnCbnSelchangeComboUpdateType)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_TILEMAP, &CTileMapEditorDlg::OnBnClickedButtonSaveTilemap)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_TILEMAP, &CTileMapEditorDlg::OnBnClickedButtonLoadTilemap)
END_MESSAGE_MAP()


// CTileMapEditorDlg 메시지 처리기


void CTileMapEditorDlg::OnEnChangeEditTilecountx()
{
}


void CTileMapEditorDlg::OnEnChangeEditTilecounty()
{
}


void CTileMapEditorDlg::OnEnChangeEditTilesizex()
{
}


void CTileMapEditorDlg::OnEnChangeEditTilesizey()
{
}


void CTileMapEditorDlg::OnEnChangeEditTileimagename()
{
}


void CTileMapEditorDlg::OnEnChangeEditTileimagesizex()
{
}


void CTileMapEditorDlg::OnEnChangeEditTileimagesizey()
{
}


void CTileMapEditorDlg::OnCbnSelchangeComboTiletype()
{
}


void CTileMapEditorDlg::OnCbnSelchangeComboTileoption()
{
}

// 타일맵 생성 버튼
void CTileMapEditorDlg::OnBnClickedButtonCreateTilemap()
{
	// 컨트롤에 입력된 값들을 얻어온다.
	UpdateData(TRUE);

	// GetcurSel : 현재 선택된 인덱스를 얻어온다.
	int	iTileType = m_TileTypeCombo.GetCurSel();

	if (iTileType == -1)
	{
		AfxMessageBox(TEXT("타일 타입을 선택하세요"));
		return;
	}

	SAFE_RELEASE(m_pTileMapObj);

	CScene*	pScene = GET_SINGLE(CSceneManager)->GetScene();

	m_pTileMapObj = pScene->SpawnObject<CEditMapObject>();

	string	strKey = CT2CA(m_strImageName);

	m_pTileMapObj->CreateTileMap((TILE_TYPE)iTileType, m_iTileCountX, m_iTileCountY, m_iTileSizeX, m_iTileSizeY,
		strKey, m_strTexturePath);
}

// 타일맵에서 사용할 이미지를 불러온다.
void CTileMapEditorDlg::OnBnClickedButtonLoadTilemapImage()
{
	TCHAR	strFilter[]	= TEXT("Texture(*.BMP, *.PNG, *.JPG) | *.bmp;*.png;*.jpg | All Files(*.*)|*.*||");

	// 파일 다이얼로그를 이용하여 이미지를 불러온다.
	CFileDialog	dlg(TRUE, TEXT(".png"), TEXT("Tile"), OFN_HIDEREADONLY, strFilter);

	if (dlg.DoModal() == IDOK)
	{
		m_strTexturePath = dlg.GetPathName();
		
		m_strImageName = dlg.GetFileTitle();

		string	strKey = CT2CA(m_strImageName);

		if(GET_SINGLE(CResourceManager)->LoadTextureFullPath(strKey, m_strTexturePath.GetString()))
		{
			CTexture*	pTex = GET_SINGLE(CResourceManager)->FindTexture(strKey);

			m_iTileImgSizeX	= pTex->GetWidth();
			m_iTileImgSizeY = pTex->GetHeight();

			SAFE_RELEASE(pTex);

			UpdateData(FALSE);
		}
	}
}


void CTileMapEditorDlg::OnLbnSelchangeListTilemapMaterial()
{
}


BOOL CTileMapEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	OnMaterialUpdate(0, 0);

	m_iTileCountX = 100;
	m_iTileCountY = 100;
	m_iTileSizeX = 100;
	m_iTileSizeY = 100;
	m_iTileposX = 0;
	m_iTileposY = 0;

	m_vFrameStart.x	= 0.f;
	m_vFrameStart.y	= 0.f;
	m_vFrameEnd.x = 100.f;
	m_vFrameEnd.y = 100.f;
	m_vFrameSize.x = 100.f;
	m_vFrameSize.y = 100.f;
	

	UpdateData(FALSE);

	m_TileTypeCombo.SetCurSel(1);
	m_TileOptionCombo.SetCurSel(0);

	m_UpdateTypeCombo.AddString(TEXT("Frame"));
	m_UpdateTypeCombo.AddString(TEXT("Option"));	

	m_UpdateTypeCombo.SetCurSel(0);

	return FALSE;
}

LRESULT CTileMapEditorDlg::OnMaterialUpdate(WPARAM wParam, LPARAM lParam)
{
	GET_SINGLE(CResourceManager)->ClearMaterialIterator();

	CMaterial*	pMaterial = GET_SINGLE(CResourceManager)->GetCurrentMaterial();

	m_MaterialList.ResetContent();

	while (pMaterial)
	{
		CString	strName = CA2CT(pMaterial->GetName().c_str());
		m_MaterialList.AddString(strName);

		GET_SINGLE(CResourceManager)->NextMaterial();

		pMaterial = GET_SINGLE(CResourceManager)->GetCurrentMaterial();
	}

	return 0;
}


void CTileMapEditorDlg::OnBnClickedButtonTilemapSetMaterial()
{
	if (!m_pTileMapObj)
		return;

	int	iMaterial = m_MaterialList.GetCurSel();

	if(iMaterial == -1)
		return;

	CString	strMaterial;

	m_MaterialList.GetText(iMaterial, strMaterial);

	string	strMaterialKey = CT2CA(strMaterial);

	CTileMap*	pTileMap = m_pTileMapObj->FindSceneComponent<CTileMap>();

	if (pTileMap)
	{
		pTileMap->SetTileMaterial(strMaterialKey);
		SAFE_RELEASE(pTileMap);
	}
}


void CTileMapEditorDlg::OnCbnSelchangeComboUpdateType()
{
	CScene*	pScene = GET_SINGLE(CSceneManager)->GetScene();

	CEditGameMode*	pGameMode = (CEditGameMode*)pScene->GetGameMode();

	if(pGameMode)
	{
		int	iSel = m_UpdateTypeCombo.GetCurSel();

		pGameMode->SetUpdateType((TILE_UPDATE_TYPE)iSel);
	}
}

void CTileMapEditorDlg::UpdateFrameData()
{
	UpdateData(TRUE);
}


void CTileMapEditorDlg::OnBnClickedButtonSaveTilemap()
{
	if (!m_pTileMapObj)
		return;

	TCHAR	strFilter[] = TEXT("TileMap(*.TMP)|*.tmp|All Files(*.*)|*.*||");

	// 파일 다이얼로그를 이용하여 이미지를 불러온다.
	CFileDialog	dlg(FALSE, TEXT(""), TEXT("Tile"), OFN_OVERWRITEPROMPT, strFilter);

	if (dlg.DoModal() == IDOK)
	{
		CString	strPath = dlg.GetPathName();

		string	strFullPath = CT2CA(strPath);

		m_pTileMapObj->Save(strFullPath.c_str());
	}
}

// 타일맵 불러오기
void CTileMapEditorDlg::OnBnClickedButtonLoadTilemap()
{
	int	iMaterial = m_MaterialList.GetCurSel();

	if (iMaterial == -1)
		return;

	CString	strMaterial;

	m_MaterialList.GetText(iMaterial, strMaterial);

	string	strMaterialKey = CT2CA(strMaterial);

	TCHAR	strFilter[] = TEXT("TileMap(*.tmp)|*.tmp|All Files(*.*)|*.*||");

	// 파일 다이얼로그를 이용하여 이미지를 불러온다.
	CFileDialog	dlg(TRUE, TEXT(""), TEXT("Tile"), OFN_HIDEREADONLY, strFilter);

	if (dlg.DoModal() == IDOK)
	{
		if (!m_pTileMapObj)
		{
			CScene*	pScene = GET_SINGLE(CSceneManager)->GetScene();

			m_pTileMapObj = pScene->SpawnObject<CEditMapObject>();
		}

		CString	strPath = dlg.GetPathName();

		string	strFullPath = CT2CA(strPath);

		m_pTileMapObj->Load(strFullPath.c_str(), strMaterialKey.c_str());
	}
}

int CTileMapEditorDlg::GetTileOption() const
{
	return m_TileOptionCombo.GetCurSel();
}
