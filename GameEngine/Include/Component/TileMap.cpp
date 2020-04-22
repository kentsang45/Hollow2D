#include "TileMap.h"
#include "../Resource/StaticMesh.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/ShaderManager.h"
#include "../Resource/Shader.h"
#include "ColliderRect.h"
#include "../Object/GameObject.h"
#include "../Resource/BlendState.h"
#include "../Resource/Material.h"
#include "Tile.h"
#include "../Scene/Scene.h"
#include "../Scene/Navigation2D.h"
#include "../CameraManager.h"
#include "CameraComponent.h"
#include "../Device.h"
#include "Transform.h"
#include "../PathManager.h"

CTileMap::CTileMap()
{
	m_bTickUpdate = true;

	SetTypeID<CTileMap>();

	m_pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh("TexRect");
	m_pLayout = GET_SINGLE(CShaderManager)->FindInputLayout(POS_UV_LAYOUT);
	m_pAlphaBlend = nullptr;
	m_pMaterial = nullptr;
	m_pTileArray = nullptr;

	m_iTileCountX = 0;
	m_iTileCountY = 0;
	m_iTileCount = 0;
	m_eTileType = TT_NONE;

	m_bTileRender = false;
}

CTileMap::CTileMap(const CTileMap & com) :
	CSceneComponent(com)
{
	m_pMesh = com.m_pMesh;

	if (m_pMesh)
		m_pMesh->AddRef();

	m_pLayout = com.m_pLayout;

	if (m_pMaterial)
		m_pMaterial->AddRef();

	m_pAlphaBlend = nullptr;

	m_iTileCountX = com.m_iTileCountX;
	m_iTileCountY = com.m_iTileCountY;
	m_iTileCount = com.m_iTileCount;

	m_vSize = com.m_vSize;
	m_vTileSize = com.m_vTileSize;
	m_eTileType = com.m_eTileType;
	m_pTileArray = nullptr;

	m_bTileRender = com.m_bTileRender;
}

CTileMap::~CTileMap()
{
	SAFE_RELEASE(m_pInstancingBuffer->pBuffer);
	SAFE_DELETE(m_pInstancingBuffer);
	SAFE_DELETE_ARRAY(m_pInstancingData);

	if (m_iTileCount != 0)
	{
		for (unsigned int i = 0; i < m_iTileCountY; ++i)
		{
			for (unsigned int j = 0; j < m_iTileCountX; ++j)
			{
				SAFE_DELETE(m_pTileArray[i * m_iTileCountX + j]);
			}
		}

		SAFE_DELETE_ARRAY(m_pTileArray);
	}

	SAFE_RELEASE(m_pMaterial);
	SAFE_RELEASE(m_pAlphaBlend);
	SAFE_RELEASE(m_pMesh);
}

int CTileMap::GetTileCountX() const
{
	return m_iTileCountX;
}

int CTileMap::GetTileCountY() const
{
	return m_iTileCountY;
}

int CTileMap::GetTileCount() const
{
	return m_iTileCount;
}

Vector3 CTileMap::GetTileSize() const
{
	return m_vTileSize;
}

TILE_TYPE CTileMap::GetTileType() const
{
	return m_eTileType;
}

void CTileMap::SetMesh(const string & strName)
{
	SAFE_RELEASE(m_pMesh);
	m_pMesh = (CStaticMesh*)GET_SINGLE(CResourceManager)->FindMesh(strName);
}

void CTileMap::SetInputLayout(const string & strName)
{
	m_pLayout = GET_SINGLE(CShaderManager)->FindInputLayout(strName);
}

void CTileMap::SetMaterial(const string & strName)
{
	CMaterial*	pMtrl = GET_SINGLE(CResourceManager)->FindMaterial(strName);

	if (pMtrl)
	{
		if (!m_pMaterial)
		{
			m_pMaterial = new CMaterial;

			m_pMaterial->Init();
		}
		m_pMaterial->CopyMaterial(pMtrl);

		m_pMaterial->SetMaterialShaderStyle(MSS_ENVIRONMENT);

		SAFE_RELEASE(pMtrl);
	}
}

void CTileMap::SetAlphaBlend()
{
	if (m_pAlphaBlend)
		return;

	m_pAlphaBlend = GET_SINGLE(CResourceManager)->FindRenderState(RENDERSTATE_ALPHABLEND);
}

void CTileMap::SetTileMesh(const string & strName)
{
	if (m_iTileCount == 0)
		return;

	for (unsigned int i = 0; i < m_iTileCount; ++i)
	{
		m_pTileArray[i]->SetMesh(strName);
	}
}

void CTileMap::SetTileInputLayout(const string & strName)
{
	if (m_iTileCount == 0)
		return;

	for (unsigned int i = 0; i < m_iTileCount; ++i)
	{
		m_pTileArray[i]->SetInputLayout(strName);
	}
}

void CTileMap::SetTileMaterial(const string & strName)
{
	if (m_iTileCount == 0)
		return;

	for (unsigned int i = 0; i < m_iTileCount; ++i)
	{
		m_pTileArray[i]->SetMaterial(strName);
	}

	m_bTileRender = true;
}

void CTileMap::SetTileAlphaBlend()
{
	if (m_iTileCount == 0)
		return;

	for (unsigned int i = 0; i < m_iTileCount; ++i)
	{
		m_pTileArray[i]->SetAlphaBlend();
	}
}

void CTileMap::CreateTile(TILE_TYPE eType, unsigned int iCountX, unsigned int iCountY,
	const Vector3 & vTileSize, const Vector3& vPos)
{
	if (m_iTileCount != 0)
	{
		for (unsigned int i = 0; i < m_iTileCountY; ++i)
		{
			for (unsigned int j = 0; j < m_iTileCountX; ++j)
			{
				SAFE_DELETE(m_pTileArray[i * m_iTileCountX + j]);
			}
		}

		SAFE_DELETE_ARRAY(m_pTileArray);
	}

	m_iTileCountX = iCountX;
	m_iTileCountY = iCountY;
	m_iTileCount = m_iTileCountX * m_iTileCountY;

	m_eTileType = eType;
	m_vTileSize = vTileSize;


	switch (eType)
	{
	case TT_RECT:
		CreateTileRect(vPos);
		break;
	case TT_ISOMETRIC:
		CreateTileIsometric(vPos);
		break;
	default:
		BOOM;
		break;
	}


	// 전체 타일 수만큼 인스턴싱 버퍼를 할당해준다.
	m_pInstancingBuffer = new InstancingBuffer;

	m_pInstancingBuffer->iSize = sizeof(TileMapInstancingData);
	m_pInstancingBuffer->iCount = m_iTileCount;
	m_pInstancingBuffer->eUsage = D3D11_USAGE_DYNAMIC;
	D3D11_BUFFER_DESC	tDesc = {};

	tDesc.Usage = D3D11_USAGE_DYNAMIC;
	tDesc.ByteWidth = m_pInstancingBuffer->iSize * m_pInstancingBuffer->iCount;
	tDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	DEVICE->CreateBuffer(&tDesc, nullptr, &m_pInstancingBuffer->pBuffer);

	m_pInstancingData = new TileMapInstancingData[m_iTileCount];

	((CNavigation2D*)m_pScene->GetNavigation(RM_2D))->SetTileMap(this);
}

void CTileMap::AddFrame(const Vector2 & vStart, const Vector2 & vEnd, const Vector2& vImgSize,
	IMAGE_TYPE eType)
{
	ImageFrame	tFrame = {};

	tFrame.vStart = vStart;
	tFrame.vEnd = vEnd;
	tFrame.vImageSize = vImgSize;
	tFrame.iImageType = eType;
	tFrame.iFrame = m_vecFrame.size();

	m_vecFrame.push_back(tFrame);

	if (m_vecFrame.size() == 1 && m_pTileArray)
	{
		for (unsigned int i = 0; i < m_iTileCount; ++i)
		{
			m_pTileArray[i]->SetFrame(tFrame);
		}
	}
}

CTile * CTileMap::GetTile(const Vector3 & vPos)
{
	int	iIndex = GetTileIndex(vPos);

	if (iIndex == -1)
		return nullptr;

	return m_pTileArray[iIndex];
}

CTile * CTileMap::GetTile(float x, float y)
{
	int	iIndex = GetTileIndex(x, y);

	if (x <= -1 || y <= -1 || x >= m_iTileCountX || y >= m_iTileCountY)
		return nullptr;

	return m_pTileArray[iIndex];
}

CTile * CTileMap::GetTileFromIndex(int x, int y)
{
	if (x == -1 || y == -1)
		return nullptr;

	return m_pTileArray[y * m_iTileCountX + x];
}

int CTileMap::GetTileIndex(const Vector3 & vPos)
{
	int	x = GetTileIndexX(vPos);
	int	y = GetTileIndexY(vPos);

	if (x == -1 || y == -1)
		return -1;

	return y * m_iTileCountX + x;
}

int CTileMap::GetTileIndex(float x, float y)
{
	int	iX = GetTileIndexX(Vector3(x, y, 0.f));
	int	iY = GetTileIndexY(Vector3(x, y, 0.f));

	if (iX == -1 || iY == -1)
		return -1;

	return iY * m_iTileCountX + iX;
}

int CTileMap::GetTileIndexX(const Vector3 & vPos)
{
	if (m_eTileType == TT_RECT)
	{
		float	fConvertX = vPos.x - m_pTransform->GetRelativePos().x;

		int	iX = (int)(fConvertX / m_vTileSize.x);

		if (iX < 0 || iX >= m_iTileCountX)
			return -1;

		return iX;
	}

	else if (m_eTileType == TT_ISOMETRIC)
	{
		int	iY = GetTileIndexY(vPos);

		if (iY < 0 || iY >= m_iTileCountY)
			return -1;

		int	iIndex = -1;

		if (iY % 2 == 0)
			iIndex = (int)vPos.x / (int)m_vTileSize.x;
		else
			iIndex = (int)(vPos.x - m_vTileSize.x / 2.f) / (int)m_vTileSize.x;

		if (iIndex < 0 || iIndex >= m_iTileCountX)
			return -1;

		return iIndex;
	}

	return -1;
}



int CTileMap::GetTileIndexY(const Vector3 & vPos)
{
	if (m_eTileType == TT_RECT)
	{
		float	fConvertY = vPos.y - m_pTransform->GetRelativePos().y;

		int	iY = (int)(fConvertY / m_vTileSize.y);

		if (iY < 0 || iY >= m_iTileCountY)
			return -1;

		return iY;
	}

	else if (m_eTileType == TT_ISOMETRIC)
	{
		// 타일  크기로  나누어서  1, 1 크기의  공간으로 변환한다.
		float	fX = vPos.x / m_vTileSize.x;
		float	fY = vPos.y / m_vTileSize.y;

		// 정수부분만 남겨둔다..
		int	idxX = (int)fX;
		int	idxY = (int)fY;

		if (idxX < 0 || idxX > m_iTileCountX)
			return -1;

		// 정수  부분을 제거한 실수부분만 남겨둔다..
		fX -= idxX;
		fY -= idxY;

		// 사각형의  아래쪽 부분일 경우
		if (fY < 0.5f)
		{
			// 우하단 사각형일 경우 fX는 0.5를 넘어가므로  fY는 0.5f - fX보다 절대  작을  수 없다. 음수가 나오기 때문이다.
			// 이경우는  좌 하단 사각형일 경우로  그중에서도 0.5에서 fX를  뺐을 경우 대각선 방향에  의해서 x와 y가 같은  값이
			// 나올  경우 대각선상에 존재한다는 것이다.
			// 그렇기 때문에 이 조건을 만족한다면  좌하단  사각형에서  좌하단 삼각형쪽을 의미한다.
			if (fY < 0.5f - fX)
			{
				if (idxX == 0)
					return -1;
				else if (idxY == 0)
					return -1;
				else if (idxY == 1)
					return 1;

				else
					return idxY * 2 - 1;
			}

			// 우하단 사각형일 경우 우하단  삼각형쪽을 체크해야  한다.
			// 이경우는  fX 에서 0.5를 뺄 경우  양수 값이  나오게  되고 대각선  특성상  이 값과 fY값이 같을 경우 대각선상에
			// 존재한다는  것이다.
			// 그렇기  때문에  이 조건을  만족한다면 우하단 사각형에서 우하단 삼각형을 의미한다.
			else if (fY < fX - 0.5f)
			{
				if (idxY == 0)
					return -1;

				else if (idxY == 1)
					return 1;

				else
					return idxY * 2 - 1;
			}

			else
				return idxY * 2;
		}

		// 사각형의 위쪽 부분일 경우
		else if (fY > 0.5f)
		{
			// 좌상단 사각형일 경우 좌상단 삼각형 영역일때 처리
			if (fY - 0.5f > fX)
			{
				if (idxX == 0)
					return -1;

				int	iIndex = idxY * 2 + 1;

				if (iIndex >= m_iTileCountY)
					return -1;

				return iIndex;
			}
			// 우상단 사각형일 경우 우상단  삼각형 영역일때 처리
			else if (fY - 0.5f > 1.f - fX)
			{
				if (idxX == m_iTileCountX)
					return -1;

				int	iIndex = idxY * 2 + 1;

				if (iIndex >= m_iTileCountY)
					return -1;

				return iIndex;
			}
			else
				return idxY * 2;
		}
		// 정 중앙일  경우
		else
			return idxY * 2;
	}


	return -1;
}


bool CTileMap::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CTileMap::Begin()
{
	CSceneComponent::Begin();
}

void CTileMap::Update(float fTime)
{
	CSceneComponent::Update(fTime);
}

void CTileMap::PostUpdate(float fTime)
{
	CSceneComponent::PostUpdate(fTime);

	if (m_bTileRender)
	{
		m_iRenderCount = 0;

		CCameraComponent*	pCamera = m_pScene->GetCameraManager()->GetMainCamera();

		Vector3	vCameraPos = pCamera->GetWorldPos() - GetWorldPos();
		Vector3	vCameraEndPos = vCameraPos + Vector3(_RESOLUTION.iWidth, _RESOLUTION.iHeight, 0.f);

		switch (m_eTileType)
		{
		case TT_RECT:
			m_iStartX = (int)(vCameraPos.x / m_vTileSize.x);
			m_iStartY = (int)(vCameraPos.y / m_vTileSize.y);
			m_iEndX = (int)(vCameraEndPos.x / m_vTileSize.x);
			m_iEndY = (int)(vCameraEndPos.y / m_vTileSize.y);
			break;
		case TT_ISOMETRIC:
			m_iStartX = GetTileIndexX(vCameraPos) - 1;
			m_iStartY = GetTileIndexY(vCameraPos) - 1;
			m_iEndX = GetTileIndexX(vCameraEndPos) + 1;
			m_iEndY = GetTileIndexY(vCameraEndPos) + 1;
			break;
		}


		m_iStartX = (int)(vCameraPos.x / m_vTileSize.x);
		m_iStartY = (int)(vCameraPos.y / m_vTileSize.y);
		m_iEndX = (int)(vCameraEndPos.x / m_vTileSize.x);
		m_iEndY = (int)(vCameraEndPos.y / m_vTileSize.y);

		m_iStartX = m_iStartX < 0 ? 0 : m_iStartX;
		m_iStartY = m_iStartY < 0 ? 0 : m_iStartY;

		m_iEndX = m_iEndX >= m_iTileCountX ? m_iTileCountX - 1 : m_iEndX;
		m_iEndY = m_iEndY >= m_iTileCountY ? m_iTileCountY - 1 : m_iEndY;

		for (int i = m_iStartY; i <= m_iEndY; ++i)
		{
			for (int j = m_iStartX; j <= m_iEndX; ++j)
			{
				m_pTileArray[i * m_iTileCountX + j]->PostUpdate(fTime);
				m_pTileArray[i * m_iTileCountX + j]->SetInstancingData(&m_pInstancingData[m_iRenderCount]);
				++m_iRenderCount;
			}
		}

		D3D11_MAPPED_SUBRESOURCE	tMap = {};
		CONTEXT->Map(m_pInstancingBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tMap);

		memcpy(tMap.pData, m_pInstancingData, sizeof(TileMapInstancingData) * m_iRenderCount);

		CONTEXT->Unmap(m_pInstancingBuffer->pBuffer, 0);

		m_pInstancingBuffer->iCount = m_iRenderCount;
	}
}

void CTileMap::Render(float fTime)
{
	CSceneComponent::Render(fTime);

	if (m_pMaterial)
	{
		if (m_pAlphaBlend)
			m_pAlphaBlend->SetState();

		size_t	iContainer = m_pMesh->GetContainerCount();

		for (size_t i = 0; i < iContainer; ++i)
		{
			size_t	iSubset = m_pMesh->GetSubsetCount(i);

			for (size_t j = 0; j < iSubset; ++j)
			{
				m_pMaterial->SetMaterial(i, j);
				m_pMesh->Render(i, j);

				m_pMaterial->ResetState();
			}
		}

		if (m_pAlphaBlend)
			m_pAlphaBlend->ResetState();
	}

	if (m_bTileRender)
	{
		m_pTileArray[0]->RenderInstancing(fTime, m_pInstancingBuffer);
		/*for (int i = m_iStartY; i <= m_iEndY; ++i)
		{
			for (int j = m_iStartX; j <= m_iEndX; ++j)
			{
				m_pTileArray[i * m_iTileCountX + j]->Render(fTime);
			}
		}*/
	}
}


void CTileMap::Save(const char * pFullPath)
{
	FILE*	pFile = nullptr;

	fopen_s(&pFile, pFullPath, "wb");

	if (pFile)
	{
		fwrite(&m_iTileCountX, sizeof(unsigned int), 1, pFile);
		fwrite(&m_iTileCountY, sizeof(unsigned int), 1, pFile);
		fwrite(&m_iTileCount, sizeof(unsigned int), 1, pFile);
		fwrite(&m_vSize, sizeof(Vector3), 1, pFile);
		fwrite(&m_vTileSize, sizeof(Vector3), 1, pFile);
		fwrite(&m_eTileType, sizeof(TILE_TYPE), 1, pFile);
		fwrite(&m_bTileRender, sizeof(bool), 1, pFile);

		int	iCount = (int)m_vecFrame.size();
		fwrite(&iCount, sizeof(int), 1, pFile);
		fwrite(&m_vecFrame[0], sizeof(ImageFrame), iCount, pFile);

		fwrite(&m_iRenderCount, sizeof(int), 1, pFile);

		for (unsigned int i = 0; i < m_iTileCount; ++i)
		{
			m_pTileArray[i]->Save(pFile);
		}

		fclose(pFile);
	}
}

void CTileMap::Load(const char * pFullPath)
{
	FILE*	pFile = nullptr;

	fopen_s(&pFile, pFullPath, "rb");

	if (pFile)
	{
		m_vecFrame.clear();

		for (unsigned int i = 0; i < m_iTileCount; ++i)
		{
			SAFE_DELETE(m_pTileArray[i]);
		}
		SAFE_DELETE_ARRAY(m_pTileArray);

		fread(&m_iTileCountX, sizeof(unsigned int), 1, pFile);
		fread(&m_iTileCountY, sizeof(unsigned int), 1, pFile);
		fread(&m_iTileCount, sizeof(unsigned int), 1, pFile);
		fread(&m_vSize, sizeof(Vector3), 1, pFile);
		fread(&m_vTileSize, sizeof(Vector3), 1, pFile);
		fread(&m_eTileType, sizeof(TILE_TYPE), 1, pFile);
		fread(&m_bTileRender, sizeof(bool), 1, pFile);

		int	iCount = 0;
		fread(&iCount, sizeof(int), 1, pFile);

		m_vecFrame.resize(iCount);
		fread(&m_vecFrame[0], sizeof(ImageFrame), iCount, pFile);

		fread(&m_iRenderCount, sizeof(int), 1, pFile);

		m_pTileArray = new CTile*[m_iTileCount];

		for (unsigned int i = 0; i < m_iTileCount; ++i)
		{
			m_pTileArray[i] = new CTile;
			m_pTileArray[i]->Load(pFile);
		}

		// 전체 타일 수만큼 인스턴싱 버퍼를 할당해준다.
		m_pInstancingBuffer = new InstancingBuffer;

		m_pInstancingBuffer->iSize = sizeof(TileMapInstancingData);
		m_pInstancingBuffer->iCount = m_iTileCount;
		m_pInstancingBuffer->eUsage = D3D11_USAGE_DYNAMIC;
		D3D11_BUFFER_DESC	tDesc = {};

		tDesc.Usage = D3D11_USAGE_DYNAMIC;
		tDesc.ByteWidth = m_pInstancingBuffer->iSize * m_pInstancingBuffer->iCount;
		tDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		tDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		DEVICE->CreateBuffer(&tDesc, nullptr, &m_pInstancingBuffer->pBuffer);

		m_pInstancingData = new TileMapInstancingData[m_iTileCount];

		((CNavigation2D*)m_pScene->GetNavigation(RM_2D))->SetTileMap(this);

		SetWorldScale(m_vSize.x, m_vSize.y, 1.f);

		fclose(pFile);
	}
}

void CTileMap::LoadPath(const char * pFileName, const string & strPathName)
{
	const char* pPath = GET_SINGLE(CPathManager)->FindPathMultibyte(strPathName);

	char	strFullPath[MAX_PATH] = {};

	if (pPath)
		strcpy_s(strFullPath, pPath);

	strcat_s(strFullPath, pFileName);

	Load(strFullPath);
}




void CTileMap::CreateTileRect(const Vector3 & vPos)
{
	m_vSize = m_vTileSize * Vector3((float)m_iTileCountX, (float)m_iTileCountY, 0.f);

	SetWorldScale(m_vSize.x, m_vSize.y, 1.f);

	SetRelativePos(vPos);

	m_pTileArray = new CTile*[m_iTileCount];

	for (unsigned int i = 0; i < m_iTileCountY; ++i)
	{
		for (unsigned int j = 0; j < m_iTileCountX; ++j)
		{
			int	iIndex = i * m_iTileCountX + j;

			m_pTileArray[iIndex] = new CTile;

			m_pTileArray[iIndex]->m_eType = m_eTileType;
			m_pTileArray[iIndex]->m_eOption = TO_NONE;
			m_pTileArray[iIndex]->m_vPos = vPos + Vector3(j * m_vTileSize.x, i * m_vTileSize.y, 0.f);
			m_pTileArray[iIndex]->m_vSize = m_vTileSize;
			m_pTileArray[iIndex]->m_vCenter = (m_pTileArray[iIndex]->m_vPos + m_pTileArray[iIndex]->m_vPos + m_pTileArray[iIndex]->m_vSize) / 2.f;

			m_pTileArray[iIndex]->m_iIndexX = j;
			m_pTileArray[iIndex]->m_iIndexY = i;
			m_pTileArray[iIndex]->m_iIndex = iIndex;

			if (!m_vecFrame.empty())
			{
				m_pTileArray[iIndex]->SetFrame(m_vecFrame[0]);
			}
		}
	}
}

void CTileMap::CreateTileIsometric(const Vector3 & vPos)
{
	m_vSize = m_vTileSize * Vector3((float)m_iTileCountX, (m_iTileCountY + 1) / 2.f, 0.f);

	SetWorldScale(m_vSize.x, m_vSize.y, 1.f);

	SetRelativePos(vPos);

	m_pTileArray = new CTile*[m_iTileCount];

	for (unsigned int i = 0; i < m_iTileCountY; ++i)
	{
		for (unsigned int j = 0; j < m_iTileCountX; ++j)
		{
			int	iIndex = i * m_iTileCountX + j;

			m_pTileArray[iIndex] = new CTile;

			m_pTileArray[iIndex]->m_eType = m_eTileType;
			m_pTileArray[iIndex]->m_eOption = TO_NONE;
			m_pTileArray[iIndex]->m_vPos = vPos + Vector3(j * m_vTileSize.x, i * m_vTileSize.y / 2.f, 0.f);

			if (i % 2 == 1)
				m_pTileArray[iIndex]->m_vPos.x += m_vTileSize.x / 2.f;

			m_pTileArray[iIndex]->m_vSize = m_vTileSize;
			m_pTileArray[iIndex]->m_iIndexX = j;
			m_pTileArray[iIndex]->m_iIndexY = i;
			m_pTileArray[iIndex]->m_iIndex = iIndex;

			if (!m_vecFrame.empty())
			{
				m_pTileArray[iIndex]->SetFrame(m_vecFrame[3]);
			}
		}
	}
}

