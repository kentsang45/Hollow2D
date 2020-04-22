#include "Material.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "RenderState.h"
#include "../Device.h"

_tagTextureInfo::_tagTextureInfo()
{
	pTexture = nullptr;
	iRegister = 0;
	bArrayTex = false;
}

_tagTextureInfo::~_tagTextureInfo()
{
	SAFE_RELEASE(pTexture);
}

_tagMaterialSubset::_tagMaterialSubset() :
	vDiffuse(Vector4::White),
	pShader(nullptr)
{
}

_tagMaterialSubset::~_tagMaterialSubset()
{
	SAFE_DELETE_NORMAL_VECLIST(vecTexture);
	SAFE_RELEASE(pShader);
}

_tagMaterialContainer::_tagMaterialContainer()
{
}

_tagMaterialContainer::~_tagMaterialContainer()
{
	SAFE_DELETE_NORMAL_VECLIST(vecSubset);
}

CMaterial::CMaterial()
{
	m_pDefaultShader = GET_SINGLE(CShaderManager)->FindShader(STANDARD_COLOR_SHADER);

	SetContainer(1);

	SetSubset(0, 1);

	memset(m_pRenderState, 0, sizeof(CRenderState*) * RST_END);

	m_eMaterialShaderStyle	= MSS_DEFAULT;

	m_bEnableInstancing	= false;

	m_pInstancingShader	= GET_SINGLE(CShaderManager)->FindShader(STANDARD_STATIC_INSTANCING_SHADER);
	m_pInstancingLayout	= GET_SINGLE(CShaderManager)->FindInputLayout(STATIC_INSTANCING_LAYOUT);

	m_tCBuffer.bPaperBurn = false;
}

CMaterial::~CMaterial()
{
	for (int i = 0; i < RST_END; ++i)
	{
		SAFE_RELEASE(m_pRenderState[i]);
	}

	SAFE_DELETE_NORMAL_VECLIST(m_vecContainer);
	SAFE_RELEASE(m_pDefaultShader);
	SAFE_RELEASE(m_pInstancingShader);

	auto	iter1 = m_mapCBuffer.begin();
	auto	iter1End = m_mapCBuffer.end();

	for (; iter1 != iter1End; ++iter1)
	{
		SAFE_DELETE_ARRAY(iter1->second->pBuffer);
	}

	SAFE_DELETE_NORMAL_MAP(m_mapCBuffer);
}

MATERIAL_SHADER_STYLE CMaterial::GetMaterialShaderStyle() const
{
	return m_eMaterialShaderStyle;
}

void CMaterial::SetSerialNumber(const string & strName)
{
	hash<string>	h;
	m_iSerialNumber = h(strName);
}

size_t CMaterial::GetSerialNumber() const
{
	return m_iSerialNumber;
}

void CMaterial::EnableInstancing()
{
	m_bEnableInstancing	= true;
}

bool CMaterial::IsEnableInstancing() const
{
	return m_bEnableInstancing;
}

Vector4 CMaterial::GetDiffuse(int iContainer, int iSubset) const
{
	return m_vecContainer[iContainer]->vecSubset[iSubset]->vDiffuse;
}

size_t CMaterial::GetContainerCount() const
{
	return m_vecContainer.size();
}

size_t CMaterial::GetSubsetCount(int iIndex) const
{
	return m_vecContainer[iIndex]->vecSubset.size();
}

bool CMaterial::CreateCBufferNode(const string & strName, int iRegister, int iSize)
{
	PCBufferNode	pBuffer = FindCBufferNode(strName);

	if(pBuffer)
		return false;

	pBuffer = new CBufferNode;

	pBuffer->strName	= strName;
	pBuffer->iRegister	= iRegister;
	pBuffer->iSize	= iSize;
	pBuffer->pBuffer	= new char[iSize];

	hash<string>	h;
	size_t iKey = h(strName);

	m_mapCBuffer.insert(make_pair(iKey, pBuffer));

	return true;
}

bool CMaterial::UpdateCBufferNode(const string & strName, void * pData)
{
	PCBufferNode	pBuffer = FindCBufferNode(strName);

	if (!pBuffer)
		return false;

	memcpy(pBuffer->pBuffer, pData, pBuffer->iSize);

	return true;
}

void CMaterial::SetMaterialShaderStyle(MATERIAL_SHADER_STYLE eStyle)
{
	m_eMaterialShaderStyle	= eStyle;
}

void CMaterial::SetContainer(size_t iContainerCount)
{
	SAFE_DELETE_NORMAL_VECLIST(m_vecContainer);

	m_vecContainer.resize(iContainerCount);

	for (size_t i = 0; i < iContainerCount; ++i)
	{
		m_vecContainer[i] = new MaterialContainer;
	}
}

void CMaterial::SetSubset(size_t iContainer, size_t iSubsetCount)
{
	SAFE_DELETE_NORMAL_VECLIST(m_vecContainer[iContainer]->vecSubset);

	m_vecContainer[iContainer]->vecSubset.resize(iSubsetCount);

	for (size_t i = 0; i < iSubsetCount; ++i)
	{
		m_vecContainer[iContainer]->vecSubset[i] = new MaterialSubset;
	}
}

void CMaterial::SetDefaultShader(const string & strName)
{
	SAFE_RELEASE(m_pDefaultShader);

	m_pDefaultShader = GET_SINGLE(CShaderManager)->FindShader(strName);
}

void CMaterial::SetSubsetShader(const string & strName, size_t iContainer,
	size_t iSubset)
{
	PMaterialSubset pSubset = m_vecContainer[iContainer]->vecSubset[iSubset];

	SAFE_RELEASE(pSubset->pShader);

	pSubset->pShader = GET_SINGLE(CShaderManager)->FindShader(strName);
}

void CMaterial::SetSubsetDiffuse(const Vector4 & vColor, size_t iContainer,
	size_t iSubset)
{
	m_vecContainer[iContainer]->vecSubset[iSubset]->vDiffuse = vColor;
}

void CMaterial::CopyMaterial(CMaterial * pMaterial)
{
	SAFE_RELEASE(m_pDefaultShader);

	m_pDefaultShader = pMaterial->m_pDefaultShader;

	m_pDefaultShader->AddRef();

	SAFE_DELETE_NORMAL_VECLIST(m_vecContainer);

	size_t	iContainer = pMaterial->m_vecContainer.size();
	for (size_t i = 0; i < iContainer; ++i)
	{
		PMaterialContainer	pContainer = pMaterial->m_vecContainer[i];

		PMaterialContainer	pNewContainer = new MaterialContainer;

		size_t	iSubset = pContainer->vecSubset.size();

		for (size_t j = 0; j < iSubset; ++j)
		{
			PMaterialSubset	pSubset = new MaterialSubset;

			pSubset->pShader = pContainer->vecSubset[j]->pShader;

			if (pSubset->pShader)
				pSubset->pShader->AddRef();

			pSubset->vDiffuse = pContainer->vecSubset[j]->vDiffuse;

			for (size_t k = 0; k < pContainer->vecSubset[j]->vecTexture.size(); ++k)
			{
				PTextureInfo	pTexInfo = new TextureInfo;
				*pTexInfo = *pContainer->vecSubset[j]->vecTexture[k];

				if (pTexInfo->pTexture)
					pTexInfo->pTexture->AddRef();

				pSubset->vecTexture.push_back(pTexInfo);
			}

			pNewContainer->vecSubset.push_back(pSubset);
		}

		m_vecContainer.push_back(pNewContainer);
	}

	for (int i = 0; i < RST_END; ++i)
	{
		m_pRenderState[i] = pMaterial->m_pRenderState[i];

		if(m_pRenderState[i])
			m_pRenderState[i]->AddRef();
	}

	auto	iter1	= m_mapCBuffer.begin();
	auto	iter1End = m_mapCBuffer.end();

	for (; iter1 != iter1End; ++iter1)
	{
		SAFE_DELETE_ARRAY(iter1->second->pBuffer);
	}

	SAFE_DELETE_NORMAL_MAP(m_mapCBuffer);

	auto	iter = pMaterial->m_mapCBuffer.begin();
	auto	iterEnd = pMaterial->m_mapCBuffer.end();

	for (; iter != iterEnd; ++iter)
	{
		PCBufferNode	pBuffer = new CBufferNode;

		*pBuffer = *iter->second;

		pBuffer->pBuffer	= new char[pBuffer->iSize];

		hash<string>	h;
		size_t iKey = h(pBuffer->strName);

		m_mapCBuffer.insert(make_pair(iKey, pBuffer));
	}

	m_iSerialNumber	= pMaterial->m_iSerialNumber;
	m_bEnableInstancing	= pMaterial->m_bEnableInstancing;

	SAFE_RELEASE(m_pInstancingShader);
	m_pInstancingShader = pMaterial->m_pInstancingShader;
	m_pInstancingLayout = pMaterial->m_pInstancingLayout;

	if(m_pInstancingShader)
		m_pInstancingShader->AddRef();

	m_strName = pMaterial->GetName();

	m_tCBuffer = pMaterial->m_tCBuffer;
}

bool CMaterial::SetTexture(int iRegister, const string & strName, int iContainer, int iSubset)
{
	if (iContainer >= m_vecContainer.size())
		return false;

	else if (iSubset >= m_vecContainer[iContainer]->vecSubset.size())
		return false;

	PMaterialSubset	pSubset = m_vecContainer[iContainer]->vecSubset[iSubset];

	SetSubsetTexture(pSubset, iRegister, strName, true);
	
	return true;
}

bool CMaterial::SetTexture(int iRegister, const string & strName, const TCHAR * pFileName,
	const string & strPathName, int iContainer, int iSubset)
{
	if (iContainer >= m_vecContainer.size())
		return false;

	else if (iSubset >= m_vecContainer[iContainer]->vecSubset.size())
		return false;

	PMaterialSubset	pSubset = m_vecContainer[iContainer]->vecSubset[iSubset];

	if (!GET_SINGLE(CResourceManager)->LoadTexture(strName, pFileName, strPathName))
		return false;

	SetSubsetTexture(pSubset, iRegister, strName, true);

	return true;
}

bool CMaterial::SetTextureFromFullPath(int iRegister, const string & strName, 
	const TCHAR * pFullPath, int iContainer, int iSubset)
{
	if (iContainer >= m_vecContainer.size())
		return false;

	else if (iSubset >= m_vecContainer[iContainer]->vecSubset.size())
		return false;

	PMaterialSubset	pSubset = m_vecContainer[iContainer]->vecSubset[iSubset];

	if (!GET_SINGLE(CResourceManager)->LoadTextureFullPath(strName, pFullPath))
		return false;

	SetSubsetTexture(pSubset, iRegister, strName, true);

	return true;
}

bool CMaterial::SetTexture(int iRegister, const string & strName, 
	const vector<const TCHAR*>& vecFileName, const string & strPathName, int iContainer, 
	int iSubset)
{
	if (iContainer >= m_vecContainer.size())
		return false;

	else if (iSubset >= m_vecContainer[iContainer]->vecSubset.size())
		return false;

	PMaterialSubset	pSubset = m_vecContainer[iContainer]->vecSubset[iSubset];

	if (!GET_SINGLE(CResourceManager)->LoadTexture(strName, vecFileName, strPathName))
		return false;

	SetSubsetTexture(pSubset, iRegister, strName, true);

	return true;
}

bool CMaterial::SetTextureFromFullPath(int iRegister, const string & strName, 
	const vector<const TCHAR*>& vecFullPath, int iContainer, int iSubset)
{
	if (iContainer >= m_vecContainer.size())
		return false;

	else if (iSubset >= m_vecContainer[iContainer]->vecSubset.size())
		return false;

	PMaterialSubset	pSubset = m_vecContainer[iContainer]->vecSubset[iSubset];

	if (!GET_SINGLE(CResourceManager)->LoadTextureFullPath(strName, vecFullPath))
		return false;

	SetSubsetTexture(pSubset, iRegister, strName, true);

	return true;
}

bool CMaterial::SetTexture(int iRegister, CTexture * pTexture, int iContainer, int iSubset)
{
	if (iContainer >= m_vecContainer.size())
		return false;

	else if (iSubset >= m_vecContainer[iContainer]->vecSubset.size())
		return false;

	PMaterialSubset	pSubset = m_vecContainer[iContainer]->vecSubset[iSubset];

	size_t iSize = pSubset->vecTexture.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		if (pSubset->vecTexture[i]->iRegister == iRegister)
		{
			SAFE_RELEASE(pSubset->vecTexture[i]->pTexture);
			pSubset->vecTexture[i]->pTexture = pTexture;

			if (pTexture)
				pTexture->AddRef();
			return true;
		}
	}

	PTextureInfo	pTexInfo = new TextureInfo;
	pTexInfo->iRegister = iRegister;
	pTexInfo->pTexture = pTexture;

	if (pTexture)
		pTexture->AddRef();

	pSubset->vecTexture.push_back(pTexInfo);

	return true;
}

void CMaterial::SetRenderState(const string & strName)
{
	CRenderState* pState = GET_SINGLE(CResourceManager)->FindRenderState(strName);

	if (nullptr == pState)
	{
		return;
	}

	RENDER_STATE_TYPE eType = pState->GetRenderStateType();
	SAFE_RELEASE(m_pRenderState[eType]);
	m_pRenderState[eType] = pState;
}

void CMaterial::ClearTexture(int iContainer, int iSubset)
{
	if(iContainer >= m_vecContainer.size())
		return;

	else if (iSubset >= m_vecContainer[iContainer]->vecSubset.size())
		return;

	PMaterialSubset	pSubset = m_vecContainer[iContainer]->vecSubset[iSubset];

	SAFE_DELETE_NORMAL_VECLIST(pSubset->vecTexture);
}

void CMaterial::SetInstancingShader(const string & strName)
{
	SAFE_RELEASE(m_pInstancingShader);
	m_pInstancingShader = GET_SINGLE(CShaderManager)->FindShader(strName);
}

void CMaterial::SetInstancingLayout(const string & strName)
{
	m_pInstancingLayout = GET_SINGLE(CShaderManager)->FindInputLayout(strName);
}

IMAGE_TYPE CMaterial::GetImageType(int iContainer, int iSubset)
{
	return m_vecContainer[iContainer]->vecSubset[iSubset]->vecTexture[0]->bArrayTex ? IT_ARRAY : IT_ATLAS;
}

void CMaterial::EnablePaperBurn(bool bEnable)
{
	m_tCBuffer.bPaperBurn = bEnable;
}

void CMaterial::SetSubsetTexture(PMaterialSubset pSubset, int iRegister, const string& strName, bool bArrayTex)
{
	size_t iSize = pSubset->vecTexture.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		if (pSubset->vecTexture[i]->iRegister == iRegister)
		{
			SAFE_RELEASE(pSubset->vecTexture[i]->pTexture);
			pSubset->vecTexture[i]->pTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);
			pSubset->vecTexture[i]->bArrayTex = bArrayTex;
			return;
		}
	}

	PTextureInfo	pTexInfo = new TextureInfo;
	pTexInfo->iRegister = iRegister;
	pTexInfo->pTexture = GET_SINGLE(CResourceManager)->FindTexture(strName);
	pTexInfo->bArrayTex = bArrayTex;

	pSubset->vecTexture.push_back(pTexInfo);
}

PCBufferNode CMaterial::FindCBufferNode(const string & strName)
{
	hash<string>	h;

	size_t	iKey = h(strName);

	auto iter = m_mapCBuffer.find(iKey);

	if(iter == m_mapCBuffer.end())
		return nullptr;

	return iter->second;
}

bool CMaterial::Init()
{
	return true;
}

void CMaterial::Update(float fTime)
{
}

void CMaterial::SetMaterial(size_t iContainer, size_t iSubset)
{
	PMaterialSubset pSubset = nullptr;
	if (iContainer >= m_vecContainer.size())
	{
		pSubset = m_vecContainer[0]->vecSubset[0];
	}

	else if (iSubset >= m_vecContainer[iContainer]->vecSubset.size())
	{
		pSubset = m_vecContainer[0]->vecSubset[0];
	}

	else
		pSubset = m_vecContainer[iContainer]->vecSubset[iSubset];

	m_tCBuffer.vDif = pSubset->vDiffuse;

	GET_SINGLE(CShaderManager)->UpdateCBuffer(MATERIAL_CBUFFER, &m_tCBuffer);

	size_t	iSize = pSubset->vecTexture.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		pSubset->vecTexture[i]->pTexture->SetTexture(pSubset->vecTexture[i]->iRegister,
			CST_PIXEL);
	}

	if (pSubset->pShader)
		pSubset->pShader->SetShader();

	else
		m_pDefaultShader->SetShader();

	for (int i = 0; i < RST_END; ++i)
	{
		if (m_pRenderState[i])
			m_pRenderState[i]->SetState();
	}

	auto	iter = m_mapCBuffer.begin();
	auto	iterEnd = m_mapCBuffer.end();

	for (; iter != iterEnd; ++iter)
	{
		GET_SINGLE(CShaderManager)->UpdateCBuffer(iter->second->strName, iter->second->pBuffer);
	}
}

void CMaterial::SetMaterialInstancing(size_t iContainer, size_t iSubset)
{
	PMaterialSubset pSubset = nullptr;
	if (iContainer >= m_vecContainer.size())
	{
		pSubset = m_vecContainer[0]->vecSubset[0];
	}

	else if (iSubset >= m_vecContainer[iContainer]->vecSubset.size())
	{
		pSubset = m_vecContainer[0]->vecSubset[0];
	}

	else
		pSubset = m_vecContainer[iContainer]->vecSubset[iSubset];

	m_tCBuffer.vDif = pSubset->vDiffuse;

	GET_SINGLE(CShaderManager)->UpdateCBuffer(MATERIAL_CBUFFER, &m_tCBuffer);

	size_t	iSize = pSubset->vecTexture.size();
	for (size_t i = 0; i < iSize; ++i)
	{
		pSubset->vecTexture[i]->pTexture->SetTexture(pSubset->vecTexture[i]->iRegister,
			CST_PIXEL);
	}

	m_pInstancingShader->SetShader();

	CONTEXT->IASetInputLayout(m_pInstancingLayout);

	for (int i = 0; i < RST_END; ++i)
	{
		if (m_pRenderState[i])
			m_pRenderState[i]->SetState();
	}

	auto	iter = m_mapCBuffer.begin();
	auto	iterEnd = m_mapCBuffer.end();

	for (; iter != iterEnd; ++iter)
	{
		GET_SINGLE(CShaderManager)->UpdateCBuffer(iter->second->strName, iter->second->pBuffer);
	}
}

void CMaterial::ResetState()
{

	for (int i = 0; i < RST_END; ++i)
	{
		if (m_pRenderState[i])
			m_pRenderState[i]->ResetState();
	}
}
