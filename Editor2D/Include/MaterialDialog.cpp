// MaterialDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Editor2D.h"

#include "MainFrm.h"
#include "TileMapEditorDialog.h"

#include "MaterialDialog.h"
#include "afxdialogex.h"
#include "Resource/ResourceManager.h"
#include "Resource/Material.h"

// CMaterialDialog 대화 상자

IMPLEMENT_DYNAMIC(CMaterialDialog, CDialogEx)

CMaterialDialog::CMaterialDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MATERIAL_DIALOG, pParent)
	, m_bIsInstancing(FALSE)
	, m_strMaterialName(_T(""))
	, m_DiffuseR(0)
	, m_DiffuseG(0)
	, m_DiffuseB(0)
	, m_DiffuseA(0)
{

}

CMaterialDialog::~CMaterialDialog()
{
}

void CMaterialDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEFAULTSHADER, m_DefaultShaderCombo);
	DDX_Control(pDX, IDC_COMBO_INSTANCINGSHADER, m_InstancingShaderCombo);
	DDX_Control(pDX, IDC_COMBO_INSTANCINGLAYOUT, m_InstancingLayoutCombo);
	DDX_Control(pDX, IDC_COMBO_RENDERSTATE, m_RenderStateCombo);
	DDX_Control(pDX, IDC_COMBO_SHADERSTYLE, m_ShaderStyleCombo);
	DDX_Check(pDX, IDC_CHECK_INSTANCING_ENABLE, m_bIsInstancing);
	DDX_Control(pDX, IDC_LIST_CONTAINER, m_ContainerList);
	DDX_Text(pDX, IDC_EDIT_MATERIAL_NAME, m_strMaterialName);
	DDX_Control(pDX, IDC_LIST_SUBSET, m_SubsetList);
	DDX_Control(pDX, IDC_LIST_MATERIAL, m_MaterialList);
	DDX_Text(pDX, IDC_EDIT_MATERIAL_DIFFUSE_R, m_DiffuseR);
	DDX_Text(pDX, IDC_EDIT_MATERIAL_DIFFUSE_G, m_DiffuseG);
	DDX_Text(pDX, IDC_EDIT_MATERIAL_DIFFUSE_B, m_DiffuseB);
	DDX_Text(pDX, IDC_EDIT_MATERIAL_DIFFUSE_A, m_DiffuseA);
}


BEGIN_MESSAGE_MAP(CMaterialDialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_DEFAULTSHADER, &CMaterialDialog::OnCbnSelchangeComboDefaultshader)
	ON_CBN_SELCHANGE(IDC_COMBO_INSTANCINGSHADER, &CMaterialDialog::OnCbnSelchangeComboInstancingshader)
	ON_CBN_SELCHANGE(IDC_COMBO_INSTANCINGLAYOUT, &CMaterialDialog::OnCbnSelchangeComboInstancinglayout)
	ON_CBN_SELCHANGE(IDC_COMBO_RENDERSTATE, &CMaterialDialog::OnCbnSelchangeComboRenderstate)
	ON_CBN_SELCHANGE(IDC_COMBO_SHADERSTYLE, &CMaterialDialog::OnCbnSelchangeComboShaderstyle)
	ON_BN_CLICKED(IDC_CHECK_INSTANCING_ENABLE, &CMaterialDialog::OnBnClickedCheckInstancingEnable)
	ON_LBN_SELCHANGE(IDC_LIST_CONTAINER, &CMaterialDialog::OnLbnSelchangeListContainer)
	ON_BN_CLICKED(IDC_BUTTON_CONTAINER_CREATE, &CMaterialDialog::OnBnClickedButtonContainerCreate)
	ON_BN_CLICKED(IDC_BUTTON_CONTAINER_DELETE, &CMaterialDialog::OnBnClickedButtonContainerDelete)
	ON_BN_CLICKED(IDC_BUTTON_SUBSET_CREATE, &CMaterialDialog::OnBnClickedButtonSubsetCreate)
	ON_BN_CLICKED(IDC_BUTTON_SUBSET_DELETE, &CMaterialDialog::OnBnClickedButtonSubsetDelete)
	ON_EN_CHANGE(IDC_EDIT_MATERIAL_NAME, &CMaterialDialog::OnEnChangeEditMaterialName)
	ON_BN_CLICKED(IDOK, &CMaterialDialog::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST_SUBSET, &CMaterialDialog::OnLbnSelchangeListSubset)
	ON_BN_CLICKED(IDC_BUTTON_CONTAINER_MODIFY, &CMaterialDialog::OnBnClickedButtonContainerModify)

	ON_LBN_SELCHANGE(IDC_LIST_MATERIAL, &CMaterialDialog::OnLbnSelchangeListMaterial)
	ON_EN_CHANGE(IDC_EDIT_MATERIAL_DIFFUSE_R, &CMaterialDialog::OnEnChangeEditMaterialDiffuseR)
	ON_EN_CHANGE(IDC_EDIT_MATERIAL_DIFFUSE_G, &CMaterialDialog::OnEnChangeEditMaterialDiffuseG)
	ON_EN_CHANGE(IDC_EDIT_MATERIAL_DIFFUSE_B, &CMaterialDialog::OnEnChangeEditMaterialDiffuseB)
	ON_EN_CHANGE(IDC_EDIT_MATERIAL_DIFFUSE_B, &CMaterialDialog::OnEnChangeEditMaterialDiffuseA)
	ON_BN_CLICKED(IDC_BUTTON_DIFFUSE_MODIFY, &CMaterialDialog::OnBnClickedButtonDiffuseModify)
	ON_BN_CLICKED(IDC_BUTTON_MATERIAL_TEXTURE_LOAD, &CMaterialDialog::OnBnClickedButtonMaterialTextureLoad)
END_MESSAGE_MAP()


// CMaterialDialog 메시지 처리기


BOOL CMaterialDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_DefaultShaderCombo.AddString(TEXT("StandardColorShader"));
	m_DefaultShaderCombo.AddString(TEXT("StandardTexShader"));
	m_DefaultShaderCombo.AddString(TEXT("StandardAnim2DShader"));
	m_DefaultShaderCombo.AddString(TEXT("StandardColliderShader"));
	m_DefaultShaderCombo.AddString(TEXT("StandardOutLineShader"));
	m_DefaultShaderCombo.AddString(TEXT("StandardAnim2DOutLineShader"));
	m_DefaultShaderCombo.AddString(TEXT("UIShader"));
	m_DefaultShaderCombo.AddString(TEXT("UIAnim2DShader"));
	m_DefaultShaderCombo.AddString(TEXT("UIBarShader"));

	m_InstancingShaderCombo.AddString(TEXT("StandardStaticInstancingShader"));
	m_InstancingShaderCombo.AddString(TEXT("StandardAnim2DInstancingShader"));
	m_InstancingShaderCombo.AddString(TEXT("TileMapShader"));

	m_InstancingLayoutCombo.AddString(TEXT("TileMapInstancingLayout"));
	m_InstancingLayoutCombo.AddString(TEXT("StaticInstancingLayout"));
	m_InstancingLayoutCombo.AddString(TEXT("Anim2DInstancingLayout"));

	m_RenderStateCombo.AddString(TEXT("AlphaBlend"));
	m_RenderStateCombo.AddString(TEXT("NoneDepth"));
	m_RenderStateCombo.AddString(TEXT("CullNone"));

	m_ShaderStyleCombo.AddString(TEXT("Environment"));
	m_ShaderStyleCombo.AddString(TEXT("Default"));
	m_ShaderStyleCombo.AddString(TEXT("Alpha"));
	m_ShaderStyleCombo.AddString(TEXT("UI"));

	return TRUE;
}


void CMaterialDialog::OnCbnSelchangeComboDefaultshader()
{
}


void CMaterialDialog::OnCbnSelchangeComboInstancingshader()
{
}


void CMaterialDialog::OnCbnSelchangeComboInstancinglayout()
{
}


void CMaterialDialog::OnCbnSelchangeComboRenderstate()
{
}


void CMaterialDialog::OnCbnSelchangeComboShaderstyle()
{
}


void CMaterialDialog::OnBnClickedCheckInstancingEnable()
{
}


void CMaterialDialog::OnLbnSelchangeListContainer()
{
}

// 컨테이너 생성
void CMaterialDialog::OnBnClickedButtonContainerCreate()
{
}

// 컨테이너 삭제
void CMaterialDialog::OnBnClickedButtonContainerDelete()
{
}

// 서브셋 생성
void CMaterialDialog::OnBnClickedButtonSubsetCreate()
{
}

// 서브셋 삭제
void CMaterialDialog::OnBnClickedButtonSubsetDelete()
{
}


void CMaterialDialog::OnEnChangeEditMaterialName()
{
}

// 재질 생성
void CMaterialDialog::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_strMaterialName.IsEmpty())
		return;

	string	strName = CT2CA(m_strMaterialName);

	if (!GET_SINGLE(CResourceManager)->CreateMaterial(strName))
	{
		AfxMessageBox(TEXT("중복된 이름의 재질이 있습니다."));
		return;
	}

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial(strName);

	// resetContent 함수는 리스트박스의 내용을 모두 지워준다.
	m_ContainerList.ResetContent();
	m_SubsetList.ResetContent();

	for (size_t i = 0; i < pMaterial->GetContainerCount(); ++i)
	{
		TCHAR	strContainer[256] = {};
		wsprintf(strContainer, TEXT("Container %d"), i);
		m_ContainerList.AddString(strContainer);

		for (size_t j = 0; j < pMaterial->GetSubsetCount(i); ++j)
		{
			TCHAR	strSubset[256] = {};
			wsprintf(strSubset, TEXT("Subset %d"), j);
			m_SubsetList.AddString(strSubset);
		}
	}

	m_MaterialList.AddString(m_strMaterialName);

	CMainFrame*	pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if (pMainFrame->GetTileMapDlg())
	{
		pMainFrame->GetTileMapDlg()->PostMessageW(UM_MATERIAL_UPDATE);
	}

	SAFE_RELEASE(pMaterial);
	/*
	GET_SINGLE(CResourceManager)->CreateMaterial("MainMapTileMaterial");

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial("MainMapTileMaterial");

	pMaterial->SetSubsetShader(TILEMAP_SHADER);
	pMaterial->SetTexture(0, "MainMapTile", TEXT("Tile.bmp"));

	SAFE_RELEASE(pMaterial);
	*/
}


void CMaterialDialog::OnLbnSelchangeListSubset()
{
}

// 기본 재질 정보 적용
void CMaterialDialog::OnBnClickedButtonContainerModify()
{
	UpdateData(TRUE);

	if (m_strMaterialName.IsEmpty())
		return;

	string	strName = CT2CA(m_strMaterialName);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial(strName);

	if (!pMaterial)
	{
		AfxMessageBox(TEXT("잘못된 이름입니다."));
		return;
	}

	int	iShaderStyle = m_ShaderStyleCombo.GetCurSel();

	if (iShaderStyle == -1)
	{
		AfxMessageBox(TEXT("Shader Style을 선택하세요"));
		return;
	}

	int	iDefaultShader = m_DefaultShaderCombo.GetCurSel();

	if (iDefaultShader == -1)
	{
		AfxMessageBox(TEXT("Default Shader를 선택하세요"));
		return;
	}

	int	iInstancingShader = m_InstancingShaderCombo.GetCurSel();

	if (iInstancingShader == -1)
	{
		AfxMessageBox(TEXT("Instancing Shader를 선택하세요"));
		return;
	}

	int	iInstancingLayout = m_InstancingLayoutCombo.GetCurSel();

	if (iInstancingLayout == -1)
	{
		AfxMessageBox(TEXT("Instancing layout을 선택하세요"));
		return;
	}

	int	iRenderState = m_RenderStateCombo.GetCurSel();

	if (iRenderState == -1)
	{
		AfxMessageBox(TEXT("RenderState를 선택하세요"));
		return;
	}

	pMaterial->SetMaterialShaderStyle((MATERIAL_SHADER_STYLE)iShaderStyle);

	CString	strText;
	m_DefaultShaderCombo.GetWindowTextW(strText);

	string	strConvert = CT2CA(strText);

	pMaterial->SetDefaultShader(strConvert);

	m_InstancingShaderCombo.GetWindowTextW(strText);
	strConvert = CT2CA(strText);
	pMaterial->SetInstancingShader(strConvert);

	m_InstancingLayoutCombo.GetWindowTextW(strText);
	strConvert = CT2CA(strText);
	pMaterial->SetInstancingLayout(strConvert);

	m_RenderStateCombo.GetWindowTextW(strText);
	strConvert = CT2CA(strText);
	pMaterial->SetRenderState(strConvert);

	if (m_bIsInstancing)
		pMaterial->EnableInstancing();

	SAFE_RELEASE(pMaterial);
}

void CMaterialDialog::OnLbnSelchangeListMaterial()
{
}

void CMaterialDialog::OnEnChangeEditMaterialDiffuseR()
{
}

void CMaterialDialog::OnEnChangeEditMaterialDiffuseG()
{
}

void CMaterialDialog::OnEnChangeEditMaterialDiffuseB()
{
}


void CMaterialDialog::OnEnChangeEditMaterialDiffuseA()
{
}

// 재질의 DIFFUSE 변경
void CMaterialDialog::OnBnClickedButtonDiffuseModify()
{
	UpdateData(TRUE);

	if (m_strMaterialName.IsEmpty())
		return;

	string	strName = CT2CA(m_strMaterialName);

	CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial(strName);

	if (!pMaterial)
	{
		AfxMessageBox(TEXT("잘못된 이름입니다."));
		return;
	}

	int	iContainer = m_ContainerList.GetCurSel();

	if (iContainer == -1)
	{
		AfxMessageBox(TEXT("컨테이너를 선택하세요"));
		return;
	}

	int	iSubset = m_SubsetList.GetCurSel();

	if (iSubset == -1)
	{
		AfxMessageBox(TEXT("서브셋을 선택하세요"));
		return;
	}

	Vector4	vDiffuse = Vector4(m_DiffuseR / 255.f, m_DiffuseG / 255.f, m_DiffuseB / 255.f, m_DiffuseA / 255.f);

	pMaterial->SetSubsetDiffuse(vDiffuse, iContainer, iSubset);

	SAFE_RELEASE(pMaterial);
}

void CMaterialDialog::OnBnClickedButtonMaterialTextureLoad()
{
	TCHAR	strFilter[] = TEXT("Texture(*.BMP, *.PNG, *.JPG) | *.bmp;*.png;*.jpg | All Files(*.*)|*.*||");

	// 파일 다이얼로그를 이용하여 이미지를 불러온다.
	CFileDialog	dlg(TRUE, TEXT(".png"), TEXT("Tile"), OFN_HIDEREADONLY, strFilter);

	if (dlg.DoModal() == IDOK)
	{
		CString strFullPath = dlg.GetPathName();

		CString	strTexName = dlg.GetFileTitle();

		string	strTexKey = CT2CA(strTexName);

		UpdateData(TRUE);

		if (m_strMaterialName.IsEmpty())
			return;

		string	strName = CT2CA(m_strMaterialName);

		CMaterial* pMaterial = GET_SINGLE(CResourceManager)->FindMaterial(strName);

		if (!pMaterial)
		{
			AfxMessageBox(TEXT("잘못된 이름입니다."));
			return;
		}

		int	iContainer = m_ContainerList.GetCurSel();

		if (iContainer == -1)
		{
			AfxMessageBox(TEXT("컨테이너를 선택하세요"));
			return;
		}

		int	iSubset = m_SubsetList.GetCurSel();

		if (iSubset == -1)
		{
			AfxMessageBox(TEXT("서브셋을 선택하세요"));
			return;
		}

		pMaterial->SetTextureFromFullPath(0, strTexKey, strFullPath, iContainer, iSubset);

		SAFE_RELEASE(pMaterial);
	}
}
