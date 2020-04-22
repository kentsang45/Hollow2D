#include "ShaderManager.h"
#include "Shader.h"
#include "../Device.h"

DEFINITION_SINGLE(CShaderManager)

CShaderManager::CShaderManager()
{
	m_iInputSize = 0;
}

CShaderManager::~CShaderManager()
{
	SAFE_DELETE_NORMAL_MAP(m_mapCBuffer);
	SAFE_RELEASE_MAP(m_mapShader);
	SAFE_RELEASE_NORMAL_MAP(m_mapInputLayout);
}

bool CShaderManager::Init()
{
	const TCHAR*	pFileName[ST_END]	=
	{
		TEXT("Standard.fx"),
		TEXT("Standard.fx")
	};

	const char* pEntry[ST_END]	=
	{
		"StandardColorVS",
		"StandardColorPS"
	};

	if (!LoadShader(STANDARD_COLOR_SHADER, pFileName, pEntry))
		return false;

	pFileName[ST_VERTEX] = TEXT("Standard.fx");
	pFileName[ST_PIXEL] = TEXT("Standard.fx");

	pEntry[ST_VERTEX] = "StandardTexVS";
	pEntry[ST_PIXEL] = "StandardTexPS";

	if (!LoadShader(STANDARD_TEX_SHADER, pFileName, pEntry))
		return false;

	pFileName[ST_VERTEX] = TEXT("Standard.fx");
	pFileName[ST_PIXEL] = TEXT("Standard.fx");

	pEntry[ST_VERTEX] = "StandardAnim2DVS";
	pEntry[ST_PIXEL] = "StandardAnim2DPS";

	if (!LoadShader(STANDARD_ANIM2D_SHADER, pFileName, pEntry))
		return false;

	pFileName[ST_VERTEX] = TEXT("Collider.fx");
	pFileName[ST_PIXEL] = TEXT("Collider.fx");

	pEntry[ST_VERTEX] = "ColliderVS";
	pEntry[ST_PIXEL] = "ColliderPS";

	if (!LoadShader(STANDARD_COLLIDER_SHADER, pFileName, pEntry))
		return false;

	pFileName[ST_VERTEX] = TEXT("UI.fx");
	pFileName[ST_PIXEL] = TEXT("UI.fx");

	pEntry[ST_VERTEX] = "UIVS";
	pEntry[ST_PIXEL] = "UIPS";

	if (!LoadShader(UI_SHADER, pFileName, pEntry))
		return false;

	pFileName[ST_VERTEX] = TEXT("UI.fx");
	pFileName[ST_PIXEL] = TEXT("UI.fx");

	pEntry[ST_VERTEX] = "UIAnim2DVS";
	pEntry[ST_PIXEL] = "UIAnim2DPS";

	if (!LoadShader(UI_ANIM2D_SHADER, pFileName, pEntry))
		return false; 
		
	pFileName[ST_VERTEX] = TEXT("UI.fx");
	pFileName[ST_PIXEL] = TEXT("UI.fx");

	pEntry[ST_VERTEX] = "UIBarVS";
	pEntry[ST_PIXEL] = "UIBarPS";

	if (!LoadShader(UI_BAR_SHADER, pFileName, pEntry))
		return false;

	pFileName[ST_VERTEX] = TEXT("Standard.fx");
	pFileName[ST_PIXEL] = TEXT("Standard.fx");

	pEntry[ST_VERTEX] = "StandardTexVS";
	pEntry[ST_PIXEL] = "StandardTexOutLine2DPS";

	if (!LoadShader(STANDARD_OUTLINE_SHADER, pFileName, pEntry))
		return false;

	pFileName[ST_VERTEX] = TEXT("Standard.fx");
	pFileName[ST_PIXEL] = TEXT("Standard.fx");

	pEntry[ST_VERTEX] = "StandardAnim2DVS";
	pEntry[ST_PIXEL] = "StandardTexOutLine2DPS";

	if (!LoadShader(STANDARD_ANIM2D_OUTLINE_SHADER, pFileName, pEntry))
		return false;

	pFileName[ST_VERTEX] = TEXT("TileMap.fx");
	pFileName[ST_PIXEL] = TEXT("TileMap.fx");

	pEntry[ST_VERTEX] = "TileMapVS";
	pEntry[ST_PIXEL] = "TileMapPS";

	if (!LoadShader(TILEMAP_SHADER, pFileName, pEntry))
		return false;

	pFileName[ST_VERTEX] = TEXT("Standard.fx");
	pFileName[ST_PIXEL] = TEXT("Standard.fx");

	pEntry[ST_VERTEX] = "StandardStaticInstancingVS";
	pEntry[ST_PIXEL] = "StandardStaticInstancingPS";

	if (!LoadShader(STANDARD_STATIC_INSTANCING_SHADER, pFileName, pEntry))
		return false;

	pFileName[ST_VERTEX] = TEXT("Standard.fx");
	pFileName[ST_PIXEL] = TEXT("Standard.fx");

	pEntry[ST_VERTEX] = "StandardAnim2DInstancingVS";
	pEntry[ST_PIXEL] = "StandardAnim2DInstancingPS";

	if (!LoadShader(STANDARD_ANIM2D_INSTANCING_SHADER, pFileName, pEntry))
		return false;


	/////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////
	// FULLSCREEN SHADER

	pFileName[ST_VERTEX] = TEXT("Share.fx");
	pFileName[ST_PIXEL] = TEXT("Standard.fx");

	pEntry[ST_VERTEX] = "FullScreenVS";
	pEntry[ST_PIXEL] = "StandardTexPS";

	if (!LoadShader(FULLSCREEN_SHADER, pFileName, pEntry))
		return false;





	// Vertex Color InputLayout
	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
		0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0);

	if (!CreateInputLayout(POS_COLOR_LAYOUT, STANDARD_COLOR_SHADER))
		return false;

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
		0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0);

	if (!CreateInputLayout(POS_UV_LAYOUT, STANDARD_TEX_SHADER))
		return false;

	// Vertex Color InputLayout
	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);

	m_iInputSize = 0;
	AddInputDesc("WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("DIFFUSE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("PIVOT", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		1, 12, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("EMPTY", 0, DXGI_FORMAT_R32_FLOAT,
		1, 4, D3D11_INPUT_PER_INSTANCE_DATA, 1);

	if (!CreateInputLayout(COLLIDER_LAYOUT, STANDARD_COLLIDER_SHADER))
		return false;

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
		0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0);

	m_iInputSize = 0;
	AddInputDesc("WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("START", 0, DXGI_FORMAT_R32G32_FLOAT,
		1, 8, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("END", 0, DXGI_FORMAT_R32G32_FLOAT,
		1, 8, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("IMGSIZE", 0, DXGI_FORMAT_R32G32_FLOAT,
		1, 8, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("IMGFRAME", 0, DXGI_FORMAT_R32_UINT,
		1, 4, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("IMGTYPE", 0, DXGI_FORMAT_R32_UINT,
		1, 4, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("TILEOPTION", 0, DXGI_FORMAT_R32_UINT,
		1, 4, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("TILETYPE", 0, DXGI_FORMAT_R32_UINT,
		1, 4, D3D11_INPUT_PER_INSTANCE_DATA, 1);

	if (!CreateInputLayout(TILEMAP_INSTANCING_LAYOUT, TILEMAP_SHADER))
		return false;

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
		0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0);

	m_iInputSize = 0;
	AddInputDesc("WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("DIFFUSE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("PIVOT", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		1, 12, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("EMPTY", 0, DXGI_FORMAT_R32_FLOAT,
		1, 4, D3D11_INPUT_PER_INSTANCE_DATA, 1);

	if (!CreateInputLayout(STATIC_INSTANCING_LAYOUT, STANDARD_STATIC_INSTANCING_SHADER))
		return false;

	AddInputDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0);
	AddInputDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
		0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0);

	m_iInputSize = 0;
	AddInputDesc("WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("DIFFUSE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
		1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("PIVOT", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		1, 12, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("START", 0, DXGI_FORMAT_R32G32_FLOAT,
		1, 8, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("END", 0, DXGI_FORMAT_R32G32_FLOAT,
		1, 8, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("ANIMTYPE", 0, DXGI_FORMAT_R32_UINT,
		1, 4, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("IMGWIDTH", 0, DXGI_FORMAT_R32_FLOAT,
		1, 4, D3D11_INPUT_PER_INSTANCE_DATA, 1);
	AddInputDesc("IMGHEIGHT", 0, DXGI_FORMAT_R32_FLOAT,
		1, 4, D3D11_INPUT_PER_INSTANCE_DATA, 1);

	if (!CreateInputLayout(ANIM2D_INSTANCING_LAYOUT, STANDARD_ANIM2D_INSTANCING_SHADER))
		return false;

	// Constant Buffer
	CreateCBuffer(TRANSFORM_CBUFFER, sizeof(TransformCBuffer),
		0, CST_VERTEX | CST_PIXEL);
	CreateCBuffer(MATERIAL_CBUFFER, sizeof(MaterialCBuffer),
		1, CST_VERTEX | CST_PIXEL);
	CreateCBuffer(ANIM2D_CBUFFER, sizeof(Animation2DCBuffer), 
		10, CST_VERTEX | CST_PIXEL);
	CreateCBuffer(BAR_CBUFFER, sizeof(BarCBuffer), 11, CST_VERTEX | CST_PIXEL);
	CreateCBuffer(OUTLINE_CBUFFER, sizeof(OutLineCBuffer), 11, CST_PIXEL);
	CreateCBuffer(TILEMAP_CBUFFER, sizeof(ImageFrame), 10, CST_VERTEX | CST_PIXEL);
	CreateCBuffer(PAPERBURN_CBUFFER, sizeof(PaperBurnCBuffer), 6, CST_VERTEX | CST_PIXEL);

	return true;
}

bool CShaderManager::LoadShader(const string & strName,
	const TCHAR * pFileName[ST_END], const char * pEntryName[ST_END],
	const string & strPathName)
{
	CShader*	pShader = FindShader(strName);

	if (pShader)
	{
		SAFE_RELEASE(pShader);
		return false;
	}

	pShader = new CShader;

	if (!pShader->LoadShader(strName, pFileName, pEntryName, strPathName))
	{
		SAFE_RELEASE(pShader);
		return false;
	}

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapShader.insert(make_pair(iKey, pShader));

	return true;
}

CShader * CShaderManager::FindShader(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapShader.find(iKey);

	if (iter == m_mapShader.end())
		return nullptr;

	iter->second->AddRef();

	return iter->second;
}

void CShaderManager::AddInputDesc(const char * pSemantic, 
	UINT iSemanticIdx, DXGI_FORMAT eFmt, UINT iInputSlot, 
	UINT iSize, D3D11_INPUT_CLASSIFICATION eInputSlotClass, 
	UINT iInstanceDataStepRate)
{
	D3D11_INPUT_ELEMENT_DESC	tDesc = {};

	tDesc.SemanticName = pSemantic;
	tDesc.SemanticIndex = iSemanticIdx;
	tDesc.Format = eFmt;
	tDesc.InputSlot = iInputSlot;
	tDesc.AlignedByteOffset = m_iInputSize;
	tDesc.InputSlotClass = eInputSlotClass;
	tDesc.InstanceDataStepRate = iInstanceDataStepRate;

	m_iInputSize += iSize;

	m_vecInputDesc.push_back(tDesc);
}

bool CShaderManager::CreateInputLayout(const string & strName, 
	const string& strShaderName)
{
	ID3D11InputLayout*	pLayout = FindInputLayout(strName);

	if (pLayout)
		return false;

	CShader*	pShader = FindShader(strShaderName);

	if (!pShader)
		return false;

	m_iInputSize = 0;

	if (FAILED(DEVICE->CreateInputLayout(&m_vecInputDesc[0], m_vecInputDesc.size(),
		pShader->GetVSCode(), pShader->GetVSCodeLength(), &pLayout)))
	{
		m_vecInputDesc.clear();
		SAFE_RELEASE(pShader);
		return false;
	}

	m_vecInputDesc.clear();
	
	SAFE_RELEASE(pShader);

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapInputLayout.insert(make_pair(iKey, pLayout));

	return true;
}

ID3D11InputLayout * CShaderManager::FindInputLayout(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapInputLayout.find(iKey);

	if (iter == m_mapInputLayout.end())
		return nullptr;

	return iter->second;
}

bool CShaderManager::CreateCBuffer(const string & strName,
	int iSize, int iRegister, int iShaderType)
{
	PCBuffer	pBuffer = FindCBuffer(strName);

	if (pBuffer)
		return false;

	pBuffer = new CBuffer;

	pBuffer->iSize = iSize;
	pBuffer->iRegister = iRegister;
	pBuffer->iShaderType = iShaderType;

	D3D11_BUFFER_DESC	tDesc = {};
	tDesc.ByteWidth = iSize;
	tDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(DEVICE->CreateBuffer(&tDesc, nullptr, &pBuffer->pBuffer)))
	{
		SAFE_DELETE(pBuffer);
		return false;
	}

	hash<string>	hs;

	size_t	iKey = hs(strName);

	m_mapCBuffer.insert(make_pair(iKey, pBuffer));

	return true;
}

bool CShaderManager::UpdateCBuffer(const string & strName, 
	void * pData)
{
	PCBuffer	pBuffer = FindCBuffer(strName);

	if (!pBuffer)
		return false;

	D3D11_MAPPED_SUBRESOURCE	tMap = {};
	CONTEXT->Map(pBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD,
		0, &tMap);

	memcpy(tMap.pData, pData, pBuffer->iSize);

	CONTEXT->Unmap(pBuffer->pBuffer, 0);

	if (pBuffer->iShaderType & CST_VERTEX)
		CONTEXT->VSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);

	if (pBuffer->iShaderType & CST_PIXEL)
		CONTEXT->PSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);

	return true;
}

PCBuffer CShaderManager::FindCBuffer(const string & strName)
{
	hash<string>	hs;

	size_t	iKey = hs(strName);

	auto	iter = m_mapCBuffer.find(iKey);

	if (iter == m_mapCBuffer.end())
		return nullptr;

	return iter->second;
}
