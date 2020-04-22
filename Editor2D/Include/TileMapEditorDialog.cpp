// TileMapEditorDialog.cpp: 구현 파일
//

#include "stdafx.h"
#include "Editor2D.h"
#include "TileMapEditorDialog.h"
#include "afxdialogex.h"

#include "Object/EditMapObject.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Resource/ResourceManager.h"
#include "Resource/Texture.h"
#include "Resource/Material.h"
#include "Component/TileMap.h"


// CTileMapEditorDialog 대화 상자

IMPLEMENT_DYNAMIC(CTileMapEditorDialog, CDialogEx)

CTileMapEditorDialog::CTileMapEditorDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TILEMAP_EDITOR_DIALOG, pParent)
	, m_iTileCountX(0)
	, m_iTileCountY(0)
	, m_iTileSizeX(0)
	, m_iTileSizeY(0)
	, m_strImageName(_T(""))
	, m_iTileImageSizeX(0)
	, m_iTileImageSizeY(0)
	, m_pTileMapObj(nullptr)
{

}

CTileMapEditorDialog::~CTileMapEditorDialog()
{
	SAFE_RELEASE(m_pTileMapObj);
}

void CTileMapEditorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TILECOUNTX, m_iTileCountX);
	DDX_Text(pDX, IDC_EDIT_TILECOUNTY, m_iTileCountY);
	DDX_Text(pDX, IDC_EDIT_TILESIZEX, m_iTileSizeX);
	DDX_Text(pDX, IDC_EDIT_TILESIZEY, m_iTileSizeY);
	DDX_Text(pDX, IDC_EDIT_TILEIMAGE_NAME, m_strImageName);
	DDX_Text(pDX, IDC_EDIT_TILEIMAGESIZEX, m_iTileImageSizeX);
	DDX_Text(pDX, IDC_EDIT_TILEIMAGESIZEY, m_iTileImageSizeY);
	DDX_Control(pDX, IDC_COMBO_TILETYPE, m_TileTypeCombo);
	DDX_Control(pDX, IDC_COMBO_TILEOPTION, m_TileOptionCombo);
	DDX_Control(pDX, IDC_LIST_TILEMAP_MATERIAL, m_MaterialList);
}




BEGIN_MESSAGE_MAP(CTileMapEditorDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_TILECOUNTX, &CTileMapEditorDialog::OnEnChangeEditTilecountx)
	ON_EN_CHANGE(IDC_EDIT_TILECOUNTY, &CTileMapEditorDialog::OnEnChangeEditTilecounty)
	ON_EN_CHANGE(IDC_EDIT_TILESIZEX, &CTileMapEditorDialog::OnEnChangeEditTilesizex)
	ON_EN_CHANGE(IDC_EDIT_TILESIZEY, &CTileMapEditorDialog::OnEnChangeEditTilesizey)
	ON_EN_CHANGE(IDC_EDIT_TILEIMAGE_NAME, &CTileMapEditorDialog::OnEnChangeImageName)
	ON_EN_CHANGE(IDC_EDIT_TILEIMAGESIZEX, &CTileMapEditorDialog::OnEnChangeEditImagesizex)
	ON_EN_CHANGE(IDC_EDIT_TILEIMAGESIZEY, &CTileMapEditorDialog::OnEnChangeEditImagesizey)
	ON_CBN_SELCHANGE(IDC_COMBO_TILETYPE, &CTileMapEditorDialog::OnCbnSelchangeComboTiletype)
	ON_CBN_SELCHANGE(IDC_COMBO_TILEOPTION, &CTileMapEditorDialog::OnCbnSelchangeComboTileoption)
	ON_BN_CLICKED(IDC_BUTTON_TILEMAP_CREATE, &CTileMapEditorDialog::OnBnClickedButtonCreateTilemap)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_TILEMAP_IMAGE, &CTileMapEditorDialog::OnBnClickedButtonLoadTilemapImage)

	ON_LBN_SELCHANGE(IDC_LIST_TILEMAP_MATERIAL, &CTileMapEditorDialog::OnLbnSelchangeListTilemapMaterial)
	ON_MESSAGE(UM_MATERIAL_UPDATE, &CTileMapEditorDialog::OnMaterialUpdate)
	ON_BN_CLICKED(IDC_BUTTON_TILEMAP_SET_MATERIAL, &CTileMapEditorDialog::OnBnClickedButtonTilemapSetMaterial)
END_MESSAGE_MAP()


// CTileMapEditorDialog 메시지 처리기


void CTileMapEditorDialog::OnEnChangeEditTilecountx()
{
}

void CTileMapEditorDialog::OnEnChangeEditTilecounty()
{
}

void CTileMapEditorDialog::OnEnChangeEditTilesizex()
{
}

void CTileMapEditorDialog::OnEnChangeEditTilesizey()
{
}

void CTileMapEditorDialog::OnEnChangeImageName()
{
}

void CTileMapEditorDialog::OnEnChangeEditImagesizex()
{
}

void CTileMapEditorDialog::OnEnChangeEditImagesizey()
{
}

void CTileMapEditorDialog::OnCbnSelchangeComboTiletype()
{
}

void CTileMapEditorDialog::OnCbnSelchangeComboTileoption()
{
}



// 타일맵 생성하기
void CTileMapEditorDialog::OnBnClickedButtonCreateTilemap()
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


// 타일맵에서 사용할 이미지 불러오기
void CTileMapEditorDialog::OnBnClickedButtonLoadTilemapImage()
{
	TCHAR	strFilter[] = TEXT("Texture(*.BMP, *.PNG, *.JPG) | *.bmp;*.png;*.jpg | All Files(*.*)|*.*||");

	// 파일 다이얼로그를 이용하여 이미지를 불러온다.
	CFileDialog	dlg(TRUE, TEXT(".png"), TEXT("Tile"), OFN_HIDEREADONLY, strFilter);

	if (dlg.DoModal() == IDOK)
	{
		m_strTexturePath = dlg.GetPathName();

		m_strImageName = dlg.GetFileTitle();

		string	strKey = CT2CA(m_strImageName);

		if (GET_SINGLE(CResourceManager)->LoadTextureFullPath(strKey, m_strTexturePath.GetString()))
		{
			CTexture*	pTex = GET_SINGLE(CResourceManager)->FindTexture(strKey);

			m_iTileImageSizeX = pTex->GetWidth();
			m_iTileImageSizeY = pTex->GetHeight();

			SAFE_RELEASE(pTex);

			UpdateData(FALSE);
		}
	}
}

BOOL CTileMapEditorDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	OnMaterialUpdate(0, 0);

	return TRUE;
}

void CTileMapEditorDialog::OnLbnSelchangeListTilemapMaterial()
{
}

LRESULT CTileMapEditorDialog::OnMaterialUpdate(WPARAM wParam, LPARAM lParam)
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

void CTileMapEditorDialog::OnBnClickedButtonTilemapSetMaterial()
{
	if (!m_pTileMapObj)
		return;

	int	iMaterial = m_MaterialList.GetCurSel();

	if (iMaterial == -1)
		return;

	CString	strMaterial;

	m_MaterialList.GetText(iMaterial, strMaterial);

	string	strMaterialKey = CT2CA(strMaterial);

	CTileMap*	pTileMap = m_pTileMapObj->FindSceneComponent<CTileMap>();

	if (pTileMap)
	{
		pTileMap->SetMaterial(strMaterialKey);
		SAFE_RELEASE(pTileMap);
	}
}
