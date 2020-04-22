#pragma once

#include "../GameEngine.h"

class ENGINE_DLL CShaderManager
{
private:
	unordered_map<size_t, class CShader*>	m_mapShader;
	unordered_map<size_t, ID3D11InputLayout*>	m_mapInputLayout;
	unordered_map<size_t, PCBuffer>			m_mapCBuffer;
	vector<D3D11_INPUT_ELEMENT_DESC>	m_vecInputDesc;
	UINT			m_iInputSize;

public:
	bool Init();
	bool LoadShader(const string& strName, const TCHAR* pFileName[ST_END],
		const char* pEntryName[ST_END], const string& strPathName = SHADER_PATH);
	class CShader* FindShader(const string& strName);

	void AddInputDesc(const char* pSemantic, UINT iSemanticIdx,
		DXGI_FORMAT eFmt, UINT iInputSlot, UINT iSize,
		D3D11_INPUT_CLASSIFICATION eInputSlotClass,
		UINT iInstanceDataStepRate);
	bool CreateInputLayout(const string& strName, const string& strShaderName);
	ID3D11InputLayout* FindInputLayout(const string& strName);

	bool CreateCBuffer(const string& strName, int iSize, int iRegister,
		int iShaderType);
	bool UpdateCBuffer(const string& strName, void* pData);
	PCBuffer FindCBuffer(const string& strName);

	DECLARE_SINGLE(CShaderManager)
};

