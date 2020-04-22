// MaterialDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GameEditorTest.h"
#include "MaterialDlg.h"
#include "afxdialogex.h"
#include "Resource/ResourceManager.h"
#include "Resource/Material.h"
#include "MainFrm.h"
#include "TileMapEditorDlg.h"

// CMaterialDlg 대화 상자

IMPLEMENT_DYNAMIC(CMaterialDlg, CDialogEx)

CMaterialDlg::CMaterialDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MATERIAL, pParent)
	, m_bIsInstancing(FALSE)
	, m_strMaterialName(_T(""))
	, m_DiffuseR(0)
	, m_DiffuseG(0)
	, m_DiffuseB(0)
{

}

CMaterialDlg::~CMaterialDlg()
{
}

void CMaterialDlg::DoDataExchange(CDataExchange* pDX)
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
}


BEGIN_MESSAGE_MAP(CMaterialDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_DEFAULTSHADER, &CMaterialDlg::OnCbnSelchangeComboDefaultshader)
	ON_CBN_SELCHANGE(IDC_COMBO_INSTANCINGSHADER, &CMaterialDlg::OnCbnSelchangeComboInstancingshader)
	ON_CBN_SELCHANGE(IDC_COMBO_INSTANCINGLAYOUT, &CMaterialDlg::OnCbnSelchangeComboInstancinglayout)
	ON_CBN_SELCHANGE(IDC_COMBO_RENDERSTATE, &CMaterialDlg::OnCbnSelchangeComboRenderstate)
	ON_CBN_SELCHANGE(IDC_COMBO_SHADERSTYLE, &CMaterialDlg::OnCbnSelchangeComboShaderstyle)
	ON_BN_CLICKED(IDC_CHECK_INSTANCING_ENABLE, &CMaterialDlg::OnBnClickedCheckInstancingEnable)
	ON_LBN_SELCHANGE(IDC_LIST_CONTAINER, &CMaterialDlg::OnLbnSelchangeListContainer)
	ON_BN_CLICKED(IDC_BUTTON_CONTAINER_CREATE, &CMaterialDlg::OnBnClickedButtonContainerCreate)
	ON_BN_CLICKED(IDC_BUTTON_CONTAINER_DELETE, &CMaterialDlg::OnBnClickedButtonContainerDelete)
	ON_BN_CLICKED(IDC_BUTTON_SUBSET_CREATE, &CMaterialDlg::OnBnClickedButtonSubsetCreate)
	ON_BN_CLICKED(IDC_BUTTON_SUBSET_DELETE, &CMaterialDlg::OnBnClickedButtonSubsetDelete)
	ON_EN_CHANGE(IDC_EDIT_MATERIAL_NAME, &CMaterialDlg::OnEnChangeEditMaterialName)
	ON_BN_CLICKED(IDOK, &CMaterialDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST_SUBSET, &CMaterialDlg::OnLbnSelchangeListSubset)
	ON_BN_CLICKED(IDC_BUTTON_CONTAINER_MODIFY, &CMaterialDlg::OnBnClickedButtonContainerModify)
	ON_LBN_SELCHANGE(IDC_LIST_MATERIAL, &CMaterialDlg::OnLbnSelchangeListMaterial)
	ON_EN_CHANGE(IDC_EDIT_MATERIAL_DIFFUSE_R, &CMaterialDlg::OnEnChangeEditMaterialDiffuseR)
	ON_EN_CHANGE(IDC_EDIT_MATERIAL_DIFFUSE_G, &CMaterialDlg::OnEnChangeEditMaterialDiffuseG)
	ON_EN_CHANGE(IDC_EDIT_MATERIAL_DIFFUSE_B, &CMaterialDlg::OnEnChangeEditMaterialDiffuseB)
	ON_BN_CLICKED(IDC_BUTTON_DIFFUSE_MODIFY, &CMaterialDlg::OnBnClickedButtonDiffuseModify)
	ON_BN_CLICKED(IDC_BUTTON_MATERIAL_TEXTURE_LOAD, &CMaterialDlg::OnBnClickedButtonMaterialTextureLoad)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_SHADER, &CMaterialDlg::OnBnClickedButtonUpdateShader)
END_MESSAGE_MAP()


// CMaterialDlg 메시지 처리기


BOOL CMaterialDlg::OnInitDialog()
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
	m_DefaultShaderCombo.AddString(TEXT("TileMapShader"));

	m_DefaultShaderCombo.SetCurSel(9);

	m_InstancingShaderCombo.AddString(TEXT("StandardStaticInstancingShader"));
	m_InstancingShaderCombo.AddString(TEXT("StandardAnim2DInstancingShader"));

	m_InstancingShaderCombo.SetCurSel(0);

	m_InstancingLayoutCombo.AddString(TEXT("TileMapInstancingLayout"));
	m_InstancingLayoutCombo.AddString(TEXT("StaticInstancingLayout"));
	m_InstancingLayoutCombo.AddString(TEXT("Anim2DInstancingLayout"));

	m_InstancingLayoutCombo.SetCurSel(0);

	m_RenderStateCombo.AddString(TEXT("AlphaBlend"));
	m_RenderStateCombo.AddString(TEXT("NoneDepth"));
	m_RenderStateCombo.AddString(TEXT("CullNone"));

	m_RenderStateCombo.SetCurSel(0);
	
	m_ShaderStyleCombo.AddString(TEXT("Environment"));
	m_ShaderStyleCombo.AddString(TEXT("Default"));
	m_ShaderStyleCombo.AddString(TEXT("Alpha"));
	m_ShaderStyleCombo.AddString(TEXT("UI"));

	m_ShaderStyleCombo.SetCurSel(0);

	m_strMaterialName	= TEXT("Tile");
	m_DiffuseR = 255;
	m_DiffuseG = 255;
	m_DiffuseB = 255;
	m_bIsInstancing	= TRUE;

	UpdateData(FALSE);

	return FALSE;
}


void CMaterialDlg::OnCbnSelchangeComboDefaultshader()
{
}


void CMaterialDlg::OnCbnSelchangeComboInstancingshader()
{
}


void CMaterialDlg::OnCbnSelchangeComboInstancinglayout()
{
}


void CMaterialDlg::OnCbnSelchangeComboRenderstate()
{
}


void CMaterialDlg::OnCbnSelchangeComboShaderstyle()
{
}


void CMaterialDlg::OnBnClickedCheckInstancingEnable()
{
}


void CMaterialDlg::OnLbnSelchangeListContainer()
{
}

// 컨테이너 생성
void CMaterialDlg::OnBnClickedButtonContainerCreate()
{
}

// 컨테이너 삭제
void CMaterialDlg::OnBnClickedButtonContainerDelete()
{
}

// 서브셋 생성
void CMaterialDlg::OnBnClickedButtonSubsetCreate()
{
}

// 서브셋 삭제
void CMaterialDlg::OnBnClickedButtonSubsetDelete()
{
}


void CMaterialDlg::OnEnChangeEditMaterialName()
{
}

// 재질 생성
void CMaterialDlg::OnBnClickedOk()
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
		TCHAR	strContainer[256]	= {};
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

	CMainFrame*	pMainFrame = (CMainFrame*)AfxGetMainWnd();

	if(pMainFrame->GetTileMapDlg())
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


void CMaterialDlg::OnLbnSelchangeListSubset()
{
}

// 기본 재질 정보 적용
void CMaterialDlg::OnBnClickedButtonContainerModify()
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

	if(iShaderStyle == -1)
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

	if(m_bIsInstancing)
		pMaterial->EnableInstancing();

	SAFE_RELEASE(pMaterial);
}


void CMaterialDlg::OnLbnSelchangeListMaterial()
{
}


void CMaterialDlg::OnEnChangeEditMaterialDiffuseR()
{
}


void CMaterialDlg::OnEnChangeEditMaterialDiffuseG()
{
}


void CMaterialDlg::OnEnChangeEditMaterialDiffuseB()
{
}

// 재질 Diffuse 변경
void CMaterialDlg::OnBnClickedButtonDiffuseModify()
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

	if(iContainer == -1)
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

	Vector4	vDiffuse = Vector4(m_DiffuseR / 255.f, m_DiffuseG / 255.f, m_DiffuseB / 255.f, 1.f);

	pMaterial->SetSubsetDiffuse(vDiffuse, iContainer, iSubset);

	SAFE_RELEASE(pMaterial);
}


void CMaterialDlg::OnBnClickedButtonMaterialTextureLoad()
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

	TCHAR	strFilter[] = TEXT("Texture(*.BMP, *.PNG, *.JPG)|*.bmp;*.png;*.jpg|All Files(*.*)|*.*||");

	// 파일 다이얼로그를 이용하여 이미지를 불러온다.
	CFileDialog	dlg(TRUE, TEXT(".png"), TEXT("Tile"), OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, strFilter);

	if (dlg.DoModal() == IDOK)
	{
		POSITION	pos = dlg.GetStartPosition();

		vector<const TCHAR*>	vecPath;

		CString strFolder = dlg.GetFolderPath();

		for (int i = 0; i <= 379; ++i)
		{
			TCHAR* pPath = new TCHAR[MAX_PATH];

			wsprintf(pPath, TEXT("%s\\Diablos_Lair_Floor_%d.png"), strFolder, i);

			vecPath.push_back(pPath);
		}
		
		/*while (pos)
		{
			CString	strPath = dlg.GetNextPathName(pos);

			TCHAR* pPath = new TCHAR[MAX_PATH];

			lstrcpy(pPath, strPath);

			vecPath.push_back(pPath);
		}*/

		if(vecPath.size() == 1)
		{
			CString strFullPath = vecPath[0];

			TCHAR	strTexName[256]	= {};
			_wsplitpath_s(strFullPath, nullptr, 0, nullptr, 0, strTexName, 256, nullptr, 0);

			string	strTexKey = CT2CA(strTexName);

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
		}

		else
		{
			TCHAR	strTexName[256] = {};
			_wsplitpath_s(vecPath[0], nullptr, 0, nullptr, 0, strTexName, 256, nullptr, 0);

			string	strTexKey = CT2CA(strTexName);

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

			pMaterial->SetTextureFromFullPath(10, strTexKey, vecPath, iContainer, iSubset);
		}

		for (size_t i = 0; i < vecPath.size(); ++i)
		{
			SAFE_DELETE_ARRAY(vecPath[i]);
		}
	}

	SAFE_RELEASE(pMaterial);
}


void CMaterialDlg::OnBnClickedButtonUpdateShader()
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

	SAFE_RELEASE(pMaterial);
}
