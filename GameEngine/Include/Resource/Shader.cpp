#include "Shader.h"
#include "../PathManager.h"
#include "../Device.h"

CShader::CShader()	:
	m_pVS(nullptr),
	m_pVSBlob(nullptr),
	m_pPS(nullptr),
	m_pPSBlob(nullptr)
{
	SetTypeID<CShader>();
}

CShader::~CShader()
{
	SAFE_RELEASE(m_pPSBlob);
	SAFE_RELEASE(m_pPS);
	SAFE_RELEASE(m_pVSBlob);
	SAFE_RELEASE(m_pVS);
}

const void * CShader::GetVSCode() const
{
	return m_pVSBlob->GetBufferPointer();
}

size_t CShader::GetVSCodeLength() const
{
	return m_pVSBlob->GetBufferSize();
}

bool CShader::LoadShader(const string & strName,
	const TCHAR * pFileName[ST_END], const char * pEntryName[ST_END], 
	const string & strPathName)
{
	SetName(strName);

	if (!LoadVertexShader(strName, pFileName[ST_VERTEX],
		pEntryName[ST_VERTEX], strPathName))
		return false;

	if (!LoadPixelShader(strName, pFileName[ST_PIXEL],
		pEntryName[ST_PIXEL], strPathName))
		return false;

	return true;
}

bool CShader::LoadVertexShader(const string & strName, 
	const TCHAR * pFileName, const char * pEntryName,
	const string & strPathName)
{
	UINT	iFlag = 0;
#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif // _DEBUG


	TCHAR	strFullPath[MAX_PATH] = {};

	const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathName);

	if (pPath)
		lstrcpy(strFullPath, pPath);

	lstrcat(strFullPath, pFileName);

	ID3DBlob*	pError = nullptr;

	// https://docs.microsoft.com/ko-kr/windows/win32/direct3dhlsl/d3dcompile-constants
	if (FAILED(D3DCompileFromFile(strFullPath, nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, pEntryName, "vs_5_0",
		iFlag, 0, &m_pVSBlob, &pError)))
	{
		OutputDebugStringA((char*)pError->GetBufferPointer());
		OutputDebugStringA("\n");
		return false;
	}

	// 1번 인자는 컴파일된 Shader코드를 넣어주어야 한다.
	// 컴파일된 Shader 코드는 m_pVSBlob에 들어가있다.
	if (FAILED(DEVICE->CreateVertexShader(m_pVSBlob->GetBufferPointer(),
		m_pVSBlob->GetBufferSize(), nullptr, &m_pVS)))
		return false;

	return true;
}

bool CShader::LoadPixelShader(const string & strName,
	const TCHAR * pFileName, const char * pEntryName, 
	const string & strPathName)
{
	UINT	iFlag = 0;
#ifdef _DEBUG
	iFlag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

	TCHAR	strFullPath[MAX_PATH] = {};

	const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathName);

	if (pPath)
		lstrcpy(strFullPath, pPath);

	lstrcat(strFullPath, pFileName);

	ID3DBlob*	pError = nullptr;

	// https://docs.microsoft.com/ko-kr/windows/win32/direct3dhlsl/d3dcompile-constants
	if (FAILED(D3DCompileFromFile(strFullPath, nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, pEntryName, "ps_5_0",
		iFlag, 0, &m_pPSBlob, &pError)))
	{
		OutputDebugStringA((char*)pError->GetBufferPointer());
		OutputDebugStringA("\n");
		return false;
	}

	// 1번 인자는 컴파일된 Shader코드를 넣어주어야 한다.
	// 컴파일된 Shader 코드는 m_pVSBlob에 들어가있다.
	if (FAILED(DEVICE->CreatePixelShader(m_pPSBlob->GetBufferPointer(),
		m_pPSBlob->GetBufferSize(), nullptr, &m_pPS)))
		return false;

	return true;
}

void CShader::SetShader()
{
	CONTEXT->VSSetShader(m_pVS, nullptr, 0);
	CONTEXT->PSSetShader(m_pPS, nullptr, 0);
}
