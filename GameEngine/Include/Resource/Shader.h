#pragma once

#include "../Ref.h"

class ENGINE_DLL CShader :
	public CRef
{
	friend class CShaderManager;

private:
	CShader();
	~CShader();

private:
	ID3D11VertexShader*	m_pVS;
	ID3DBlob*	m_pVSBlob;
	ID3D11PixelShader*	m_pPS;
	ID3DBlob*	m_pPSBlob;

public:
	const void* GetVSCode()	const;
	size_t GetVSCodeLength()	const;

public:
	bool LoadShader(const string& strName, const TCHAR* pFileName[ST_END],
		const char* pEntryName[ST_END], const string& strPathName = SHADER_PATH);
	bool LoadVertexShader(const string& strName, const TCHAR* pFileName,
		const char* pEntryName, const string& strPathName = SHADER_PATH);
	bool LoadPixelShader(const string& strName, const TCHAR* pFileName,
		const char* pEntryName, const string& strPathName = SHADER_PATH);
	void SetShader();
};

