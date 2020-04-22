#pragma once

#include "../Ref.h"
#include "DirectXTex.h"

class ENGINE_DLL CTexture :
	public CRef
{
public:
	CTexture();
	~CTexture();

private:
	vector<ScratchImage*>		m_vecImage;
	vector<const TCHAR*>		m_vecFileName;
	string						m_strPathName;
	ID3D11ShaderResourceView*	m_pSRV;
	unsigned int				m_iWidth;
	unsigned int				m_iHeight;
	IMAGE_TYPE					m_eType;

public:
	unsigned int GetWidth()	const;
	unsigned int GetHeight()	const;
	IMAGE_TYPE GetImageType()	const;

public:
	bool LoadTexture(const string& strName, const TCHAR* pFileName,
		const string& strPathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const string& strName, const TCHAR* pFullPath);
	bool LoadTexture(const string& strName, const vector<const TCHAR*>& vecFileName,
		const string& strPathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const string& strName, const vector<const TCHAR*>& vecFullPath);
	void SetTexture(int iRegister, int iShaderType);

private:
	bool CreateResource();
	bool CreateResourceArray();
};

