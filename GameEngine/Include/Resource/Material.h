#pragma once

#include "../Ref.h"

typedef struct _tagTextureInfo
{
	class CTexture*		pTexture;
	int			iRegister;
	bool				bArrayTex;

	_tagTextureInfo();
	~_tagTextureInfo();
}TextureInfo, *PTextureInfo;

typedef struct _tagMaterialSubset
{
	Vector4			vDiffuse;
	class CShader*	pShader;
	vector<PTextureInfo>	vecTexture;

	_tagMaterialSubset();
	~_tagMaterialSubset();
}MaterialSubset, *PMaterialSubset;

typedef struct _tagMaterialContainer
{
	vector<PMaterialSubset>	vecSubset;

	_tagMaterialContainer();
	~_tagMaterialContainer();
}MaterialContainer, *PMaterialContainer;

class ENGINE_DLL CMaterial :
	public CRef
{
public:
	CMaterial();
	~CMaterial();

private:
	class CShader*	m_pDefaultShader;
	class CShader*	m_pInstancingShader;
	ID3D11InputLayout*	m_pInstancingLayout;
	vector<PMaterialContainer>	m_vecContainer;
	MaterialCBuffer	m_tCBuffer;
	class CRenderState*	m_pRenderState[RST_END];
	MATERIAL_SHADER_STYLE	m_eMaterialShaderStyle;
	unordered_map<size_t, PCBufferNode>	m_mapCBuffer;
	size_t				m_iSerialNumber;
	bool				m_bEnableInstancing;


public:
	MATERIAL_SHADER_STYLE GetMaterialShaderStyle()	const;
	void SetSerialNumber(const string& strName);
	size_t GetSerialNumber()	const;
	void EnableInstancing();
	bool IsEnableInstancing()	const;
	Vector4 GetDiffuse(int iContainer, int iSubset)	const;
	size_t GetContainerCount() const;
	size_t GetSubsetCount(int iIndex) const;

public:
	bool CreateCBufferNode(const string& strName, int iRegister, int iSize);
	bool UpdateCBufferNode(const string& strName, void* pData);
	void SetMaterialShaderStyle(MATERIAL_SHADER_STYLE eStyle);
	void SetContainer(size_t iContainerCount);
	void SetSubset(size_t iContainer, size_t iSubsetCount);
	void SetDefaultShader(const string& strName);
	void SetSubsetShader(const string& strName,
		size_t iContainer = 0, size_t iSubset = 0);
	void SetSubsetDiffuse(const Vector4& vColor,
		size_t iContainer = 0, size_t iSubset = 0);
	void CopyMaterial(CMaterial* pMaterial);
	bool SetTexture(int iRegister, const string& strName, int iContainer = 0, int iSubset = 0);
	bool SetTexture(int iRegister, const string& strName, const TCHAR* pFileName,
		const string& strPathName = TEXTURE_PATH, int iContainer = 0, int iSubset = 0);
	bool SetTextureFromFullPath(int iRegister, const string& strName, const TCHAR* pFullPath,
		int iContainer = 0, int iSubset = 0);
	bool SetTexture(int iRegister, const string& strName, const vector<const TCHAR*>& vecFileName,
		const string& strPathName = TEXTURE_PATH, int iContainer = 0, int iSubset = 0);
	bool SetTextureFromFullPath(int iRegister, const string& strName, const vector<const TCHAR*>& vecFullPath,
		int iContainer = 0, int iSubset = 0);
	bool SetTexture(int iRegister, class CTexture* pTexture, int iContainer = 0, int iSubset = 0);
	void SetRenderState(const string& strName);
	void ClearTexture(int iContainer = 0, int iSubset = 0);
	void SetInstancingShader(const string& strName);
	void SetInstancingLayout(const string& strName);
	IMAGE_TYPE GetImageType(int iContainer = 0, int iSubset = 0);
	void EnablePaperBurn(bool bEnable);


private:
	void SetSubsetTexture(PMaterialSubset pSubset, int iRegister, const string& strName, bool bArrayTex);
	PCBufferNode FindCBufferNode(const string& strName);

public:
	bool Init();
	void Update(float fTime);
	void SetMaterial(size_t iContainer, size_t iSubset);
	void SetMaterialInstancing(size_t iContainer, size_t iSubset);
	void ResetState();
};

