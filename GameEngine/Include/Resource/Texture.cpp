#include "Texture.h"
#include "../PathManager.h"
#include "../Device.h"

CTexture::CTexture()	:
	m_pSRV(nullptr),
	m_eType(IT_ATLAS)
{
}

CTexture::~CTexture()
{
	SAFE_DELETE_NORMAL_VECLIST(m_vecImage);
	SAFE_RELEASE(m_pSRV);
}

unsigned int CTexture::GetWidth() const
{
	return m_iWidth;
}

unsigned int CTexture::GetHeight() const
{
	return m_iHeight;
}

IMAGE_TYPE CTexture::GetImageType() const
{
	return m_eType;
}

bool CTexture::LoadTexture(const string & strName, const TCHAR * pFileName,
	const string & strPathName)
{
	const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathName);

	TCHAR	strFullPath[MAX_PATH] = {};

	if (pPath)
		lstrcpy(strFullPath, pPath);

	lstrcat(strFullPath, pFileName);

	return LoadTextureFullPath(strName, strFullPath);
}

bool CTexture::LoadTextureFullPath(const string & strName, const TCHAR * pFullPath)
{
	SetName(strName);

	ScratchImage*	pImage = new ScratchImage;

	// 경로에서 확장자를 얻어온다.
	TCHAR	strExt[_MAX_EXT] = {};

	_wsplitpath_s(pFullPath, nullptr, 0, nullptr, 0, nullptr, 0, strExt, _MAX_EXT);

	char	_strExt[_MAX_EXT] = {};
	
	WideCharToMultiByte(CP_ACP, 0, strExt, -1, _strExt,
		lstrlen(strExt), nullptr, nullptr);
	
	_strupr_s(_strExt);

	if (strcmp(_strExt, ".DDS") == 0)
	{
		if (FAILED(LoadFromDDSFile(pFullPath, DDS_FLAGS_NONE, nullptr, *pImage)))
			return false;
	}

	else if (strcmp(_strExt, ".TGA") == 0)
	{
		if (FAILED(LoadFromTGAFile(pFullPath, nullptr, *pImage)))
			return false;
	}

	else
	{
		if (FAILED(LoadFromWICFile(pFullPath, WIC_FLAGS_NONE, nullptr, *pImage)))
			return false;
	}

	m_vecImage.push_back(pImage);

	return CreateResource();
}

bool CTexture::LoadTexture(const string & strName, const vector<const TCHAR*>& vecFileName,
	const string & strPathName)
{
	const TCHAR* pPath = GET_SINGLE(CPathManager)->FindPath(strPathName);

	vector<const TCHAR*>	vecFullPath;
	vecFullPath.reserve(vecFileName.size());

	for (size_t i = 0; i < vecFileName.size(); ++i)
	{
		TCHAR*	pFullPath = new TCHAR[MAX_PATH];
		memset(pFullPath, 0, sizeof(TCHAR) * MAX_PATH);

		if (pPath)
			lstrcpy(pFullPath, pPath);
		lstrcat(pFullPath, vecFileName[i]);

		vecFullPath.push_back(pFullPath);
	}


	if (!LoadTextureFullPath(strName, vecFullPath))
	{
		for (size_t i = 0; i < vecFullPath.size(); ++i)
		{
			SAFE_DELETE_ARRAY(vecFullPath[i]);
		}

		return false;
	}

	for (size_t i = 0; i < vecFullPath.size(); ++i)
	{
		SAFE_DELETE_ARRAY(vecFullPath[i]);
	}

	return true;
}

bool CTexture::LoadTextureFullPath(const string & strName, const vector<const TCHAR*>& vecFullPath)
{
	SetName(strName);

	for (size_t i = 0; i < vecFullPath.size(); ++i)
	{
		ScratchImage*	pImage = new ScratchImage;

		// 경로에서 확장자를 얻어온다.
		TCHAR	strExt[_MAX_EXT] = {};

		_wsplitpath_s(vecFullPath[i], nullptr, 0, nullptr, 0, nullptr, 0, strExt, _MAX_EXT);

		char	_strExt[_MAX_EXT] = {};

		WideCharToMultiByte(CP_ACP, 0, strExt, -1, _strExt,
			lstrlen(strExt), nullptr, nullptr);

		_strupr_s(_strExt);

		if (strcmp(_strExt, ".DDS") == 0)
		{
			if (FAILED(LoadFromDDSFile(vecFullPath[i], DDS_FLAGS_NONE, nullptr, *pImage)))
			{
				SAFE_DELETE(pImage);
				return false;
			}
		}

		else if (strcmp(_strExt, ".TGA") == 0)
		{
			if (FAILED(LoadFromTGAFile(vecFullPath[i], nullptr, *pImage)))
			{
				SAFE_DELETE(pImage);
				return false;
			}
		}

		else
		{
			HRESULT hr = LoadFromWICFile(vecFullPath[i], WIC_FLAGS_NONE, nullptr, *pImage);
			if (FAILED(hr))
			{
				SAFE_DELETE(pImage);
				return false;
			}
		}

		m_vecImage.push_back(pImage);
	}

	return CreateResourceArray();
}

void CTexture::SetTexture(int iRegister, int iShaderType)
{
	if(iShaderType & CST_VERTEX)
		CONTEXT->VSSetShaderResources(iRegister, 1, &m_pSRV);

	if(iShaderType & CST_PIXEL)
		CONTEXT->PSSetShaderResources(iRegister, 1, &m_pSRV);
}

bool CTexture::CreateResource()
{
	if (FAILED(CreateShaderResourceView(DEVICE, m_vecImage[0]->GetImages(),
		m_vecImage[0]->GetImageCount(), m_vecImage[0]->GetMetadata(), &m_pSRV)))
		return false;

	m_iWidth = m_vecImage[0]->GetImages()[0].width;
	m_iHeight = m_vecImage[0]->GetImages()[0].height;

	return true;
}

bool CTexture::CreateResourceArray()
{
	ScratchImage*	pArrayImage = new ScratchImage;

	HRESULT result = pArrayImage->Initialize2D(m_vecImage[0]->GetMetadata().format,
		m_vecImage[0]->GetMetadata().width,
		m_vecImage[0]->GetMetadata().height,
		m_vecImage.size(),
		m_vecImage[0]->GetMetadata().mipLevels);

	int	iMipLevel = m_vecImage[0]->GetMetadata().mipLevels;

	// Array Texture의 픽셀정보를 불러온 텍스쳐의 픽셀정보로 채워준다.
	for (size_t i = 0; i < m_vecImage.size(); ++i)
	{
		const Image*	pImages = m_vecImage[i]->GetImages();

		// 각각의 텍스쳐들을 밉맵 수준만큼 반복한다.
		for (size_t mip = 0; mip < iMipLevel; ++mip)
		{
			const Image* pSrc = &pArrayImage->GetImages()[i * iMipLevel + mip];
			const Image* pDest = &pImages[mip];

			memcpy(pSrc->pixels, pDest->pixels, pSrc->slicePitch);
		}
	}

	ID3D11Texture2D*	pTexture = NULL;

	if (FAILED(DirectX::CreateTextureEx(DEVICE, pArrayImage->GetImages(),
		pArrayImage->GetImageCount(),
		pArrayImage->GetMetadata(),
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE,
		0, 0, FALSE,
		(ID3D11Resource**)&pTexture)))
	{
		assert(false);
		return false;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC	tViewDesc = {};
	tViewDesc.Format = m_vecImage[0]->GetMetadata().format;
	tViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	tViewDesc.Texture2DArray.MostDetailedMip = 0;
	tViewDesc.Texture2DArray.MipLevels = iMipLevel;
	tViewDesc.Texture2DArray.FirstArraySlice = 0;
	tViewDesc.Texture2DArray.ArraySize = m_vecImage.size();

	if (FAILED(DEVICE->CreateShaderResourceView(pTexture, &tViewDesc, &m_pSRV)))
	{
		assert(false);
		return false;
	}

	SAFE_DELETE(pArrayImage);

	SAFE_RELEASE(pTexture);

	return true;
}
